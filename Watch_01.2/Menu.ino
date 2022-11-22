/////BEGIN MENU FUNCTIONS//////
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define APP_SIDE 24
#define Y_VAL_TOP 7
#define X_VAL_LEFT 22
#define X_VAL_2 X_VAL_LEFT + 27
#define X_VAL_3 X_VAL_2 + 27
#define Y_VAL_BOTTOM SCREEN_HEIGHT/2 + 8
#define Y_VAL_CURSOR 5
#define X_VAL_CURSOR 7

#define BUTTON_NOT_PRESSED 0
#define BUTTON_DOWN 1
#define BUTTON_UP 2
#define BUTTON_SELECT 3
#define NUM_APPS 5

#define CONTINUE_WHILE 0
#define POWER_OFF 1
#define RETURN_CLOCK 2

//Function declarations
void drawClockApp(bool inverted);
void drawDodgeBlockApp(bool inverted);
void drawMorbinApp(bool inverted);
void drawStopWatchApp(bool inverted);


int currentApp = 0;

void setCurrentApp(int appNum) {
  currentApp = appNum;
}


void drawArrows() {
  //drawPixel(int16_t x, int16_t y, uint16_t color);
  int arrowColor = SSD1306_WHITE;
  display.drawPixel(4,1, arrowColor);
  display.drawPixel(4,2, arrowColor);
  display.drawPixel(4,3, arrowColor);
  display.drawPixel(4,4, arrowColor);
  display.drawPixel(4,5, arrowColor);
  display.drawPixel(4,6, arrowColor);
  display.drawPixel(4,7, arrowColor);
  display.drawPixel(4,8, arrowColor);
  display.drawPixel(4,9, arrowColor);
  display.drawPixel(4,10, arrowColor);
  display.drawPixel(3,2, arrowColor);
  display.drawPixel(2,3, arrowColor);
  display.drawPixel(1,4, arrowColor);
  display.drawPixel(5,2, arrowColor);
  display.drawPixel(6,3, arrowColor);
  display.drawPixel(7,4, arrowColor);

  display.drawPixel(4,SCREEN_HEIGHT - 1, arrowColor);
  display.drawPixel(4,SCREEN_HEIGHT - 2, arrowColor);
  display.drawPixel(4,SCREEN_HEIGHT - 3, arrowColor);
  display.drawPixel(4,SCREEN_HEIGHT - 4, arrowColor);
  display.drawPixel(4,SCREEN_HEIGHT - 5, arrowColor);
  display.drawPixel(4,SCREEN_HEIGHT - 6, arrowColor);
  display.drawPixel(4,SCREEN_HEIGHT - 7, arrowColor);
  display.drawPixel(4,SCREEN_HEIGHT - 8, arrowColor);
  display.drawPixel(4,SCREEN_HEIGHT - 9, arrowColor);
  display.drawPixel(4,SCREEN_HEIGHT - 10, arrowColor);
  display.drawPixel(3,SCREEN_HEIGHT - 2, arrowColor);
  display.drawPixel(2,SCREEN_HEIGHT - 3, arrowColor);
  display.drawPixel(1,SCREEN_HEIGHT - 4, arrowColor);
  display.drawPixel(5,SCREEN_HEIGHT - 2, arrowColor);
  display.drawPixel(6,SCREEN_HEIGHT - 3, arrowColor);
  display.drawPixel(7,SCREEN_HEIGHT - 4, arrowColor);
}





void drawClockApp(bool inverted) {
  int backColor = inverted ? SSD1306_WHITE : SSD1306_BLACK;
  int frontColor = inverted ? SSD1306_BLACK : SSD1306_WHITE;
  display.fillRect(X_VAL_LEFT, Y_VAL_TOP, APP_SIDE, APP_SIDE, backColor);
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(frontColor);
  display.setCursor(X_VAL_LEFT + X_VAL_CURSOR, Y_VAL_TOP + Y_VAL_CURSOR);
  display.print('T');

  //DISPLAY THE DIRECTIONS 
  display.setCursor(SCREEN_WIDTH - 20, 5);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("OFF");

  display.setCursor(SCREEN_WIDTH - 20, SCREEN_HEIGHT - 10);
  display.print("SEL");

  drawArrows();
  

  if (inverted) {
    drawDodgeBlockApp(false);
    drawMorbinApp(false);
    drawStopWatchApp(false);
    drawApp5(false);
    drawApp6(false);
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
    drawApp5(false);
    drawApp6(false);
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
    drawApp5(false);
    drawApp6(false);
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
    drawApp5(false);
    drawApp6(false);
  }
}

void drawApp5(bool inverted) {
  int backColor = inverted ? SSD1306_WHITE : SSD1306_BLACK;
  int frontColor = inverted ? SSD1306_BLACK : SSD1306_WHITE;
  display.fillRect(X_VAL_3, Y_VAL_TOP, APP_SIDE, APP_SIDE, backColor);
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(frontColor);
  display.setCursor(X_VAL_3 + X_VAL_CURSOR, Y_VAL_TOP + Y_VAL_CURSOR);
  display.print('R');
  
  if (inverted) {
    drawClockApp(false);
    drawDodgeBlockApp(false);
    drawMorbinApp(false);
    drawStopWatchApp(false);
    drawApp6(false);
  }
}

void drawApp6(bool inverted) {
  int backColor = inverted ? SSD1306_WHITE : SSD1306_BLACK;
  int frontColor = inverted ? SSD1306_BLACK : SSD1306_WHITE;
  display.fillRect(X_VAL_3, Y_VAL_BOTTOM, APP_SIDE, APP_SIDE, backColor);
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(frontColor);
  display.setCursor(X_VAL_3 + X_VAL_CURSOR, Y_VAL_BOTTOM + Y_VAL_CURSOR);
  display.print('6');
  
  if (inverted) {
    drawClockApp(false);
    drawDodgeBlockApp(false);
    drawMorbinApp(false);
    drawStopWatchApp(false);
    drawApp5(false);
  }
}

int menu() {
    display.clearDisplay();

    //Initialize menu display
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
    else if (currentApp == 4) {
      drawApp5(true);
    }
    else if (currentApp == 5) {
      drawApp6(true);
    }
    display.display();
    delay(500);

    long unsigned currM = millis();

    //Stay in menu unless user wants out
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
          return RETURN_CLOCK;   // RETURN TO CLOCK
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
        else if (currentApp == 4) {
          app5();
          break;
        }
        else if (currentApp == 5) {
          app6();
          break;
        }
        
      }

      //Change display when navigate buttons are pressed
      if (buttonPressed == BUTTON_DOWN || buttonPressed == BUTTON_UP) {
        currM = millis();
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
        else if (currentApp == 4) {
          drawApp5(true);
        }
        else if (currentApp == 5) {
          drawApp6(true);
        }
        display.display();
      }

      //Power Off at 10 seconds, or if user presses top right button
      if (digitalRead(wakeUpPin) == LOW || ((millis() - currM) >= 10000)) {
        return POWER_OFF;   //End
      }
      
      
    }

    return CONTINUE_WHILE;   //Continue While loop - Stay in menu
}

/////END MENU FUNCTIONS//////




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


void app6() {
    display.clearDisplay();

    char powerString[15];
//    analogReadResolution(12);
    int charge = analogRead(CHARGE_PIN);


    //NOT MY CODE//
    const float V_BAND_GAP = 1.1;     // typical
    ADMUX = _BV(REFS0)    // ref = Vcc
      | 14;           // channel 14 is the bandgap reference
    ADCSRA |= _BV(ADSC);   // start conversion
    loop_until_bit_is_clear(ADCSRA, ADSC);  // wait until complete
    //I REPEAT, THIS IS STOLEN CODE//

    float floatCharge = V_BAND_GAP * 1024.0 / ADC;
  
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(17, 30);
    
    sprintf(powerString, "Output: %d.%04d V", (int)floatCharge, (int)(floatCharge*10000)%10000);
    display.print(powerString);
    display.display();
    delay(3000);
}
