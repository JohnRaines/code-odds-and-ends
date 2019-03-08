//Pin connected to SRCLK of 74HC595

int clockPin = 5;

//Pin connected to RCLK of 74HC595

int latchPin = 6;

////Pin connected to SER of 74HC595

int dataPin = 7;







void setup() {

  // put your setup code here, to run once:

  pinMode(latchPin, OUTPUT);

  pinMode(clockPin, OUTPUT);

  pinMode(dataPin, OUTPUT);


}



void loop() {

  int x;

  int y;

  // put your main code here, to run repeatedly:

  

  for(x = 0; x <=255; x++) {

  digitalWrite(latchPin, 0);

  shiftOut(x);

  digitalWrite(latchPin, 1);

  delay(1000);

  }



  while(true) {

       y = 5;

  }

  

}



void shiftOut(byte myDataOut) {

  int i = 0;

  int pinState; 

  

  //initially write 0 to the data and clock pin

  digitalWrite(dataPin, 0);

  digitalWrite(clockPin, 0);
  delay(10);

  

  for (i = 7; i >=0; i--) { //iterate 8 bits of a byte data

    digitalWrite(clockPin, 0); //falling clock edges
    delay(10);

    

    if (myDataOut & (1 << i)) { //find if i-th bit of a byte data is low or high

      pinState = 1;

    }

    else {

      pinState = 0;

    }

    

    //Shift a bit per clock-pin cycle    

    digitalWrite(dataPin, pinState);
    delay(10);
    digitalWrite(clockPin, 1); //rising clock edge
    delay(10);
    digitalWrite(dataPin, 0);
    delay(10);
  }

  //Stop shifting

  digitalWrite(clockPin, 0);
  delay(10);

}
