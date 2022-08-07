// Output pins
int constexpr
  DATA_PIN= 11,  // SER
  CLOCK_PIN= 12, // SRCLK
  LATCH_PIN= 13,  // RCLK
  NEG_EN_PIN= 10  // ̅EN
;
#define BASIC_SR_PINS\
  DATA_PIN,\
  CLOCK_PIN,\
  LATCH_PIN


int constexpr
  D1_PIN= A1,
  D2_PIN= A2,
  D3_PIN= A3,
  D4_PIN= A4
;
#define D_PINS\
  D1_PIN,\
  D2_PIN,\
  D3_PIN,\
  D4_PIN
int constexpr DN_PIN[]= {D_PINS};

int constexpr OUTPUT_PINS[]= {BASIC_SR_PINS,   D_PINS};




// Input pins
int constexpr
  POT_PIN= A0,
  BUT_PIN= A5
;
#define IN_PINS\
  POT_PIN,\
  BUT_PIN
int constexpr INPUT_PIN_N[]= {IN_PINS};