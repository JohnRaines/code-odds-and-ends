#define OUT 3

void setup() {
  // put your setup code here, to run once:
  pinMode(OUT, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  for (byte i=0; i < 255; i++)
  {
    analogWrite(OUT, 255);
    Serial.println(i);
    delay(500);
  }

}
