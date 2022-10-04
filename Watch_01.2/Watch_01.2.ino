 #include "LowPower.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int wakeUpPin = 2; // external interrupt 0
const int BTN_SE = 3;
const int BTN_NW = 4;
const int BTN_SW = 5;

int displayON = 0;

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int menu();

void printDisplay(bool printSeconds);
 
void wakeUp()
{
//  Serial.println("woke up");
  
}
 
void setup()
{
  //////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////

  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
//  Serial.println("display logo");
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
//  Serial.println("clear logo");
  delay(2000);

  //////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////
  
  //pinMode(LED_BUILTIN, OUTPUT);
   pinMode(wakeUpPin, INPUT);//_PULLUP);
   attachInterrupt(digitalPinToInterrupt(wakeUpPin), wakeUp, FALLING);
   pinMode(BTN_SE, INPUT);
   pinMode(BTN_NW, INPUT);
//   attachInterrupt(digitalPinToInterrupt(wakeUpPin2), wakeUp, FALLING);

  //////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
//    Serial.println("Couldn't find RTC");
//    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
//    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
//     rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void setCurrentApp(int appNum);

#define CONTINUE_WHILE 0
#define POWER_OFF 1
#define RETURN_CLOCK 2

#define TOP_CURSOR_Y 5
#define BOTTOM_CURSOR_Y SCREEN_HEIGHT - 10
#define LEFT_CURSOR_X 0
#define RIGHT_CURSOR_X_3_LETTERS SCREEN_WIDTH - 20


bool powerOffFlag = true;

void loop()
{
    //Sleep until wake button is pressed//
    if (powerOffFlag == true) {
//      Serial.println("Going to Sleep");
      display.clearDisplay();
      display.display();
      delay(200);
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
      delay(20);
    }
    powerOffFlag = true;
    
    display.clearDisplay();

    //DISPLAY THE DIRECTIONS 
    display.setCursor(RIGHT_CURSOR_X_3_LETTERS, TOP_CURSOR_Y);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print("OFF");
  
    display.setCursor(LEFT_CURSOR_X, BOTTOM_CURSOR_Y);
    display.print("MENU");

//    Serial.println("woke up");
    printDisplay(false);

    bool breakOut = false;

    setCurrentApp(0);
    delay(500);

    long unsigned currM = millis();
    
    //Run for 5 seconds
    while ((millis() - currM) < 5000) {
      //BTN_SW is the menu
      if (digitalRead(BTN_SW) == LOW) {
        //Stay in menu until player requests to power off or to go back to clock
        while (1) {
          int menuOutput = menu();
          if (menuOutput == POWER_OFF) {
            breakOut = true;
            break;
          }
          else if (menuOutput == RETURN_CLOCK) {
            powerOffFlag = false;
            break;
          }
        }

        if (breakOut == true || powerOffFlag == false) {
          break;
        }
        
      }

      //User can turn off watch with top right button
      if (digitalRead(wakeUpPin) == LOW) {
        break;
      }
    }
}
