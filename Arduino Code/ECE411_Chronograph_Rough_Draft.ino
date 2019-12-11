
  
//LCD Screen and IR Sensor

#include <LiquidCrystal.h>// include the library code
/**********************************************************/
//char array1[]=" Chronograph";  //the string to print on the LCD
//char array2[]="Practicum!";  //the string to print on the LCD

int tim = 100;  //the value of delay time
// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(4, 6, 10, 9, 8, 7);
/*********************************************************/

int ifRead1 = A0;
int ifRead2 = A1;
long start;
long stop1;
float calculated;
long counter;
long counter2;

void setup()
{  
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows
   
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(2, INPUT);
  }
/*********************************************************/

void loop()
{
  ifRead1 = analogRead(A0);
  ifRead2 = analogRead(A1);
  lcd.clear();
  lcd.print("Ready");

  counter = 0;
  counter2 = 0;
  
  while( (analogRead(A0) > (ifRead1/2.0)) && digitalRead(2)==LOW ) 
  {
     ++counter2;
     if (counter2 == 2000)
     {
         lcd.clear();
         lcd.print("Ready");
         lcd.setCursor(0,1);
         lcd.print("S1:");
         lcd.setCursor(3,1);
         lcd.print(analogRead(A0));  // Print a message to the LCD.
         lcd.setCursor(7,1);
         lcd.print("S2:");
         lcd.setCursor(10,1);      
         lcd.print(analogRead(A1));  // Print a message to the LCD.
         counter2 = 0;
     }
  }
  if (digitalRead(2) == LOW)
  {
    lcd.clear();
    start = micros();
    lcd.print("Started...");
    while( ( analogRead(A1) > (ifRead2/2.0) ) && (counter < 35000) && digitalRead(2)==LOW ) 
    {
      counter = counter+1;
    }
      
    lcd.clear();
    if (digitalRead(2) == HIGH)
    {
      lcd.clear();
      lcd.print("Reset...");
      delay(2500);
    }
    else if (counter < 35000)
    {
      stop1 = micros(); 
      calculated = (5.000/12.000) / (((stop1 - start) / 1000000.00));
      lcd.print(calculated);
      lcd.setCursor(5,0);
      lcd.print("FPS");
      delay(2500);
    }    
    else
    {
      lcd.print("error");
      delay(1000);
    }
  
  }
  else
  {
    lcd.clear();
    lcd.print("Reset...");
    delay(1000);
  }
} 

//void loop() 
//{
//   
//   lcd.clear();
//   ifRead1=analogRead(A0); 
//   lcd.print("Sensor 1:       ");
//   lcd.setCursor(10,0);
//   lcd.print(ifRead1);  // Print a message to the LCD.
//   //delay(tim);
//
//   ifRead2=analogRead(A1);
//   lcd.setCursor(0,1);
//   lcd.print("Sensor 2:       ");
//   lcd.setCursor(10,1);
//   lcd.print(ifRead2);  // Print a message to the LCD.
//   delay(tim);
//   
//}

/************************************************************/
