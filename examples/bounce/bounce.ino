// движение с отскоком от стен

#include <Arduino.h>
#include <GVector.h>

void printCanvas(int w, int h, int tx, int ty) {
    Serial.print(' ');
    for (int x = 0; x < w; x++) Serial.write("__", 2);
    Serial.println(' ');

    for (int y = 0; y < h; y++) {
        Serial.print('|');
        for (int x = 0; x < w; x++) {
            if (x == tx && y == ty) Serial.write("[]", 2);
            else Serial.write(y == h - 1 ? "__" : "  ", 2);
        }
        Serial.println('|');
    }
    Serial.println();
    Serial.println();
}

void setup() {
    Serial.begin(115200);
}

int w = 200, h = 100;
GVector pos(w / 2, h / 2);
GVector vel(12, 9);

void loop() {
    pos += vel;
    if (pos.x >= w || pos.x < 0) {
        pos.x = constrain(pos.x, 0, w - 1);
        vel.reflectY();
    }
    if (pos.y >= h || pos.y < 0) {
        pos.y = constrain(pos.y, 0, h - 1);
        vel.reflectX();
    }
    printCanvas(w / 10, h / 10, pos.x / 10, pos.y / 10);
    delay(400);
}