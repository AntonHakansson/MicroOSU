
_main:

;microOSU.c,23 :: 		void main() {
;microOSU.c,24 :: 		initialize();
	CALL       _initialize+0
;microOSU.c,25 :: 		update();
	CALL       _update+0
;microOSU.c,26 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_initialize:

;microOSU.c,28 :: 		void initialize() {
;microOSU.c,30 :: 		INTCON = 0;
	CLRF       INTCON+0
;microOSU.c,32 :: 		ANSEL = 0b00000000;             // No analog inputs
	CLRF       ANSEL+0
;microOSU.c,33 :: 		ANSELH = 0b00000000;            // No analog inputs
	CLRF       ANSELH+0
;microOSU.c,35 :: 		TRISA = 0b11111111;
	MOVLW      255
	MOVWF      TRISA+0
;microOSU.c,36 :: 		TRISB = 0b00000000;
	CLRF       TRISB+0
;microOSU.c,37 :: 		TRISC = 0b00000000;
	CLRF       TRISC+0
;microOSU.c,38 :: 		PORTA = 0b00000000;
	CLRF       PORTA+0
;microOSU.c,39 :: 		PORTB = 0b00000000;
	CLRF       PORTB+0
;microOSU.c,40 :: 		PORTC = 0b00000000;
	CLRF       PORTC+0
;microOSU.c,49 :: 		Lcd_Init();
	CALL       _Lcd_Init+0
;microOSU.c,51 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;microOSU.c,59 :: 		Lcd_Rs = 0;
	BCF        RB4_bit+0, 4
;microOSU.c,60 :: 		Lcd_Cmd(64);
	MOVLW      64
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;microOSU.c,61 :: 		Lcd_Rs = 1;
	BSF        RB4_bit+0, 4
;microOSU.c,63 :: 		LCD_Chr_Cp(0b00001110);
	MOVLW      14
	MOVWF      FARG_Lcd_Chr_CP_out_char+0
	CALL       _Lcd_Chr_CP+0
;microOSU.c,64 :: 		LCD_Chr_Cp(0b00010101);
	MOVLW      21
	MOVWF      FARG_Lcd_Chr_CP_out_char+0
	CALL       _Lcd_Chr_CP+0
;microOSU.c,65 :: 		LCD_Chr_Cp(0b00010001);
	MOVLW      17
	MOVWF      FARG_Lcd_Chr_CP_out_char+0
	CALL       _Lcd_Chr_CP+0
;microOSU.c,66 :: 		LCD_Chr_Cp(0b00011111);
	MOVLW      31
	MOVWF      FARG_Lcd_Chr_CP_out_char+0
	CALL       _Lcd_Chr_CP+0
;microOSU.c,67 :: 		LCD_Chr_Cp(0b00010001);
	MOVLW      17
	MOVWF      FARG_Lcd_Chr_CP_out_char+0
	CALL       _Lcd_Chr_CP+0
;microOSU.c,68 :: 		LCD_Chr_Cp(0b00010001);
	MOVLW      17
	MOVWF      FARG_Lcd_Chr_CP_out_char+0
	CALL       _Lcd_Chr_CP+0
;microOSU.c,69 :: 		LCD_Chr_Cp(0b00010001);
	MOVLW      17
	MOVWF      FARG_Lcd_Chr_CP_out_char+0
	CALL       _Lcd_Chr_CP+0
;microOSU.c,70 :: 		LCD_Chr_Cp(0b00000000);
	CLRF       FARG_Lcd_Chr_CP_out_char+0
	CALL       _Lcd_Chr_CP+0
;microOSU.c,72 :: 		Lcd_Rs = 1;
	BSF        RB4_bit+0, 4
;microOSU.c,73 :: 		}
L_end_initialize:
	RETURN
; end of _initialize

_update:

;microOSU.c,75 :: 		void update() {
;microOSU.c,77 :: 		Lcd_Out(1, 1, "HEJ OCH ");
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr1_microOSU+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;microOSU.c,78 :: 		Lcd_Chr_Cp(0);
	CLRF       FARG_Lcd_Chr_CP_out_char+0
	CALL       _Lcd_Chr_CP+0
;microOSU.c,79 :: 		for(i=0; i<5; i++) {
	CLRF       update_i_L0+0
L_update0:
	MOVLW      5
	SUBWF      update_i_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_update1
;microOSU.c,80 :: 		LCD_Chr(2, i+1, 49+i);
	MOVLW      2
	MOVWF      FARG_Lcd_Chr_row+0
	INCF       update_i_L0+0, 0
	MOVWF      FARG_Lcd_Chr_column+0
	MOVF       update_i_L0+0, 0
	ADDLW      49
	MOVWF      FARG_Lcd_Chr_out_char+0
	CALL       _Lcd_Chr+0
;microOSU.c,79 :: 		for(i=0; i<5; i++) {
	INCF       update_i_L0+0, 1
;microOSU.c,81 :: 		}
	GOTO       L_update0
L_update1:
;microOSU.c,82 :: 		for(i=0; i<5; i++) {
	CLRF       update_i_L0+0
L_update3:
	MOVLW      5
	SUBWF      update_i_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_update4
;microOSU.c,83 :: 		LCD_Chr(3, 1+i, 65+i);
	MOVLW      3
	MOVWF      FARG_Lcd_Chr_row+0
	INCF       update_i_L0+0, 0
	MOVWF      FARG_Lcd_Chr_column+0
	MOVF       update_i_L0+0, 0
	ADDLW      65
	MOVWF      FARG_Lcd_Chr_out_char+0
	CALL       _Lcd_Chr+0
;microOSU.c,82 :: 		for(i=0; i<5; i++) {
	INCF       update_i_L0+0, 1
;microOSU.c,84 :: 		}
	GOTO       L_update3
L_update4:
;microOSU.c,85 :: 		while(1==1) {
L_update6:
;microOSU.c,86 :: 		for(i=0; i<16; i++) {
	CLRF       update_i_L0+0
L_update8:
	MOVLW      16
	SUBWF      update_i_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_update9
;microOSU.c,87 :: 		Lcd_Cmd( (i<=7) ? _LCD_SHIFT_RIGHT : _LCD_SHIFT_LEFT);
	MOVF       update_i_L0+0, 0
	SUBLW      7
	BTFSS      STATUS+0, 0
	GOTO       L_update11
	MOVLW      28
	MOVWF      R0+0
	GOTO       L_update12
L_update11:
	MOVLW      24
	MOVWF      R0+0
L_update12:
	MOVF       R0+0, 0
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;microOSU.c,88 :: 		Delay_ms(500);
	MOVLW      6
	MOVWF      R11+0
	MOVLW      19
	MOVWF      R12+0
	MOVLW      173
	MOVWF      R13+0
L_update13:
	DECFSZ     R13+0, 1
	GOTO       L_update13
	DECFSZ     R12+0, 1
	GOTO       L_update13
	DECFSZ     R11+0, 1
	GOTO       L_update13
	NOP
	NOP
;microOSU.c,86 :: 		for(i=0; i<16; i++) {
	INCF       update_i_L0+0, 1
;microOSU.c,89 :: 		}
	GOTO       L_update8
L_update9:
;microOSU.c,90 :: 		}
	GOTO       L_update6
;microOSU.c,91 :: 		}
L_end_update:
	RETURN
; end of _update
