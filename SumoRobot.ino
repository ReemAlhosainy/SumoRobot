// mot1 is on the right and mot3 is on the left
int mot1 = 6;
int mot2 = 5;
int mot3 = 11;
int mot4 = 10;
const int IRsensor0 = 9;    //front
const int IRsensor1 = 7;    //back
int ECHO=12;int TRIG=13;long dur;int dist;

// sumo rules require 5 seconds of waiting
const int wait_time=5000;
 int readULTRASONICsensor()
{
  // clears the trigpin condition
 digitalWrite(TRIG,LOW);
 delayMicroseconds(2);
 // sets the trigpin HIGH (ACTIVATE) for 10 microseconds
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  //Reads the echopin,returns the speed wave travel time in microseconds
  dur=pulseIn(ECHO,HIGH);
  //Calculating the distance 
  dist=dur*0.034/2; //speed of sound wave divided by 2 (go & back)
  //display distance for checking
  //Serial.println(dist);
  return dist;
}
void setup() {
  // put your setup code here, to run once:
  pinMode(IRsensor0, INPUT);
  pinMode(IRsensor1, INPUT);
  pinMode(ECHO,      INPUT);
  pinMode(TRIG,     OUTPUT);
  pinMode(mot1,     OUTPUT);
  pinMode(mot2,     OUTPUT);
  pinMode(mot3,     OUTPUT);
  pinMode(mot4,     OUTPUT);
  //for checking
 Serial.begin(9600);
 delay(5000);
}
void loop() 
{
  int d= readULTRASONICsensor();
  Serial.println(d);
  // put your main code here, to run repeatedly:
  readIRsensors();
 if(d>50)
 {
  search();
 }
 else
 {
  motorstoop();
  delay(20);
  attack(d);
 }
}
void motorright()
{
  digitalWrite(mot1, 0);
  digitalWrite(mot2, 1);
  digitalWrite(mot3, 1);
  digitalWrite(mot4, 0); 
}
void motorleft()
{
  digitalWrite(mot1, 1);
  digitalWrite(mot2, 0);
  digitalWrite(mot3, 0);
  digitalWrite(mot4, 1); 
}
void motorstoop()
{
  digitalWrite(mot1, 0);
  digitalWrite(mot2, 0);
  digitalWrite(mot3, 0);
  digitalWrite(mot4, 0); 
}
void motorforward()
{
  digitalWrite(mot1, 1);
  digitalWrite(mot2, 0);
  
  digitalWrite(mot3, 1);
  digitalWrite(mot4, 0); 
}
void motorbackward()
{
  digitalWrite(mot1, 0);
  digitalWrite(mot2, 1);
  digitalWrite(mot3, 0);
  digitalWrite(mot4, 1); 
}
void search()
{
  readIRsensors();
  motorright();
  delay(80);
  int d=readULTRASONICsensor();
  while (d>50)
  {
    motorforward();
    delay(50);
    d=readULTRASONICsensor();
    readIRsensors();
    motorleft();
    delay(20);
  }
}
void attack(int d)
{ 
  motorforward();
  if(readULTRASONICsensor()<d)
  {
    //Serial.println("attack");
    d=readULTRASONICsensor();
    attack(d);
  }
  else
  {
    search();
  }
}
void readIRsensors()
{
  int FrontSen=digitalRead(IRsensor0);
  Serial.println(FrontSen);
  delay(500);
  int BackSen =digitalRead(IRsensor1);
  Serial.println(BackSen);
  delay(500);
  //if back sensor reads black the robot must move forward
  //white=0;black=1
  if(BackSen==0)
  {
        Serial.println("Forward");
    motorforward();
    delay(100);
    motorleft();
    delay(20);
  }
  //if front sensor reads black the robot must move Backward
 else if(FrontSen==0)
  {
        Serial.println("backward");

    motorbackward();

    motorleft();
    delay(20);
  }
  
}
