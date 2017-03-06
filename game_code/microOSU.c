#define CLOCK_FREQUENCY (8)

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


// TODO: Implement Antons code to interface with keypad
// https://electrosome.com/matrix-keypad-pic-microcontroller/
/* #define KEYPAD_ROWS (3)
#define KEYPAD_COLS (4)

char keypadPort at PortA;
char keypad[KEYPAD_ROWS][KEYPAD_COLS];*/

void initialize();
void update();
int getKeypadValue();

int isButtonDown = 0; // 1 = down, 0 = up

/*
  Keypad layout
  1 2 3
  4 5 6
  7 8 9
  * 0 #
*/
int keypadLayout[] = {
  0b00000000, 0b00010000, 0b00100000,
  0b00110000, 0b01000000, 0b01010000,
  0b01100000, 0b01110000, 0b10000000,
  0b10010000, 0b10100000, 0b10110000
};

void main() {
   initialize();
   while(1) {
     update();
   }
}

void initialize() {

   INTCON = 0;
   OSCCON = 0b01110111;            // Oscillator 8 MHz (Oscillator control)
   ANSEL = 0b00000000;             // No analog inputs
   ANSELH = 0b00000000;            // No analog inputs

   TRISA = 0b00000000;
   TRISB = 0b11111111;
   TRISC = 0b00000000;
   PORTA = 0b00000000;
   PORTB = 0b00000000;
   PORTC = 0b00001111;

   OPTION_REG.T0SE = 0; // Choose to work with internal clock
   OPTION_REG.T0CS = 0; // Choose to react on low2high edge
   INTCON.GIE = 1;   // Enable global interrupt bit
   INTCON.T0IE = 1; // Enable Timer0 overflow interrupt bit

   INTCON.GIE = 1;
   INTCON.RBIE = 1;
   INTCON.RBIF = 0;
   OPTION_REG.NOT_RBPU = 0;

   IOCB.F5 = 1;
   IOCB.F6 = 1;
   IOCB.F7 = 1;

   WPUB.F5 = 1;
   WPUB.F6 = 1;
   WPUB.F7 = 1;

}

void update() {}
void interrupt() {

  // Timer0: Internal interrupt
   if(INTCON.T0IE == 1) {
      INTCON.T0IE = 0;
      PORTC.F0 = ~PORTC.F0;
   }

   // External interrupt
   if(INTCON.RBIF == 1) {
      INTCON.RBIF = 0;
      if(isButtonDown == 0) {
        isButtonDown = 1;
        PORTC = keypadLayout[getKeypadValue()];
      }
      else {
        isButtonDown = 0;
        PORTC = keypadLayout[0];
      }
   }

}

int getKeypadValue() {
  return 7;
  /*char i, j;

  for(i=0; i<keypadRows; i++) {
    PORTB = ~(0b0001000 >> i);
     for(j=0; j<keypadCols; j++) {
      if(PORTB&(0b00100000 << j) == 0) {

      }
     }
  }*/

  /*int i;
  for(i = 0; i < 4; i++) {
    PORTB.F3 = (i != 0 ? 1:0);
    PORTB.F2 = (i != 1 ? 1:0);
    PORTB.F1 = (i != 2 ? 1:0);
    PORTB.F0 = (i != 3 ? 1:0);

    if(PORTB.F5 == 0) { return i*3; }  //inputValue[0][0];
    if(PORTB.F6 == 0) { return 1+i*3; }  //inputValue[0][1];
    if(PORTB.F7 == 0) { return 2+i*3; }  //inputValue[0][2];
  }*/
  
  
  
  return 0;
}