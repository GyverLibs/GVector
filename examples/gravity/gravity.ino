// движение планеты вокруг солнца

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

int w = 400, h = 300;
GVector pos(100, 100);
GVector vel(2, -1);

void loop() {
    GVector center(w / 2, h / 2);
    GVector dir = GVector::sub(center, pos);

    // "сила тяжести"
    GVector accel = dir.normalized().mul(1000 / dir.magSq()).limit(5);

    vel += accel;
    pos += vel;
    printCanvas(w / 10, h / 10, pos.x / 10, pos.y / 10);
    delay(400);
}