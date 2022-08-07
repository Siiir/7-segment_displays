inline void imediateSetup(){
  pinMode(NEG_EN_PIN, OUTPUT);
  digitalWrite(NEG_EN_PIN,HIGH);
}

inline void generalSetup(){
  int constexpr OUTPUT_PINS[]= {BASIC_SR_PINS,   D_PINS};
  for (int const pin : OUTPUT_PINS){
    pinMode(pin, OUTPUT);
  }

  displayBits(0); digitalWrite(NEG_EN_PIN,LOW);
}
