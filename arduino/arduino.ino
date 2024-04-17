#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>


#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int bonusCanX;
int bonusCanY;
bool bonusCanHareket;
int bonusCanWidth = 5;
int bonusCanHeight = 5;



int paletKon, paletGen;

int topX, topY, topSpeedX, topSpeedY;
int bonusX, bonusY;
int bonusSpeedX = 0;
int bonusSpeedY = 2;

bool tuglalar[4][8];
int tuglaSayac = 32;




bool carpismaVarmi = false;

bool paletKonDegisti = false;



const int digitPins[1] = {53}; 
const int segmentPins[7] = {8, 7, 6, 11, 10, 9, 14};
const byte digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

const int digitPins1[1] = {12};
const int segmentPins1[7] = {46, 47, 48, 49, 50, 51, 52};
const byte digits1[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

int j=0;

bool game = false;
int selected = 0;
int entered = -1;

bool bonusFlag = false ;

int puan = 0;
int can = 3;
int baslangicTuglaSayisi = 8; 
int tamamlananTuglaSayisi = 0;



const int LED_PIN_1 = 22; 
const int LED_PIN_2 = 23; 
const int LED_PIN_3 = 24; 


#define POT_PIN A0

int lightPin = A1;
int lightValue = 0;

void displaymenu(void) {

  if (lightValue > 10){
      oled.invertDisplay(true);
      } else {
        oled.invertDisplay(false);
      }


  int up = digitalRead(3);
  int down = digitalRead(2);
  int enter = digitalRead(4);
  int back = digitalRead(5);

  if (up == LOW && down == LOW) {
  };
  if (up == LOW) {
    selected = selected + 1;
    delay(100);
  };
  if (down == LOW) {
    selected = selected - 1;
    delay(100);
  };
  if (enter == LOW) {
    entered = selected;
  };
  if (back == LOW) {
    entered = -1;
  };
  const char *options[2] = {
    " Baslat",
    " Cikis"
  };

  if (entered == -1) {
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(10,10);
    oled.println(F("Oyuna Hosgeldiniz!"));
    oled.println("");
    for (int i = 0; i < 2; i++) {
      if (i == selected) {
        oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        oled.println(options[i]);
      } else if (i != selected) {
        oled.setTextColor(SSD1306_WHITE);
        oled.println(options[i]);
      }
    }
  } else if (entered == 0) {
    oled.clearDisplay();
    game = true;
    playGame();

  } else if (entered == 1) {
    oled.clearDisplay();
    closeGame();

  }
 

  oled.display();
}

void setup() {

  pinMode(lightPin, INPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  pinMode(LED_PIN_1, OUTPUT); // LED pinlerini çıkış olarak ayarla
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);

  for (int i : digitPins) {
    pinMode(i, OUTPUT);
  }
  for (int i : segmentPins) {
    pinMode(i, OUTPUT);
  }

    for (int k : digitPins1) {
    pinMode(k, OUTPUT);
  }
  for (int k : segmentPins1) {
    pinMode(k, OUTPUT);
  }

  




  Serial.begin(9600);
  if (!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); 
  }
  oled.clearDisplay();
  oled.drawPixel(10, 20, SSD1306_WHITE);
  oled.display();
  
}


void yazdirPuan(int puan) {
  
  digitalWrite(digitPins[0], LOW);
  
  
  int birlerBasamagi = puan % 10;

  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digits[birlerBasamagi][i]);
    
  }

  

  
}
void yazdirPuan1(int puan) {
  
  digitalWrite(digitPins1[0], LOW);
  
  
  int onlarBasamagi = puan / 10;

  for (int k = 0; k < 7; k++) {
    digitalWrite(segmentPins1[k], digits1[onlarBasamagi][k]);
    
  }

  

  
}
  

void loop() {
  if (!game) {
    displaymenu();
    lightValue = analogRead(lightPin); 
  } else {
    switch (can) {
      case 3:
        digitalWrite(LED_PIN_1, HIGH); 
        digitalWrite(LED_PIN_2, HIGH);
        digitalWrite(LED_PIN_3, HIGH);
        break;
      case 2:
        digitalWrite(LED_PIN_1, HIGH); 
        digitalWrite(LED_PIN_2, HIGH);
        digitalWrite(LED_PIN_3, LOW);
        break;
      case 1:
        digitalWrite(LED_PIN_1, HIGH); 
        digitalWrite(LED_PIN_2, LOW);
        digitalWrite(LED_PIN_3, LOW);
        break;
      case 0:
        digitalWrite(LED_PIN_1, LOW); 
        digitalWrite(LED_PIN_2, LOW);
        digitalWrite(LED_PIN_3, LOW);
        break;
    }

    moveBall();
    
    if (bonusFlag){
       moveBonus();

    }
    

    if (game == false) {
      displaymenu();
    }

    checkCollision(); 
    checkLevelCompleted();
    yazdirPuan(puan); 
    yazdirPuan1(puan); 

    drawPalet();
    movePalet();
    if (bonusY + 4 >= SCREEN_HEIGHT - 4) { 
    if (bonusX >= paletKon && bonusX <= paletKon + paletGen) {
      bonusX = -bonusCanWidth; 
      bonusY = -bonusCanHeight;
      
      if (can == 1){
        can++ ;
      }else if (can == 2){
        can++ ;
      }
    }
  }

    lightValue = analogRead(lightPin);
  }
}


void closeGame() {
  oled.clearDisplay();
  oled.setTextSize(0.2);
  oled.setCursor(10, 20);
  oled.println("Oyuna gosterdiginiz");
  oled.setCursor(10, 35);
  oled.println("ilgi ve desteginiz");
  oled.setCursor(10, 50);
  oled.println("icin tesekkurler.");
  oled.display();
  
}
void checkLevelCompleted() {
  bool tuglalarBittiMi = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      if (tuglalar[i][j]) {
        tuglalarBittiMi = false; 
        break; 
      }
    }
    if (!tuglalarBittiMi) {
      break; 
    }
  }

  if (tuglalarBittiMi) {
    baslangicTuglaSayisi += 8;
    tamamlananTuglaSayisi = 0; 

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 8; j++) {
        if (tamamlananTuglaSayisi < baslangicTuglaSayisi) {
          tuglalar[i][j] = true;
          tamamlananTuglaSayisi++;
        } else {
          tuglalar[i][j] = false;
        }
      }
    }

    tuglaSayac = baslangicTuglaSayisi; // Tuğla sayısını güncelle
    
    topX = SCREEN_WIDTH / 2;
    topY = SCREEN_HEIGHT - 10;

    paletKon = SCREEN_WIDTH / 2 - 16;
    paletGen = 32;

    paletKon = SCREEN_WIDTH / 2 - paletGen / 2;

    topSpeedX = topSpeedX * 1.2;
    topSpeedY = topSpeedY * 1.2;


    if (baslangicTuglaSayisi == 32) {
      game = false;
      oled.setTextSize(1);
      oled.setTextColor(WHITE);
      oled.setCursor(30, 20);
      oled.println("Tebrikler!");
      oled.setCursor(40, 40);
      oled.print("PUAN: ");
      oled.print(puan);
      oled.display(); 
      delay(2000);
      selected = 0; 
      entered = -1; 
      
      baslangicTuglaSayisi = 8;
      puan = 0;
      can = 3;
      tamamlananTuglaSayisi = 0;
      tuglaSayac = baslangicTuglaSayisi;
      topX = SCREEN_WIDTH / 2;
      topY = SCREEN_HEIGHT - 10;
      paletKon = SCREEN_WIDTH / 2 - 16;
      paletGen = 32;
      paletKon = SCREEN_WIDTH / 2 - paletGen / 2;

    } else {
      oled.clearDisplay();
      oled.setTextSize(1);
      oled.setCursor(10, 20);
      oled.println("Bir sonraki            seviyeye gectiniz");
      oled.display();
      delay(2000);
      game = true;
    }
  }
}






void playGame() { 
  if (can == 0) {
      game = false ;  
      displaymenu(); 
    }


  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 8; j++) {
      if (tamamlananTuglaSayisi < baslangicTuglaSayisi) {
        tuglalar[i][j] = true;
        tamamlananTuglaSayisi++;
      } else {
        tuglalar[i][j] = false;
      }
    }
  }
  tuglaSayac = baslangicTuglaSayisi;

  topX = SCREEN_WIDTH / 2;
  topY = SCREEN_HEIGHT - 10;
  topSpeedX = 3;
  topSpeedY = -3;

  paletKon = SCREEN_WIDTH / 2 - 16;
  paletGen = 32;

  checkLevelCompleted();

  topX = SCREEN_WIDTH / 2;
  topY = SCREEN_HEIGHT - 10;


  paletKon = SCREEN_WIDTH / 2 - 16;
  paletGen = 32;

  paletKon = SCREEN_WIDTH / 2 - paletGen / 2;


}
void drawPalet() {

  oled.fillRect(paletKon, SCREEN_HEIGHT - 4, paletGen, 4, WHITE);
  oled.display();
}
void movePalet() {

  int potValue = analogRead(POT_PIN);

  uint8_t yeniPaletKon = map(potValue, 0, 1023, 0, SCREEN_WIDTH - paletGen);

  if (paletKon != yeniPaletKon) {
    paletKon = yeniPaletKon;
    paletKonDegisti = true;
  }
}



void drawBall() {

  oled.fillCircle(topX, topY, 2, WHITE);
  oled.display();
}
void moveBall() {

  int yeniTopX = topX + topSpeedX;
  int yeniTopY = topY + topSpeedY;
  if (topX != yeniTopX) {
  oled.clearDisplay();
  }


  if (yeniTopX < 0 || yeniTopX >= SCREEN_WIDTH) {

    topSpeedX *= -1;
  }
  if (yeniTopY < 0) {

    topSpeedY *= -1;
  } else if (yeniTopY >= SCREEN_HEIGHT) {

    can--;
    
    if (can == 0) {
      game = false ;
      
      oled.setTextSize(1);
      oled.setTextColor(WHITE);
      oled.setCursor(30, 20);
      oled.println("Oyun Bitti!");
      oled.setCursor(40, 40);
      oled.print("PUAN: ");
      oled.print(puan);
      oled.display(); 
      delay(2000);
    } else {
      
      oled.setTextSize(0.5);
      oled.setTextColor(WHITE);
      oled.setCursor(10, 30);
      oled.println("1 CAN KAYBETTIN !!!");
      oled.display();
      delay(700);
      yeniTopX = SCREEN_WIDTH / 2;
      yeniTopY = SCREEN_HEIGHT - 10;
      topSpeedX *= -1;
      topSpeedY *= -1;

      paletKon = SCREEN_WIDTH / 2 - 16;
      paletGen = 32;
    }
  }
    if (lightValue > 10){
      oled.invertDisplay(true);     
      }else {
        oled.invertDisplay(false);
      }


  topX = yeniTopX;
  topY = yeniTopY;
  drawBricks();
  drawBall();
}




void drawBricks() {
  int cizilenTuglaSayisi = 0; 
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 8; j++) {
      if(tuglalar[i][j] && cizilenTuglaSayisi < tuglaSayac) {
        oled.fillRect(j * 16, i * 8, 16, 8, WHITE);
        oled.drawRect(j * 16, i * 8, 16, 8, BLACK);
        cizilenTuglaSayisi++;
      }
    }
  }
}





void checkCollision() {
  int topSol = topX - 4;
  int topSag = topX + 4;
  int topUst = topY - 4;
  int topAlt = topY + 4;

  int tuglaGen = 16;
  int tuglaYuk = 8;

  int tuglaX, tuglaY;


  if (topY + 4 >= SCREEN_HEIGHT - 4) { 
    if (topX >= paletKon && topX <= paletKon + paletGen) {
      topSpeedY *= -1; 
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      if (tuglalar[i][j]) {
        tuglaX = j * tuglaGen;
        tuglaY = i * tuglaYuk;

        if (topSag >= tuglaX && topSol <= tuglaX + tuglaGen &&
            topAlt >= tuglaY && topUst <= tuglaY + tuglaYuk) {

          tuglalar[i][j] = false;
          tuglaSayac--;
          puan++;
          bonusFlag = true ;

          int randomSayi = random(100);

          if (randomSayi < 10) {
              drawBonus(tuglaX + tuglaGen / 2, tuglaY + tuglaYuk);
          }

          carpismaVarmi = true; 

          if (topSpeedX > 0 && topSpeedY > 0) {
            if (topSag - tuglaX < topAlt - tuglaY) {

              topSpeedX *= -1;
            } else {

              topSpeedY *= -1;
            }
          } else if (topSpeedX > 0 && topSpeedY < 0) {

            if (topSag - tuglaX < tuglaY + tuglaYuk - topUst) {

              topSpeedX *= -1;
            } else {

              topSpeedY *= -1;
            }
          } else if (topSpeedX < 0 && topSpeedY < 0) {

            if (tuglaX + tuglaGen - topSol < tuglaY + tuglaYuk - topUst) {

              topSpeedX *= -1;
            } else {

              topSpeedY *= -1;
            }
          } else if (topSpeedX < 0 && topSpeedY > 0) {

            if (tuglaX + tuglaGen - topSol < topAlt - tuglaY) {

              topSpeedX *= -1;
            } else {

              topSpeedY *= -1;
            }
          }

        }
      }
    }
  }
}






void drawBonus(int x, int y) {
  bonusX = x;
  bonusY = y;
  bonusCanHareket = true;

  oled.fillRect(bonusX, bonusY, bonusCanWidth, bonusCanHeight, WHITE);
  oled.display();
}
void moveBonus() {

  int yeniBonusX = bonusX + bonusSpeedX;
  int yeniBonusY = bonusY + bonusSpeedY;

  if (yeniBonusY >= SCREEN_HEIGHT) {

    bonusX = -bonusCanWidth; 
    bonusY = -bonusCanHeight; 
  } else {

    bonusX = yeniBonusX;
    bonusY = yeniBonusY;


  }
  
  drawBonus(bonusX, bonusY);
}