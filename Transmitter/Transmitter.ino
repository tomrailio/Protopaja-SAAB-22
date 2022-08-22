#define LE_PIN 4
#define DATA_PIN 11
#define CLK_PIN 13

/* Synthesizer register value, calculated with ADF4350 evaluation board software
   On RF Settings:
       Output frequency: 2400 Mhz
       Reference frequency: 10 Mhz
       
   On Register 4:
       RF output power: -4dbm
       
   Leave all other fields unchanged
*/
#define REGISTER_5 0x580005U
#define REGISTER_4 0x850024U
#define REGISTER_3 0x4B3U
#define REGISTER_2 0x4E42U
#define REGISTER_1 0x8008011U
#define REGISTER_0 0x780000U

#define GREEN_LED 10
// #define BUTTON 2


#define DELAY 1

// Set up basic pins: LE, CLK, DATA for synthesizer,
// GREEN_LED indicates that the microcontroller is active
void setup_ports() {
  pinMode(LE_PIN, OUTPUT);
  digitalWrite(LE_PIN, HIGH);

  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  // Turn on the green LED when the device is powered
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(GREEN_LED, HIGH);
  
  //pinMode(BUTTON, INPUT);

  digitalWrite(CLK_PIN, LOW);
  digitalWrite(DATA_PIN, LOW);
}

// Write binary data to synthesizer registers
void write_register(unsigned long value) {
  digitalWrite(LE_PIN, LOW);
  delayMicroseconds(DELAY);
  for (int i=31; i >= 0; i--) {                    
    if ((value >> i) & 1)
      digitalWrite(DATA_PIN, HIGH);
    else
      digitalWrite(DATA_PIN, LOW);
    delayMicroseconds(DELAY);
    digitalWrite(CLK_PIN, HIGH);
    delayMicroseconds(DELAY);
    digitalWrite(CLK_PIN, LOW);
    delayMicroseconds(DELAY);
  }
  digitalWrite(DATA_PIN, LOW);
  digitalWrite(LE_PIN, HIGH);
  delayMicroseconds(DELAY);
}

void setup() {
  setup_ports();
  delay(1000);
  
  // Programming the synthesizer output level and other functions
  write_register(REGISTER_5);
  write_register(REGISTER_4);
  write_register(REGISTER_3);
  write_register(REGISTER_2);
  write_register(REGISTER_1);
  write_register(REGISTER_0);
}

void loop() {
}
