#include "functions.inc"
#include "setups.inc"

namespace jointCountUpTo9{
  void setup(){
    commonSetup();
    pinMode(POT_PIN,INPUT);
    pinMode(BUT_PIN,INPUT_PULLUP);

    #ifndef NDEBUG
      #define showSize(type)\
        Serial.print("sizeof(" #type ") == "); Serial.print(sizeof(type))
      #define nl Serial.print('\n');
      #define tb Serial.print('\t');

      nl nl nl

      #undef nl
      #undef tb
    #endif

    dPinsWrite(LOW);
  }

  void loop(){
    // Preinitialized loop variables
      static unsigned long iter_delay= 1000000ul;
      static uint_fast8_t n=0;

    LOOP_START:
      // Debug-loop variables
      #ifndef NDEBUG
        long unsigned constexpr SER_DEBUG_DELAY= 1000000;
        static long unsigned next_debug_time= 0;
        if (micros()>=next_debug_time){
          Serial.print("Debug "); Serial.print(next_debug_time/1000); Serial.print(":\t"
            "`iter_delay` == "); Serial.print(iter_delay); Serial.print(";  "
            "“button value“ == "); Serial.print(analogRead(BUT_PIN)); Serial.print(";  "
            "`n` == "); Serial.print(n); Serial.print(";  ");
          Serial.print("\n");
          next_debug_time= micros()+SER_DEBUG_DELAY;
        }
      #endif

      writeNTo5Slots(n);
      {
        unsigned long const end= micros()+iter_delay;
        do{
          auto const cur_pot= analogRead(POT_PIN);
          iter_delay= cur_pot*5000ul;

          uint16_t const cur_but= analogRead(BUT_PIN);
          if (cur_but<=400){
            n= 0; goto LOOP_START;
          }
        }while(micros()<end);
      }

    n++; n%=10;
  }
}


namespace countUpProgram{
  void setup(){
    commonSetup();

    for (unsigned m=0; m<120; m++) {
      display5Digits(m, 4*FLICKER_INTERNAL_DELAY);
    }
  }

  void loop(){}
}


namespace _ {
  void setup(){
    commonSetup();
  }
  void loop(){}
}