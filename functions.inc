#include "G:\My Drive\Open to public\IT\full-fledged\C, C++\Arduino\7-segment_displays\constexpr.inc"
#include "G:\My Drive\Open to public\IT\full-fledged\C, C++\Arduino\7-segment_displays\pin_defs.inc"

inline void dPinsWrite(byte const val){
  for(int const pin : DN_PIN)  digitalWrite(pin, val);
}

// For 5161AS
inline void displayBits(byte const bits){
    digitalWrite(LATCH_PIN,LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, bits);
    digitalWrite(LATCH_PIN,HIGH);
}

inline void displayN(byte const nBeneath10){
  displayBits(SEG_N_BITS[nBeneath10]);
}

// For SH546 1AS
inline void writeBitsTo4Slots(byte bits){
  for (int pin= 9; pin>=2; pin--){
    byte const bit= bits&1;
    digitalWrite(pin, bit);
    bits>>=1;
  }
}
inline void writeNTo4Slots(byte const nBeneath10){
  writeBitsTo4Slots(SEG_N_BITS[nBeneath10]);
}
inline void writeNTo5Slots(byte const nBeneath10){
  displayN(nBeneath10);
  writeNTo4Slots(nBeneath10);
}
inline void displayNIn5Slots(byte const nBeneath10){
  dPinsWrite(LOW);
  writeNTo5Slots(nBeneath10);
}

unsigned constexpr FLICKER_INTERNAL_DELAY= 1000;
inline void flicker4Digits(const byte* digs){
  digs+=4;
  for (int offset= 3; offset>=0; offset--){
    digitalWrite(D1_PIN+((offset+1)&11),HIGH);
    digitalWrite(D1_PIN+offset,LOW);
    writeNTo4Slots(*--digs);
  }
  delay(FLICKER_INTERNAL_DELAY);
}
inline void flicker4Digits(unsigned n){
    for (int offset= 3; offset>=0; offset--){
      digitalWrite(D1_PIN+((offset+1)&11),HIGH);
      digitalWrite(D1_PIN+offset,LOW);
      writeNTo4Slots(n%10);
      n/=10;
    }
    delay(FLICKER_INTERNAL_DELAY);
}

inline void flash4Digits(const byte* digs){
  flicker4Digits(digs);
  digitalWrite(D1_PIN,HIGH);
}
inline void flash4Digits(unsigned const digs){
  flicker4Digits(digs);
  digitalWrite(D1_PIN,HIGH);
}

inline void display5Digits(const byte* digs){
  displayN(*digs++);
  flash4Digits(digs);
}
inline void display5Digits(uint32_t digs){
  {
    byte const n= digs/10000;
    displayN(n);
  }
  {
    digs%=10000;
    flash4Digits(digs);
  }
}
inline void display5Digits(uint32_t digs, unsigned long const mSec){
  {
    byte const n= digs/10000;
    displayN(n);
  }
  {
    digs%=10000;
  
    unsigned long start, end;
    for (start= micros(), end= start+mSec;    micros()<end;)
        flash4Digits(digs);
  }
}
