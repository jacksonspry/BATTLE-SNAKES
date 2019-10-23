class createbody {
  public:
#include <Adafruit_NeoPixel.h>
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, 15, NEO_GRB + NEO_KHZ800);
    byte led[64] = {0, 1, 2, 3, 4, 5, 6, 7, 15, 14, 13, 12, 11, 10, 9, 8, 16, 17, 18, 19, 20, 21, 22, 23, 31, 30, 29, 28, 27, 26, 25, 24, 32, 33, 34,
                    35, 36, 37, 38, 39, 47, 46, 45, 44, 43, 42, 41, 40, 48, 49, 50, 51, 52, 53, 54, 55, 63, 62, 61, 60, 59, 58, 57, 56
                   }; //array the swaps every other row of the matrix to create an x y plane instead of snake pattern
    int body1[16]; //array for storing body positions of player 1
    int body2[16];
    int l1, r1, c1, l2, r2, c2;
    void pushcoords (int r1, int c1, int r2, int c2) { //get current coords
      for (int pos = 15; pos > 2; pos = pos - 2) { //shift pairs of coords down one entry in the array
        body1[pos] = body1[pos - 2];
        body1[pos - 1] = body1[pos - 3];
        body2[pos] = body2[pos - 2];
        body2[pos - 1] = body2[pos - 3];
      }
      body1[0] = r1; //write new coords in the first array entry
      body1[1] = c1; //first two entries (for a coordinate pair)
      body2[0] = r2;
      body2[1] = c2;
    }
    void setlength(int l1, int l2) { //input snanke lengths
      strip.setPixelColor(led[body1[(l1 * 2)] + body1[l1 * 2 + 1] * 8], 0, 0, 0); //draw the end pixel off
      strip.setPixelColor(led[body2[(l2 * 2)] + body2[l2 * 2 + 1] * 8], 0, 0, 0); //draw the end pixel off
      strip.show();
      body1[l1 * 2] = 0; //erase the array entry longer than the snake
      body1[(l1 * 2) + 1] = 0;
      body2[l2 * 2] = 0;
      body2[(l2 * 2) + 1] = 0;
    }
    void draw() {
      strip.setPixelColor(led[body1[0] + body1[1] * 8], 255, 0, 0); //draw the new head of p1 snake
      strip.setPixelColor(led[body2[0] + body2[1] * 8], 0, 0, 255);
      strip.show();
    }
    void checkcollision() {
      for (int k = 0; k < l1 * 2; k = k + 2) {
        if (r1 == body2[2 + k] && c1 == body2[3 + k]) {
          int p2win = 1;
          while (p2win == 1) {
          }
        }
      }
      for (int k = 0; k < l1 * 2; k = k + 2) {
        if (r2 == body1[2 + k] && c2 == body1[3 + k]) {
          int p1win = 1;
          while (p1win == 1) {
          }
        }
      }
    }
};



class Food {
  public:
    int location = -1;
    int checkfood(createbody body) {
      if (location == -1) {
        return 0;
      }
      
      int l1 = body.body1[0] + 8 * body.body1[1];
      int l2 = body.body2[0] + 8 * body.body2[1];
      if (l1 == location) {
        return 1;
      }
      else {
        if (location == l2) {
          return 2;
        }

        else {
          return 0;
        }
      }
    }

    int makefood (createbody body, int a) {
      int f = random(64);
      Serial.print(f);
      for (int i = 0; i < body.l1 * 2; i = i + 2) {
        int check = body.body1[i] + body.body1[i + 1] * 8;
        Serial.print("hello1");
        if (check == f) {
          
          f = -1;
          break;
        }
        Serial.print("hello");
        if (f == -1) {
          makefood(body, a);
        }
      }
     
      for (int i = 0; i < body.l2 * 2; i = i + 2) {
        int check = body.body2[i] + body.body2[i + 1] * 8;
        if (check == f) {
          f = -1;
          break;
        }
      }
      if (f == -1) {
        makefood(body, a);
      }
      Serial.print(" f:");
       Serial.print(f);
      location = f;
      return f;
    }
};












