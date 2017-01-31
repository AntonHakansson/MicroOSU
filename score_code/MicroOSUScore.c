// LCD display configuration
sbit LCD_RS at RB4_bit; // RS på LCD: n ansluts till B4 på PIC:en
sbit LCD_EN at RB5_bit; // E(Enable på LCD: n ansluts till B5 på PIC:en

sbit LCD_D4 at RB0_bit; // D4 på LCD: n ansluts till B0 på PIC:en
sbit LCD_D5 at RB1_bit; // D5 på LCD: n ansluts till B1 på PIC:en
sbit LCD_D6 at RB2_bit; // D6 på LCD: n ansluts till B2 på PIC:en
sbit LCD_D7 at RB3_bit; // D7 på LCD: n ansluts till B3 på PIC:en

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
   OSCCON = 0b01110111;            // Oscillator 8 MHz (Oscillator control)
   ANSEL = 0b00000000;             // No analog inputs
   ANSELH = 0b00000000;            // No analog inputs

   TRISA = 0b00000000;
   TRISB = 0b00000000;
   TRISC = 0b00000000;
   PORTA = 0b00000000;
   PORTB = 0b00000000;
   PORTC = 0b00000000;

   // Hardware setup
   Lcd_Init();
   Lcd_Cmd(_LCD_CLEAR);
   Lcd_Cmd(_LCD_CURSOR_OFF);

   LCD_RS = 0;
   Lcd_Cmd(64);
   LCD_RS = 1;

   LCD_Chr_Cp(0b00000000);
   LCD_Chr_Cp(0b00001110);
   LCD_Chr_Cp(0b00011111);
   LCD_Chr_Cp(0b00011111);
   LCD_Chr_Cp(0b00011111);
   LCD_Chr_Cp(0b00001110);
   LCD_Chr_Cp(0b00000000);
   LCD_Chr_Cp(0b00000000);

   LCD_RS = 0;
   LCD_Cmd(128);
   LCD_RS = 1;

   Lcd_Out(1, 1, "Score: ");
   Lcd_Out(1, 8, "1337");

}

void update() {
  /*while(1) {
    LCD_Chr(2, 2, 0);
  }*/
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
