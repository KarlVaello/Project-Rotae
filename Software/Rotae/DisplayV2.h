
#ifndef DisplayV2_H
#define DisplayV2_H

#include <Arduino.h>
#include <TFT_HX8357_Due.h> // Hardware-specific library
#include <URTouch.h>
#include <URTouchCD.h>
//#include <UTFT_Buttons.h>

#include "LiveData.h"
#include "Chrono.h"




class DisplayV2 {
  public:
    DisplayV2();
    ~DisplayV2();
    void DisplayV2UI(LiveData ld);
    void DisplayV2Init();
};

#endif
