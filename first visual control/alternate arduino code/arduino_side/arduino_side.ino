//Code for setting up fan speeds for push pull config
//
//

#define FANA 3      // fan layout: A D
#define FANB 4      //             B C
#define FANC 5
#define FAND 6
#define XMAX 640    
#define YMAX 80    
#define low  255
#define high 160


void setup() {
  pinMode(FANA, OUTPUT);
  pinMode(FANB, OUTPUT);
  pinMode(FANC, OUTPUT);
  pinMode(FAND, OUTPUT);
  Serial.begin(9600);
  SerialUSB.begin(9600);
  
}

void loop() {
  //String strings;
  //char xcord;
  //int ycord;
  //int hyph;

  //strings = "999100100";  
  //analogWrite(FANC,int(175));
  //analogWrite(FAND,int(175));
  //pulser();
  
  //analogWrite(FANA,int(45));
  analogWrite(FANA,int(low));
  analogWrite(FANC,int(low));
  analogWrite(FAND,int(low));
  //delay(3000);
  //analogWrite(FANA,int(high));
  //analogWrite(FANC,int(high));
  //analogWrite(FAND,int(high));
  //delay(1000);
}


void updateFans(String x) {
  analogWrite(FANC,int(128));
  analogWrite(FAND,int(255)); 
}

void pulser(){
  analogWrite(FANC,0);
  analogWrite(FAND,0);
  delay(2000);
  analogWrite(FANC,175);
  analogWrite(FAND,175);
}


