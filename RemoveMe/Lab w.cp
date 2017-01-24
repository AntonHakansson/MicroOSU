#line 1 "C:/Users/Deltagare/Documents/HZorn/Microdatatillämpningar/WPU-ION-MKP/Lab w.c"
void initialize();
void update();
int fetchKeypadValue();

int isButtonDown = 0;

int send[]={0b00000000,0b00010000,0b00100000,
 0b00110000,0b01000000,0b01010000,
 0b01110000,0b10000000,0b10010000};

void main() {
 initialize();
 update();
}

void initialize() {

 OSCCON = 0b01110111;
 ANSEL = 0b00000000;
 ANSELH = 0b00000000;

 TRISA = 0b00000000;
 TRISB = 0b11100000;
 TRISC = 0b00000000;
 PORTA = 0b00000000;
 PORTB = 0b00000000;
 PORTC = 0b00000000;

 INTCON.GIE = 1;
 INTCON.RBIE = 1;
 INTCON.RBIF = 0;
 OPTION_REG.F7 = 0;

 IOCB.F5 = 1;
 IOCB.F6 = 1;
 IOCB.F7 = 1;

 WPUB.F5 = 1;
 WPUB.F6 = 1;
 WPUB.F7 = 1;
}

void interrupt(){
 if(INTCON.RBIF == 1) {
 INTCON.RBIF = 0;
 if(isButtonDown == 0) {
 isButtonDown = 1;
#line 51 "C:/Users/Deltagare/Documents/HZorn/Microdatatillämpningar/WPU-ION-MKP/Lab w.c"
 PORTC=fetchKeypadValue();
 delay_ms(500);
 PORTC=0b00000000;
 delay_ms(100);
 }
 else { isButtonDown = 0; }
 }

}

void update(){
 while(1){}
}

int fetchKeypadValue(){
#line 76 "C:/Users/Deltagare/Documents/HZorn/Microdatatillämpningar/WPU-ION-MKP/Lab w.c"
 int i;
 for(i=0;i<4;i++){
 switch (i) {
 case 1: PORTB.F3 = 0;
 PORTB.F2 = 1;
 PORTB.F1 = 1;
 PORTB.F0 = 1;

 if(PORTB.F5 == 0) { return send[0]; }
 if(PORTB.F6 == 0) { return send[1]; }
 if(PORTB.F7 == 0) { return send[2]; }
 break;

 case 2: PORTB.F3 = 1;
 PORTB.F2 = 0;
 PORTB.F1 = 1;
 PORTB.F0 = 1;

 if(PORTB.F5 == 0) { return send[3]; }
 if(PORTB.F6 == 0) { return send[4]; }
 if(PORTB.F7 == 0) { return send[5]; }
 break;

 case 3: PORTB.F3 = 1;
 PORTB.F2 = 1;
 PORTB.F1 = 0;
 PORTB.F0 = 1;

 if(PORTB.F5 == 0) { return send[6];}
 if(PORTB.F6 == 0) { return send[7];}
 if(PORTB.F7 == 0) { return send[8];}
 break;

 case 4: PORTB.F3 = 1;
 PORTB.F2 = 1;
 PORTB.F1 = 1;
 PORTB.F0 = 0;

 if(PORTB.F5 == 0) { return send[9];}
 if(PORTB.F6 == 0) { return send[10];}
 if(PORTB.F7 == 0) { return send[11];}
 break;
 }
 }
#line 165 "C:/Users/Deltagare/Documents/HZorn/Microdatatillämpningar/WPU-ION-MKP/Lab w.c"
 return -1;
}
