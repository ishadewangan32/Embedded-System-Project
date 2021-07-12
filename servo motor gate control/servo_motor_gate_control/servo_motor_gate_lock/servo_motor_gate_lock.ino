#include <Keypad.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>
LiquidCrystal lcd(9,8,7,6,5,4);
char password[4];
char pass[4],pass1[4];
int i=0;
char customKey=0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char hexaKeys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS] = {A0,A1,A2,A3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A4,A5,3,2};   //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
int led;
int buzzer = 10;
int m11;
int m12;
void setup()
{
  Serial.begin(9600);
  pinMode(11, OUTPUT);

  lcd.begin(16,2);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  
  lcd.setCursor(0,0);
  lcd.print("  DOOR SAFTY  ");
  lcd.setCursor(0,1);
  lcd.print(" KEYPAD LOCK ");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("ISHA");
  lcd.setCursor(0,1);
  lcd.print(" Welcomes U :) ");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("ENTER PASS KEY");
 
  lcd.setCursor(0,1);
  for(int j=0;j<4;j++)
    EEPROM.write(j, j+49);
  for(int j=0;j<4;j++)
    pass[j]=EEPROM.read(j);
}

void loop()
{
  digitalWrite(11, HIGH);
  customKey = customKeypad.getKey();
  if(customKey=='#')
    change();
  if (customKey)
  {
    password[i++]=customKey;
    lcd.print(customKey);
    Serial.print(customKey);
    beep();
    delay(2000);
  }
  if(i==4)
  {
    delay(200);
    for(int j=0;j<4;j++)
      pass[j]=EEPROM.read(j);
    if(!(strncmp(password, pass,4)))
    {
      digitalWrite(led, HIGH);
      beep();
      delay(200);
      lcd.clear();
      lcd.print("Passkey Accepted");
      digitalWrite(11, LOW);
      delay(4000);
      
      lcd.setCursor(0,1);
      lcd.print("#.Change Passkey");     
      delay(2000);
      lcd.clear();
      lcd.print("Enter Passkey:  ");
      lcd.setCursor(0,1);
      i=0;
      digitalWrite(led, LOW);
    }
    else
    {
      digitalWrite(11, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      lcd.clear();
      lcd.print("Access Denied...");    
      lcd.setCursor(0,1);
      lcd.print("#.Change Passkey");      
      delay(1000);
      
      lcd.clear();
      lcd.print("Enter Passkey:");      
      lcd.setCursor(0,1);
      i=0;
      digitalWrite(buzzer, LOW);
    }
  }
}
void change()
{
  int j=0;
  lcd.clear();
  lcd.print("Current Passkey");
  lcd.setCursor(0,1);
  while(j<4)
  {
    char key=customKeypad.getKey();
    if(key)
    {
      pass1[j++]=key;
      lcd.print(key);
      Serial.print(key);
      beep();
    }
    key=0;
  }
  delay(500);

  if((strncmp(pass1, pass, 4)))
  {
    lcd.clear();
    lcd.print("Wrong Passkey...");
    lcd.setCursor(0,1);
    lcd.print("Better Luck Again");
    delay(1000);
  }
  else
  {
    j=0;
    lcd.clear();
    lcd.print("Enter New Passk:");
    lcd.setCursor(0,1);
    while(j<4)
    {
      char key=customKeypad.getKey();
      if(key)
      {
        pass[j]=key;
        lcd.print(key);
        Serial.print(key);
        EEPROM.write(j,key);
        j++;
        beep();
      }
    }
    lcd.print(" Done......");
    delay(1000);
  }
  lcd.clear();
  lcd.print("Enter Ur Passk:");
  lcd.setCursor(0,1);
  customKey=0;
}
void beep()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
}
