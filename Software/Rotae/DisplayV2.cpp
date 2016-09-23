
#include "DisplayV2.h"

#include <TFT_HX8357_Due.h> // Hardware-specific library

TFT_HX8357_Due tft = TFT_HX8357_Due();       // Invoke custom library

//<<constructor>>

DisplayV2::DisplayV2() {
}

//<<destructor>>
DisplayV2::~DisplayV2() {
  /*nothing to destruct*/
}


/*
  Control init isplay at star on setup arduino function.
  This set up somo importand display config
*/
void DisplayV2::DisplayV2Init() {

  tft.begin();
  tft.setRotation(180);
  tft.fillScreen(tft.color565(210, 215, 211)); // Clear screen to navy background

  tft.fillRect(0, 0, 480, 20, tft.color565(103, 129, 159));

}



void DisplayV2::DisplayV2UI(LiveData ld){
}
