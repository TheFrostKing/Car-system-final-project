#include <DHT11.h>
#include <Display.h>
#include <TM1637Display.h>

//Thermistor formula
int Vo;
float R1 = 2252;
float logR2, R2, T;
float A = 1.484778004e-03, B = 2.348962910e-04, C = 1.006037158e-07;  // Steinhart-Hart and Hart Coefficients

//MODES
const int NORMAL = 1;
const int HAZARD = 2;
int mode = NORMAL;
const int ON = 1;
const int OFF = 2;
int changeStateLeft = 0; // will define the ON and OFF position of the LEFT blinker
int changeStateRight = 0; // will define the ON and OFF position of the RIGHT blinker

//PINS
const int RED_LED   = 4; // RED LED
const int GREEN_LED   = 5; // GREEN LED
const int BLUE_LED   = 6; // BLUE LED
const int YELLOW_LED   = 7; // YELLOW LED
const int POTMETER = 14;
const int THERMISTOR = 15;
const int RIGHT_BUTTON = 8;
const int LEFT_BUTTON = 9;
const int LDR = 16;

//setting intervals and const

const int RED_INTERVAL = 1000; // ms
const int BLINKER_INTERVAL = 400; // ms
const int YELLOW_INTERVAL = 200; // ms
const int BUTTON_INTERVAL_LEFT_GLOBAL = 40;
const int BUTTON_INTERVAL_RIGHT_GLOBAL = 40;
const int BUTTON_INTERVAL_RIGHT = 50;//ms
const int BUTTON_INTERVAL_LEFT = 50;
const int POT_INTERVAL = 10;
const int THERMISTOR_INTERVAL = 5000;
const int LDR_INTERVAL = 50;
const int UPPER_TH = 400; // THIS VALUE MAY NEED TO BE CHANGED DEPENDING ON THE LIGHT CONDITIONS IN THE BUILDING
const int LOWER_TH = 250; //THIS VALUE MAY NEED TO BE CHANGED DEPENDING ON THE LIGHT CONDITIONS IN THE BUILDING
unsigned long current_time;

//setting times
unsigned long left_btn_time = 0;
unsigned long left_btn_time_global = 0;
unsigned long right_btn_time_global = 0;
unsigned long right_btn_time = 0;
unsigned long rled_time = 0;
unsigned long gled_time = 0;
unsigned long pot_time = 0;
unsigned long thermistor = 0;
unsigned long ldr_time = 0;
unsigned long previousMillis = 0;
unsigned long bled_time = 0;

//setting last state
int red_state = LOW;
int green_state = LOW;
int blue_state = LOW;
int yellow_state = LOW;

//setting potentiometer const
const int POT_LEFT = -1;
const int POT_CENTER = 0;
const int POT_RIGHT = 1;

int leftBtnLast = HIGH;
int rightBtnLast = HIGH;

//bools
bool isLeftBlinkerStopTriggered = false;
bool leftBlinkerTurned = false;
bool isRightBlinkerStopTriggered = false;
bool rightBlinkerTurned = false;
int potValue;
bool isHazardEnabled = false;
bool isDark = false;
bool previousStats = false;

//functions
void BlinkHazard(int ledPin) // toggle RED_LED right turn
{
  if (current_time - previousMillis >= RED_INTERVAL)
  {
    if (isHazardEnabled) {
      // save the last time you blinked the LED
      previousMillis = current_time;
      // if the LED is off turn it on and vice-versa:
      if (red_state == LOW) {
        red_state = HIGH;
      } else {
        red_state = LOW;
      }
    }
  }
  // set the LED with the ledState of the variable:
  digitalWrite(ledPin, red_state);
}

void LeftBlinkerStop() // stops the blinker with rotating the wheel
{
  if (leftBlinkerTurned == true)
  {
    if (potValue == POT_LEFT)
    {
      isLeftBlinkerStopTriggered = true;
    }
    if (potValue > POT_LEFT && isLeftBlinkerStopTriggered == true)
    {
      digitalWrite(BLUE_LED, LOW);
      isLeftBlinkerStopTriggered = false;
      leftBlinkerTurned = false;
      changeStateLeft = OFF;
    }
  }
}

void RightBlinkerStop() // // stops the blinker with rotating the wheel. The logic repeats again here.
{
  if (rightBlinkerTurned == true)
  {
    if (potValue == POT_RIGHT)
    {
      isRightBlinkerStopTriggered = true;
    }
    if (potValue < POT_RIGHT && isRightBlinkerStopTriggered == true)
    {
      digitalWrite(GREEN_LED, LOW);
      rightBlinkerTurned = false;
      changeStateRight = OFF;
      isRightBlinkerStopTriggered = false;
    }
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(RED_LED , OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(LDR, INPUT);
  left_btn_time = millis();
  right_btn_time = millis();
  rled_time = millis();
  gled_time = millis();
  bled_time = millis();
  Display.clear();
}

void loop()
{
  current_time = millis();
  potValue = map(analogRead(POTMETER), 0, 1023, -2, 2);
  const int LEFT_BTN_STATE = digitalRead(LEFT_BUTTON);
  const int RIGHT_BTN_STATE = digitalRead(RIGHT_BUTTON);
  int ldrValue = analogRead(LDR);
  if (Serial.available())
  {
    String dataTransferred = Serial.readStringUntil('\n');
    {
      if ( dataTransferred == "NORMAL") //checks for the string NORMAL in the serial monitor
      {
        mode = NORMAL;

      }
      else if (dataTransferred == "HAZARD") //checks for the string HAZARD in the serial monitor
      {
        mode = HAZARD;
      }
    }
  }

  if ((current_time - pot_time ) > POT_INTERVAL)  //POTMETER
  {
    RightBlinkerStop();
    LeftBlinkerStop();
    pot_time = current_time;
  }

  if (mode == HAZARD)  //  HAZARD mode
  {
    isHazardEnabled = true;
    BlinkHazard(RED_LED);
    BlinkHazard(GREEN_LED);
    BlinkHazard(BLUE_LED);
  }

  if ((current_time - ldr_time) > LDR_INTERVAL) //headlights
  {
    if (ldrValue > UPPER_TH)    //applying hysteresis, using two tresholds to remove oscillation
    {
      isDark = false;
      if (isDark != previousStats)  // using state detections which I learned from the buttons so when I change a state it would register a change on the program
      {
        if (!isDark)
        {
          digitalWrite(YELLOW_LED, LOW);
          Serial.println("HdlOFF");    // sending a message to the APP
        }
        previousStats = isDark;
      }
    }

    if (ldrValue < LOWER_TH)           // ldr check previous state so it send a message only when change has occured
    {
      isDark = true; 
      if (isDark != previousStats)
      {
        if (isDark)
        {
          digitalWrite(YELLOW_LED, HIGH);
          Serial.println("HdlON");
        }
        previousStats = isDark;
      }
    }
    ldr_time = current_time;
  }

  if ((current_time - left_btn_time_global) > BUTTON_INTERVAL_LEFT_GLOBAL)
  {
    if (LEFT_BTN_STATE != leftBtnLast)
    {
      if (LEFT_BTN_STATE == LOW)
      {
        changeStateLeft++;
        changeStateLeft = changeStateLeft % 3;
        changeStateRight = OFF;  // turning off the right indicator if on
        if (changeStateLeft == 0)
        {
          changeStateLeft = ON;
        }
        if (changeStateLeft == ON)
        {
          Serial.println("Left");
        }
      }
      leftBtnLast = LEFT_BTN_STATE;
    }
    left_btn_time_global = current_time;
  }

  if ((current_time - right_btn_time_global) > BUTTON_INTERVAL_RIGHT_GLOBAL)
  {
    if (RIGHT_BTN_STATE != rightBtnLast)
    {
      if (RIGHT_BTN_STATE == LOW)
      {
        changeStateLeft = OFF; //turning off the left indicator if on
        changeStateRight++;
        changeStateRight = changeStateRight % 3;
        if (changeStateRight == 0)
        {
          changeStateRight = ON;
        }
        if (changeStateRight == ON)
        {
          Serial.println("Right");
        }
      }
      rightBtnLast = RIGHT_BTN_STATE;
    }
    right_btn_time_global = current_time;
  }

  if ((current_time - thermistor ) > THERMISTOR_INTERVAL) // applying the thermistor which has 5sec refresh rate
  {
    Vo = analogRead(THERMISTOR);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (A + B * logR2 + C * logR2 * logR2 * logR2));
    T =  T - 273.15;
    Serial.print("Temp: ");
    Serial.println(T);
    thermistor = current_time;
  }

  if (mode == NORMAL)                //Normal Mode
  {
    isHazardEnabled = false;
    digitalWrite(RED_LED, LOW);

    if (rightBlinkerTurned == true)       //blink right
    {
      if (current_time - gled_time >= BLINKER_INTERVAL)
      {
        // save the last time you blinked the LED
        gled_time = current_time;
        // if the LED is off turn it on and vice-versa:
        if (green_state == LOW) {
          green_state = HIGH;
        } else {
          green_state = LOW;
        }
        // set the LED with the ledState of the variable:
        digitalWrite(GREEN_LED, green_state);
      }
    }

    if (leftBlinkerTurned == true)       //blink left
    {
      if (current_time - previousMillis >= BLINKER_INTERVAL)
      {
        // save the last time you blinked the LED
        previousMillis = current_time;
        // if the LED is off turn it on and vice-versa:
        if (blue_state == LOW) {
          blue_state = HIGH;
        } else {
          blue_state = LOW;
        }
        // set the LED with the ledState of the variable:
        digitalWrite(BLUE_LED, blue_state);
      }
    }

    if ((current_time - left_btn_time ) > BUTTON_INTERVAL_LEFT) // LEFT
    {
      if (changeStateLeft == ON) {
        leftBlinkerTurned = true;
        changeStateRight = OFF;      // turn off right
        if (rightBlinkerTurned == true)
        {
          digitalWrite(GREEN_LED, LOW);
          rightBlinkerTurned = false;
        }
      }
      else
      {
        digitalWrite(BLUE_LED, LOW);
        leftBlinkerTurned = false;
      }
      // Reset for next interval.
      left_btn_time = current_time;
    }

    if ((current_time - right_btn_time ) > BUTTON_INTERVAL_RIGHT) // RIGHT
    {

      if (changeStateRight == ON)
      {
        rightBlinkerTurned = true;
        changeStateLeft = OFF; // turn off left
        leftBlinkerTurned = false;
      }
      else {
        digitalWrite(GREEN_LED, LOW);
        rightBlinkerTurned = false;
      }
      right_btn_time = current_time;
    }
  }
}
