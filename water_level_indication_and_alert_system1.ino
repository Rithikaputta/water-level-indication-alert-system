#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

const int trigPin = 8;
const int echoPin = 7;


const int greenLED = 13;
const int yellowLED = 6;
const int redLED = 4;

long duration;
float distance;

const float tankHeight = 20.0;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  lcd.begin(16,2);
  lcd.print("water level");
  delay(2000);
  lcd.clear();
}

void loop()
{
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  
  distance = duration * 0.034 / 2;

  float waterLevel = tankHeight - distance;

  if (waterLevel < 0)
    waterLevel = 0;

  if (waterLevel > tankHeight)
    waterLevel = tankHeight;

  int percentage = (waterLevel / tankHeight) * 100;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level:");
  lcd.print(percentage);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Dist:");
  lcd.print(distance);
  lcd.print("cm");

  if (percentage < 30)
  {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
  }
  else if (percentage < 70)
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
  }
  else
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
  }

  Serial.print("Water Level: ");
  Serial.print(percentage);
  Serial.println("%");

  delay(1000);
}