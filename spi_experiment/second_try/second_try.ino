#include <SPI.h>


#define CS 0
#define CLK 1
#define MOSI 2
int x = 0;
int y = 0;
int i = 0;

void setup() {
   pinMode(CS, OUTPUT);
   pinMode(CLK, OUTPUT);
   pinMode(MOSI, OUTPUT);
   digitalWrite(CLK, LOW);
   SPI.begin();
   Serial.begin(9600);
  //mcpWrite(3,255);
}


void loop() {
  /*
  //loop pot 2
  for(byte i = 0; i<255; i++)
  {
    mcpWrite(2,i);
    delay(500);
    x = analogRead(1);
    y = analogRead(0);
    Serial.print(i);
    Serial.print(" ");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
  }

  mcpWrite(2,0);
  
  //loop pot 1
  for(byte i = 0; i<255; i++)
  {
    mcpWrite(1,i);
    delay(500);
    x = analogRead(1);
    y = analogRead(0);
    Serial.print(i);
    Serial.print(" ");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
  }
*/
  //loop both
  for(byte i = 90; i<255; i++)
  {
    mcpWrite(3,255);
    delay(2500);
    x = analogRead(1);
    y = analogRead(0);
    Serial.print(i);
    Serial.print(" ");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
  }
  
}

void keyPressed()
  {
    mcpWrite(3,i);
    delay(1500);
    x = analogRead(1);
    y = analogRead(0);
    Serial.print(i);
    Serial.print(" ");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
    i++;
  }

void mcpWrite(byte pot, byte value){
  digitalWrite(CS, LOW);
  transferSPI((pot & B11) | B00010000);
  transferSPI(value);
  digitalWrite(CS, HIGH);
}

void transferSPI(byte data) {
  for (byte i=1; i<=8; i++) {
    digitalWrite(MOSI, (data >> (8-i)) & 1 ? HIGH : LOW);
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
}


