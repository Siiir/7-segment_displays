inline void imediateSetup(){
  pinMode(NEG_EN_PIN, OUTPUT);
  digitalWrite(NEG_EN_PIN,HIGH);
}

inline void generalSetup(){
  for (int const pin : OUTPUT_PINS){
    pinMode(pin, OUTPUT);
  }
  displayBits(0); digitalWrite(NEG_EN_PIN,LOW);

  #ifndef NDEBUG
    Serial.begin(9600);
  #endif
}

inline void commonSetup(){
  imediateSetup();
  generalSetup();
}
