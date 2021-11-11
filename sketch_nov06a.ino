#include <DHT11.h>
#include <Display.h>
#include <TM1637Display.h>

const int RED_LED   = 4; // RED LED
const int GREEN_LED   = 5; // GREEN LED
const int BLUE_LED   = 6; // BLUE LED
const int YELLOW_LED   = 7; // YELLOW LED
const int POTMETER = 14;
const int RIGHT_BUTTON = 8;
const int LEFT_BUTTON = 9;
const int LDR = 16;
const int UPPER_TH = 300; // THIS VALUES MAY NEED TO BE CHANGED DEPENDING ON THE LIGHT CONDITIONS IN THE BUILDING
const int LOWER_TH = 200; //THIS VALUES MAY NEED TO BE CHANGED DEPENDING ON THE LIGHT CONDITIONS IN THE BUILDING
//setting intervals
unsigned long previousMillis = 0;

const int RED_INTERVAL = 380; // ms
const int GREEN_INTERVAL = 600; // ms
const int BLUE_INTERVAL = 360; // ms
const int YELLOW_INTERVAL = 200; // ms
const int BUTTON_INTERVAL = 300;
const int BUTTON_INTERVAL_RIGHT = 50;//ms
const int BUTTON_INTERVAL_LEFT = 50;
const int POT_INTERVAL = 10;

//setting times
unsigned long left_btn_time = 0;
unsigned long right_btn_time = 0;
unsigned long rled_time = 0;
unsigned long gled_time = 0;
unsigned long bled_time = 0;
unsigned long yled_time = 0;
unsigned long pot_time = 0;

//setting last state
int red_state = LOW;
int green_state = LOW;
int blue_state = LOW;
int yellow_state = LOW;

int changeState = 0;
const int ON = 1;
const int OFF = 2;
//setting potentiometer const
const int POT_LEFT = -1;
const int POT_CENTER = 0;
const int POT_RIGHT = 1;
unsigned long current_time;
int leftBtnLast = HIGH;
int rightBtnLast = HIGH;
//functions


//bools
bool isLeftBlinkerStopTriggered = false;
bool leftBlinkerTurned = false;
bool isRightBlinkerStopTriggered = false;
bool rightBlinkerTurned = false;
int potValue;

void LeftBlinker() // stops the blinker with rotating the wheel
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
      changeState = 2;
    }
  }
}

void RightBlinker()
{
  if (rightBlinkerTurned == true)
  {
    if (potValue == POT_RIGHT)
    {
      isRightBlinkerStopTriggered = true;
    }
    if (potValue < POT_RIGHT && isRightBlinkerStopTriggered == true)
    {
      digitalWrite(RED_LED, LOW);
      isRightBlinkerStopTriggered = false;
      rightBlinkerTurned = false;
    }
  }
}
void setup()
{
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
  yled_time = millis();
  Display.clear();
  Serial.begin(9600);
}

void loop()
{
  current_time = millis();
  potValue = map(analogRead(POTMETER), 0, 1023, -2, 2);
  const int LEFT_BTN_STATE = digitalRead(LEFT_BUTTON);
  const int RIGHT_BTN_STATE = digitalRead(RIGHT_BUTTON);
  if (rightBlinkerTurned == true)
  {
    if (current_time - rled_time >= RED_INTERVAL)
    {
      // save the last time you blinked the LED
      rled_time = current_time;
      // if the LED is off turn it on and vice-versa:
      if (red_state == LOW) {
        red_state = HIGH;
      } else {
        red_state = LOW;
      }
      digitalWrite(RED_LED, red_state);
    }
  }

  if (current_time - previousMillis >= BLUE_INTERVAL)
  {
    // save the last time you blinked the LED
    previousMillis = current_time;
    // if the LED is off turn it on and vice-versa:
    if (leftBlinkerTurned == true)
    {
      if (blue_state == LOW) {
        blue_state = HIGH;
      } else {
        blue_state = LOW;
      }
      // set the LED with the ledState of the variable:
      digitalWrite(BLUE_LED, blue_state);
    }
  }


  if ((current_time - left_btn_time ) > BUTTON_INTERVAL_LEFT)
  {
    if (LEFT_BTN_STATE != leftBtnLast)
    {
      if (LEFT_BTN_STATE == LOW)
      {
        changeState++;
        changeState = changeState % 3;
        if (changeState == 0)
        {
          changeState = 1;
        }
      }
      leftBtnLast = LEFT_BTN_STATE;
    }
    if (changeState == 1) {
      leftBlinkerTurned = true;
      if (rightBlinkerTurned == true)
      {
        digitalWrite(RED_LED, LOW);
        rightBlinkerTurned = false;
      }
    }
    if (changeState == 2)
    {
      digitalWrite(BLUE_LED, LOW);
      leftBlinkerTurned = false;
    }
    // Reset for next interval.
    left_btn_time = current_time;
  }

  if ((current_time - pot_time ) > POT_INTERVAL)
  {
    RightBlinker();
    LeftBlinker();
    pot_time = current_time;
  }

  if ((current_time - right_btn_time ) > BUTTON_INTERVAL_RIGHT)
  {
    if (RIGHT_BTN_STATE != rightBtnLast)
    {
      if (RIGHT_BTN_STATE == LOW)
      {
        rightBlinkerTurned = true;
        changeState = 2;
        if (leftBlinkerTurned == true)
        {
          digitalWrite(BLUE_LED, LOW);
          leftBlinkerTurned = false;
        }
      }
      rightBtnLast = RIGHT_BTN_STATE;
    }
    right_btn_time = current_time;
  }
}
