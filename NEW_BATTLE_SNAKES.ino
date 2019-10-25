#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, 15, NEO_GRB + NEO_KHZ800);
const int buttons[2][2] = {{14, 16}, {5, 4}}; //{{rb1, lb1},{rb2,lb2}}
const int led1 = 0, led2 = 12;
byte locks[2];
int props[2][3] = {{3, 0, 5}, {1, 0, 3}}; //{{props1, change1, length 1}, {props2, change2, length 2}}
int body [2][16][2] = {{{5, 7}}, {{2, 0}}}; //[player], [segment], [coords(r,c)]
int timedraw = 200;
byte led[64] = {0, 1, 2, 3, 4, 5, 6, 7, 15, 14, 13, 12, 11, 10, 9, 8, 16, 17, 18, 19, 20, 21, 22, 23, 31, 30, 29, 28, 27, 26, 25, 24, 32, 33, 34,
                35, 36, 37, 38, 39, 47, 46, 45, 44, 43, 42, 41, 40, 48, 49, 50, 51, 52, 53, 54, 55, 63, 62, 61, 60, 59, 58, 57, 56
               }; //array the swaps every other row of the matrix to create an x y plane instead of snake pattern

void setup() {
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      pinMode (buttons[i][j], INPUT);
    }
  }

  strip.begin(); //begin led strip
  strip.show();    // initialize all pixels to 'off'
  Serial.begin (9600);
}

void loop() {
  delay(20);
  for (int i = 0; i < 2; i++) {
    if (props[i][1] == 0) {
      props[i][1] = readbut(buttons[i][0], buttons[i][1], i);
    }
  }
  if (millis() > timedraw) {
    Serial.print("\n");
    for (int i = 0; i < 5; i++) {
      Serial.print(" ");
      for (int k = 0; k < 2; k++){
        Serial.print(body[0][i][k]);
      }
    }
    changedir();
    writecoords();
    checkcolision();
    eraseplayer();
    drawplayer();
    timedraw = timedraw + 225;
  }
}

int readbut(int rb , int lb, int l) { //used to translate button inputs into  when given a player's button pins
  if (digitalRead(lb) == 0 && digitalRead(rb) == 0) { //if both buttons are depressed
    locks[l] = 0;
    return 0;
  }
  if (digitalRead(rb) != digitalRead(lb) && locks[l] == 0) { //if player 1s right button is pressed and the other value is not set
    locks[l] = 1;
    return (digitalRead(rb) - digitalRead(lb));
  }
  else {
    return 0;
  }
}

void changedir() {
  for (int i = 0; i < 2; i++) {
    if (props[i][1] != 0) {
      props[i][0] = props[i][0] + props[i][1];
      if (props[i][0] < 0 || props[i][0] > 3) {
        props[i][0] = (((props[i][0] + 1) * (-3) / 5) + 3);
      }
      props[i][1] = 0;
    }
  }
}

void writecoords() {
  for (int i = 0; i < 2; i++) {
    for (int p = props[i][2]; p > 0; p--) {
      body[i][p][0] = body[i][p-1][0];
      body[i][p][1] = body[i][p-1][1];
    }
    for (int j = 0; j < 2; j++) {
      body[i][0][j] = (body[i][1][j] + (- abs(props[i][0] - 2 + j) + 1));
      if (body[i][0][j] > 7 || body[i][0][j] < 0) {
        body[i][0][j] = (((body[i][0][j] + 1) * (-7) / 9) + 7);
      }
    }
  }
}

void checkcolision(){
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < props[abs(i-1)][2]; j++){
      if ((body[i][0][0] == body[abs(i-1)][j][0]) && (body[i][0][1] == body[abs(i-1)][j][1])){
        Serial.print(3-i);
        Serial.print(" wins");
        delay(2000);
      }
    }
  }
}

void drawplayer() {
  for (int i = 0; i < 2; i++) {
    strip.setPixelColor(led[body[i][0][0] + body[i][0][1] * 8], 255 - (255 * i), 0, 255 * i);
  }
  strip.show();
}

void eraseplayer() {
  for (int i = 0; i < 2; i++) {
    strip.setPixelColor(led[body[i][props[i][2]][0] + body[i][props[i][2]][1] * 8], 0, 0, 0);
  }
}

