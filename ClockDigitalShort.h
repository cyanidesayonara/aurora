/*
 * Aurora: https://github.com/pixelmatix/aurora
 * Copyright (c) 2014 Jason Coon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

// Portions of this code are adapted from PJRC DS1307RTC Library: https://www.pjrc.com/teensy/td_libs_DS1307RTC.html
// Uses PJRC Time Library: https://www.pjrc.com/teensy/td_libs_Time.html

#ifndef ClockDigitalShort_H
#define ClockDigitalShort_H



enum SetTimeState {
  SetHour,
  SetMinute,
  SetSecond,
};

static const unsigned int SetTimeStatesCount = 3;
SetTimeState SetTimeStates[SetTimeStatesCount] = {
  SetHour,
  SetMinute,
  SetSecond,
};

class ClockDigitalShort : public Drawable {
  public:
    char timeBuffer[9];
    uint8_t y = 11;
    uint8_t x = 11;
    rgb24 color = CRGB(CRGB::White);

    bool twentyFourHour = false;

    unsigned int drawFrame() {
      return drawFrame(y);
      return drawFrame(x);
    }

    unsigned int drawFrame(const int cy) {
      int x = 13;

      if (isTimeAvailable) {
        uint8_t hour = time.Hour;
        if (!twentyFourHour && hour > 12)
          hour -= 12;
        else if (!twentyFourHour && hour == 0)
          hour = 12;

        indexedLayer.setFont(font8x13);
        sprintf(timeBuffer, "%02d:%02d", hour, time.Minute);

//        if (hour < 10)
//          x = 4;
      }
      else {
        indexedLayer.setFont(font3x5);
        sprintf(timeBuffer, "No Clock");
      }

      indexedLayer.setIndexedColor(1, color);
      indexedLayer.fillScreen(0);
      indexedLayer.drawString(x, cy, 1, timeBuffer);

      return 0;
    }

//    void drawMoveClockIndicator() {
//      for (int16_t x = 2; x <= 26; x += 6) {
        // upper indicators (in case the clock's at the bottom)
//        backgroundLayer.drawTriangle(x + 0, y - 1, x + 1, y - 2, x + 2, y - 1, CRGB(CRGB::SlateGray));

        // lower indicators (in case the clock's at the top)
//        backgroundLayer.drawTriangle(x + 0, y + 11, x + 1, y + 12, x + 2, y + 11, CRGB(CRGB::SlateGray));
//      }
//    }

    char* clockYFilename = (char*) "clockY.txt";
//    char* clockXFilename = (char*) "clockX.txt";
    char* clock24hFilename = (char*) "clock24h.txt";

    void loadSettings() {
      y = loadByteSetting(clockYFilename, 11);
//      x = loadByteSetting(clockXFilename, 11);
      twentyFourHour = loadByteSetting(clock24hFilename, 0) == 1;
      boundY();
//      boundX();
    }

    void saveSettings() {
      saveClockYSetting();
//      saveClockXSetting();
    }

    void saveClockYSetting() {
      saveIntSetting(clockYFilename, y);
    }

//    void saveClockXSetting() {
//      saveIntSetting(clockXFilename, x);
//    }

    void saveTwentyFourHourSetting() {
      saveIntSetting(clock24hFilename, twentyFourHour);
    }

    void boundY() {
      if (y < -1)
        y = -1;
      else if (y > 55)
        y = 55;
    }

//    void boundX() {
//      if (x < 0)
//        x = 0;
//      else if (x > 34)
//        x = 34;
//    }
};
extern ClockDigitalShort clockDigitalShort;

#endif
