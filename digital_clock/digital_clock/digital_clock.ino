#include<LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup()
{
  lcd.begin(16, 2);// colms, ro
  }
  uint8_t ss = 0, mm = 0, hh = 0;
  // this need some modification// Next time we will get accurate time
  void loop() {
    // time parameters
    ss ++;
    if (ss == 60){
      ss = 0;
      mm ++;
  if (mm == 60){
    mm = 0;
    hh++;
    if (hh == 24){
      hh = 0;
      }
     }
   }
  // Display
  lcd.setCursor(0, 0);
  lcd.print("Digital Clock");
  lcd.setCursor(0, 1);
  if (hh < 10){
    lcd.print(0);
    }
    lcd.print(hh);
    lcd.print(":");
    if (mm < 10){
      lcd.print(0);
      }
      lcd.print(mm);
      lcd.print(":");
  if (ss < 10){
  lcd.print(0);
  }
  lcd.print(ss);
  delay(1000);
}
