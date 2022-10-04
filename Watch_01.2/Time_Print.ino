
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels



void printTime(DateTime now, bool printSeconds) 
{
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  if (printSeconds)
    display.setCursor(21, 30);
  else if (now.hour() < 10)
    display.setCursor(38, 30);
  else
    display.setCursor(33,30);
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
  display.setCursor(30,10);
  display.print(" (");
  display.print(daysOfTheWeek[now.dayOfTheWeek()]);
  display.print(") ");
}

void printDisplay(bool printSeconds)
{
  DateTime now = rtc.now();
  printTime(now, printSeconds);
  printDate(now);
  printWeekDay(now);
  display.display();
  display.clearDisplay();
}




      
