#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SoftwareSerial.h>

float receivedValue;
int latitude;
 
Servo myservo;
SoftwareSerial BTSerial(2, 3);
LiquidCrystal_I2C lcd(0x27,16,2);
 
void setup() {

  lcd.init();  // LCD초기 설정             
  lcd.backlight(); // LCD초기 설정  
  lcd.setCursor(0,0); //텍스트가 LCD에 나타날 위치
  lcd.print("Cydial 1.0"); 
  lcd.setCursor(0,1);
  lcd.print("Ready To Connect"); 

  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.print("Ready");
  myservo.attach(4);
}
 
void loop() {

  if(BTSerial.available())
  {
    lcd.setCursor(0,1);
    lcd.print("Retrieving...   ");
    String data = BTSerial.readString();
    receivedValue = data.toFloat();
    latitude = round(receivedValue);
    lcd.setCursor(0,1);
    lcd.print("Lat: "+data);
    Serial.println("Lat:"+data);
    myservo.write(90-latitude);
  }
}