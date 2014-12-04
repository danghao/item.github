//==============================================================================
//	file name   : I2C.c
//==============================================================================

#define     MyDef       extern          //
#include	"Global.h"			        //

//==============================================================================
//     I2C SFR define
//==============================================================================
//      I2CCR           [0xE9]          // I2C Control1 Register
//      I2CSR           [0xEA]          // I2C State Register
//      I2CSAR0         [0xEB]          // I2C Self Address Register
//      I2CSAR1         [0xF1]          // I2C Self Address Register
//      I2CDR           [0xEC]          // I2C Data Register
//      I2CSDHR         [0xED]          // I2C SDA Hold Time Register
//      I2CSCLR         [0xEE]          // I2C SCL Low Period Register
//      I2CSCHR         [0xEF]          // I2C SCL High Period Register
//------------------------------------------------------------------------------
//      I2CCR           [0xE9]          // I2C Control Register
//------------------------------------------------------------------------------
#define     IICRST      (0x80)          // bit7 =1:I2C Register clear
#define     IICEN       (0x40)          // bit6 =1:I2C Function Block active
#define     TXDLYENB    (0x20)          // bit5 =1:disable I2CSDHR register
#define     IICIE       (0x10)          // bit4 =1:I2C Interrupt enable
#define     ACKEN       (0x08)          // bit3 =1:ACK generate at 9th clock
#define     IMASTER     (0x04)          // bit2 =1:Master ID [R]
#define     STOPC       (0x02)          // bit1 =1:Stop signal generation
#define     STARTC      (0x01)          // bit0 =1:Start signal generation
//------------------------------------------------------------------------------
//      I2CSR           [0xEA]          // I2C State
//------------------------------------------------------------------------------
#define     GCALL       (0x80)          // bit7 =1:General Call(Slave), Address Ack(master)
#define     TEND        (0x40)          // bit6 =1:1 byte transfered
#define     STOPD       (0x20)          // bit5 =1:Stop detected
#define     SSEL        (0x10)          // bit4 =1:Slave Address Matched
#define     MLOST       (0x08)          // bit3 =1:Arbiration Lost
#define     BUSY        (0x04)          // bit2 =1:Busy
#define     TMODE       (0x02)          // bit1 =1:Transmit mode
#define     RXACK       (0x01)          // bit0 =1:Acknowledge

//------------------------------------------------------------------------------
//    I2C Constant define by User
//------------------------------------------------------------------------------
#define     SELF_ADDRESS    (0x74)      //
#define     SLAVE_ADDRESS   (0xA0)      //
//==============================================================================
//    I2C interface format (similar to EEPROM 24C04)
//==============================================================================
//
//    Write :  SRT MAD SAD DATA0 DATA1 DATA2 DATA3 STP
//    Read  :  SRT MAD SAD RST MAD+1 DATA0 DATA1 DATA2 DATA3 STP
//
//          SRT : I2C Start signal
//          MAD : Slave Main Address (SLave Device Address)
//          SAD : Slave Sub address  (SLave Sub Register Address)
//          RST : Restart Signal
//          DATAn : n'th Data Byte
//          STP : Stop signal
//------------------------------------------------------------------------------
//  task	: I2C multi master initialize
//  input   : none
//  output  : none
//------------------------------------------------------------------------------
void I2C_Initialize(void)
{
    I2CCR     = IICEN+IICIE+ACKEN;      // 6=1:i2C block active, 4=1:enable, 3=1:ACK enable
    I2CSAR0   = SELF_ADDRESS;           // Self Address Register
    I2CSDHR   = 0x10;                   // SDA Hold Time Register
    I2CSCLR   = 0x10;                   // SCL Low Period Register
    I2CSCHR   = 0x10;                   // SCL High Period Register
    I2CSR     = 0x00;                   // State Register
    
//  IE1     |= 0x04;                    // IE1.2 interrupt enable
}
//------------------------------------------------------------------------------
//    task  : I2C Error
//    input : none
//    output: none
//------------------------------------------------------------------------------
void I2C_Error(void)
{
    I2CCR     = 0x00;                   // I2C block disable
    _nop_();                            //
    I2C_Initialize();                   //
}
//==============================================================================
//	task  : Multi Master I2C interrupt subroutine
//==============================================================================

void I2C_Int_Handler(void) interrupt 8  using 1
{
    if(I2CSR&(STOPD+MLOST))             // stop and arbtration lost
    {   I2C_Error();                    //
        return;                         //
    }
    
    if(I2CCR & IMASTER)                 //master mode
    {   if(I2CSR & TMODE)                       //master transmit ?
        {   if(I2CSR & RXACK)                           //RXACK  ack in?
            {   if(f_I2C_Read)                          //
                {   if(f_I2C_Sad)                       //
                    {   f_I2C_Sad = OFF;                //
                        I2CDR = rI2C_Sad;               // sub register address out
                    }
                    else
                    {   f_I2C_Read = OFF;               //
                        I2CDR  = SLAVE_ADDRESS+1;       // restart  read command out
                        I2CCR |= STARTC;                // 4=1:enable, 3=1:ACK enable, 0=1:start
                        wI2C_Post = &xI2C_Data[0];      //
                    }
                }
                else
                {   if(f_I2C_Sad)                       // write
                    {   f_I2C_Sad = OFF;                //
                        I2CDR = rI2C_Sad;               // sub register address out
                    }
                    else
                    {   rI2C_Byte--;                    // ACK ok
                        if(rI2C_Byte)                   //
                             I2CDR = *wI2C_Post++;      //
                        else I2CCR |= STOPC;            //STOP generation
                    }
                }
            }
            else  I2CCR |= STOPC;                       //STOP generation
        } 
        else                                    //master receive? 
        {   rI2C_Byte--;                                //last byte no ACK!
            if(rI2C_Byte)                               //
            {   if(rI2C_Byte==1)                        //
                    I2CCR &= ~ACKEN;                    //last byte read, no ACK!
                *wI2C_Post++ = I2CDR;                   //master receive
            }
            else  I2CCR |= STOPC;                       //STOP generation
        }
    }
    else                            //slave mode
    {   if(I2CSR & SSEL)                        //SSEL[4] address matchded?
        {   if(I2CSR & TMODE)                           //
            {   wI2C_Post = &xI2C_Data[0]+xI2C_Data[0]; //slave address match transmit
                I2CDR = *wI2C_Post++;                   //
            }
            else
            {   wI2C_Post = &xI2C_Data[0];              //slave address match receive
                f_Touch   = ON;                         //
            }
        }
        else
        {   if(I2CSR & TMODE)                   //slave transmit?
            {   if(I2CSR & RXACK)                       //
                    I2CDR   = *wI2C_Post++;             //
                else I2CCR |= STOPC;                    //
            }
            else 
            {   *wI2C_Post++ = I2CDR;          //slave receive
                if(f_Touch)
                {   f_Touch   = OFF;                    //
                    f_Key_Ok  = ON;                     //
                    rKey_Cmd  = xI2C_Data[0];           //
        //            rFND_Mode = KEY;                    //
                }
            }
        }
    }
    I2CSR = 0x00;                                       // next process start
}

//==============================================================================
//    task  :
//==============================================================================
//------------------------------------------------------------------------------
//    task  : I2C Data Transmit
//    input : rI2C_Slave, xI2C_Data[4], rI2C_Byte
//    output: f_Ack_Ok
//------------------------------------------------------------------------------
void Write_I2C(void)
{
    if(I2CSR & BUSY)                    //busy check!
        I2C_Error();                    //
    
    xI2C_Data[0] = 0x18;                //
    xI2C_Data[1] = 0x00;                //
    xI2C_Data[2] = 0x55;                //
    xI2C_Data[3] = 0xFF;                //
    
    rI2C_Byte = 5;                      //5 byte
    rI2C_Sad  = 0x33;                   //slave sub register address
    f_I2C_Sad = ON;                     //
    
    I2CCR     = IICEN+IICIE+ACKEN;      // 4=1:enable, 3=1:ACK enable
    wI2C_Post = &xI2C_Data[0];          //
    I2CDR     = SLAVE_ADDRESS;          //
    I2CCR    |= STARTC;                 // 0=1:start
}
//------------------------------------------------------------------------------
//    task  : I2C Data Read
//    input : rI2C_Slave, rI2C_Byte
//    output: rI2C_Buffer[4]
//------------------------------------------------------------------------------

void Read_I2C(void)
{
    if(I2CSR & BUSY)                    //busy check!
        I2C_Error();                    //
    
    rI2C_Byte = 5;                      //5 byte
    rI2C_Sad  = 3;                      //slave sub register address  &rI2C_Data[3]
    f_I2C_Sad = ON;                     //
    f_I2C_Read= ON;                     //
    
    I2CCR = IICEN+IICIE+ACKEN;          // 4=1:enable, 3=1:ACK enable
    wI2C_Post = &xI2C_Data[0];          //
    I2CDR   = SLAVE_ADDRESS;            //
    I2CCR  |= STARTC;                   // 0=1:start
}

//==============================================================================
//    task  : I2C Data Process
//    input :
//    output:
//==============================================================================
void Process_I2C(void)
{
//      f_I2C_RdWr = ~f_I2C_RdWr;   //

//      if(f_I2C_RdWr)              //
//#if MASTER
//            Write_I2C1();         // 4byte data write
//#endif
//      else
//            Read_I2C1();          // 10byte data read

}
//==============================================================================
