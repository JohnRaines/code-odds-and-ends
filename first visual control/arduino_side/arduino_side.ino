//Code for changing fan speeds based on 
//
//

#define FANA 3      // fan layout: A D
#define FANB 4      //             B C
#define FANC 5
#define FAND 6
#define XMAX 640    //left = 0, right = 640
#define YMAX 480    //top = 0, bottom = 480


void setup() {
  pinMode(FANA, OUTPUT);
  pinMode(FANB, OUTPUT);
  pinMode(FANC, OUTPUT);
  pinMode(FAND, OUTPUT);
  Serial.begin(9600);
  SerialUSB.begin(9600);
  
}

void loop() {
  int strings;
  int xcord;
  int ycord;
  int hyph;

  
  // put your main code here, to run repeatedly:
  while (SerialUSB.available())
  {
    delay(30);
    if (SerialUSB.available() > 0){
      //read incoming string
      xcord = SerialUSB.read();     //data in form XX-YY
     /* if (SerialUSB.available() > 0)
      {
        ycord = SerialUSB.read();
      }*/
      updateFans(xcord,1);   //update fan speeds
    }
  }
}

void updateFans(int x, int y) {
  Serial.println(String(x) + " " + String(y));
}

