#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

/*LiquidCrystal_I2C lcd(0x3F, 20, 4);  // set the LCD address to 0x3F for a 16 chars and 2 line display
RTC_DS3231 rtc;*/

// make some custom characters:

void comecarLcd() {
  Serial.begin(115200);
  rtc.begin();
  lcd.init();
  // Make sure backlight is on
  lcd.backlight();

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Clears the LCD screen
  lcd.clear();

  // Print a message to the lcd.
}

// Print All the custom characters
void updateLcd() {
  DateTime now = rtc.now();
  lcd.setCursor(9, 3);
  lcd.print("Time->");
  if(now.hour() < 10){
    lcd.print("0");
  }
  lcd.print(now.hour());
  lcd.print(":");
  if(now.minute() < 10){
    lcd.print("0");
  }
  lcd.print(now.minute());
  delay(1000);
}