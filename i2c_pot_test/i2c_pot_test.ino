#include <Wire.h>

#define CS 0
#define CLK 1
#define MOSI 2
int x = 0;
int y = 0;

void setup() {
   //pinMode(CS, OUTPUT);
   pinMode(CLK, OUTPUT);
   pinMode(MOSI, OUTPUT);
   digitalWrite(CLK, LOW);
   Serial.begin(9600);
}

void loop() {
  mcpWrite(1,0);

  //loop pot 0
  for(byte i = 0; i<171; i++)
  {
    mcpWrite(0,i);
    delay(100);
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
  for(byte i = 0; i<171; i++)
  {
    mcpWrite(1,i);
    delay(100);
    x = analogRead(1);
    y = analogRead(0);
    Serial.print(i);
    Serial.print(" ");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
  }

  //loop both
  for(byte i = 0; i<171; i++)
  {
    mcpWrite(7,i);
    delay(100);
    x = analogRead(1);
    y = analogRead(0);
    Serial.print(i);
    Serial.print(" ");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
  }
}

void mcpWrite(byte pot, byte value){
  digitalWrite(CS, LOW);
  transferSPI(B01010000); //start byte
  transferSPI(B10101000 | pot);//potbyte
  transferSPI(value);
  digitalWrite(CS, HIGH);
}

void transferSPI(byte data) {
  for (byte i=1; i<=8; i++) {
    digitalWrite(MOSI, (data >> (8-i)) & 1 ? HIGH : LOW);
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
  digitalWrite(CLK, HIGH);
  digitalWrite(CLK, LOW);
}
