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

void menu();
 
void wakeUp()
{
  Serial.println("woke up");
  
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
  Serial.println("display logo");
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  Serial.println("clear logo");
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
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void printTime(DateTime now, bool printSeconds) 
{
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  if (printSeconds)
    display.setCursor(21, 30);
  else
    display.setCursor(28,30);
  display.print(now.hour(), DEC);
  display.print(':');
  if (now.minute() < 10) {
    display.print('0');
  }
  display.print(now.minute(), DEC);
  if (printSeconds) {
    display.print(':');
    if (now.second() < 10) {
      display.print('0');
    }
    display.print(now.second(), DEC);
  }
  display.println();
}

void printDate(DateTime now) 
{
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35,20);
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.day(), DEC);
  display.print('/');
  display.print(now.year(), DEC);
  display.println();
}

void printWeekDay(DateTime now) 
{
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(34,10);
  display.print(" (");
  display.print(daysOfTheWeek[now.dayOfTheWeek()]);
  display.print(") ");
}

void printDisplay(bool printSeconds)
{
  Serial.println("woke up");
  DateTime now = rtc.now();
  printTime(now, printSeconds);
  printDate(now);
  printWeekDay(now);
  display.display();
  display.clearDisplay();
}

long secondCount = 0;

void displayTimeApp() {
      bool printSeconds = false;
      display.clearDisplay();
      display.clearDisplay();
      printDisplay(printSeconds);
  
      //Keep track of time variables
      DateTime now = rtc.now();
      secondCount = 0;

      while ((secondCount < 750000)) {
        secondCount++;
        if (digitalRead(BTN_SW) == LOW) {
          menu();
          break;
        }
      }
      
      //Count to 5 seconds, updating time. If no more buttons are pressed, go back to sleep
//      while ((secondCount < 5)) {
//        
//        if (now.second() != rtc.now().second()) {
//          secondCount++;
//          
//          //5 second
//          if (secondCount >= 5) {
//            break;
//          }
//          
//          printDisplay(printSeconds);
//          now = rtc.now();    // Reset now to now
//        }
//        
//      }
      //END WHILE LOOP - 5 seconds passed, no buttons pressed
}



/////BEGIN DODGE BLOCK FUNCTIONS/////
#define NUM_BLOCKS 7
#define EMPTY_VAL 300
#define STARTING_X_VAL 129
#define ENDING_X_VAL -10

#define BLOCK_SIDE 7
#define PLAYER_SIDE 10

#define MAX_Y_VAL SCREEN_HEIGHT + 3 - BLOCK_SIDE

int xVals[NUM_BLOCKS];
int yVals[NUM_BLOCKS];
int playerX;
int playerY;

void deleteBlock(int index) {
    xVals[index] = EMPTY_VAL;
    yVals[index] = EMPTY_VAL;
}

void initializeBlocks() {
    for (int i = 0; i < NUM_BLOCKS; i++) {
      deleteBlock(i);
    }
    playerX = 0;
    playerY = 20;
}

void createNewBlock() {
    for (int i = 0; i < NUM_BLOCKS; i++) {
      if (xVals[i] == EMPTY_VAL) {
        xVals[i] = STARTING_X_VAL;
        yVals[i] = random(0, MAX_Y_VAL);
        break;
      }
    }
}


void dodgeBlock() {
    display.clearDisplay();
    delay(500);
    int genCount = 0;
    int blocksDodged = 0;
    initializeBlocks();
    display.drawRect(playerX, playerY, PLAYER_SIDE, PLAYER_SIDE, SSD1306_WHITE);
  
  
    //BLOCK CODE//
    while (digitalRead(wakeUpPin) == HIGH) {
      for (int i = 0; i < NUM_BLOCKS; i++) {
        if (xVals[i] != EMPTY_VAL) {
          display.drawRect(xVals[i], yVals[i], BLOCK_SIDE, BLOCK_SIDE, SSD1306_BLACK);
          xVals[i] -= 2;
          display.drawRect(xVals[i], yVals[i], BLOCK_SIDE, BLOCK_SIDE, SSD1306_WHITE);
          
          if (xVals[i] <= ENDING_X_VAL) {
            deleteBlock(i);
            blocksDodged++;
          }
        }
      }
      
      genCount++;
      if (genCount == 12) {
        createNewBlock();
        genCount = 0;
      }
  
  
      //PLAYER CODE//
      if ((digitalRead(BTN_SW) == LOW) && (playerY + 2 + PLAYER_SIDE < SCREEN_HEIGHT)) {
        display.drawRect(playerX, playerY, PLAYER_SIDE, PLAYER_SIDE, SSD1306_BLACK);
        playerY += 2;
        display.drawRect(playerX, playerY, PLAYER_SIDE, PLAYER_SIDE, SSD1306_WHITE);
      }
      else if ((digitalRead(BTN_NW) == LOW) && (playerY - 2 > 0)) {
        display.drawRect(playerX, playerY, PLAYER_SIDE, PLAYER_SIDE, SSD1306_BLACK);
        playerY -= 2;
        display.drawRect(playerX, playerY, PLAYER_SIDE, PLAYER_SIDE, SSD1306_WHITE);
      }

      //Display changes
      display.display();
  
      bool collision = false;
  
      for (int i = 0; i < NUM_BLOCKS; i++) {
        if ((xVals[i] < PLAYER_SIDE) && (xVals[i] + BLOCK_SIDE > 0)) {
          if ((yVals[i] + BLOCK_SIDE > playerY) && (yVals[i] < playerY + PLAYER_SIDE)) {
            collision = true;
          }
        }
      }
  
      if (collision == true) {
        break;
      }
    }

    delay(1000);

    //Print Player score
    display.clearDisplay();

    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(12, 30);
    display.print("Blocks Dodged: ");
    display.print(blocksDodged);

    display.display();
    
    delay(3000);
}
/////END DODGE BLOCK FUNCTIONS//////

/////MORBIN/////////

void morbin() {
    display.clearDisplay();
  
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(12, 30);
    display.print("IT'S MORBIN TIME");
    display.display();
    delay(3000);
}

/////END MORBIN///////

/////STOPWATCH//////

void stopWatch() {
  display.clearDisplay();
  
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  
  int ms = 0;
  int sec = 0;
  int mins = 0;
  bool startButton = false;
  bool pause = false;
  bool breakOut = false;

  display.setCursor(15, 30);
  display.print("00:00.0");
  display.display();

  //Keep Repeating stop watch until top right button pressed.
  while (digitalRead(wakeUpPin) == HIGH) {
    startButton = false;
    ms = 0;
    sec = 0;
    mins = 0;
    pause = false;
    breakOut = false;

    if (digitalRead(BTN_SW) == LOW) {
      startButton = true;
    }

    while (startButton) {
      delay(59);
      ms++;
      if (ms > 9) {
        ms = 0;
        sec++;
      }
      if (sec > 59) {
        sec = 0;
        mins++;
      }
      
      display.setCursor(15, 30);
      display.clearDisplay();
      
      if (mins < 10)
        display.print('0');
      display.print(mins);
      display.print(':');
      if (sec < 10)
        display.print('0');
      display.print(sec);
      display.print('.');
      display.print(ms);
      display.display();
      

      if (digitalRead(BTN_SE) == LOW) {
        pause = true;
      }

      if (pause) {
        while (digitalRead(BTN_SW) == HIGH) {
          delay(250);
          if (digitalRead(BTN_SE) == LOW) {
            breakOut = true;
            break;
          }
        }
        pause = false;
      }

      if (breakOut) {
        display.clearDisplay();
        display.setCursor(15, 30);
        display.print("00:00.0");
        display.display();
        break;
      }
    }
    
  }
  
}



////END STOPWATCH//////



/////BEGIN MENU FUNCTIONS//////
#define APP_SIDE 24
#define Y_VAL_TOP 7
#define X_VAL_LEFT 5
#define X_VAL_2 32
#define Y_VAL_BOTTOM SCREEN_HEIGHT/2 + 8
#define Y_VAL_CURSOR 5
#define X_VAL_CURSOR 7

#define BUTTON_NOT_PRESSED 0
#define BUTTON_DOWN 1
#define BUTTON_UP 2
#define BUTTON_SELECT 3
#define NUM_APPS 3

//Function declarations
void drawClockApp(bool inverted);
void drawDodgeBlockApp(bool inverted);
void drawMorbinApp(bool inverted);
void drawStopWatchApp(bool inverted);


void drawClockApp(bool inverted) {
  int backColor = inverted ? SSD1306_WHITE : SSD1306_BLACK;
  int frontColor = inverted ? SSD1306_BLACK : SSD1306_WHITE;
  display.fillRect(X_VAL_LEFT, Y_VAL_TOP, APP_SIDE, APP_SIDE, backColor);
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(frontColor);
  display.setCursor(X_VAL_LEFT + X_VAL_CURSOR, Y_VAL_TOP + Y_VAL_CURSOR);
  display.print('P');

  if (inverted) {
    drawDodgeBlockApp(false);
    drawMorbinApp(false);
    drawStopWatchApp(false);
  }
}

void drawDodgeBlockApp(bool inverted) {
  int backColor = inverted ? SSD1306_WHITE : SSD1306_BLACK;
  int frontColor = inverted ? SSD1306_BLACK : SSD1306_WHITE;
  display.fillRect(X_VAL_LEFT, Y_VAL_BOTTOM, APP_SIDE, APP_SIDE, backColor);
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(frontColor);
  display.setCursor(X_VAL_LEFT + X_VAL_CURSOR, Y_VAL_BOTTOM + Y_VAL_CURSOR);
  display.print('D');

  if (inverted) {
    drawClockApp(false);
    drawMorbinApp(false);
    drawStopWatchApp(false);
  }
}

void drawMorbinApp(bool inverted) {
  int backColor = inverted ? SSD1306_WHITE : SSD1306_BLACK;
  int frontColor = inverted ? SSD1306_BLACK : SSD1306_WHITE;
  display.fillRect(X_VAL_2, Y_VAL_TOP, APP_SIDE, APP_SIDE, backColor);
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(frontColor);
  display.setCursor(X_VAL_2 + X_VAL_CURSOR, Y_VAL_TOP + Y_VAL_CURSOR);
  display.print('M');
  
  if (inverted) {
    drawClockApp(false);
    drawDodgeBlockApp(false);
    drawStopWatchApp(false);
  }
}

void drawStopWatchApp(bool inverted) {
  int backColor = inverted ? SSD1306_WHITE : SSD1306_BLACK;
  int frontColor = inverted ? SSD1306_BLACK : SSD1306_WHITE;
  display.fillRect(X_VAL_2, Y_VAL_BOTTOM, APP_SIDE, APP_SIDE, backColor);
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(frontColor);
  display.setCursor(X_VAL_2 + X_VAL_CURSOR, Y_VAL_BOTTOM + Y_VAL_CURSOR);
  display.print('S');
  
  if (inverted) {
    drawClockApp(false);
    drawDodgeBlockApp(false);
    drawMorbinApp(false);
  }
}

void menu() {
    display.clearDisplay();
    delay(500);
    int currentApp = 0;
    drawClockApp(true);
    drawDodgeBlockApp(false);
    drawMorbinApp(false);
    display.display();
    

    while (1) {
      int buttonPressed = 0;

      //GET BUTTON PRESSED
      if (digitalRead(BTN_SW) == LOW) {
        buttonPressed = BUTTON_DOWN;
      }
      else if (digitalRead(BTN_NW) == LOW) {
        buttonPressed = BUTTON_UP;
      }
      else if (digitalRead(BTN_SE) == LOW) {
        buttonPressed = BUTTON_SELECT;
      }
      
      //Increment current app
      if (buttonPressed == BUTTON_DOWN) {
        delay(200);
        if (currentApp < NUM_APPS)
          currentApp++;
        else
          currentApp = 0;
      }
      else if ((buttonPressed == BUTTON_UP)) {
        delay(200);
        if (currentApp > 0)
          currentApp--;
        else
          currentApp = NUM_APPS;
      }

      //Select Button or change display
      if (buttonPressed == BUTTON_SELECT) {
        if (currentApp == 0) {
//          displayTimeApp();
          break;
        }
        else if (currentApp == 1) {
          dodgeBlock();
          break;
        }
        else if (currentApp == 2) {
          morbin();
          break;
        }
        else if (currentApp == 3) {
          stopWatch();
          break;
        }
      }

      //Change display
      if (buttonPressed == BUTTON_DOWN || buttonPressed == BUTTON_UP) {
        if (currentApp == 0) {
          drawClockApp(true);
        }
        else if (currentApp == 1) {
          drawDodgeBlockApp(true);
        }
        else if (currentApp == 2) {
          drawMorbinApp(true);
        }
        else if (currentApp == 3) {
          drawStopWatchApp(true);
        }
        display.display();
      }

      
      
    }
    
//    delay(5000);
}

/////END MENU FUNCTIONS//////

void loop()
{
    //Sleep until wake button is pressed//
    Serial.println("Going to Sleep");
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    delay(10);

    display.clearDisplay();
    printDisplay(false);

    secondCount = 0;

    
    //Count to 5 seconds, updating time. If no more buttons are pressed, go back to sleep
    while ((secondCount < 750000)) {
        secondCount++;
      if (digitalRead(BTN_SW) == LOW) {
        menu();
        break;
      }
    }
      //END WHILE LOOP - 5 seconds passed, no buttons pressed

//    menu();
    
    Serial.println("clear time");
    display.clearDisplay();
    display.display();

    
}
