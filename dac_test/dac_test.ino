int i = 0;

void setup() {
  // put your setup code here, to run once:
  analogWriteResolution(12);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(DAC1, i);
  delay(10);
  i++;
  if(i > 4095) i = 0;
  

}
