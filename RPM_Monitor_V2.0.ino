#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define ENCODEROUTPUT 663 // Pulses per One Complete Rotaion.

const int OPTSEN_A = 3; // optical sensor A connected to pin 3 (external interrupt)
//The sample code for driving one way motor encoder
volatile long encoderValue = 0;
int rpm = 0;
boolean measureRpm = false;

float time;
float angconst = 0.10471;
float angvelo = 0;
float velo = 0;
float mmin = 0;

int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;

unsigned long previousMillis2 = 0;
const long interval2 = 2000;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  EncoderInit(); // Enabling the Interrupt
}

void loop()
{

  unsigned long currentMillis2 = millis();

  // Update RPM value on every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    // Revolutions per minute (RPM) =
    // (total encoder pulse in 1s / motor encoder output) x 60s
    rpm = (float)(encoderValue * 60 / ENCODEROUTPUT);

    // Only update display when there have readings
    if ( rpm > 0) {


      Serial.print(encoderValue);
      Serial.print(" pulse / ");
      Serial.print(ENCODEROUTPUT);
      Serial.print(" pulse per rotation x 60 seconds = ");
      Serial.print(rpm);
      Serial.println(" RPM");

    }

    encoderValue = 0;
  }

  if (currentMillis2 - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis2;
    lcd.clear();
  }

      angvelo = (float) rpm * 0.10471;
      velo = (float) angvelo * 0.10; // add the radius here in meters... its 10 cm currently
      mmin =   (float) velo * 60;

      time = (float) 2.7 / mmin ;

      int hours = time / 60;
      int mins = time - (hours * 60);
      int secs = (time - (hours * 60) - mins) * 60;


      Serial.print("Rate: ");
      Serial.print(mmin, 4);
      Serial.println(" m/min");
      Serial.print("Time to complete 2.7m (min) : ");
      Serial.print(mins);
      Serial.print(":");
      Serial.println(secs);
      
      lcd.setCursor(0, 0);
      lcd.print("T:");
      lcd.setCursor(8, 0);
      lcd.print(mins);
      lcd.setCursor(10, 0);
      lcd.print(":");
      lcd.setCursor(12, 0);
      lcd.print(secs);
      lcd.setCursor(0, 1);
      lcd.print(mmin);
      lcd.setCursor(5, 1);
      lcd.print(" m/min");

}

void EncoderInit()
{
  // Attach interrupt at Optical Encoder sensor A on each rising signal
  attachInterrupt(0, updateEncoder, CHANGE);
}
                  
void updateEncoder()
{
  // Add encoderValue by 1, each time it detects rising signal
  // from hall sensor A
  encoderValue++;
}
