
_main:

;Lab w.c,11 :: 		void main() {
;Lab w.c,12 :: 		initialize();
	CALL       _initialize+0
;Lab w.c,13 :: 		update();
	CALL       _update+0
;Lab w.c,14 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_initialize:

;Lab w.c,16 :: 		void initialize() {
;Lab w.c,18 :: 		OSCCON = 0b01110111;            // Oscillator 8 MHz (Oscillator control)
	MOVLW      119
	MOVWF      OSCCON+0
;Lab w.c,19 :: 		ANSEL = 0b00000000;             // No analog inputs
	CLRF       ANSEL+0
;Lab w.c,20 :: 		ANSELH = 0b00000000;            // No analog inputs
	CLRF       ANSELH+0
;Lab w.c,22 :: 		TRISA = 0b00000000;
	CLRF       TRISA+0
;Lab w.c,23 :: 		TRISB = 0b11100000;
	MOVLW      224
	MOVWF      TRISB+0
;Lab w.c,24 :: 		TRISC = 0b00000000;
	CLRF       TRISC+0
;Lab w.c,25 :: 		PORTA = 0b00000000;
	CLRF       PORTA+0
;Lab w.c,26 :: 		PORTB = 0b00000000;
	CLRF       PORTB+0
;Lab w.c,27 :: 		PORTC = 0b00000000;
	CLRF       PORTC+0
;Lab w.c,29 :: 		INTCON.GIE = 1;
	BSF        INTCON+0, 7
;Lab w.c,30 :: 		INTCON.RBIE = 1;
	BSF        INTCON+0, 3
;Lab w.c,31 :: 		INTCON.RBIF = 0;
	BCF        INTCON+0, 0
;Lab w.c,32 :: 		OPTION_REG.F7 = 0;
	BCF        OPTION_REG+0, 7
;Lab w.c,34 :: 		IOCB.F5 = 1;
	BSF        IOCB+0, 5
;Lab w.c,35 :: 		IOCB.F6 = 1;
	BSF        IOCB+0, 6
;Lab w.c,36 :: 		IOCB.F7 = 1;
	BSF        IOCB+0, 7
;Lab w.c,38 :: 		WPUB.F5 = 1;
	BSF        WPUB+0, 5
;Lab w.c,39 :: 		WPUB.F6 = 1;
	BSF        WPUB+0, 6
;Lab w.c,40 :: 		WPUB.F7 = 1;
	BSF        WPUB+0, 7
;Lab w.c,41 :: 		}
L_end_initialize:
	RETURN
; end of _initialize

_interrupt:
	MOVWF      R15+0
	SWAPF      STATUS+0, 0
	CLRF       STATUS+0
	MOVWF      ___saveSTATUS+0
	MOVF       PCLATH+0, 0
	MOVWF      ___savePCLATH+0
	CLRF       PCLATH+0

;Lab w.c,43 :: 		void interrupt(){
;Lab w.c,44 :: 		if(INTCON.RBIF == 1) {
	BTFSS      INTCON+0, 0
	GOTO       L_interrupt0
;Lab w.c,45 :: 		INTCON.RBIF = 0;
	BCF        INTCON+0, 0
;Lab w.c,46 :: 		if(isButtonDown == 0) {
	MOVLW      0
	XORWF      _isButtonDown+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt32
	MOVLW      0
	XORWF      _isButtonDown+0, 0
L__interrupt32:
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt1
;Lab w.c,47 :: 		isButtonDown = 1;
	MOVLW      1
	MOVWF      _isButtonDown+0
	MOVLW      0
	MOVWF      _isButtonDown+1
;Lab w.c,51 :: 		PORTC=fetchKeypadValue();
	CALL       _fetchKeypadValue+0
	MOVF       R0+0, 0
	MOVWF      PORTC+0
;Lab w.c,52 :: 		delay_ms(500);
	MOVLW      6
	MOVWF      R11+0
	MOVLW      19
	MOVWF      R12+0
	MOVLW      173
	MOVWF      R13+0
L_interrupt2:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt2
	DECFSZ     R12+0, 1
	GOTO       L_interrupt2
	DECFSZ     R11+0, 1
	GOTO       L_interrupt2
	NOP
	NOP
;Lab w.c,53 :: 		PORTC=0b00000000;
	CLRF       PORTC+0
;Lab w.c,54 :: 		delay_ms(100);
	MOVLW      2
	MOVWF      R11+0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      186
	MOVWF      R13+0
L_interrupt3:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt3
	DECFSZ     R12+0, 1
	GOTO       L_interrupt3
	DECFSZ     R11+0, 1
	GOTO       L_interrupt3
	NOP
;Lab w.c,55 :: 		}
	GOTO       L_interrupt4
L_interrupt1:
;Lab w.c,56 :: 		else { isButtonDown = 0; }
	CLRF       _isButtonDown+0
	CLRF       _isButtonDown+1
L_interrupt4:
;Lab w.c,57 :: 		}
L_interrupt0:
;Lab w.c,59 :: 		}
L_end_interrupt:
L__interrupt31:
	MOVF       ___savePCLATH+0, 0
	MOVWF      PCLATH+0
	SWAPF      ___saveSTATUS+0, 0
	MOVWF      STATUS+0
	SWAPF      R15+0, 1
	SWAPF      R15+0, 0
	RETFIE
; end of _interrupt

_update:

;Lab w.c,61 :: 		void update(){
;Lab w.c,62 :: 		while(1){}
L_update5:
	GOTO       L_update5
;Lab w.c,63 :: 		}
L_end_update:
	RETURN
; end of _update

_fetchKeypadValue:

;Lab w.c,65 :: 		int fetchKeypadValue(){
;Lab w.c,77 :: 		for(i=0;i<4;i++){
	CLRF       R2+0
	CLRF       R2+1
L_fetchKeypadValue7:
	MOVLW      128
	XORWF      R2+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__fetchKeypadValue35
	MOVLW      4
	SUBWF      R2+0, 0
L__fetchKeypadValue35:
	BTFSC      STATUS+0, 0
	GOTO       L_fetchKeypadValue8
;Lab w.c,78 :: 		switch (i) {
	GOTO       L_fetchKeypadValue10
;Lab w.c,79 :: 		case 1: PORTB.F3 = 0;
L_fetchKeypadValue12:
	BCF        PORTB+0, 3
;Lab w.c,80 :: 		PORTB.F2 = 1;
	BSF        PORTB+0, 2
;Lab w.c,81 :: 		PORTB.F1 = 1;
	BSF        PORTB+0, 1
;Lab w.c,82 :: 		PORTB.F0 = 1;
	BSF        PORTB+0, 0
;Lab w.c,84 :: 		if(PORTB.F5 == 0) { return send[0]; }  //inputValue[0][0];
	BTFSC      PORTB+0, 5
	GOTO       L_fetchKeypadValue13
	MOVF       _send+0, 0
	MOVWF      R0+0
	MOVF       _send+1, 0
	MOVWF      R0+1
	GOTO       L_end_fetchKeypadValue
L_fetchKeypadValue13:
;Lab w.c,85 :: 		if(PORTB.F6 == 0) { return send[1]; }  //inputValue[0][1];
	BTFSC      PORTB+0, 6
	GOTO       L_fetchKeypadValue14
	MOVF       _send+2, 0
	MOVWF      R0+0
	MOVF       _send+3, 0
	MOVWF      R0+1
	GOTO       L_end_fetchKeypadValue
L_fetchKeypadValue14:
;Lab w.c,86 :: 		if(PORTB.F7 == 0) { return send[2]; }  //inputValue[0][2];
	BTFSC      PORTB+0, 7
	GOTO       L_fetchKeypadValue15
	MOVF       _send+4, 0
	MOVWF      R0+0
	MOVF       _send+5, 0
	MOVWF      R0+1
	GOTO       L_end_fetchKeypadValue
L_fetchKeypadValue15:
;Lab w.c,87 :: 		break;
	GOTO       L_fetchKeypadValue11
;Lab w.c,89 :: 		case 2: PORTB.F3 = 1;
L_fetchKeypadValue16:
	BSF        PORTB+0, 3
;Lab w.c,90 :: 		PORTB.F2 = 0;
	BCF        PORTB+0, 2
;Lab w.c,91 :: 		PORTB.F1 = 1;
	BSF        PORTB+0, 1
;Lab w.c,92 :: 		PORTB.F0 = 1;
	BSF        PORTB+0, 0
;Lab w.c,94 :: 		if(PORTB.F5 == 0) { return send[3]; }  //inputValue[1][0];
	BTFSC      PORTB+0, 5
	GOTO       L_fetchKeypadValue17
	MOVF       _send+6, 0
	MOVWF      R0+0
	MOVF       _send+7, 0
	MOVWF      R0+1
	GOTO       L_end_fetchKeypadValue
L_fetchKeypadValue17:
;Lab w.c,95 :: 		if(PORTB.F6 == 0) { return send[4]; }  //inputValue[1][1];
	BTFSC      PORTB+0, 6
	GOTO       L_fetchKeypadValue18
	MOVF       _send+8, 0
	MOVWF      R0+0
	MOVF       _send+9, 0
	MOVWF      R0+1
	GOTO       L_end_fetchKeypadValue
L_fetchKeypadValue18:
;Lab w.c,96 :: 		if(PORTB.F7 == 0) { return send[5]; }  //inputValue[1][2];
	BTFSC      PORTB+0, 7
	GOTO       L_fetchKeypadValue19
	MOVF       _send+10, 0
	MOVWF      R0+0
	MOVF       _send+11, 0
	MOVWF      R0+1
	GOTO       L_end_fetchKeypadValue
L_fetchKeypadValue19:
;Lab w.c,97 :: 		break;
	GOTO       L_fetchKeypadValue11
;Lab w.c,99 :: 		case 3: PORTB.F3 = 1;
L_fetchKeypadValue20:
	BSF        PORTB+0, 3
;Lab w.c,100 :: 		PORTB.F2 = 1;
	BSF        PORTB+0, 2
;Lab w.c,101 :: 		PORTB.F1 = 0;
	BCF        PORTB+0, 1
;Lab w.c,102 :: 		PORTB.F0 = 1;
	BSF        PORTB+0, 0
;Lab w.c,104 :: 		if(PORTB.F5 == 0) { return  send[6];}  //inputValue[2][0];
	BTFSC      PORTB+0, 5
	GOTO       L_fetchKeypadValue21
	MOVF       _send+12, 0
	MOVWF      R0+0
	MOVF       _send+13, 0
	MOVWF      R0+1
	GOTO       L_end_fetchKeypadValue
L_fetchKeypadValue21:
;Lab w.c,105 :: 		if(PORTB.F6 == 0) { return  send[7];}  //inputValue[2][1];
	BTFSC      PORTB+0, 6
	GOTO       L_fetchKeypadValue22
	MOVF       _send+14, 0
	MOVWF      R0+0
	MOVF       _send+15, 0
	MOVWF      R0+1
	GOTO       L_end_fetchKeypadValue
L_fetchKeypadValue22:
;Lab w.c,106 :: 		if(PORTB.F7 == 0) { return  send[8];}  //inputValue[2][2];
	BTFSC      PORTB+0, 7
	GOTO       L_fetchKeypadValue23
	MOVF       _send+16, 0
	MOVWF      R0+0
	MOVF       _send+17, 0
	MOVWF      R0+1
	GOTO       L_end_fetchKeypadValue
L_fetchKeypadValue23:
;Lab w.c,107 :: 		break;
	GOTO       L_fetchKeypadValue11
;Lab w.c,109 :: 		case 4: PORTB.F3 = 1;
L_fetchKeypadValue24:
	BSF        PORTB+0, 3
;Lab w.c,110 :: 		PORTB.F2 = 1;
	BSF        PORTB+0, 2
;Lab w.c,111 :: 		PORTB.F1 = 1;
	BSF        PORTB+0, 1
;Lab w.c,112 :: 		PORTB.F0 = 0;
	BCF        PORTB+0, 0
;Lab w.c,114 :: 		if(PORTB.F5 == 0) { return  send[9];}  //inputValue[3][0];
	BTFSC      PORTB+0, 5
	GOTO       L_fetchKeypadValue25
	MOVF       _send+18, 0
	MOVWF      R0+0
	MOVF       _send+19, 0
	MOVWF      R0+1
	GOTO       L_end_fetchKeypadValue
L_fetchKeypadValue25:
;Lab w.c,115 :: 		if(PORTB.F6 == 0) { return  send[10];}  //inputValue[3][1];
	BTFSC      PORTB+0, 6
	GOTO       L_fetchKeypadValue26
	MOVF       _send+20, 0
	MOVWF      R0+0
	MOVF       _send+21, 0
	MOVWF      R0+1
	GOTO       L_end_fetchKeypadValue
L_fetchKeypadValue26:
;Lab w.c,116 :: 		if(PORTB.F7 == 0) { return  send[11];}  //inputValue[3][2];
	BTFSC      PORTB+0, 7
	GOTO       L_fetchKeypadValue27
	MOVF       _send+22, 0
	MOVWF      R0+0
	MOVF       _send+23, 0
	MOVWF      R0+1
	GOTO       L_end_fetchKeypadValue
L_fetchKeypadValue27:
;Lab w.c,117 :: 		break;
	GOTO       L_fetchKeypadValue11
;Lab w.c,118 :: 		}
L_fetchKeypadValue10:
	MOVLW      0
	XORWF      R2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__fetchKeypadValue36
	MOVLW      1
	XORWF      R2+0, 0
L__fetchKeypadValue36:
	BTFSC      STATUS+0, 2
	GOTO       L_fetchKeypadValue12
	MOVLW      0
	XORWF      R2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__fetchKeypadValue37
	MOVLW      2
	XORWF      R2+0, 0
L__fetchKeypadValue37:
	BTFSC      STATUS+0, 2
	GOTO       L_fetchKeypadValue16
	MOVLW      0
	XORWF      R2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__fetchKeypadValue38
	MOVLW      3
	XORWF      R2+0, 0
L__fetchKeypadValue38:
	BTFSC      STATUS+0, 2
	GOTO       L_fetchKeypadValue20
	MOVLW      0
	XORWF      R2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__fetchKeypadValue39
	MOVLW      4
	XORWF      R2+0, 0
L__fetchKeypadValue39:
	BTFSC      STATUS+0, 2
	GOTO       L_fetchKeypadValue24
L_fetchKeypadValue11:
;Lab w.c,77 :: 		for(i=0;i<4;i++){
	INCF       R2+0, 1
	BTFSC      STATUS+0, 2
	INCF       R2+1, 1
;Lab w.c,119 :: 		}
	GOTO       L_fetchKeypadValue7
L_fetchKeypadValue8:
;Lab w.c,165 :: 		return -1;
	MOVLW      255
	MOVWF      R0+0
	MOVLW      255
	MOVWF      R0+1
;Lab w.c,166 :: 		}
L_end_fetchKeypadValue:
	RETURN
; end of _fetchKeypadValue
