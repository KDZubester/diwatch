//BEGIN APP5 -- SET TIME

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define BLINK_WAIT_MS 300
#define EDIT_HOUR 0
#define EDIT_MINUTE 1
#define EDIT_MONTH 2
#define EDIT_DAY 3
#define EDIT_YEAR 4


#define FILL_RECT_X 0
#define CURSOR_Y 25

#define TIME_CURSOR_X 28
#define RECT_HOUR_X TIME_CURSOR_X
#define RECT_MINUTE_X RECT_HOUR_X + 35
#define FILL_RECT_WIDTH_2 25
#define RECT_Y CURSOR_Y

#define DATE_CURSOR_X 1
#define RECT_MONTH_X DATE_CURSOR_X
#define RECT_DAY_X DATE_CURSOR_X + 35
#define RECT_YEAR_X DATE_CURSOR_X + 70
#define FILL_RECT_WIDTH_4 50

//Defaults
int currHour = 12;
int currMonth = 4;
int currDay = 5;
long currYear = 2022;
int currMinute = 30;


void app5() {
    display.clearDisplay();

    //DISPLAY DIRECTIONS 
    display.setCursor(SCREEN_WIDTH - 27, 5);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print("DONE");

    display.setCursor(SCREEN_WIDTH - 27, SCREEN_HEIGHT - 10);
    display.print("NEXT");
  
    drawArrows();
    //DISPLAY DIRECTIONS 


    // Write Set time
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(35, 2);
    display.print("Set Time");

    //Write the Default Starting Time
    display.setTextSize(2); // Draw 2X-scale text
    display.setCursor(TIME_CURSOR_X, CURSOR_Y);
    char toPrintString[10] = "";
    sprintf(toPrintString, "%02d:%02d", currHour, currMinute);
    display.print(toPrintString);
    display.display();

    delay(500);

    //Initialize to be editing hours
    unsigned long currM = millis();
    bool flashOn = true;
    int currEdit = EDIT_HOUR;
    int currRectX = RECT_HOUR_X;
    int currCursorX = TIME_CURSOR_X;
    bool dateEdit = false;
    
    //Set Time
    while (digitalRead(wakeUpPin) == HIGH) {
      
      //BEGIN INC/DEC
      if (digitalRead(BTN_SW) == LOW || digitalRead(BTN_NW) == LOW) {
        
        //DECREMENT
        if (digitalRead(BTN_SW) == LOW) {
          if (currEdit == EDIT_HOUR) {
            if (currHour == 0) {
              currHour = 23;
            }
            else {
              currHour--;
            }
          }
          else if (currEdit == EDIT_MINUTE) {
            if (currMinute == 0) {
              currMinute = 59;
            }
            else {
              currMinute--;
            }
          }
          else if (currEdit == EDIT_MONTH) {
            if (currMonth == 1) {
              currMonth = 12;
            }
            else {
              currMonth--;
            }
          }
          else if (currEdit == EDIT_DAY) {
            if (currDay == 1) {
              currDay = 31;
            }
            else {
              currDay--;
            }
          }
          else if (currEdit == EDIT_YEAR) {
            if (currYear == 2021) {
              currYear = 2047;
            }
            else {
              currYear--;
            }
          }
        }
        
        //INCREMENT
        else if (digitalRead(BTN_NW) == LOW) {

          if (currEdit == EDIT_HOUR) {
            if (currHour == 23) {
              currHour = 0;
            }
            else {
              currHour++;
            }
          }
          else if (currEdit == EDIT_MINUTE) {
            if (currMinute == 59) {
              currMinute = 0;
            }
            else {
              currMinute++;
            }
          }
          else if (currEdit == EDIT_MONTH) {
            if (currMonth == 12) {
              currMonth = 1;
            }
            else {
              currMonth++;
            }
          }
          else if (currEdit == EDIT_DAY) {
            if (currDay == 31) {
              currDay = 1;
            }
            else {
              currDay++;
            }
          }
          else if (currEdit == EDIT_YEAR) {
            if (currYear == 2047) {
              currYear = 2021;
            }
            else {
              currYear++;
            }
          }
        }

        //END INC/DEC



        //DISPLAY INC OR DEC
        display.fillRect(FILL_RECT_X, RECT_Y, SCREEN_WIDTH, 25, SSD1306_BLACK);
        
        display.setCursor(currCursorX, CURSOR_Y);
        
        if (!dateEdit)
          sprintf(toPrintString, "%02d:%02d", currHour, currMinute);
        else
          sprintf(toPrintString, "%02d/%02d/%04d", currMonth, currDay, currYear);
        
        display.print(toPrintString);
        display.display();
        delay(150);
        
      }


      //Go to next edit if BTN_SE is pressed
      else if (digitalRead(BTN_SE) == LOW) {
        delay(50);

        currM = millis();
        // Wait while BTN_SE is pressed, return if at 3 seconds to exit without changing time
        while (digitalRead(BTN_SE) == LOW) {
          if ( (millis() - currM) >= 2950) {
            return;
          }
        }
        
        if (currEdit == EDIT_YEAR) {
          currEdit = EDIT_HOUR;
          currRectX = RECT_HOUR_X;
          currCursorX = TIME_CURSOR_X;
          dateEdit = false;
          display.fillRect(FILL_RECT_X, RECT_Y, SCREEN_WIDTH, 25, SSD1306_BLACK);
        }
        else {
          currEdit++;
          if (currEdit == EDIT_MINUTE)
            currRectX = RECT_MINUTE_X;
          else if (currEdit == EDIT_MONTH) {
            currRectX = RECT_MONTH_X;
            currCursorX = DATE_CURSOR_X;
            dateEdit = true;
            display.fillRect(FILL_RECT_X, RECT_Y, SCREEN_WIDTH, 25, SSD1306_BLACK);
          }
            
          //THE REST
        }
      }

      
      //If no buttons pressed, flash
      else if ( ((millis() - currM) >= BLINK_WAIT_MS) && flashOn) {
        currM = millis();
        flashOn = false;
        //Blink off
        if (currEdit == EDIT_MONTH) {
          display.fillRect(RECT_MONTH_X, RECT_Y, 23, 25, SSD1306_BLACK);
          dateEdit = true;
        }
        else if (currEdit == EDIT_DAY)
          display.fillRect(RECT_DAY_X, RECT_Y, FILL_RECT_WIDTH_2, 25, SSD1306_BLACK);
        else if (currEdit == EDIT_YEAR)
          display.fillRect(RECT_YEAR_X, RECT_Y, FILL_RECT_WIDTH_4, 25, SSD1306_BLACK);
        else {
          display.fillRect(currRectX, RECT_Y, FILL_RECT_WIDTH_2, 25, SSD1306_BLACK);
          dateEdit = false;
        }
        display.display();
      }
      else if ( ((millis() - currM) >= BLINK_WAIT_MS) && !flashOn) {
        currM = millis();
        flashOn = true;
        //Blink on
        display.setCursor(currCursorX, CURSOR_Y);

        if (!dateEdit)
          sprintf(toPrintString, "%02d:%02d", currHour, currMinute);
        else
          sprintf(toPrintString, "%02d/%02d/%04d", currMonth, currDay, currYear);
        
        display.print(toPrintString);
        display.display();
      }

    }
      

    // rtc.adjust(DateTime(year, month, day, hour, minute, second));
    rtc.adjust(DateTime(currYear, currMonth, currDay, currHour, currMinute, 0));
    
    delay(500);
}
