#include "G:\My Drive\Open to public\IT\full-fledged\C, C++\Arduino\7-segment_displays\constexpr.inc"
#include "G:\My Drive\Open to public\IT\full-fledged\C, C++\Arduino\7-segment_displays\pin_defs.inc"

template<typename Ret = void, typename... Args>
inline Ret noOp(Args... args){}

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

unsigned constexpr FLICKER_INTERNAL_DELAY= 1;
inline void flicker4Digits(const byte* digs){
  digs+=4;
  for (int offset= 3; offset>=0; offset--){
    digitalWrite(D1_PIN+((offset+1)&11),HIGH);
    digitalWrite(D1_PIN+offset,LOW);
    writeNTo4Slots(*--digs);
    delay(FLICKER_INTERNAL_DELAY);
  }
}
inline void flicker4Digits(uint16_t n){
    for (int offset= 3; offset>=0; offset--){
      digitalWrite(D1_PIN+((offset+1)&11),HIGH);
      digitalWrite(D1_PIN+offset,LOW);
      writeNTo4Slots(n%10);
      n/=10;
      delay(FLICKER_INTERNAL_DELAY);
    }
}

inline void flash4Digits(const byte* digs){
  flicker4Digits(digs);
  digitalWrite(D1_PIN,HIGH);
}
inline void flash4Digits(unsigned const digs){
  flicker4Digits(digs);
  digitalWrite(D1_PIN,HIGH);
}

inline void flash5Digits(const byte* digs){
  displayN(*digs++);
  flash4Digits(digs);
  displayBits(0);
}
inline void flash5Digits(uint32_t digs){
  displayN(digs/10000);
  flash4Digits(digs%10000);
  displayBits(0);
}

template<class Digs>
inline void show4Digits(Digs digs, long unsigned const duration_ms){
	unsigned long const end= micros()+duration_ms;
	do{
		flash4Digits(digs);
	}while(micros()<end);
}

template<class Digs, long unsigned DURATION_MS=1400000>
inline void show4Digits(Digs digs){
  show4Digits(digs, DURATION_MS);
}

inline void show5Digits(const byte* digs, long unsigned const duration_ms){
  displayN(*digs++);
  show4Digits(digs,duration_ms);
  displayBits(0);
}
inline void show5Digits(uint32_t digs, long unsigned const duration_ms){
  {
    byte const n= digs/10000;
    displayN(n);
  }
  {
    digs%=10000;
	show4Digits<uint16_t>(digs,duration_ms);
  }
  {
	displayBits(0);
  }
}
template<class Digs, long unsigned DURATION_MS=1400000>
inline void show5Digits(Digs digs){
	show5Digits(digs,DURATION_MS);
}