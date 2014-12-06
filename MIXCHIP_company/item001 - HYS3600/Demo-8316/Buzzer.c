//==============================================================================
//	file name	: Time.c
//==============================================================================

#define      MyDef       extern         //
#include	"Global.h"			        //

//------------------------------------------------------------------------------
//	external prototype function
//------------------------------------------------------------------------------



//==============================================================================
//	Melody Control
//==============================================================================
//------------------------------------------------------------------------------
//     [Frequency]
//------------------------------------------------------------------------------
//     음표     C(도)   D(레)   E(미)   F(파)   G(솔)   A(라)   B(시)
//	Octave 1 130.810 146.830 164.810 174.610 196.600 220.000 246.940
//	Octave 2 261.630 293.660 329.630 349.230 392.000 440.000 493.880
//	Octave 3 523.250 587.330 659.260 698.460 783.990 880.000 987.770
//	Octave 4 1046.50 1174.70 1318.50 1396.90 1568.00 1760.00 1975.50
//  Octave 5 2092.00 2350.00 2638.00 2794.00 3136.00 3520.00 3950.00
//
//                         8MHz/128/2 = 31.25KHz
#define	Do1		238		// 31250/130.81Hz = 238.896
#define	Re1		212		// 31250/146.83Hz = 212.831
#define	Mi1		189		// 31250/164.81Hz = 189.61
#define	Fa1		178		// 31250/174.61Hz = 178.97
#define	Sol1	158		// 31250/196.60Hz = 158.95
#define	Ra1		141		// 31250/220.00Hz = 142.045
#define	Chi1	126		// 31250/246.94Hz = 126.549
#define	Do2		119		// 31250/262Hz    = 119.275
#define	Re2		105		// 31250/294Hz    = 106.292
#define	Mi2		93		// 62500/330Hz    = 189.39
#define	Fa2		88		// 62500/349Hz    = 179.083
#define	Sol2	79		// 62500/392Hz    = 159.43
#define	Ra2		70		// 62500/440Hz    = 142.045	      오케스트라 기준 주파수
#define	Chi2	62		// 62500/496Hz    = 126.008
//                          8MHz/32/2 = 125KHz
#define	Do3		238		// 62500/512Hz    = 122.07
#define	Re3		212		// 62500/590Hz    = 105.932
#define	Mi3		189		// 125000/665Hz   = 187.97
#define	Fa3		178		// 125000/694Hz   = 180.11
#define	Sol3	158		// 125000/781Hz   = 160.051
#define	Ra3		141		// 125000/868Hz   = 144.00
#define	Chi3	126		// 125000/976Hz   = 128.073
#define	Do4		119		// 125000/1042Hz  = 119.96
#define	Re4		105		// 125000/1179Hz  = 106.022
#define	Mi4 	93		// 250000/1330Hz  = 187.97
#define	Fa4		88		// 250000/1389Hz  = 179.98
#define	Sol4	79		// 250000/1563Hz  = 159.94
#define	Ra4		70		// 250000/1736Hz  = 144.00
#define	Chi4	62		// 250000/1953Hz  = 128.00

//                          8MHz/32/2 = 500KHz
#define	Do5		238		//  
#define	Re5		212		// 
//------------------------------------------------------------------------------
//	[Length] 
//------------------------------------------------------------------------------
//	Largo		4000 = 160 x 25 mSec  (Adagio, Rento) 아주 느리게 
//	Andante  	3700 = 148 x 25 mSec                  느리게 
//	Andantino	3350 = 134 x 25 mSec                  조금 느리게 
//	Moderato	3000 = 120 x 25 mSec                  보통 빠르게 
//	Allegretto  2700 = 108 x 25 mSec                  조금 빠르게 
//	Allegro  	2350 =  94 x 25 mSec                  빠르게 
//    Vivache	2000 =  80 x 25 mSec  (Presto)        아주 빠르게  
//
//	온 음표 :  /1
//	2분음표 :  /2
//  4분음표 :  /4
//	8분음표 :  /8
//	16분음표:  /16
//	쉼표 	: 
//------------------------------------------------------------------------------
//	25mSec T2 interrupt Count 기준 Length
//------------------------------------------------------------------------------
#define	EOT   	    0xFF		// end of table
#define	PAUSE  	    0x0A 		// PAUSE (쉼표)

#define	Largo		160 		//
#define	Andante	    148 		//
#define	Andantino	134 		//
#define	Moderato	120 		//
#define	Allegretto	108 		//
#define	Allegro	    94 		    //
#define	Vivache	    80 		    //

//------------------------------------------------------------------------------
//     Melody : "짱가"  
//------------------------------------------------------------------------------
code Byte Tab_Beep_JJangGa[] =
{	Allegro/16,Ra4,             // 전주곡
	Allegro/16,Chi4,            //
	Allegro/16,Do5,	            //
	Allegro/16,Ra4,	            //
	Allegro/8, Ra4,	            //
	Allegro/8, Mi4,	            //
	Allegro/8, Fa4,	            //
	Allegro/8, Re4,	            //
	Allegro/8, Mi4,	            //
	Allegro/8, Do4,	            //

	Allegro/16,Chi3,            //
	Allegro/16,Do4,	            //
	Allegro/16,Re4,	            //
	Allegro/16,Mi4,	            //
	Allegro/8, Do4,	            //
	Allegro/8, Chi3,            //
	Allegro/8, Ra3,	            //
	Allegro/8, Sol3-3,          //#
	Allegro/8, Ra3,             //

	Allegro/1, PAUSE,           //
	//-------------------------------------------------
	Allegro/8, Mi4,	            //
	Allegro/16,Mi4,	            //
	Allegro/16,Mi4,	            //
	Allegro/8, Mi4,	            //
	Allegro/8, Do4,	            //
	Allegro/4, Re4-2,           //
	Allegro/8, Re4-3,           // #

	Allegro/16,Chi3,            //
	Allegro/16,Chi3,            //
	Allegro/8, Re4,	            //
	Allegro/16,Re4,	            //
	Allegro/16,Re4,	            //
	Allegro/8, Re4,	            //
	Allegro/8, Do4,	            //
	Allegro/4, Ra3,	            //
	Allegro/4, PAUSE,           //

	Allegro/8, Ra3,	            //
	Allegro/16,Ra3,	            //
	Allegro/16,Ra3,	            //
	Allegro/8, Ra3,	            //
	Allegro/8, Ra4,	            //
	Allegro/8, Sol4,            //
	Allegro/16,Fa4,	            //
	Allegro/16,Fa4,	            //
	Allegro/8, Fa4,	            //

	Allegro/8, Mi4,	            //
	Allegro/16,Mi4,	            //
	Allegro/16,Mi4,	            //
	Allegro/16,Mi4,	            //
	Allegro/16,Do4,	            //
	Allegro/8, Re4,	            //
	Allegro/4, Mi4,	            //
	Allegro/4, PAUSE,           //

	Allegro/8, Mi4,	            //
	Allegro/16,Mi4,	            //
	Allegro/16,Mi4,	            //
	Allegro/8, Mi4,	            //
	Allegro/16,Do4,	            //
	Allegro/4, Re4-3,           //#
	Allegro/8, Re4-3,           //
	
	Allegro/16,Chi3,            //
	Allegro/16,Chi3,            //
	Allegro/8, Re4,	            //
	Allegro/16,Re4,	            //
	Allegro/16,Re4,	            //
	Allegro/8, Re4,	            //
	Allegro/8, Mi4,	            //
	Allegro/4, Do4,	            //
	Allegro/4, PAUSE,           //

	Allegro/8, Mi4,	            //
	Allegro/16,Mi4,	            //
	Allegro/16,Ra4,	            //
	Allegro/16,Ra4,	            //
	Allegro/8, Ra4,	            //
	Allegro/4, Do5,	            //
	Allegro/8, Chi4,            //
	Allegro/8, Ra4,	            //
	Allegro/8, Do5,	            //
	Allegro/16,Do5,	            //
	Allegro/16,Chi4,            //
	Allegro/8, Chi4,            //
	Allegro/16,Chi4,            //
	Allegro/4, Ra4,	            //
	Allegro/4, PAUSE,           //

	//--------------------------------------
	Allegro/16,Ra4,	            //후렴구
	Allegro/16,Chi4,            //
	Allegro/16,Do5,	            //
	Allegro/16,Ra4,	            //
	Allegro/8, Ra4,	            //
	Allegro/8, Mi4,             //
	Allegro/8, Fa4,	            //
	Allegro/8, Re4,	            //
	Allegro/8, Mi4,	            //
	Allegro/8, Do4,	            //

	Allegro/16,Chi3,            //
	Allegro/16,Do4,	            //
	Allegro/16,Re4,	            //
	Allegro/16,Mi4,	            //
	Allegro/8, Do4,	            //
	Allegro/8, Chi3,            //
	Allegro/8, Ra3,	            //
	Allegro/8, Sol3-3,          // #
	Allegro/4, Ra3,             //

	Allegro/2, PAUSE,           //

	Allegro/16,Ra4,	            //
	Allegro/16,Chi4,            //
	Allegro/16,Do5,	            //
	Allegro/16,Ra4,	            //
	Allegro/8, Ra4,	            //
	Allegro/8, Mi4,	            //
	Allegro/8, Fa4,	            //
	Allegro/8, Re4,	            //
	Allegro/8, Mi4,	            //
	Allegro/8, Do4,	            //

	Allegro/16,Chi3,            //
	Allegro/16,Do4,	            //
	Allegro/16,Re4,	            //
	Allegro/16,Mi4,	            //
	Allegro/8, Do4,	            //
	Allegro/8, Chi3,            //
	Allegro/8, Ra3,	            //
	Allegro/8, Sol3-3,          // #
	Allegro/8, Ra3,             //
	EOT,       EOT  			// End of table
};

//------------------------------------------------------------------------------
//     Melody sound : "고향의 봄"
//------------------------------------------------------------------------------
code Byte Tab_Beep_Home[] =
{	Andante/8,  Sol3,				//
	Andante/100,PAUSE,			    //
	Andante/8,  Sol3,				//
	Andante/16, Mi3,				//
	Andante/16, Fa3,				//
	Andante/8,  Sol3,				//
	Andante/8,  Ra3,				//
	Andante/100,PAUSE,			    //
	Andante/8,  Ra3,				//
	Andante/4,  Sol3,				//
	Andante/100,PAUSE,			    //
	Andante/8,  Sol3,				//
	Andante/8,  Do4,				//
	Andante/8,  Mi4,				//
	Andante/16, Re4,				//
	Andante/16, Do4,				//
	Andante/2,  Re4,				//
	Andante/8,  Mi4,				//
	Andante/100,PAUSE,			    //
	Andante/8,  Mi4,				//
	Andante/8,  Re4,				//
	Andante/100,PAUSE,			    //
	Andante/8,  Re4,				//
	Andante/8,  Do4,				//
	Andante/16, Re4,				//
	Andante/16, Do4,				//
	Andante/4,  Ra3,				//
	Andante/8,  Sol3,				//
	Andante/100,PAUSE,			    //
	Andante/8,  Sol3,				//
	Andante/100,PAUSE,			    //
	Andante/8,  Sol3,				//
	Andante/16, Mi3,				//
	Andante/16, Re3,				//
	Andante/2,  Do3,				//
	EOT,EOT  					    // End of table
};

//------------------------------------------------------------------------------
//     Melody : "첨밀밀"
//------------------------------------------------------------------------------
#define bm_Chamm Moderato //bandmaster
code Byte Tab_Beep_Chamm[]=			//
{	
	bm_Chamm/4, Mi4,
	bm_Chamm/8, Sol4,
	bm_Chamm/8, Ra4,
	bm_Chamm/3, Mi4,
	bm_Chamm/16,0,
	bm_Chamm/8, Do4,
	bm_Chamm/16,Re4,
	bm_Chamm/16,0,
	bm_Chamm/16,Re4,
	bm_Chamm/16,Do4,
	bm_Chamm/8, Re4,
	bm_Chamm/8, Sol4,
	bm_Chamm/3, Mi4,
	bm_Chamm/8, 0,
	
	bm_Chamm/16,Re4,
	bm_Chamm/16,0,
	bm_Chamm/16,Re4,
	bm_Chamm/16,0,
	bm_Chamm/8, Re4,
	bm_Chamm/8, Mi4,
	bm_Chamm/8, Re4,
	bm_Chamm/8, Do4,
	bm_Chamm/8, Ra3,
	bm_Chamm/8, Sol3,
	bm_Chamm/3, Do4,
	bm_Chamm/8, Mi4,
	bm_Chamm/8, Re4,
	bm_Chamm/8, Do4,
	bm_Chamm/8, Ra3,
	bm_Chamm/8, Sol3,
	bm_Chamm/2, Do4,
	bm_Chamm/8, 0,
	
	EOT,EOT  					            // End of table
};

//------------------------------------------------------------------------------
//     Melody : "생일축하 노래"
//------------------------------------------------------------------------------
#define bm_HBD Vivache //bandmaster
code Byte Tab_Beep_HappyBirthDay[]=			// 
{	
	bm_HBD/8,   Re4,
	bm_HBD/16,  0,
	bm_HBD/8,   Re4,
	bm_HBD/16,  0,
	bm_HBD/4,   Mi4,
	bm_HBD/16,  0,
	bm_HBD/4,   Re4,
	bm_HBD/16,  0,
	bm_HBD/8,   Sol4,
	bm_HBD/16,  0,
	bm_HBD/8,   Sol4,
	bm_HBD/16,  0,
	bm_HBD/2,   Fa4-3,
	bm_HBD/8,   0,

	bm_HBD/8,   Re4,
	bm_HBD/16,  0,
	bm_HBD/8,   Re4,
	bm_HBD/16,  0,
	bm_HBD/4,   Mi4,
	bm_HBD/16,  0,
	bm_HBD/4,   Re4,
	bm_HBD/16,  0,
	bm_HBD/8,   Ra4,
	bm_HBD/16,  0,
	bm_HBD/8,   Ra4,
	bm_HBD/16,  0,
	bm_HBD/2,   Sol4,
	bm_HBD/8,   0,
	
	bm_HBD/8,   Re4,
	bm_HBD/16,  0,
	bm_HBD/8,   Re4,
	bm_HBD/16,  0,
	bm_HBD/4,   Re5,
	bm_HBD/16,  0,
	bm_HBD/4,   Chi4,
	bm_HBD/16,  0,
	bm_HBD/4,   Sol4,
	bm_HBD/16,  0,
	bm_HBD/4,   Fa4-2,
	bm_HBD/16,  0,
	bm_HBD/2,   Mi4,
	bm_HBD/4,   0,
	
	bm_HBD/8,   Do5,
	bm_HBD/16,  0,
	bm_HBD/8,   Do5,
	bm_HBD/16,  0,
	bm_HBD/4,   Chi4,
	bm_HBD/16,  0,
	bm_HBD/4,   Sol4,
	bm_HBD/16,  0,
	bm_HBD/8,   Ra4,
	bm_HBD/16,  0,
	bm_HBD/8,   Ra4,
	bm_HBD/16,  0,
	bm_HBD/2,   Sol4,
	bm_HBD/16,  0,

	EOT,EOT  					// End of table
};

//------------------------------------------------------------------------------
//     off sound : "사라짐 효과음"
//------------------------------------------------------------------------------
code Byte Tab_Beep_Off[]=			//
{	Andante/60, Mi4,				//
	Andante/60, Re4,				//
	Andante/60, Do4,				//
	Andante/60, Chi3,				//
	Andante/50, Ra3,				//
	Andante/50, Sol3,				//
	Andante/50, Fa3,				//
	Andante/30, Mi3,				//
	Andante/30, Re3,				//
	Andante/20, Do3,				//
	EOT,EOT  					    // End of table
};

//------------------------------------------------------------------------------
//     1736 Hz beep sound table 
//------------------------------------------------------------------------------
code Byte Tab_Alarm_High[]=
{	Andante/30, Ra4,				// 1.736 kHz
	Andante/80, PAUSE,				//
	Andante/30, Ra4,				//
	Andante/80, PAUSE,				//
	Andante/30, Ra4,				//
	Andante/20, PAUSE,				//
	Andante/30, Ra4,				//
	Andante/80, PAUSE,				//
	Andante/30, Ra4,				//
	Andante/80, PAUSE,				//
	Andante/30, Ra4,				//
	EOT,EOT  					    // End of table
};
//------------------------------------------------------------------------------
//     521 Hz beep sound table 
//------------------------------------------------------------------------------
code Byte Tab_Beep_Low[]=
{	Andante/20, Do3,				// 521 Hz
	Andante/50, PAUSE,				//
	Andante/20, Do3,				//
	Andante/50, PAUSE,				//
	Andante/20, Do3,				//
	Andante/8,  PAUSE,				//
	Andante/20, Do3,				//
	Andante/50, PAUSE,				//
	Andante/20, Do3,				//
	Andante/50, PAUSE,				//
	Andante/20, Do3,				//
	EOT,EOT  					    // End of table
};

//------------------------------------------------------------------------------
//	task	: Melody start 
//------------------------------------------------------------------------------

void Melody_Out(void)				    //
{   T2CRH   = 0x80;                     //
    T2ADR   = 25000;                    // 1us x 25000 = 20ms
    T2CRL   = 0x60;                     // psc = 8 MHz/8 = 1us
    T2CRH   = 0x81;                     //
    
	rMelody_cnt = 1;  			        //
	IE2	    |= 0x08;			        // IE2.4 (INT16E)
}

//------------------------------------------------------------------------------
//     task  : Timer2 25 mSec time interval interrupt
//------------------------------------------------------------------------------

void T2_Int_Handler(void) interrupt 15  using 1 //
{
    Byte  m;
      
	if (rMelody_cnt) 				    //
		rMelody_cnt--;				    // 50 x N   ms
	else
	{	m = *wMelody_Ptr++;			    //
		if (m == EOT)				    //
		{	T0CR    = 0x00;			    //
	        T0DR    = 0x00;			    // 
	        IE2	    &= ~0x08;			// IE2.4 (INT16E)
            return;                     //
		}
		else rMelody_cnt = m;		    //
		
		m = *wMelody_Ptr++;			    //
		if(m == PAUSE) 			        //
	        T0CR  = 0x00;               // pulse stop temperary
		else if (m != EOT)			    //
		{	T0DR   = m;			        //
	        T0CR   = 0x89;              // P35 is T0O
		}
	}
}
//==============================================================================
//	task  : Melody Sound Process
//==============================================================================

void Process_Melody(void)						//
{
    if(rMelody_Mode==BEEP_NONE)    return;      //
      
	switch(rMelody_Mode)						// melody service
	{
		case	BEEP_ALARM:						//
			wMelody_Ptr = &Tab_Alarm_High[0];   //
		break;							        //
      
		case	BEEP_OFF:						//
			wMelody_Ptr = &Tab_Beep_Off[0];     //
		break;							        //
      
		case	BEEP_ERROR:						//
			wMelody_Ptr = &Tab_Beep_Home[0];    //
		break;							        //
	
		case	BEEP_LOW:						//
			wMelody_Ptr = &Tab_Beep_Low[0];	    //
		break;							        //
      
 		case	BEEP_JJangGa:					//
 			wMelody_Ptr = &Tab_Beep_JJangGa[0]; //
 		break;							        //
	
		case	BEEP_Home:						//
			wMelody_Ptr = &Tab_Beep_Home[0];    //
		break;							        //
	
		case	BEEP_Chamm:						//
			wMelody_Ptr = &Tab_Beep_Chamm[0];   //
		break;							        //
	
		case	BEEP_HappyBD:					//
			wMelody_Ptr = &Tab_Beep_HappyBirthDay[0]; //
		break;
	} 
	Melody_Out();						        //
	rMelody_Mode = BEEP_NONE;					//
}
//==============================================================================
//     the end of Buzzer.C
