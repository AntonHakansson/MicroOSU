sbit LCD_RS at RB4_bit; // RS på LCD: n ansluts till B4 på PIC:en
sbit LCD_EN at RB5_bit; // E(Enable på LCD: n ansluts till B5 på PIC:en

sbit LCD_D4 at RB0_bit; // D4 på LCD: n ansluts till B0 på PIC:en
sbit LCD_D5 at RB1_bit; // D5 på LCD: n ansluts till B1 på PIC:en
sbit LCD_D6 at RB2_bit; // D6 på LCD: n ansluts till B2 på PIC:en
sbit LCD_D7 at RB3_bit; // D7 på LCD: n ansluts till B3 på PIC:en

// Tell mirco processor how it is connected to the LCD display
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
}

void initialize() {

   INTCON = 0;
   OSCCON = 0b01110111;            // Oscillator 8 MHz (Oscillator control)
   ANSEL = 0b00000000;             // No analog inputs
   ANSELH = 0b00000000;            // No analog inputs

   TRISA = 0b11111111;
   TRISB = 0b00000000;
   TRISC = 0b00000000;
   PORTA = 0b00000000;
   PORTB = 0b00000000;
   PORTC = 0b00000000;

   // Hardware setup
   Lcd_Init();
   Lcd_Cmd(_LCD_CLEAR);
   Lcd_Cmd(_LCD_CURSOR_OFF);

   Lcd_Rs = 0;
   Lcd_Cmd(64);
   Lcd_Rs = 1;

   LCD_Chr_Cp(0b00000000);
   LCD_Chr_Cp(0b00001110);
   LCD_Chr_Cp(0b00011111);
   LCD_Chr_Cp(0b00011111);
   LCD_Chr_Cp(0b00011111);
   LCD_Chr_Cp(0b00001110);
   LCD_Chr_Cp(0b00000000);
   LCD_Chr_Cp(0b00000000);

   Lcd_Rs = 1;
}

void update() {
  while(1) {
    LCD_Chr(2, 2, 0);
  }
}
