//*******************************************************************************
//  File Name       : Flash.c
//  Device          : MC96F8316
//  Date            : 2012-08-03
//  Author	        : BJ Lim
//  Frequency	    : IRC 8.0 MHz
//  Compiler        : Keil uVision4
//******************************************************************************
#define      MyDef       extern                         //
#include	"Global.h"			                        //

#define APPLICATION_START	0x0000                      //
#define APPLICATION_END		0x37FF                      //
#define BACKUP_DATA_START	0x3800                      //2KB
#define BACKUP_DATA_END		0x3FFF                      //

#define BYTE_SECTOR		    32                          // 32B per sector
#define PAGE			    512                         // 512 page
#define MEMORY_SIZE		    0x3FFF                      // 16KB
#define DataFlash ((unsigned char volatile code *) 0)   //


//=============================================================================
//  task : Backup Information block write at Flash area
//      -Page data (32byte) load  from flash memory
//      -Page buffer (8byte) modify
//      -Page erase at flash memory
//      -Page write at flash memory
//=============================================================================
void DataFlash_Write(Byte index)
{
    Byte k,i;
    Word page_addr;
    
    page_addr = 0x3800 + index/4 * 32;          // �ش� Page�� ���� �ּ� ã�� (32byte����)
    i = (index % 4) * 8;                        // �ش� Page�� Data ���� �ּ� (8byte����)
    
    for(k=0;k<32;k++)
        Flash_Buf[k] = DataFlash[page_addr+k];  // �ش� Page 32byte�� ��� �о����
    for(k=0;k<8;k++)
    {   Flash_Buf[i] = Backup_Info[k];           // �ش� Page 32Byte �� backup �� 8�� data modify
        i++;
    }

	FMCR  = 0x01;                               // page erase 
    _nop_();                                    //
    _nop_();                                    //
    _nop_();                                    //
    DPTR0 = 0x8000;                             //
    for(k=0; k<32; k++)                         // move 32byte data to write buffer
	{	ACC = 0x00;		                        //
		#pragma asm
			movx  @DPTR,A                       ;
			inc   DPTR                          ;
		#pragma endasm
	}
	FSADRL = (Byte)(page_addr&0xff);            //
	FSADRM = (Byte)((page_addr>>8)&0xff);       //
	FSADRH = 0x00;                              //
  	FIDR   = 0xA5;                              //
  	FMCR   = 0x02;	                            // Start Erase
    _nop_();                                    //
    _nop_();                                    //
    _nop_();                                    //

	FMCR  = 0x01;                               // page write
    _nop_();                                    //
    _nop_();                                    //
    _nop_();                                    //
    DPTR0 = 0x8000;                             //
    DPTR1 = (Word)&Flash_Buf[0];                //
    for(k=0; k<32; k++)                         // move 32byte data to write buffer
	{
	    #pragma asm
		    mov   EO, #1                        ;DPTR1
		    movx  A,@DPTR                       ;
		    inc   DPTR                          ;
		    mov   EO, #0                        ;DPTR0, ���� ���û��°� DPTR0�� �ǵ��� �� ��!
			movx  @DPTR,A                       ;
			inc   DPTR                          ;
		#pragma endasm
	}
	FSADRL = (Byte)(page_addr&0xff);            //
	FSADRM = (Byte)((page_addr>>8)&0xff);       //
	FSADRH = 0x00;                              //
  	FIDR   = 0xA5;                              //
  	FMCR   = 0x03;	                            // Start write
    _nop_();                                    //
    _nop_();                                    //
    _nop_();                                    //
}
//=============================================================================
//      task    : 1 byte erase
//      input   : address (word)
//=============================================================================
/*
void DataFlsh_Byte_Erase(Word addr)
{
    Byte k;
    
    k = (Byte)(addr % 32);
    
	FMCR  = 0x01;                               // page erase 
    _nop_();                                    //
    _nop_();                                    //
    _nop_();                                    //
    DPTR0 = 0x8000+k;                           //
	ACC = 0x00;		                            //
#pragma asm
	movx  @DPTR,A                       ;
#pragma endasm
	FSADRL = (Byte)(addr&0xff);                 //
	FSADRM = (Byte)((addr>>8)&0xff);            //
	FSADRH = 0x00;                              //
  	FIDR   = 0xA5;                              //
  	FMCR   = 0x02;	                            // Start Erase
    _nop_();                                    //
    _nop_();                                    //
    _nop_();                                    //
}
*/
//=============================================================================
//      task    : 1 byte Write
//      input   : address (word)
//=============================================================================
void DataFlsh_Byte_Write(Word addr, Byte dt)
{
    Byte k;
    
    k = (Byte)(addr % 32);
    
    if(DataFlash[addr])     //---------------------------------------- �ش� ��ġ�� ���� 0�� �ƴ� ��� ����� 
    {	FMCR  = 0x01;                               // byte erase 
        _nop_();                                    //
        _nop_();                                    //
        _nop_();                                    //
        DPTR0 = 0x8000+k;                           //
    	ACC = 0x00;		                            //
#pragma asm
    	movx  @DPTR,A                       ;
#pragma endasm
    	FSADRL = (Byte)(addr&0xff);                 //
    	FSADRM = (Byte)((addr>>8)&0xff);            //
    	FSADRH = 0x00;                              //
      	FIDR   = 0xA5;                              //
      	FMCR   = 0x02;	                            // Start Erase
        _nop_();                                    //
        _nop_();                                    //
        _nop_();                                    //
    }
    //----------------------------------------------------------------- �ش� ��ġ�� ���� ��ֱ� 
    k = (Byte)(addr % 32);                      //
    FMCR  = 0x01;                               // page write
    _nop_();                                    //
    _nop_();                                    //
    _nop_();                                    //
    DPTR0 = 0x8000+k;                           //
    ACC = dt;		                            //
#pragma asm
    movx  @DPTR,A                       ;
#pragma endasm
    FSADRL = (Byte)(addr&0xff);                 //
    FSADRM = (Byte)((addr>>8)&0xff);            //
    FSADRH = 0x00;                              //
    FIDR   = 0xA5;                              //
    FMCR   = 0x03;	                            // Start write
    _nop_();                                    //
    _nop_();                                    //
    _nop_();                                    //
}
//=============================================================================
//      task    : Data Flash read
//      input   : Index
//      output  : Backup_Info[]
//=============================================================================
void DataFlash_Read(Byte index)
{
    Byte k;
    Word addr;
    
    addr = 0x3800 + index*8;
    for(k=0;k<8;k++)
    {   Backup_Info[k] = DataFlash[addr];
        addr++;
    }
}
//=============================================================================
