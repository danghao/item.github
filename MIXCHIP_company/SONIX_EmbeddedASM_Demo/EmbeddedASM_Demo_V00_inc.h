ifndef __SN8P2708A__INC__H
SN8P2708A__INC__H equ 1
	L	EQU	0x80
	H	EQU	0x81
	R	EQU	0x82
	Z	EQU	0x83
	Y	EQU	0x84
	X	EQU	0x85
	PFLAG	EQU	0x86
		FZ	EQU	PFLAG.0
		FDC	EQU	PFLAG.1
		FC	EQU	PFLAG.2
		FNPD	EQU	PFLAG.6
		FNT0	EQU	PFLAG.7
	RBANK	EQU	0x87
		FRBNKS0	EQU	RBANK.0
	P4CON	EQU	0xAE
		FP4CON7	EQU	P4CON.7
		FP4CON6	EQU	P4CON.6
		FP4CON5	EQU	P4CON.5
		FP4CON4	EQU	P4CON.4
		FP4CON3	EQU	P4CON.3
		FP4CON2	EQU	P4CON.2
		FP4CON1	EQU	P4CON.1
		FP4CON0	EQU	P4CON.0
	DAM	EQU	0xB0
		FDAENB	EQU	DAM.7
		FDAB6	EQU	DAM.6
		FDAB5	EQU	DAM.5
		FDAB4	EQU	DAM.4
		FDAB3	EQU	DAM.3
		FDAB2	EQU	DAM.2
		FDAB1	EQU	DAM.1
		FDAB0	EQU	DAM.0
	ADM	EQU	0xB1
		FADENB	EQU	ADM.7
		FADS	EQU	ADM.6
		FEOC	EQU	ADM.5
		FGCHS	EQU	ADM.4
		FCHS2	EQU	ADM.2
		FCHS1	EQU	ADM.1
		FCHS0	EQU	ADM.0
	ADB	EQU	0xb2
	ADR	EQU	0xb3
		FADCKS2	EQU	ADR.7
		FADCKS	EQU	ADR.6
		FADCKS1	EQU	ADR.6
		FADLEN	EQU	ADR.5
		FADCKS0	EQU	ADR.4
		FADB3	EQU	ADR.3
		FADB2	EQU	ADR.2
		FADB1	EQU	ADR.1
		FADB0	EQU	ADR.0
	SIOM	EQU	0xb4
		FSENB	EQU	SIOM.7
		FSTART	EQU	SIOM.6
		FSRATE1	EQU	SIOM.5
		FSRATE0	EQU	SIOM.4
		FSCKMD	EQU	SIOM.2
		FSEDGE	EQU	SIOM.1
		FTXRX	EQU	SIOM.0
	SIOR	EQU	0xb5
	SIOB	EQU	0xb6
	P0M	EQU	0xb8
		FP02M	EQU	P0M.2
		FP01M	EQU	P0M.1
		FP00M	EQU	P0M.0
	PEDGE	EQU	0xbf
		FP00G1	EQU	PEDGE.4
		FP00G0	EQU	PEDGE.3
	P1W	EQU	0xc0
		FP17W	EQU	P1W.7
		FP16W	EQU	P1W.6
		FP15W	EQU	P1W.5
		FP14W	EQU	P1W.4
		FP13W	EQU	P1W.3
		FP12W	EQU	P1W.2
		FP11W	EQU	P1W.1
		FP10W	EQU	P1W.0
	P1M	EQU	0xc1
		FP17M	EQU	P1M.7
		FP16M	EQU	P1M.6
		FP15M	EQU	P1M.5
		FP14M	EQU	P1M.4
		FP13M	EQU	P1M.3
		FP12M	EQU	P1M.2
		FP11M	EQU	P1M.1
		FP10M	EQU	P1M.0
	P2M	EQU	0xc2
		FP27M	EQU	P2M.7
		FP26M	EQU	P2M.6
		FP25M	EQU	P2M.5
		FP24M	EQU	P2M.4
		FP23M	EQU	P2M.3
		FP22M	EQU	P2M.2
		FP21M	EQU	P2M.1
		FP20M	EQU	P2M.0
	P3M	EQU	0xc3
		FP30M	EQU	P3M.0
	P4M	EQU	0xc4
		FP47M	EQU	P4M.7
		FP46M	EQU	P4M.6
		FP45M	EQU	P4M.5
		FP44M	EQU	P4M.4
		FP43M	EQU	P4M.3
		FP42M	EQU	P4M.2
		FP41M	EQU	P4M.1
		FP40M	EQU	P4M.0
	P5M	EQU	0xc5
		FP57M	EQU	P5M.7
		FP56M	EQU	P5M.6
		FP55M	EQU	P5M.5
		FP54M	EQU	P5M.4
		FP53M	EQU	P5M.3
		FP52M	EQU	P5M.2
		FP51M	EQU	P5M.1
		FP50M	EQU	P5M.0
	INTRQ	EQU	0xc8
		FADCIRQ	EQU	INTRQ.7
		FTC1IRQ	EQU	INTRQ.6
		FTC0IRQ	EQU	INTRQ.5
		FT0IRQ	EQU	INTRQ.4
		FSIOIRQ	EQU	INTRQ.3
		FP02IRQ	EQU	INTRQ.2
		FP01IRQ	EQU	INTRQ.1
		FP00IRQ	EQU	INTRQ.0
	INTEN	EQU	0xc9
		FADCIEN	EQU	INTEN.7
		FTC1IEN	EQU	INTEN.6
		FTC0IEN	EQU	INTEN.5
		FT0IEN	EQU	INTEN.4
		FSIOIEN	EQU	INTEN.3
		FP02IEN	EQU	INTEN.2
		FP01IEN	EQU	INTEN.1
		FP00IEN	EQU	INTEN.0
	OSCM	EQU	0xca
		FCPUM1	EQU	OSCM.4
		FCPUM0	EQU	OSCM.3
		FCLKMD	EQU	OSCM.2
		FSTPHX	EQU	OSCM.1
	WDTR	EQU	0xcc
	TC0R	EQU	0xcd
	PCL	EQU	0xce
	PCH	EQU	0xcf
	P0	EQU	0xd0
		FP02	EQU	P0.2
		FP01	EQU	P0.1
		FP00	EQU	P0.0
	P1	EQU	0xd1
		FP17	EQU	P1.7
		FP16	EQU	P1.6
		FP15	EQU	P1.5
		FP14	EQU	P1.4
		FP13	EQU	P1.3
		FP12	EQU	P1.2
		FP11	EQU	P1.1
		FP10	EQU	P1.0
	P2	EQU	0xd2
		FP27	EQU	P2.7
		FP26	EQU	P2.6
		FP25	EQU	P2.5
		FP24	EQU	P2.4
		FP23	EQU	P2.3
		FP22	EQU	P2.2
		FP21	EQU	P2.1
		FP20	EQU	P2.0
	P3	EQU	0xd3
		FP30	EQU	P3.0
	P4	EQU	0xd4
		FP47	EQU	P4.7
		FP46	EQU	P4.6
		FP45	EQU	P4.5
		FP44	EQU	P4.4
		FP43	EQU	P4.3
		FP42	EQU	P4.2
		FP41	EQU	P4.1
		FP40	EQU	P4.0
	P5	EQU	0xd5
		FP57	EQU	P5.7
		FP56	EQU	P5.6
		FP55	EQU	P5.5
		FP54	EQU	P5.4
		FP53	EQU	P5.3
		FP52	EQU	P5.2
		FP51	EQU	P5.1
		FP50	EQU	P5.0
	T0M	EQU	0xd8
		FT0ENB	EQU	T0M.7
		FT0RATE2	EQU	T0M.6
		FT0RATE1	EQU	T0M.5
		FT0RATE0	EQU	T0M.4
	T0C	EQU	0xd9
	TC0M	EQU	0xda
		FTC0ENB	EQU	TC0M.7
		FTC0RATE2	EQU	TC0M.6
		FTC0RATE1	EQU	TC0M.5
		FTC0RATE0	EQU	TC0M.4
		FTC0CKS	EQU	TC0M.3
		FALOAD0	EQU	TC0M.2
		FTC0OUT	EQU	TC0M.1
		FPWM0OUT	EQU	TC0M.0
	TC0C	EQU	0xdb
	TC1M	EQU	0xdc
		FTC1ENB	EQU	TC1M.7
		FTC1RATE2	EQU	TC1M.6
		FTC1RATE1	EQU	TC1M.5
		FTC1RATE0	EQU	TC1M.4
		FTC1CKS	EQU	TC1M.3
		FALOAD1	EQU	TC1M.2
		FTC1OUT	EQU	TC1M.1
		FPWM1OUT	EQU	TC1M.0
	TC1C	EQU	0xdd
	TC1R	EQU	0xde
	STKP	EQU	0xdf
		FGIE	EQU	STKP.7
		FSTKPB2	EQU	STKP.2
		FSTKPB1	EQU	STKP.1
		FSTKPB0	EQU	STKP.0
	P0UR	EQU	0xe0
		FP02R	EQU	P0UR.2
		FP01R	EQU	P0UR.1
		FP00R	EQU	P0UR.0
	P1UR	EQU	0xe1
		FP17R	EQU	P1UR.7
		FP16R	EQU	P1UR.6
		FP15R	EQU	P1UR.5
		FP14R	EQU	P1UR.4
		FP13R	EQU	P1UR.3
		FP12R	EQU	P1UR.2
		FP11R	EQU	P1UR.1
		FP10R	EQU	P1UR.0
	P2UR	EQU	0xe2
		FP27R	EQU	P2UR.7
		FP26R	EQU	P2UR.6
		FP25R	EQU	P2UR.5
		FP24R	EQU	P2UR.4
		FP23R	EQU	P2UR.3
		FP22R	EQU	P2UR.2
		FP21R	EQU	P2UR.1
		FP20R	EQU	P2UR.0
	P3UR	EQU	0xe3
		FP30R	EQU	P3UR.0
	P4UR	EQU	0xe4
		FP47R	EQU	P4UR.7
		FP46R	EQU	P4UR.6
		FP45R	EQU	P4UR.5
		FP44R	EQU	P4UR.4
		FP43R	EQU	P4UR.3
		FP42R	EQU	P4UR.2
		FP41R	EQU	P4UR.1
		FP40R	EQU	P4UR.0
	P5UR	EQU	0xe5
		FP57R	EQU	P5UR.7
		FP56R	EQU	P5UR.6
		FP55R	EQU	P5UR.5
		FP54R	EQU	P5UR.4
		FP53R	EQU	P5UR.3
		FP52R	EQU	P5UR.2
		FP51R	EQU	P5UR.1
		FP50R	EQU	P5UR.0
	@HL	EQU	0xe6
	DP0X	EQU	0xe6
	@YZ	EQU	0xe7
	DP1X	EQU	0xe7
	P1OC	EQU	0xe9
		FP10OC	EQU	P1OC.0
		FP11OC	EQU	P1OC.1
		FP52OC	EQU	P1OC.2
	STK7L	EQU	0xf0
	STK7H	EQU	0xf1
	STK6L	EQU	0xf2
	STK6H	EQU	0xf3
	STK5L	EQU	0xf4
	STK5H	EQU	0xf5
	STK4L	EQU	0xf6
	STK4H	EQU	0xf7
	STK3L	EQU	0xf8
	STK3H	EQU	0xf9
	STK2L	EQU	0xfa
	STK2H	EQU	0xfb
	STK1L	EQU	0xfc
	STK1H	EQU	0xfd
	STK0L	EQU	0xfe
	STK0H	EQU	0xff
@RST_WDT	macro		
 		   MOV  A, #0x5A
		   B0MOV  WDTR, A
	endm

SleepMode	macro	
		B0BSET	FCPUM0
	endm

GreenMode	macro	
		B0BSET	FCPUM1
		NOP
		NOP
	endm

SlowMode	macro	
		B0BSET	FCLKMD
		B0BSET	FSTPHX
	endm

Slow2Normal	macro	
		B0BCLR	FSTPHX
		NOP
		NOP
		NOP
		B0BCLR	FCLKMD
	endm

@P00_MODE	macro	val	; val = 0 input mode
					; val = 1 output mode
		IFNDEF  val
			ECHO	Error: @P00_MODE macro need one parameter
			ECHO	Syntax: @P00_MODE  Mode
			ECHO	Example:
			ECHO	@P00_MODE 0  Configure P0.0 as input mode
			ECHO	@P00_MODE 1  Configure P0.0 as output mode			
			ERROR
			ECHO
		ENDIF

		IF val == 0		; val = 0 input mode					
			   B0BCLR FP00M	
			
		ELSEIF val == 1		; val = 1 output mode
			
			    B0BSET FP00M			
		ELSE
			ECHO	Error: val is invalid parameter of @P00_MODE macro
			ECHO	Syntax: @P00_MODE  Mode
			ECHO	Example:
			ECHO	@P00_MODE 0  Configure P0.0 as input mode
			ECHO	@P00_MODE 1  Configure P0.0 as output mode			
			ERROR
			ECHO				
		ENDIF		
	endm

@P00_OUT	macro	val	; val = 0 output low
					; val = 1 output high
		IFNDEF  val
			ECHO	Error: @P00_OUT macro need one parameter
			ECHO	Syntax: @P00_OUT  Level			
			ECHO	Example:
			ECHO	@P00_OUT 0  P0.0 output high
			ECHO	@P00_OUT 1  P0.0 output low
			ERROR
			ECHO
		ENDIF
					
		IF val == 0		; val = 0 P0.0 output low
			B0BCLR FP00	
					
		ELSEIF val == 1		; val = 1 P0.0 output high			
			B0BSET FP00
			
		ELSE
			ECHO	Error: val is invalid parameter of @P00_OUT macro
			ECHO	Syntax: @P00_OUT    Level
			ECHO	Example:
			ECHO	@P00_OUT 0  P0.0 output high
			ECHO	@P00_OUT 1  P0.0 output low
			ERROR
			ECHO			
		ENDIF
	endm

@P01_MODE	macro	val	; val = 0 input mode
					; val = 1 output mode
		IFNDEF  val
			ECHO	Error: @P01_MODE macro need one parameter
			ECHO	Syntax: @P01_MODE  Mode
			ECHO	Example:
			ECHO	@P01_MODE 0  Configure P0.1 as input mode
			ECHO	@P01_MODE 1  Configure P0.1 as output mode			
			ERROR
			ECHO
		ENDIF

		IF val == 0		; val = 0 input mode				
		   	B0BCLR FP01M		
			
		ELSEIF val == 1		; val = 1 output mode			
			B0BSET FP01M
			
		ELSE
			ECHO	Error: val is invalid parameter of @P01_MODE macro
			ECHO	Syntax: @P01_MODE  Mode
			ECHO	Example:
			ECHO	@P01_MODE 0  Configure P0.1 as input mode
			ECHO	@P01_MODE 1  Configure P0.1 as output mode			
			ERROR
			ECHO				
		ENDIF
	endm

@P01_OUT	macro	val	; val = 0 output low
					; val = 1 output high
		IFNDEF  val
			ECHO	Error: @P01_OUT macro need one parameter
			ECHO	Syntax: @P01_OUT    Level
			ECHO	Example:
			ECHO	@P01_OUT 0  P0.1 output high
			ECHO	@P01_OUT 1  P0.1 output low
			ERROR
			ECHO
		ENDIF
					
		IF val == 0		; val = 0 output low			
			   B0BCLR FP01
			   			
		ELSEIF val == 1		; val = 1 output high			
			   B0BSET FP01			
		ELSE
			ECHO	Error: val is invalid parameter of @P01_OUT macro
			ECHO	Syntax: @P01_OUT    Level
			ECHO	Example:
			ECHO	@P01_OUT 0  P0.1 output high
			ECHO	@P01_OUT 1  P0.1 output low
			ERROR
			ECHO			
		ENDIF
	endm

@P02_MODE	macro	val	; val = 0 input mode
					; val = 1 output mode
		IFNDEF  val
			ECHO	Error: @P02_MODE macro need one parameter
			ECHO	Syntax: @P02_MODE  Mode
			ECHO	Example:
			ECHO	@P02_MODE 0  Configure P0.2 as input mode
			ECHO	@P02_MODE 1  Configure P0.2 as output mode			
			ERROR
			ECHO
		ENDIF

		IF val == 0		; val = 0 input mode			
			B0BCLR FP02M			
			
		ELSEIF val == 1		; val = 1 output mode			
			B0BSET FP02M			
		ELSE
			ECHO	Error: val is invalid parameter of @P02_MODE macro
			ECHO	Syntax: @P02_MODE  Mode
			ECHO	Example:
			ECHO	@P02_MODE 0  Configure P0.2 as input mode
			ECHO	@P02_MODE 1  Configure P0.2 as output mode			
			ERROR
			ECHO				
		ENDIF		
	endm

@P02_OUT	macro	val	; val = 0 output low
					; val = 1 output high
		IFNDEF  val
			ECHO	Error: @P02_OUT macro need one parameter
			ECHO	Syntax: @P02_OUT    Level
			ECHO	Example:
			ECHO	@P02_OUT 0  P0.2 output high
			ECHO	@P02_OUT 1  P0.2 output low
			ERROR
			ECHO
		ENDIF
					
		IF val == 0		; val = 0 output low			
			   B0BCLR FP02
			
		ELSEIF val == 1		; val = 1 output high			
			   B0BSET FP02			
		ELSE
			ECHO	Error: val is invalid parameter of @P02_OUT macro
			ECHO	Syntax: @P02_OUT    Level
			ECHO	Example:
			ECHO	@P02_OUT 0  P0.2 output high
			ECHO	@P02_OUT 1  P0.2 output low
			ERROR
			ECHO			
		ENDIF
	endm

@PWM0_MAX_DUTY	macro	Max_Duty
	
		;Max_Duty	TC0 Overflow Boundary	PWM Duty Range
		;	256	FFh to 00h		0/256 ~ 255/256
		;	64	3Fh to 40h		0/64 ~ 63/64
		;	32	1Fh to 20h		0/32 ~ 31/32
		;	16	0Fh to 10h		0/16 ~ 15/16
		
		IFNDEF  Max_Duty
			ECHO	Error: @PWM0_MAX_DUTY MACRO need Max-Duty parameter
			ECHO	Syntax: @PWM0_MAX_DUTY  Max-Duty
			ECHO	<Max-Duty = 256 Duty from 0/256 to 255/256>
			ECHO	<Max-Duty =  64  Duty from 0/64  to  63/64>
			ECHO	<Max-Duty =  32  Duty from 0/32  to  31/32>			
			ECHO	<Max-Duty =  16  Duty from 0/16  to  15/16>
			ECHO    Example:
			ECHO	@PWM0_MAX_DUTY 256   Configure maximum duty cycle as 256
			ERROR
			ECHO
		ENDIF		

		Duty_Temp = Max_Duty		
		IF	Duty_Temp == 256			
				;Set real chip PWM0 output
				B0BCLR	FALOAD0
				B0BCLR	FTC0OUT
				B0BSET	FPWM0OUT
				
		ELSEIF	Duty_Temp == 64			
				;Set real chip PWM0 output
				B0BCLR	FALOAD0
				B0BSET	FTC0OUT
				B0BSET	FPWM0OUT
				
		ELSEIF	Duty_Temp == 32
			
				;Set real chip PWM0 output
				B0BSET	FALOAD0
				B0BCLR	FTC0OUT
				B0BSET	FPWM0OUT
				
		ELSEIF	Duty_Temp == 16
			
				;Set real chip PWM0 output
				B0BSET	FALOAD0
				B0BSET	FTC0OUT
				B0BSET	FPWM0OUT
				
		ELSE
			ECHO	Error: Max_Duty is invalid Max-Duty parameter of @PWM0_MAX_DUTY MACRO
			ECHO	Syntax: @PWM0_MAX_DUTY  Max-Duty
			ECHO	<Max-Duty = 256 Duty from 0/256 to 255/256>
			ECHO	<Max-Duty =  64  Duty from 0/64  to  63/64>
			ECHO	<Max-Duty =  32  Duty from 0/32  to  31/32>			
			ECHO	<Max-Duty =  16  Duty from 0/16  to  15/16>
			ECHO    Example:
			ECHO	@PWM0_MAX_DUTY 256   Configure maximum duty cycle as 256
			ERROR
			ECHO			
		ENDIF		
	ENDM

@PWM1_MAX_DUTY	macro	Max_Duty
	
		;Max_Duty	TC1 Overflow Boundary	PWM Duty Range
		;	256	FFh to 00h		0/256 ~ 255/256
		;	64	3Fh to 40h		0/64 ~ 63/64
		;	32	1Fh to 20h		0/32 ~ 31/32
		;	16	0Fh to 10h		0/16 ~ 15/16
		
		IFNDEF  Max_Duty
			ECHO	Error: @PWM1_MAX_DUTY MACRO need Max-Duty parameter
			ECHO	Syntax: @PWM1_MAX_DUTY  Max-Duty
			ECHO	<Max-Duty = 256 Duty from 0/256 to 255/256>
			ECHO	<Max-Duty =  64  Duty from 0/64  to  63/64>
			ECHO	<Max-Duty =  32  Duty from 0/32  to  31/32>			
			ECHO	<Max-Duty =  16  Duty from 0/16  to  15/16>
			ECHO    Example:
			ECHO	@PWM1_MAX_DUTY 256   Configure maximum duty cycle as 256
			ERROR
			ECHO
		ENDIF		
		
		Duty_Temp = Max_Duty
		IF	Duty_Temp == 256
			
				;Set real chip PWM0 output
				B0BCLR	FALOAD1
				B0BCLR	FTC1OUT
				B0BSET	FPWM1OUT
				
		ELSEIF	Duty_Temp == 64
			
				;Set real chip PWM0 output
				B0BCLR	FALOAD1
				B0BSET	FTC1OUT
				B0BSET	FPWM1OUT
				
		ELSEIF	Duty_Temp == 32
			
				;Set real chip PWM0 output
				B0BSET	FALOAD1
				B0BCLR	FTC1OUT
				B0BSET	FPWM1OUT
				
		ELSEIF	Duty_Temp == 16
			
				;Set real chip PWM0 output
				B0BSET	FALOAD1
				B0BSET	FTC1OUT
				B0BSET	FPWM1OUT
				
		ELSE
			ECHO	Error: Max_Duty is invalid Max-Duty parameter of @PWM1_MAX_DUTY MACRO
			ECHO	Syntax: @PWM1_MAX_DUTY  Max-Duty
			ECHO	<Max-Duty = 256 Duty from 0/256 to 255/256>
			ECHO	<Max-Duty =  64  Duty from 0/64  to  63/64>
			ECHO	<Max-Duty =  32  Duty from 0/32  to  31/32>			
			ECHO	<Max-Duty =  16  Duty from 0/16  to  15/16>
			ECHO    Example:
			ECHO	@PWM1_MAX_DUTY 256   Configure maximum duty cycle as 256
			ERROR
			ECHO		
		ENDIF	
				
	ENDM

@PWM01_MAX_DUTY	macro	Max_Duty
		
		;Max_Duty	TC0 Overflow Boundary	PWM0 Duty Range
		;       	TC1 Overflow Boundary	PWM1 Duty Range
		;	256	FFh to 00h		0/256 ~ 255/256
		;	64	3Fh to 40h		0/64 ~ 63/64
		;	32	1Fh to 20h		0/32 ~ 31/32
		;	16	0Fh to 10h		0/16 ~ 15/16
		
		IFNDEF  Max_Duty
			ECHO	Error: @PWM01_MAX_DUTY MACRO need Max-Duty parameter
			ECHO	Syntax: @PWM01_MAX_DUTY  Max-Duty
			ECHO	<Max-Duty = 256 Duty from 0/256 to 255/256>
			ECHO	<Max-Duty =  64  Duty from 0/64  to  63/64>
			ECHO	<Max-Duty =  32  Duty from 0/32  to  31/32>			
			ECHO	<Max-Duty =  16  Duty from 0/16  to  15/16>
			ECHO    Example:
			ECHO	@PWM01_MAX_DUTY 256   Configure maximum duty cycle as 256
			ERROR
			ECHO
		ENDIF	

		Duty_Temp = Max_Duty		
		IF	Duty_Temp == 256			
			
				;Set real chip PWM0/PWM1 output
				B0BCLR	FALOAD0
				B0BCLR	FTC0OUT
				B0BSET	FPWM0OUT
				B0BCLR	FALOAD1
				B0BCLR	FTC1OUT
				B0BSET	FPWM1OUT
				
		ELSEIF	Duty_Temp == 64
			
				;Set real chip PWM0/PWM1 output
				B0BCLR	FALOAD0
				B0BSET	FTC0OUT
				B0BSET	FPWM0OUT
				B0BCLR	FALOAD1
				B0BSET	FTC1OUT
				B0BSET	FPWM1OUT
				
		ELSEIF	Duty_Temp == 32
			
				;Set real chip PWM0 output
				B0BSET	FALOAD0
				B0BCLR	FTC0OUT
				B0BSET	FPWM0OUT
				B0BSET	FALOAD1
				B0BCLR	FTC1OUT
				B0BSET	FPWM1OUT
				
		ELSEIF	Duty_Temp == 16
			
				;Set real chip PWM0 output
				B0BSET	FALOAD0
				B0BSET	FTC0OUT
				B0BSET	FPWM0OUT
				B0BSET	FALOAD1
				B0BSET	FTC1OUT
				B0BSET	FPWM1OUT
				
		ELSE
			ECHO	Error: Max_Duty is invalid Max-Duty parameter of @PWM01_MAX_DUTY MACRO
			ECHO	Syntax: @PWM01_MAX_DUTY  Max-Duty
			ECHO	<Max-Duty = 256 Duty from 0/256 to 255/256>
			ECHO	<Max-Duty =  64  Duty from 0/64  to  63/64>
			ECHO	<Max-Duty =  32  Duty from 0/32  to  31/32>			
			ECHO	<Max-Duty =  16  Duty from 0/16  to  15/16>
			ECHO    Example:
			ECHO	@PWM01_MAX_DUTY 256   Configure maximum duty cycle as 256
			ERROR
			ECHO			
		ENDIF	
				
	ENDM

@P00_EDGE	MACRO       VAL
			
		IFNDEF  VAL
			ECHO	Error: @P00_EDGE macro need one parameter
			ECHO	Syntax: @P00_EDGE  EDGE
			ECHO	<EDGE = 1, Rising edge trigger for P0.0 interrupt>
			ECHO 	<EDGE = 2, Falling edge trigger for P0.0 interrupt>
			ECHO 	<EDGE = 3, Level change(Bi-direction) trigger for P0.0 interrupt>
			ECHO    Example:
			ECHO	@P00_EDGE 2   Configure P0.0 interrupt as falling edge trigger
			ERROR
			ECHO
		ENDIF	
			
		IF VAL == 1
		   MOV		A,#00001000B
		   B0MOV	PEDGE,A
		ELSEIF VAL == 2
		   MOV		A,#00010000B
		   B0MOV	PEDGE,A
		ELSEIF VAL == 3
		   MOV		A,#00011000B
		   B0MOV	PEDGE,A
		ELSE
		   ECHO	Error: VAL is invalid parameter of @P00_EDGE macro
		   ECHO	Syntax: @P00_EDGE  EDGE
		   ECHO	<EDGE = 1, Rising edge trigger for P0.0 interrupt>
		   ECHO	<EDGE = 2, Falling edge trigger for P0.0 interrupt>
		   ECHO	<EDGE = 3, Level change(Bi-direction) trigger for P0.0 interrupt>
		   ECHO	Example:
		   ECHO	@P00_EDGE 2   Configure P0.0 interrupt as falling edge trigger
		   ERROR
		   ECHO		        
		ENDIF	
				
	ENDM

endif
