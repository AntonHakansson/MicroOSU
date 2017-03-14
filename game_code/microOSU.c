//#define CLOCK_FREQUENCY (8)
/*
sbit LCD_RS at RB4_bit; // RS på LCD: n ansluts till B4 på PIC:en
sbit LCD_EN at RB5_bit; // E(Enable på LCD: n ansluts till B5 på PIC:en

sbit LCD_D4 at RB0_bit; // D4 på LCD: n ansluts till B0 på PIC:en
sbit LCD_D5 at RB1_bit; // D5 på LCD: n ansluts till B1 på PIC:en
sbit LCD_D6 at RB2_bit; // D6 på LCD: n ansluts till B2 på PIC:en
sbit LCD_D7 at RB3_bit; // D7 på LCD: n ansluts till B3 på PIC:en
*/
// Tell mirco processor how it is connected to the LCD display
/*sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;*/


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

   INTCON = 0b00000000;
   OSCCON = 0b01110111;            // Oscillator 8 MHz (Oscillator control)
   ANSEL = 0b00000000;             // No analog inputs
   ANSELH = 0b00000000;            // No analog inputs

   TRISA = 0b00000000;
   TRISB = 0b11110000;
   TRISC = 0b00000000;
   PORTA = 0b00000000;
   PORTB = 0b00001111;
   PORTC = 0b00000000;

   INTCON.GIE = 1;      // Enable global interrupts
   INTCON.INTE = 1;     // Enable external interrupts
   INTCON.INTF = 0;     // Clear flag
   INTCON.T0IE = 0;     // Enable Timer0 overflow interrupt bit
   INTCON.T0IF = 0;     // Clear flag
   INTCON.RBIE = 1;     // Enable Interrupt on change
   INTCON.RBIF = 0;     // Clear flag

   OPTION_REG.T0CS = 0; // Use internal clock source
   OPTION_REG.PSA = 0;  // Use timer0 PSA
   OPTION_REG.PS2 = 0;  // PSA bit 2
   OPTION_REG.PS1 = 1;  // PSA bit 1
   OPTION_REG.PS0 = 0;  // PSA bit 0

   // Enable interrupt on change for individual pins on port B
   IOCB.F5 = 1;
   IOCB.F6 = 1;
   IOCB.F7 = 1;

}

int counter = 0;

void update() {}
void interrupt() {

  // Timer0: Internal interrupt
   if(INTCON.T0IE == 1) {
      INTCON.T0IE = 0;
      //PORTC.F0 = ~PORTC.F0;
   }

   // External interrupt
   if(INTCON.RBIF == 1) {
     //PORTC = (PORTB & 0b00001111);
     //PORTC = keypadLayout[getKeypadValue()];
     PORTC = keypadLayout[counter % 12];
     counter++;
     /*if(isButtonDown == 0) {
        isButtonDown = 1;
        PORTC = keypadLayout[getKeypadValue()];
      }
      else {
        isButtonDown = 0;
        PORTC = keypadLayout[0];
      }*/
      INTCON.RBIF = 0;
   }

}

int getKeypadValue() {
  int i;
  PORTB = 0b00001111;
  for(i = 0; i < 4; i++) {
    PORTB.F3 = (i != 0 ? 1:0);  // Row 1
    PORTB.F2 = (i != 1 ? 1:0);  // Row 2
    PORTB.F1 = (i != 2 ? 1:0);  // Row 3
    PORTB.F0 = (i != 3 ? 1:0);  // Row 4

    if(PORTB.F5 == 0) { return i*3; }
    if(PORTB.F6 == 0) { return 1+i*3; }
    if(PORTB.F7 == 0) { return 2+i*3; }
  }
  PORTB = 0b00001111;
  return 0;
}
