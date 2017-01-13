
_initialize:

;MicroOSUScore.c,6 :: 		void initialize() {
;MicroOSUScore.c,8 :: 		OSCCON = 0b01110111;            // Oscillator 8 MHz (Oscillator control)
	MOVLW      119
	MOVWF      OSCCON+0
;MicroOSUScore.c,9 :: 		ANSEL = 0b00000000;             // No analog inputs
	CLRF       ANSEL+0
;MicroOSUScore.c,10 :: 		ANSELH = 0b00000000;            // No analog inputs
	CLRF       ANSELH+0
;MicroOSUScore.c,12 :: 		TRISA = 0b00000001;
	MOVLW      1
	MOVWF      TRISA+0
;MicroOSUScore.c,13 :: 		TRISB = 0b00000001;
	MOVLW      1
	MOVWF      TRISB+0
;MicroOSUScore.c,14 :: 		TRISC = 0b00000000;
	CLRF       TRISC+0
;MicroOSUScore.c,15 :: 		PORTA = 0b00000000;
	CLRF       PORTA+0
;MicroOSUScore.c,16 :: 		PORTB = 0b00000000;
	CLRF       PORTB+0
;MicroOSUScore.c,17 :: 		PORTC = 0b00000001;
	MOVLW      1
	MOVWF      PORTC+0
;MicroOSUScore.c,19 :: 		OPTION_REG.T0SE = 0; // Choose to work with internal clock
	BCF        OPTION_REG+0, 4
;MicroOSUScore.c,20 :: 		OPTION_REG.T0CS = 0; // Choose to react on low2high edge
	BCF        OPTION_REG+0, 5
;MicroOSUScore.c,21 :: 		INTCON.GIE = 1;      // Enable global interrupt bit
	BSF        INTCON+0, 7
;MicroOSUScore.c,22 :: 		INTCON.T0IE = 1;     // Enable Timer0 overflow interrupt bit
	BSF        INTCON+0, 5
;MicroOSUScore.c,23 :: 		}
L_end_initialize:
	RETURN
; end of _initialize

_main:

;MicroOSUScore.c,27 :: 		void main() {
;MicroOSUScore.c,29 :: 		initialize();
	CALL       _initialize+0
;MicroOSUScore.c,30 :: 		update();
	CALL       _update+0
;MicroOSUScore.c,32 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_update:

;MicroOSUScore.c,34 :: 		void update() {
;MicroOSUScore.c,36 :: 		while(1) {
L_update0:
;MicroOSUScore.c,38 :: 		}
	GOTO       L_update0
;MicroOSUScore.c,39 :: 		}
L_end_update:
	RETURN
; end of _update

_interrupt:
	MOVWF      R15+0
	SWAPF      STATUS+0, 0
	CLRF       STATUS+0
	MOVWF      ___saveSTATUS+0
	MOVF       PCLATH+0, 0
	MOVWF      ___savePCLATH+0
	CLRF       PCLATH+0

;MicroOSUScore.c,41 :: 		void interrupt() {
;MicroOSUScore.c,42 :: 		if(INTCON.T0IE == 1) {
	BTFSS      INTCON+0, 5
	GOTO       L_interrupt2
;MicroOSUScore.c,43 :: 		LEDA1 = ~LEDA1;
	MOVLW      2
	XORWF      PORTA+0, 1
;MicroOSUScore.c,44 :: 		INTCON.T0IE = 0;
	BCF        INTCON+0, 5
;MicroOSUScore.c,45 :: 		}
L_interrupt2:
;MicroOSUScore.c,46 :: 		}
L_end_interrupt:
L__interrupt7:
	MOVF       ___savePCLATH+0, 0
	MOVWF      PCLATH+0
	SWAPF      ___saveSTATUS+0, 0
	MOVWF      STATUS+0
	SWAPF      R15+0, 1
	SWAPF      R15+0, 0
	RETFIE
; end of _interrupt
