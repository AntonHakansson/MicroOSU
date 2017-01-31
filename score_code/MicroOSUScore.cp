#line 1 "C:/Users/Deltagare/Desktop/Google Drive/School/Micro Computer/Ny mapp/MicroOSUScore.c"


void update();
void interrupt();

void initialize() {

 OSCCON = 0b01110111;
 ANSEL = 0b00000000;
 ANSELH = 0b00000000;

 TRISA = 0b00000001;
 TRISB = 0b00000001;
 TRISC = 0b00000000;
 PORTA = 0b00000000;
 PORTB = 0b00000000;
 PORTC = 0b00000001;

 OPTION_REG.T0SE = 0;
 OPTION_REG.T0CS = 0;
 INTCON.GIE = 1;
 INTCON.T0IE = 1;
}

sbit LEDA1 at PORTA.B1;

void main() {

 initialize();
 update();

}

void update() {

 while(1) {

 }
}

void interrupt() {
 if(INTCON.T0IE == 1) {
 LEDA1 = ~LEDA1;
 INTCON.T0IE = 0;
 }
}
