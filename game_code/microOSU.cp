#line 1 "C:/Users/Deltagare/Desktop/Google Drive/School/Micro Computer/microOSU/microOSU.c"


sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;

sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;


sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

void initialize();
void update();


void main() {
 initialize();
 update();
}

void initialize() {

 INTCON = 0;

 ANSEL = 0b00000000;
 ANSELH = 0b00000000;

 TRISA = 0b11111111;
 TRISB = 0b00000000;
 TRISC = 0b00000000;
 PORTA = 0b00000000;
 PORTB = 0b00000000;
 PORTC = 0b00000000;
#line 49 "C:/Users/Deltagare/Desktop/Google Drive/School/Micro Computer/microOSU/microOSU.c"
 Lcd_Init();

 Lcd_Cmd(_LCD_CURSOR_OFF);







 Lcd_Rs = 0;
 Lcd_Cmd(64);
 Lcd_Rs = 1;

 LCD_Chr_Cp(0b00001110);
 LCD_Chr_Cp(0b00010101);
 LCD_Chr_Cp(0b00010001);
 LCD_Chr_Cp(0b00011111);
 LCD_Chr_Cp(0b00010001);
 LCD_Chr_Cp(0b00010001);
 LCD_Chr_Cp(0b00010001);
 LCD_Chr_Cp(0b00000000);

 Lcd_Rs = 1;
}

void update() {
 char i;
 Lcd_Out(1, 1, "HEJ OCH ");
 Lcd_Chr_Cp(0);
 for(i=0; i<5; i++) {
 LCD_Chr(2, i+1, 49+i);
 }
 for(i=0; i<5; i++) {
 LCD_Chr(3, 1+i, 65+i);
 }
 while(1==1) {
 for(i=0; i<16; i++) {
 Lcd_Cmd( (i<=7) ? _LCD_SHIFT_RIGHT : _LCD_SHIFT_LEFT);
 Delay_ms(500);
 }
 }
}
