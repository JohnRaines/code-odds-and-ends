#include <AutoPID.h>

#include <SPI.h>

#define CS 0
#define CLK 1
#define MOSI 2
int x = 0;
int y = 0;
int xerr = 0;
int yerr = 0;
int xpidout = 0;
int ypidout = 0;
int setpoint = 0;
double Kp = 0;
double Ki = 0;
double Kd = 0;
int incomingByte = 0;   // for incoming serial data

void setup() {
        Serial.begin(9600);
        SerialUSB.begin(9600);     // opens serial port, sets data rate to 9600 bps

        //setup pids
        AutoPID xpid(&xerr(double), &setpoint(double), &xpidout(double), -1000, 1000,Kp,Ki,Kd)
}

void loop() {

        // get x error:
        if (SerialUSB.available() > 0) {
                // read the incoming byte:
                xerr = SerialUSB.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);
        }
        // get y error:
        if (SerialUSB.available() > 0) {
                // read the incoming byte:
                yerr = SerialUSB.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);
        }
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
