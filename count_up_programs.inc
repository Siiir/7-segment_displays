#include "functions.inc"
#include "setups.inc"

template <class Counter, void(*DISP)(Counter), void(*SHOW)(Counter), Counter STOP_N>
class CountUpToStop{
  public:
    static void setup(){
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
    }

    static void loop(){
      // Preinitialized loop variables
        static unsigned long iter_delay= 1000000ul;
        static Counter n=0;

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

		DISP(n);
        {
          unsigned long const end= micros()+iter_delay;
          do{
			SHOW(n); // >4ms
            auto const cur_pot= analogRead(POT_PIN);
            iter_delay= cur_pot*5000ul;

			SHOW(n); // >4ms
            uint16_t const cur_but= analogRead(BUT_PIN);
            if (cur_but<=400){
              n= 0; goto LOOP_START;
            }
          }while(micros()<end);
        }

      n++; n%=STOP_N;
    }
};

template <class Counter, void(*DISP)(Counter), Counter STOP_N>
using CountUpToStopWithDisp= CountUpToStop<Counter, DISP, &noOp, STOP_N>;
template <class Counter, void(*SHOW)(Counter), Counter STOP_N>
using CountUpToStopWithShow= CountUpToStop<Counter, &noOp, SHOW, STOP_N>;


using JointCountUpTo9= CountUpToStopWithDisp<
	byte,
	&displayNIn5Slots,
	10
>;
using CountUpTo9999= CountUpToStopWithShow<
	uint16_t,
	&flash4Digits,
	9999
>;
using CountUpTo99999= CountUpToStopWithShow<
	uint32_t,
	&flash5Digits,
	99999
>;