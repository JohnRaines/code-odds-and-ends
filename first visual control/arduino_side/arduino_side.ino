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

  strings = "999100100";  
 /* for(int i = 0; i < 9; i++){
    if (SerialUSB.available()){
        //read incoming string
        strings += char(SerialUSB.read());     
    }
  }*/
  updateFans(strings); 
}


void updateFans(String x) {
  int xcord = x.substring(3,6).toInt();
  int ycord = x.substring(6,9).toInt();
  if (xcord == 0 && ycord == 0) return;        //return early if garbage packet
  if (x.substring(0,3).toInt() != 999) return;
  if (x.length() != 9) return;
  double xgrad, ygrad;           //describe relative position
  double apow, bpow, cpow, dpow; //percentages of full power
  
  Serial.println(x + " " + String(xcord) + " " +String(ycord));

  xgrad = double(xcord) / double(XMAX);
  ygrad = double(ycord) / double(YMAX);
  dpow = ((xgrad) + (1 - ygrad)) / 2 * 255;
  cpow = (xgrad + ygrad) / 2 * 255;
  apow = ((1 - xgrad) + (1-ygrad)) / 2 * 255;
  bpow = ((1 - xgrad) + ygrad) / 2 * 255;

  //Serial.println(String(apow) + " " + String(dpow));
  //Serial.println(String(bpow) + " " + String(cpow) + "\n");

  //analogWrite(FANA,int(255));
  //analogWrite(FANB,int(255));
  analogWrite(FANC,int(193));
  analogWrite(FAND,int(255));
  
}

