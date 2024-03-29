/*
   @files objectifySevenSegmentDisplays.ino
   @author Sebastian Cikes <cikes.sebastian@gmail.com>
   @version 1.0

   @section LICENSE

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   General Public License for more details at
   https://www.gnu.org/copyleft/gpl.html
*/

class Disp {
  private:
    const int latchPin = 8;
    const int clockPin = 12;
    const int dataPin = 11;

    unsigned long pos;
    byte value[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    void updateDisplay() {
      int decimalValue = binaryArrayToDecimal(this->value);

      shiftOut(dataPin, clockPin, MSBFIRST, decimalValue);
    }

    int binaryArrayToDecimal(byte binaryArray[]) {
      int decimalValue = 0;

      for (int i = 0; i < 8; i++) {
        decimalValue = (decimalValue << 1) | binaryArray[i];
      }

      return decimalValue;
    }

    void setLatch() {
      digitalWrite(latchPin, HIGH);
    }

    void resetLatch() {
      digitalWrite(latchPin, LOW);
    }

  public:
    Disp(unsigned long pos, bool value[8]) {
      this->pos = pos;
      memcpy(this->value, value, sizeof(this->value));

      pinMode(latchPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, OUTPUT);
    }

    Disp(unsigned long pos) {
      this->pos = pos;
      memset(this->value, 0, sizeof(this->value));

      pinMode(latchPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, OUTPUT);
    }

    // Copy constructor
    Disp(const Disp& other) {
      this->pos = other.pos;
      memcpy(this->value, other.value, sizeof(this->value));
    }

    // Copy assignment operator
    Disp& operator=(const Disp& other) {
      if (this != &other) {
        this->pos = other.pos;
        memcpy(this->value, other.value, sizeof(this->value));
      }
      return *this;
    }

    void setValue(bool newValue[8]) {
      for (byte i = 0; i < 8; i++) {
        this->value[i] = newValue[i];
      }
    }

    byte *getValue() {
      return this->value;
    }

    unsigned long getPosition() {
      return this->pos;
    }

    // Static method to update multiple displays based on their positions
    static void updateDisplays(Disp displays[], int numDisplays) {
      for (int i = 0; i < numDisplays; i++) {
        for (int j = i + 1; j < numDisplays; j++) {
          if (displays[i].getPosition() > displays[j].getPosition()) {
            // Swap displays[i] and displays[j]
            Disp temp = displays[i];
            displays[i] = displays[j];
            displays[j] = temp;
          }
        }
      }

      displays[0].resetLatch();

      // Update displays in sorted order
      for (int i = 0; i < numDisplays; i++) {
        displays[i].updateDisplay();
      }

      displays[0].setLatch();
    }
};

const bool displayValues[38][8] = {
  {0, 0, 1, 1, 1, 1, 1, 1}, //0 - 0
  {0, 0, 0, 0, 0, 1, 1, 0}, //1 - 1
  {0, 1, 0, 1, 1, 0, 1, 1}, //2 - 2
  {0, 1, 0, 0, 1, 1, 1, 1}, //3 - 3
  {0, 1, 1, 0, 0, 1, 1, 0}, //4 - 4
  {0, 1, 1, 0, 1, 1, 0, 1}, //5 - 5
  {0, 1, 1, 1, 1, 1, 0, 1}, //6 - 6
  {0, 0, 0, 0, 0, 1, 1, 1}, //7 - 7
  {0, 1, 1, 1, 1, 1, 1, 1}, //8 - 8
  {0, 1, 1, 0, 1, 1, 1, 1}, //9 - 9
  {0, 1, 1, 1, 0, 1, 1, 1}, //A - 10
  {0, 1, 1, 1, 1, 1, 0, 0}, //b - 11
  {0, 0, 1, 1, 1, 0, 0, 1}, //C - 12
  {0, 1, 0, 1, 1, 0, 0, 0}, //c - 13
  {0, 1, 0, 1, 1, 1, 1, 0}, //d - 14
  {0, 1, 1, 1, 1, 0, 0, 1}, //E - 15
  {0, 1, 1, 1, 0, 0, 0, 1}, //F - 16
  {0, 0, 1, 1, 1, 1, 0, 1}, //G - 17
  {0, 1, 1, 0, 1, 1, 1, 1}, //g - 18
  {0, 1, 1, 1, 0, 1, 1, 0}, //H - 19
  {0, 1, 1, 1, 0, 1, 0, 0}, //h - 20
  {0, 0, 0, 0, 0, 1, 1, 0}, //I - 21
  {0, 0, 0, 0, 0, 1, 0, 1}, //i - 22
  {0, 0, 0, 0, 1, 1, 0, 1}, //j - 23
  {0, 0, 1, 1, 1, 0, 0, 0}, //L - 24
  {0, 0, 1, 1, 0, 0, 0, 0}, //l - 25
  {0, 0, 1, 1, 0, 1, 1, 1}, //N - 26
  {0, 1, 0, 1, 0, 1, 0, 0}, //n - 27
  {0, 0, 1, 1, 1, 1, 1, 1}, //O - 28
  {0, 1, 0, 1, 1, 1, 0, 0}, //o - 29
  {0, 1, 1, 1, 0, 0, 1, 1}, //p - 30
  {0, 1, 1, 0, 0, 1, 1, 1}, //q - 31
  {0, 1, 0, 1, 0, 0, 0, 0}, //r - 32
  {0, 1, 1, 0, 1, 1, 0, 1}, //S - 33
  {0, 1, 1, 1, 1, 0, 0, 0}, //t - 34
  {0, 0, 1, 1, 1, 1, 1, 0}, //U - 35
  {0, 0, 0, 1, 1, 1, 0, 0}, //u - 36
  {0, 1, 1, 0, 0, 1, 1, 0}  //y - 37
};

const int numDisplays = 2;
Disp displays[numDisplays] = {
  Disp(1),
  Disp(2)
};

void setup() {
}

void loop() {
  for (int i = 0; i < 38; i++) {
    displays[0].setValue(displayValues[i]);
    Disp::updateDisplays(displays, numDisplays);
    delay(500);
  }
}
