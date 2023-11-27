#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
//LiquidCrystal(rs, rw, enable, data4, data5, data6, data7)(can be changed)
LiquidCrystal lcd(12, 11, 10, 2, 3, 4, 5);
//RX,TX pins connected to the Barcode scanner(can be changed)
SoftwareSerial QRSerial(8, 7);

int equipmentSensor1 = 9;
int lock1 = 13;
void setup() {
  //start lcd screen(16x2)
  lcd.begin(16, 2);
  //serialmonitors
  Serial.begin(9600);
  QRSerial.begin(9600);
}


void loop() {
  // welcome message
  lcd.clear();
  lcd.print("Welcome  Welkom Scan QR code");
  //barcode scanning
  if (QRSerial.available()) {
    while (QRSerial.available()) {
      char data = QRSerial.read();
      Serial.print(data);
      delay(5);
    }
  }
  //data processing(still needs work)
  bool renting = true;
  int lockernumber = 1;
  char language = 'e';

  //now we act based on the data

  int Sensor = 0;  //only false for testing

  lcd.clear();
  if (language == 'n') {
    lcd.print("locker ");
    lcd.print(lockernumber);
    lcd.setCursor(0, 1);
    lcd.print("gaat open.");
  } else {
    lcd.print("Opening locker  ");
    lcd.print(lockernumber);
  }

  delay(5000);
  //code to open lock on locker
  /*switch(lockernumber){
        case 1:
        digitalwrite(lock1,1); (lockpin to high)
        break;
      /*case 2:
        digitalwrite(lock2,1);
        break:
      }   */


  lcd.clear();
  if (renting == true) {
    if (language == 'n') {
      lcd.print("pak uitrusting  alstublieft.");
    } else {
      lcd.print("Please take     equipment.");
    }
    while (Sensor == 1) {  //while equipment inside
      switch (lockernumber) {
        case 1:
          Sensor = digitalRead(equipmentSensor1);
          break;
          /*case 2:
        Sensor=digitalRead(equipmentSensor2);
        break:*/
      }
      delay(1000)
    }
  } else {
    if (language == 'n') {
      lcd.print("leg uitrusting  terug AUB.");
    } else {
      lcd.print("Please return   equipment.");
    }
    while (Sensor == 0) {  //while no equipent inside
      switch (lockernumber) {
        case 1:
          Sensor = digitalRead(equipmentSensor1);
          break;
          /*case 2:
        Sensor=digitalRead(equipmentSensor2);
        break:*/
      }
      delay(1000)
    }
  }
  lcd.clear();

  if (language == 'n') {
    lcd.print("Sluit deur      alstublieft.");
  } else {
    lcd.print("Please close    locker door.");
  }
  //detect this somehow

  //lock locker
  /*switch(lockernumber){
        case 1:
        digitalwrite(lock1,0); (lockpin to low)
        break;
      /*case 2:
        digitalwrite(lock2,0);
        break:
      }   */
  lcd.clear();
  if (language == 'n') {
    lcd.print("Dankuwel,       veel plezier!");
  } else {
    lcd.print("Thank you,     have fun!");
  }
  delay(10000)
}
