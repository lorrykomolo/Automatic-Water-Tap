#define echoPinC 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinC 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPinL 4 // attach pin D4 Arduino to pin Echo of HC-SR04
#define trigPinL 5 //attach pin D5 Arduino to pin Trig of HC-SR04
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// set the LCD address to 0x27 for a 16 chars and 2 line display
//connect lcd sda to A4 amd scl to A5
LiquidCrystal_I2C lcd(0x27,16,2);
int RelayPin = 6;
long durationC;
long durationL;
int distanceC;
int distanceCM;
int distanceL;
int distanceLM;
int fillLevel;
void setup() {
  lcd.init(); // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.clear();
  pinMode(trigPinC, OUTPUT);
  pinMode(echoPinC, INPUT); 
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  // Set RelayPin as an output pin
  pinMode(RelayPin, OUTPUT); 
  Serial.begin(9600);
  Serial.println("Ultrasonic Sensor HC-SR04 Test");
  Serial.println("with Arduino UNO R3");
}
void loop() {
  //code for hight of container
  digitalWrite(trigPinC, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinC, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinC, LOW);
  durationC = pulseIn(echoPinC, HIGH);
  // Calculating the distance
  distanceC = durationC * 0.034 / 2;
  distanceCM=map(distanceC,3,50,100,0);
  Serial.print("Hight of container: ");
  if(distanceCM<=100){
  Serial.print(distanceCM);
  Serial.println("%");}
  else{
  Serial.println(distanceCM=100);
    }
  //code for waterlevel
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  // Calculating the distance
  distanceL = durationL * 0.034 / 2;
  Serial.print("Remaining Can Capacity: ");
  if(distanceL<=100){
  Serial.print(distanceL);
  Serial.println("%");}
  else{
  Serial.println(distanceL=100);
    }
  fillLevel=distanceCM-distanceL;
  Serial.print("Fill Level= ");
  Serial.print(fillLevel);
  Serial.println("%");
  delay(1500);
  // Let's turn on the relay...
  if (fillLevel<95){
  digitalWrite(RelayPin, LOW);
  delay(100);
  Serial.println("on");
  lcd.setCursor(0,0);
  lcd.print("Tap ON  ");
  lcd.setCursor(0,1);
  lcd.print("Filling    %");
  lcd.setCursor(8,1);
  lcd.print(fillLevel);
  }
  else{
  // Let's turn off the relay...
  digitalWrite(RelayPin, HIGH);
  delay(100);
  lcd.clear();
  Serial.println("off");
  lcd.setCursor(0,0);
  lcd.print("Tap OFF");
  }
}
