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
  String strings;
  char xcord;
  int ycord;
  int hyph;

  strings = "";  
  for(int i = 0; i < 9; i++){
    if (SerialUSB.available()){
        //read incoming string
        strings += char(SerialUSB.read());     
    }
  }
  updateFans(strings); 
}


void updateFans(String x) {
  int xcord = x.substring(4,6).toInt();
  int ycord = x.substring(7,8).toInt();
  Serial.println(x + " " + String(xcord));
}

