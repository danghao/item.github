
;-------------------------------------------------------------------------------
;	Crt0 For Chip SN8P2612
;-------------------------------------------------------------------------------

CHIP SN8P2612	

IF H == 0
	public H
ENDIF
IF L == 0
	public L
ENDIF
IF X == 0
	public X
ENDIF
public I
public T

public __ClearWatchDogTimer
public __ClrRAM
PUBLIC _sgv_init_entry

Extern CODE _main

;-------------------------------------------------------------------------------
;			Data section
;-------------------------------------------------------------------------------
crt0@data SEGMENT DATA AT 0x00 INBANK
	IF H == 0
		H ds 1
	ENDIF
	IF L == 0
		L ds 1
	ENDIF
	IF X == 0
		X ds 1
	ENDIF
	I ds 1
	T	ds 1

;-------------------------------------------------------------------------------
;			Code section
;-------------------------------------------------------------------------------
crt0@code SEGMENT CODE AT 0x0 INBANK
	ORG	0				;Code section start
	jmp		_sgv_init_entry		;Reset vector
	org 7
	nop

_SGV_INIT_CODE_BEGIN segment CODE  
_sgv_init_entry:
;Initialize STKP
	MOV A,# 0x7F
	B0MOV STKP, A 
	
	CALL __ClearWatchDogTimer;
	CALL __ClrRAM;

; Define a null segment
_SGV_INIT_CODE segment CODE BANK 0x0 INBANK

_SGV_INIT_CODE_END segment CODE

;-------------------------------------------------------------------------------
; Clear Watch dog timer
;-------------------------------------------------------------------------------
	CALL __ClearWatchDogTimer;
	JMP _main	

;-------------------------------------------------------------------------------
; Clear Watch dog timer
;-------------------------------------------------------------------------------
__ClearWatchDogTimer:
	MOV  A, #5AH
	B0MOV  WDTR, A
	RET
	
;-------------------------------------------------------------------------------
; ClrRAM
; Use index @YZ to clear RAM 
;-------------------------------------------------------------------------------

__ClrRAM:

	CLR 		Y
	B0MOV		Z,#0x3f

ClrRAM10:
	CLR 		@YZ
	DECMS		Z
	JMP 		ClrRAM10
	CLR 		@YZ

	RET
