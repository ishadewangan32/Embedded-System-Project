#include<Keypad.h>
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'c','0','=','+'}
};

byte rowPins[ROWS] = {2,3,4,5}; 
byte colPins[COLS] = {6,7,8,9}; 
int i=0;
double d=0,result=0;
char arr[10], prev_key=0;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup(){
   Serial.begin(9600);
}
void loop(){
  char key = keypad.getKey();
  
  if (key){
     Serial.print(key);
     if(key == '+' || key == '-' || key == '*' || key == '/')
     {
        if(prev_key==0)
          result=atol(arr);
        i=0;  
     }
     else
     {
       arr[i++]=key;
       arr[i]=NULL;
     }
     
     if(key == '+' || key == '-' || key == '*' || key == '/')
     { 
        calculate(prev_key);
        prev_key=key;  
     }
      
     if(key == '=')
     {
       calculate(prev_key);
       d=(long int)result;
       if(d==result)
       {
         Serial.println(result,0); 
       }
       else
       {
         Serial.println(result);        
       }
       arr[0]=NULL;
     }

     if(key == 'c')
     {
      Serial.println(" ");
     }
  }
}
  int calculate(char ch)
  {
   switch(ch){
    case '+':
     result=result+atol(arr);
     break;
    case '-':
     result=result-atol(arr);
     break; 
    case '*':
     result=result*atol(arr);
     break; 
    case '/':
     result=result/atol(arr);
     d=1;
     break; 
     case 'c':
      result=0;
      arr[0]=NULL;
      i=0;
      prev_key=0;
     break;
     default:
      int j=0;
   }
  }
