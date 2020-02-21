
// https://www.youtube.com/watch?v=xLUcfeT4EgU
// Keyboard https://playground.arduino.cc/Code/Keypad/

#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

const byte rows = 4; //number of the keypad's rows and columns
const byte cols = 4;

char Keys[rows][cols] = {
  { '1', '2', '3', 'A'},
  { '4', '5', '6', 'B'},
  { '7', '8', '9', 'C'},
  { '*', '0', '#', 'D'}
};

byte rowPins [rows] = {2, 3, 4, 5}; //pins of the keypad
byte colPins [cols] = {6, 7, 8, 9};

Keypad keypad = Keypad( makeKeymap(Keys), rowPins, colPins, 4, 4 );

String input_sec = "";

void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Second");
  lcd.setCursor(5, 1);
  input_sec = "";
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  char whichKey = keypad.getKey();

  if (whichKey != NO_KEY) 
  { 
    lcd.print(whichKey); 
    delay(100);
    if(whichKey == '*' || whichKey == '#' || whichKey == 'A' || whichKey == 'B' || whichKey == 'C')      //define invalid keys
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Invalid Key!");
        delay(1000);
        lcd.clear();
        start_display();
      }
    
    
    else if( whichKey == 'A')
    {
      //Activate
      Serial.println("Re-Activating");     
    }
    else if( whichKey == 'B')
    {
      //Back
      Serial.println("Back one speace");     
    }
    else if( whichKey == 'C')
    {
      //canclel
      Serial.println("Cancel entered second"); 
      enable_output_with_countdown(input_sec.toInt());
    }

    else if( whichKey == 'D')
    {
      //Entering time done
      Serial.println("Starting count down for provided second"); 
      enable_output_with_countdown(input_sec.toInt());
      setup();     
    }
    else    
    {
      //read provided input as number between 1 -9
      input_sec = input_sec +  whichKey ;
      Serial.println(input_sec);
      
    }

    delay(input_sec.toInt());
   }
}

void enable_output_with_countdown(int input_sec){
  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Starting in 5 sec");
  for (int i =3; i > 0; i--)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Starting  " + String(i));   
    delay(1000);  
  }
  
  lcd.clear();
  digitalWrite(12, LOW);

  for (int i = input_sec; i >= 0; i--)
  {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Count down");
    
    lcd.setCursor(5, 1);
    lcd.print(i);
       
    delay(1000);     
  }
  
  digitalWrite(12, HIGH);
  lcd.clear();
  lcd.print("Completed ...");
  delay(2000); 
    
  lcd.clear();
  }

void start_display()
{
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("A:Actvate B:<--");
   lcd.setCursor(0, 1);
   lcd.print("C:Cancel, B:Done");
}
  
void end_display()
{
  
}
