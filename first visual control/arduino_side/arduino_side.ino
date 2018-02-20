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
  char xcord;
  int ycord;
  int hyph;

  void updateFans(char,int);
  
  // put your main code here, to run repeatedly:
  if (SerialUSB.available())
  {
      //read incoming string
      xcord = SerialUSB.read();     
      updateFans(xcord,1);   //update fan speeds
     /* if (SerialUSB.available() > 0)
      {
        ycord = SerialUSB.read();
      }*/
    }
   
}


void updateFans(char x, int y) {
  Serial.println(String(x) + " " + String(y));
}

