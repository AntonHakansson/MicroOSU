void initialize();
void update();
int fetchKeypadValue();

int isButtonDown = 0;   // 1 = down, 0 = up

int send[]={0b00000000,0b00010000,0b00100000,
            0b00110000,0b01000000,0b01010000,
            0b01110000,0b10000000,0b10010000};

void main() {
   initialize();
   update();
}

void initialize() {

   OSCCON = 0b01110111;            // Oscillator 8 MHz (Oscillator control)
   ANSEL = 0b00000000;             // No analog inputs
   ANSELH = 0b00000000;            // No analog inputs

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
        /*PORTC.F3 = ~PORTC.F3;
        fetchKeypadValue();*/

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

     /*int line[]={0b00100111,0b00101011,0b00101101,0b00101110,
                 0b01000111,0b01001011,0b01001101,0b01001110,
                 0b10000111,0b10001011,0b10001101,0b10001110};*/
                 
     /*int inputValue[4][3]={{'1','2','3',},
                           {'4','5','6',},
                           {'7','8','9',},
                           {'*','0','#',}};*/
                           
     int i;
     for(i=0;i<4;i++){
         switch (i) {
            case 1: PORTB.F3 = 0;
                    PORTB.F2 = 1;
                    PORTB.F1 = 1;
                    PORTB.F0 = 1;

                    if(PORTB.F5 == 0) { return send[0]; }  //inputValue[0][0];
                    if(PORTB.F6 == 0) { return send[1]; }  //inputValue[0][1];
                    if(PORTB.F7 == 0) { return send[2]; }  //inputValue[0][2];
                    break;

            case 2: PORTB.F3 = 1;
                    PORTB.F2 = 0;
                    PORTB.F1 = 1;
                    PORTB.F0 = 1;

                    if(PORTB.F5 == 0) { return send[3]; }  //inputValue[1][0];
                    if(PORTB.F6 == 0) { return send[4]; }  //inputValue[1][1];
                    if(PORTB.F7 == 0) { return send[5]; }  //inputValue[1][2];
                    break;

            case 3: PORTB.F3 = 1;
                    PORTB.F2 = 1;
                    PORTB.F1 = 0;
                    PORTB.F0 = 1;

                    if(PORTB.F5 == 0) { return  send[6];}  //inputValue[2][0];
                    if(PORTB.F6 == 0) { return  send[7];}  //inputValue[2][1];
                    if(PORTB.F7 == 0) { return  send[8];}  //inputValue[2][2];
                    break;

            case 4: PORTB.F3 = 1;
                    PORTB.F2 = 1;
                    PORTB.F1 = 1;
                    PORTB.F0 = 0;

                    if(PORTB.F5 == 0) { return  send[9];}  //inputValue[3][0];
                    if(PORTB.F6 == 0) { return  send[10];}  //inputValue[3][1];
                    if(PORTB.F7 == 0) { return  send[11];}  //inputValue[3][2];
                    break;
         }
     }

     /***************/
     //PORTB.F3 = 0;
     //PORTB.F2 = 1;
     //PORTB.F1 = 1;
     //PORTB.F0 = 1;
     
     //if(PORTB.F5 == 0) { return 49; }
     //if(PORTB.F6 == 0) { return 50; }
     //if(PORTB.F7 == 0) { return 51; }
     /***************/
     
     /***************/
     //PORTB.F3 = 1;
     //PORTB.F2 = 0;
     //PORTB.F1 = 1;
     //PORTB.F0 = 1;

     //if(PORTB.F5 == 0) { return 52; }
     //if(PORTB.F6 == 0) { return 53; }
     //if(PORTB.F7 == 0) { return 54; }
     /***************/
     
     /***************/
     //PORTB.F3 = 1;
     //PORTB.F2 = 1;
     //PORTB.F1 = 0;
     //PORTB.F0 = 1;

     //if(PORTB.F5 == 0) { return 55; }
     //if(PORTB.F6 == 0) { return 56; }
     //if(PORTB.F7 == 0) { return 57; }
     /***************/
     
     /***************/
     //PORTB.F3 = 1;
     //PORTB.F2 = 1;
     //PORTB.F1 = 1;
     //PORTB.F0 = 0;

     //if(PORTB.F5 == 0) { return 42; }
     //if(PORTB.F6 == 0) { return 48; }
     //if(PORTB.F7 == 0) { return 35; }
     /***************/
     
     return -1;
}