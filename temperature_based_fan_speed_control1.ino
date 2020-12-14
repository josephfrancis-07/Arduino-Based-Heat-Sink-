#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);
int tempPin = A0; // the output pin of TMP36
int sensorInput; 
double dcel;
int fan = 11;// the pin where fan is
int led = 8;
int tempMin = 30; // the temperature to start the fan 0%
int tempMax = 60; // the maximum temperature when fan is at 100%
int fanSpeed;
int fanLCD;

void setup()
{
 lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(tempPin ,INPUT);
  pinMode(fan, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop()
{
  dcel = readTemp(); //function to get the temp in Dcel
  if(dcel < tempMin) // if temp is lower than minimum temp
    {
      fanSpeed = 0; // fan is not spinning
      analogWrite(fan, fanSpeed);
      fanLCD=0;
      digitalWrite(fan, LOW);
     }
  
  if((dcel >= tempMin) && (dcel <= tempMax)) // if temperature is higher than minimum temp
     {
       fanSpeed = dcel;//map(temp, tempMin, tempMax, 0, 100); // the actual speed of fan//map(temp, tempMin, tempMax, 32, 255);
       fanSpeed=4.25*fanSpeed;
       fanLCD = map(dcel, tempMin, tempMax, 0, 100); // speed of fan to display on LCD100
       analogWrite(fan, fanSpeed); // spin the fan at the fanSpeed speed
     }
  
   if(dcel > tempMax) // if temp is higher than tempMax
     {
       digitalWrite(led, HIGH); // turn on led
       analogWrite(fan,255);
       fanLCD=100;
     }
  else // else turn of led
     {
       digitalWrite(led, LOW);
     }
  
  lcd.print("TEMP : ");
  lcd.print(dcel);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("FAN SPEED: ");
  lcd.print(fanLCD); // display the fan speed
  lcd.print("%");  
  delay(200);
  lcd.clear();
}

int readTemp()                 
{
  sensorInput = analogRead(A0);        //read the analog sensor and store it
  dcel = (double)sensorInput / 1024;   //find percentage of input reading//find percentage of input reading
  dcel = dcel * 5;                     //multiply by 5V to get voltage
  dcel = dcel - 0.5;                   //Subtract the offset 
  dcel = dcel * 100;                   //Convert to degrees 
  
  return dcel;
}
    


    
    
   
