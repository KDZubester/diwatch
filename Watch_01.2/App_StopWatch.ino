
/////STOPWATCH//////

#define TOP_CURSOR_Y 5
#define BOTTOM_CURSOR_Y SCREEN_HEIGHT - 10
#define LEFT_CURSOR_X 0
#define RIGHT_CURSOR_X_3_LETTERS SCREEN_WIDTH - 20

#define SW_X_CURSOR 15
#define SW_Y_CURSOR 25


int ms = 0;
int sec = 0;
int mins = 0;

void clearSW() {
  display.clearDisplay();
  printSWInstructions();
  
  display.setTextSize(2);
  display.setCursor(SW_X_CURSOR, SW_Y_CURSOR);
  display.print("00:00.00");
  ms = 0;
  sec = 0;
  mins = 0;
}

void printSWInstructions() {
  //DISPLAY THE DIRECTIONS 
  display.setCursor(SCREEN_WIDTH - 27, TOP_CURSOR_Y);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("MENU");

  display.setCursor(LEFT_CURSOR_X, BOTTOM_CURSOR_Y);
  display.print("START");

  display.setCursor(SCREEN_WIDTH - 20, BOTTOM_CURSOR_Y);
  display.print("RST");
}

void stopWatch() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  char toPrintString[10] = "";
  
  bool startButton = false;
  bool pause = true;
  bool restart = false;
  bool done = false;

  printSWInstructions();

  display.setTextSize(2);
  display.setCursor(SW_X_CURSOR, SW_Y_CURSOR);

  sprintf(toPrintString, "%02d:%02d.%02d\n", mins, sec, ms);
  display.print(toPrintString);
        
  display.display();
  delay(200);

  //Keep Repeating stop watch until top right button pressed.
  while (digitalRead(wakeUpPin) == HIGH) {
    startButton = false;
    pause = false;
    restart = false;
    done = false;

    unsigned long currM;

    if (digitalRead(BTN_SE) == LOW) {
      clearSW();
      display.display();
    }

    if (digitalRead(BTN_SW) == LOW) {
      startButton = true;
      display.fillRect(0, SCREEN_HEIGHT - 10, 50, 20, SSD1306_BLACK); //CLEAR START
      display.fillRect(SCREEN_WIDTH - 33, SCREEN_HEIGHT - 10, 50, 10, SSD1306_BLACK); //CLEAR RST
      display.fillRect(SCREEN_WIDTH - 30, 0, 50, 20, SSD1306_BLACK);    //CLEAR MENU
      
      display.setCursor(SCREEN_WIDTH - 27, BOTTOM_CURSOR_Y);
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.print("STOP");
      
      currM = millis();
    }

    while (startButton) {

      //Increase milliseconds every 10 milliseconds
      if ((millis() - currM) >= 50) {

//        Serial.println(millis() - currM);

//        display.clearDisplay();
        display.fillRect(10, 20, 110, 30, SSD1306_BLACK);

//        printSWInstructions();
        
        currM = millis();
        
        ms+=5;
        if (ms > 99) {
          ms = 0;
          sec++;
        }
        if (sec > 59) {
          sec = 0;
          mins++;
        }

        display.setTextSize(2);
        display.setCursor(SW_X_CURSOR, SW_Y_CURSOR);
        display.setTextColor(SSD1306_WHITE);
        
        sprintf(toPrintString, "%02d:%02d.%02d\n", mins, sec, ms);
        display.print(toPrintString);
        
        display.display();
      }

      
      
      

      if (digitalRead(BTN_SE) == LOW) {
        pause = true;
      }

      if (pause) {
        while (1) {
          display.fillRect(SCREEN_WIDTH - 33, SCREEN_HEIGHT - 10, 50, 10, SSD1306_BLACK);
          printSWInstructions();
          display.display();
          delay(250);
          if (digitalRead(BTN_SE) == LOW) {
            restart = true;
            break;
          }
          else if (digitalRead(wakeUpPin) == LOW) {
            done = true;
            break;
          }
          else if (digitalRead(BTN_SW) == LOW) {
            display.fillRect(0, SCREEN_HEIGHT - 10, 50, 20, SSD1306_BLACK); //CLEAR START
            display.fillRect(SCREEN_WIDTH - 33, SCREEN_HEIGHT - 10, 50, 10, SSD1306_BLACK); //CLEAR RST
            display.fillRect(SCREEN_WIDTH - 30, 0, 50, 20, SSD1306_BLACK);    //CLEAR MENU
      
            display.setCursor(SCREEN_WIDTH - 27, BOTTOM_CURSOR_Y);
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.print("STOP");
            break;
          }
        }
        pause = false;
      }

      if (restart) {
        clearSW();
        display.display();
        break;
      }
      if (done) {
        break;
      }
    }

    if (done)  {
      break;
    }
  }
  
}

////END STOPWATCH//////
