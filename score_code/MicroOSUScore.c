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

int getTemp();
void initialize();
void update();
char getKeypadInput();


void main() {
   initialize();
   while(1) {
     update();
   }
}

void initialize() {

   INTCON = 0;
   OSCCON = 0b01110111;            // Oscillator 8 MHz (Oscillator control)
   ANSEL = 0b11111111;             // No analog inputs
   ANSELH = 0b00000000;            // No ADC converter
   //ADCON0.ADON = 1;
   ADCON1.VCFG0 = 1;

   TRISA = 0b11111111;
   TRISB = 0b00000000;
   TRISC = 0b11110000;
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

   //Lcd_Out(1, 1, "Score: ");
   //Lcd_Out(1, 8, "1337");

}

double temp;
int getTemp() {
  temp = ADC_Read(1) >> 2;
  temp = (temp/1024.0)*5000.0;
  return temp;
  //return temp/10.0;
}
char tempValue[16];
unsigned tempV;
float tempDec;

void update() {
    int pow;
    int i, digit;
    Lcd_Cmd(_LCD_CLEAR);
    
   tempV = ADC_Read(1) >> 2;
   //tempDec = tempV * 0.4706;
   tempDec = tempV * 0.19607;
   tempV = tempDec;
   //tempV /= 1000;
   //tempV = 1397;
   
   FloatToStr(tempDec, tempValue);
   Lcd_Out_Cp(tempValue);
   //Lcd_Out(1, 1, Ltrim(tempValue));
   
   //IntToStr(tempV/10, tempValue);
   //Lcd_Out(1, 1, Ltrim(tempValue));
   //Lcd_Chr_Cp('.');
   //IntToStr(tempV%10, tempValue);
   //Lcd_Out_Cp(Ltrim(tempValue));
   //Lcd_Out_Cp("\xDFC");

   pow = 1000;
   tempV %= 10000;
   for(i = 0; i < 4; i++) {
     digit = tempV / pow;
     Lcd_Chr(2, i+1, digit + '0');
     tempV -= pow * digit;
     pow /= 10;
   }

   /*if(PORTC.F4) Lcd_Chr(4, 1, '1');
   else Lcd_Chr(4, 1, '0');
   if(PORTC.F5) Lcd_Chr(4, 2, '1');
   else Lcd_Chr(4, 2, '0');
   if(PORTC.F6) Lcd_Chr(4, 3, '1');
   else Lcd_Chr(4, 3, '0');
   if(PORTC.F7) Lcd_Chr(4, 4, '1');
   else Lcd_Chr(4, 4, '0');*/

   //Lcd_Chr(4, 6, getKeypadInput());
   delay_ms(1000);
}

char getKeypadInput() {
  if(PORTC == 0b00000000) return '0';
  if(PORTC == 0b00010000) return '1';
  if(PORTC == 0b00100000) return '2';
  if(PORTC == 0b00110000) return '3';
  if(PORTC == 0b01000000) return '4';
  if(PORTC == 0b01010000) return '5';
  if(PORTC == 0b01100000) return '6';
  if(PORTC == 0b01110000) return '7';
  if(PORTC == 0b10000000) return '8';
  if(PORTC == 0b10010000) return '9';
  if(PORTC == 0b10100000) return '#';
  return '?';
}