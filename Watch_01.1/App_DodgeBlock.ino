
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
