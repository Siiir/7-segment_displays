#include "functions.inc"

namespace jointCountUpTo9{
  void setup(){
    dPinsWrite(LOW);
    for (uint_fast8_t n=0; n<10; n++){
      writeNTo5Slots(n);
      delay(2000);
    }
  }
}

void countUpProgram(){
  for (unsigned m=0; m<120; m++) {
    display5Digits(m, 4*FLICKER_INTERNAL_DELAY);
  }
}
