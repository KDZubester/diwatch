//BEGIN APP5 -- SET TIME

void app5() {
    display.clearDisplay();
    int hour = 12;
    int minute = 0;
    
  
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(38, 30);

    char toPrintString[5] = "";

    sprintf(toPrintString, "%02d:%02d", hour, minute);
    display.print(toPrintString);
    display.display();

    delay(500);

    while (digitalRead(wakeUpPin) == HIGH) {
      while (digitalRead(BTN_SE) == HIGH) {
        if (digitalRead(BTN_SW) == LOW) {

          if (hour == 0) {
            hour = 23;
          }
          else {
            hour--;
          }
          
          display.fillRect(35, 25, 110, 35, SSD1306_BLACK);
          
          display.setCursor(38, 30);
          sprintf(toPrintString, "%02d:%02d", hour, minute);
          display.print(toPrintString);
          display.display();
        }
        else if (digitalRead(BTN_NW) == LOW) {

          if (hour == 23) {
            hour = 0;
          }
          else {
            hour++;
          }
          
          display.fillRect(35, 25, 110, 35, SSD1306_BLACK);
          
          display.setCursor(38, 30);
          sprintf(toPrintString, "%02d:%02d", hour, minute);
          display.print(toPrintString);
          display.display();
        }
        else if (digitalRead(BTN_SE) == LOW) {
          break;
        }

        if ((digitalRead(BTN_SW) == HIGH) && (digitalRead(BTN_NW) == HIGH)) {
          //Blink Hours
          display.fillRect(35, 25, 30, 35, SSD1306_BLACK);
          display.display();
          
          delay(200);
  
          display.setCursor(38, 30);
          sprintf(toPrintString, "%02d:%02d", hour, minute);
          display.print(toPrintString);
          display.display();
  
          delay(200);
        }
        else {
          delay(200);
        }
      }

      display.display();

      delay(500);
      while (digitalRead(BTN_SE) == HIGH) {
        if (digitalRead(BTN_SW) == LOW) {

          if (minute == 0) {
            minute = 59;
          }
          else {
            minute--;
          }
          
          display.fillRect(35, 25, 110, 35, SSD1306_BLACK);
          
          display.setCursor(38, 30);
          sprintf(toPrintString, "%02d:%02d", hour, minute);
          display.print(toPrintString);
          display.display();
        }
        else if (digitalRead(BTN_NW) == LOW) {

          if (minute == 59) {
            minute = 0;
          }
          else {
            minute++;
          }
          
          display.fillRect(35, 25, 110, 35, SSD1306_BLACK);
          
          display.setCursor(38, 30);
          sprintf(toPrintString, "%02d:%02d", hour, minute);
          display.print(toPrintString);
          display.display();
        }

        else if (digitalRead(BTN_SE) == LOW) {
          break;
        }


        if ((digitalRead(BTN_SW) == HIGH) && (digitalRead(BTN_NW) == HIGH)) {
          //Blink minutes
          display.fillRect(70, 25, 30, 35, SSD1306_BLACK);
          display.display();
          
          delay(200);
  
          display.setCursor(38, 30);
          sprintf(toPrintString, "%02d:%02d", hour, minute);
          display.print(toPrintString);
          display.display();
  
          delay(200);
        }
        else {
          delay(200);
        }
        
      }
      
    }

    // rtc.adjust(DateTime(year, month, day, hour, minute, second));
    rtc.adjust(DateTime(2022, 9, 21, hour, minute, 0));
    
    display.display();
    delay(500);
}
