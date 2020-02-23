#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#include "Pushbutton.h"
Pushbutton button(ZUMO_BUTTON);
#define motor1Pin1 2
#define motor1Pin2 3
#define motor2Pin1 4
#define motor2Pin2 5
#define trigPin1 10 // prawy
#define echoPin1 11 // prawy
#define trigPin2 6 // lewy
#define echoPin2 7 // lewy
#define trigPin3 8 // srodek
#define echoPin3 9 // srodek
 
long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;
void setup() 
{
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
display.setTextColor(WHITE);

pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
display.clearDisplay();

display.print("Nacisnij przycisk ");
display.setCursor(0,15); 
display.print("zeby uruchomic.");
display.setCursor(50,30); 
display.print("[OK]");
display.display();
button.waitForButton();
display.clearDisplay();
}

void loop() 
{ 
SonarSensor(trigPin1, echoPin1);
RightSensor = distance;
SonarSensor(trigPin2, echoPin2);
LeftSensor = distance;
SonarSensor(trigPin3, echoPin3);
FrontSensor = distance;
  


//////////////////////////////////////////////////////////////////////////// 
if (FrontSensor<7 && RightSensor<7 && LeftSensor<7)
{
       // display.clearDisplay();
        display.setCursor(10,45); 
        display.print("Ewakuacja");         
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH); 
        delay(250);
}
else if(FrontSensor<=17 && LeftSensor<=17)/// lewy sensor i srodkowy
{ // display.clearDisplay();
        display.setCursor(10,45);
        display.print("w Prawo"); 
        wPrawo();

}
else if(LeftSensor<=13)/// lewy sensor 
{ // display.clearDisplay();
        display.setCursor(10,45);
        display.print("w Prawo"); 
        wPrawo();

}
else if(FrontSensor<=17 && RightSensor<=17)/// prawy sensor i srodkowy
{     // display.clearDisplay();
        display.setCursor(10,45);
        display.print("w Lewo"); 
        wLewo();
        
}
else if(RightSensor<=13)/// prawy sensor 
{     // display.clearDisplay();
        display.setCursor(10,45);
        display.print("w Lewo"); 
        wLewo();
        
}
else if(FrontSensor<=17 && FrontSensor>=0)/// srodkowy - jedz do tylu
{     // display.clearDisplay();
        display.setCursor(10,45);
        display.print("do Tylu"); 
        doTylu();
        
}

else  /// w innym wypadku jedz do przodu
{//display.clearDisplay();
        display.setCursor(10,45); 
        display.print("do Przodu");         
        doPrzodu();
       
}
delay(5); //////// wyswietlanie danych z czujnikow
  display.setCursor(0, 0);
  display.print("<--      ||      -->");
  display.setTextSize(1);
  display.setCursor(10, 25);
  display.print(LeftSensor);
  display.setCursor(50, 25);
  display.print(FrontSensor);
  display.setCursor(90, 25);
  display.print(RightSensor);
  display.display();
}

void SonarSensor(int trigPin,int echoPin)  //////// zliczanie odleglosci
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration/58.2; 
}

void doPrzodu(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH); 
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
}
void doTylu(){
        digitalWrite(motor1Pin1, HIGH); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
        
}
void wLewo(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
}
void wPrawo(){
        digitalWrite(motor1Pin1, HIGH); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
}
