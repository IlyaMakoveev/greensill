#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "DHT.h"

int buttonState = 0; 
int lastButtonState = 0;
int clickCount = 0;

LiquidCrystal_I2C LCD(0x3F,16,2);
DHT dht(2, DHT11);

void setup() {
   LCD.init();
   LCD.backlight();
   dht.begin();
   pinMode(A1, INPUT);
   Serial.begin(9600);
   pinMode(3, OUTPUT);
   pinMode(4, INPUT_PULLUP);

  int buttonState = 0;
  int lastButtonState = 0;
  int clickCount = 0;
}

void loop() {
   int humidity = dht.readHumidity();
   int temp = dht.readTemperature();
   int potenciom = analogRead(A0);
   int light = analogRead(A2); 
   int dl = map(light, 315, 700, 0, 255);
   int b = map(potenciom, 0, 1023, 0, 255);

   int clickCountPrev = clickCount;
   bool sost = 0;


  buttonState = digitalRead(4);
    if (buttonState == LOW && lastButtonState == HIGH) {
      clickCount++;
      Serial.print("Клики: ");
      Serial.println(clickCount);
    }
    lastButtonState = buttonState; 
  // конец счетчика кноки
  
  if (clickCount % 2 == 0){
    analogWrite(3, b);
  }

  if (clickCount % 2 == 1){
    analogWrite(3, dl);
  }

  LCD.setCursor(0, 0);
  LCD.print("Humidity: ");
  LCD.print(humidity);

  LCD.setCursor(0, 1);
  LCD.print("Temp: ");
  LCD.print(temp);

}