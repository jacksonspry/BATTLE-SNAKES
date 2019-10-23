#include <Adafruit_NeoPixel.h>
#include "create.body.h";
Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, 15, NEO_GRB + NEO_KHZ800);
createbody body;
Food f;
int dir1 = 3, row1 = 5, col1 = 7, lock1 = 0, rt1 = 0, lt1 = 0, length1 = 5, lock = 0; //player 1 variables
int dir2 = 1, row2 = 2, col2 = 0, lock2 = 0, rt2 = 0, lt2 = 0, length2 = 5, needfood = 1, food; //player 2 variables
const int p1rb = 14, p1lb = 16, p2rb = 5, p2lb = 4, led1 = 0, led2 = 12;
float timedraw = 300;

void setup() {
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (p1rb, INPUT);
  pinMode (p1lb, INPUT);
  pinMode (p2rb, INPUT);
  pinMode (p2lb, INPUT);
  strip.begin(); //begin led strip
  strip.show();    // initialize all pixels to 'off'
  Serial.begin (9600);
}

void loop() {
  delay(20); // short delay
  readbuttons();
  if (millis() > timedraw && lock == 0) { //if the time has surpassed the next incriment time, incriment again
    lock = 1; //a lock to ensure it only activates movplayers once
//    if (needfood == 1) {
//     food = f.makefood(body, 1);
//     Serial.print(food);
//     strip.setPixelColor(food, 100, 100, 100);
//     strip.show();
//      needfood = 0;
//    }
    moveplayers();
    timedraw = timedraw + 225; //amount of milliseconds between pixels drawn
  }
  lock = 0; //turn the lock off
}

void readbuttons() { //to translate button inputs
  if (digitalRead(p1rb) == 1 && lt1 == 0 && lock1 == 0) { //if player 1s right button is pressed and the other value is not set
    rt1 = 1; //variable to incriment the direction right
    lock1 = 1; //lock inputs until both buttons are unpressed
  }
  if (digitalRead(p1lb) == 1 && rt1 == 0 && lock1 == 0) {
    lt1 = 1;
    lock1 = 1;
  }
  if (digitalRead(p1lb) == 0 && digitalRead(p1rb) == 0) { //loop to unlock the buttons when both are unpresesd
    lock1 = 0;
  }
  if (digitalRead(p2rb) == 1 && lt2 == 0 && lock2 == 0) {
    rt2 = 1;
    lock2 = 1;
  }
  if (digitalRead(p2lb) == 1 && rt2 == 0 && lock2 == 0) {
    lt2 = 1;
    lock2 = 1;
  }
  if (digitalRead(p2lb) == 0 && digitalRead(p2rb) == 0) {
    lock2 = 0;
  }
}

void moveplayers() {
  changedirection();
  incrimenthead();
  body.pushcoords (row1, col1, row2, col2);
  body.setlength (length1, length2);
  body.checkcollision();
  body.draw();
//  if (f.checkfood(body) == 1) {
//    length1++;
//    needfood = 1;
//  }
//    if (f.checkfood(body) == 2) {
//    length2++;
//    needfood = 1;
//  }
}
void changedirection() {
  if (lt1 == 1 || rt1 == 1) { //if either of the change direction inputs are on for p1
    dir1 = dir1 + rt1 - lt1; //incriment the direction up or down based on the input
    rt1 = 0; //turn direction changers off
    lt1 = 0;
    if (dir1 < 0 || dir1 > 3) { //if direction is outside of the 4 possible
      dir1 = (((dir1 + 1) * (-3) / 5) + 3); //warp the direction back around
    }
  }
  if (lt2 == 1 || rt2 == 1) { //do the same for p2
    dir2 = dir2 + rt2 - lt2;
    rt2 = 0;
    lt2 = 0;
    if (dir2 < 0 || dir2 > 3) {
      dir2 = (((dir2 + 1) * (-3) / 5) + 3);
    }
  }
}

void incrimenthead() {
  row1 = row1 + (- abs(dir1 - 2) + 1); //add or subtract a row if the direction is 2 or 0 respectivley
  col1 = col1 + (- abs(dir1 - 1) + 1); //add or subtract a column if the direction is 1 or 3 respectivley
  row2 = row2 + (- abs(dir2 - 2) + 1); //same for p2
  col2 = col2 + (- abs(dir2 - 1) + 1);
  if (col1 > 7 || col1 < 0) { //if the column goes out of bounds
    col1 = (((col1 + 1) * (-7) / 9) + 7); //warp it to the other side of the screen
  }
  if (row1 > 7 || row1 < 0) { //if the row goes out of bounds
    row1 = (((row1 + 1) * (-7) / 9) + 7); //warp it to the other side of the screen
  }
  if (col2 > 7 || col2 < 0) {
    col2 = (((col2 + 1) * (-7) / 9) + 7);
  }
  if (row2 > 7 || row2 < 0) {
    row2 = (((row2 + 1) * (-7) / 9) + 7);
  }
}


