#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "DHT.h"
#include <Ethernet.h>




LiquidCrystal_I2C LCD(0x3F,16,2);
DHT dht(2, DHT11);

void setup() {
   LCD.init();
   LCD.backlight();
   dht.begin();
     pinMode(A1, INPUT);
        Serial.begin(9600);
     pinMode(3, OUTPUT);
     pinMode(4, INPUT);

}

void loop() {
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   int p = analogRead(A0);
   int l = analogRead(A2);
   bool button = digitalRead(4);
   static bool buttonp = 0;

   int dl = map(l, 315, 700, 0, 255);
   int b = map(p, 0, 1023, 0, 255);

   if (button == HIGH && !buttonp) {
      buttonp = !buttonp;
      delay(50); 
   }

   if (buttonp) {
      analogWrite(3, b);
      Serial.println("B");
   } else {
      analogWrite(3, dl);
      Serial.println("A");
   }

   LCD.setCursor(0, 0);
   LCD.print("Humidity: ");
   LCD.print(h);

   LCD.setCursor(0, 1);
   LCD.print("Temp: ");
   LCD.print(t);

   int sol = analogRead(A1);
   Serial.print("sol = ");
   Serial.println(sol);

   delay(30);
   LCD.clear();
}