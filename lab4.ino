#include <LiquidCrystal_I2C.h>

// C++ code
//
LiquidCrystal_I2C lcd (32, 16, 2);

char LCD_LANGUAGE = 'E';
const int analogInTmp = A0;
const int analogInMst = A1;
const int buttonPin = 2;
int buttonState = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(analogInTmp, INPUT);
  pinMode(analogInMst, INPUT);
  pinMode(buttonPin, INPUT);
  lcd.init();
  printLocalizedText();
}

void loop()
{
  double rawValueTmp = analogRead(analogInTmp);
  double rawValueMst = analogRead(analogInMst);
  double moisture = rawValueMst / 8.76;
  double voltage = (rawValueTmp / 1023) * 5000; // 5000 to get millivots.
   // 500 is the offset
  double tempC = (voltage-500) * 0.1;
  buttonState = digitalRead(buttonPin);
  if(LCD_LANGUAGE == 'E'){
    double tempF = (tempC * 1.8) + 32; // convert to F
    if(tempF >= 100){
      lcd.setCursor(7, 0);
    }
    else{
      lcd.setCursor(8, 0);
    }
    lcd.print(tempF);
    lcd.setCursor(8, 1);
    lcd.print(moisture);
  }
  else if(LCD_LANGUAGE == 'T'){
    
    lcd.setCursor(8, 0);
    lcd.print(tempC);
    lcd.setCursor(8, 1);
    lcd.print(moisture);
  
  }
  if(buttonState && LCD_LANGUAGE == 'E')
  {	

    LCD_LANGUAGE = 'T';
	printLocalizedText();
  	delay(100); 
  }
  else if(buttonState && LCD_LANGUAGE == 'T'){

    
  	LCD_LANGUAGE = 'E';
    printLocalizedText();
    delay(100);
  }
}

void printLocalizedText(){
  if(LCD_LANGUAGE == 'E')
  {	
    lcd.clear();
    lcd.print("TEM(F):");
    
    lcd.setCursor(0,1);
    lcd.print("HUM(%):");
    
    lcd.setCursor(14, 0);
    lcd.print("EN");
 
  }
  else if(LCD_LANGUAGE == 'T'){
    lcd.clear();
    lcd.print("SIC(C):");
    
    lcd.setCursor(0,1);
    lcd.print("NEM(%):");

    lcd.setCursor(14, 0);
    lcd.print("TR");

  }

}