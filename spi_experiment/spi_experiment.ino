#include <SPI.h>
#define SLAVESELECT 2 //chip select pin
int channelB = 0;   //A0 is the output of pot 2
int channelA = 1;   //A1 is the output of pot 1
int cba = 0x11; //command bit for writing to pot A
int cbb = 0x12; //command bit for writing to pot B
int cbx = 0x13; //command bit for writing to both
int pota = 0; //holds the read value of a
int potb = 0; //holds the read value of b


void setup() {
  pinMode (SLAVESELECT, OUTPUT);
  SPI.begin(); //spi initialize
  Serial.begin(9600);// serial init
  delay(10);   //wait for init to do it's magic
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));//start spi communication
  digitalWrite(SLAVESELECT, LOW);
  
  Serial.println("test");
  SPI.transfer(cbx);
  SPI.transfer(0);
}

void loop() {
  //write all possible values to A and read inputs
  /*for(int i = cba; i < 0x11FF; i++)
    {
      SPI.transfer16(i);
      delay(100);
      pota = analogRead(channelA);
      potb = analogRead(channelB);
      Serial.print (pota);
      Serial.print(" ");
      Serial.println(potb);
      
    }*/
  SPI.transfer(cbx);
  SPI.transfer(0x00);
  pota = analogRead(channelA);
  potb = analogRead(channelB);
  Serial.print (pota);
  Serial.print(" ");
  Serial.println(potb);
  delay(1000);
  SPI.transfer(cbx);
  SPI.transfer(0xFF);
  pota = analogRead(channelA);
  Serial.print (pota);
  Serial.print(" ");
  Serial.println(potb);
  delay(1000);
  
}
