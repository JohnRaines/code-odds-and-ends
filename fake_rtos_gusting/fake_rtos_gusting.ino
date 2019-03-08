//fake rtos operation for chaotic fan gusts
#define FANA 6
#define FANB 4
#define FANC 5
#define FAND 3
#define high 160
#define low 50

int ticks = 0;
bool Atoggle = false;
bool Btoggle = false;
bool Ctoggle = false;
bool Dtoggle = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(FANA, OUTPUT);
  pinMode(FANB, OUTPUT);
  pinMode(FANC, OUTPUT);
  pinMode(FAND, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  ticks = ticks + 5;
  acheck();
  bcheck();
  ccheck();
  dcheck();
  Serial.println(ticks);
}

//functions for gusting the fans
void agust() {
  if (Atoggle){
    analogWrite(FANA,int(low));
  }
  else analogWrite(FANA,int(high));
}

void bgust() {
  if (Btoggle){
    analogWrite(FANB,int(low));
  }
  else analogWrite(FANB,int(high));
}

void cgust() {
  if (Ctoggle){
    analogWrite(FANC,int(low));
  }
  else analogWrite(FANC,int(high));
}

void dgust() {
  if (Dtoggle){
    analogWrite(FAND,int(low));
  }
  else analogWrite(FAND,int(high));
}

//functions for checking if time to adjust
void acheck(){
  if(ticks %2700 == 1){
    Atoggle = false;
    agust();
    //return;
  }
  if(ticks %2700 == 2000){
    Atoggle = true;
    agust();
    //return;
  }
  
}

void bcheck(){
  if(ticks %2700 == 1){
    Btoggle = false;
    bgust();
  }
  if(ticks %2700 == 2000){
    Btoggle = true;
    bgust();
  }
}

void ccheck(){
  if(ticks %3200 == 1){
    Ctoggle = false;
    cgust();
  }
  if(ticks %3200 == 2500){
    Ctoggle = true;
    cgust();
  }
}

void dcheck(){
  if(ticks %4000 == 1){
    Dtoggle = false;
    dgust();
  }
  if(ticks %4000 == 3000){
    Dtoggle = true;
    dgust();
  }
}


