#define Threshold 600
#define LEDPIN_COUNT 7

//MUX 設定
const int controlPin[4] = {3, 4, 5, 6};
const int SIG_pin = 14;
const int muxChannel[16][4] = {
  {0, 0, 0, 0}, //channel 0
  {1, 0, 0, 0}, //channel 1
  {0, 1, 0, 0}, //channel 2
  {1, 1, 0, 0}, //channel 3
  {0, 0, 1, 0}, //channel 4
  {1, 0, 1, 0}, //channel 5
  {0, 1, 1, 0}, //channel 6
  {1, 1, 1, 0}, //channel 7
  {0, 0, 0, 1}, //channel 8
  {1, 0, 0, 1}, //channel 9
  {0, 1, 0, 1}, //channel 10
  {1, 1, 0, 1}, //channel 11
  {0, 0, 1, 1}, //channel 12
  {1, 0, 1, 1}, //channel 13
  {0, 1, 1, 1}, //channel 14
  {1, 1, 1, 1} //channel 15
};

const int PIN[5] = {0, 1, 2, 3, 4};
const int LEDPIN[LEDPIN_COUNT] = {7, 8, 9, 10, 11, 12, 13};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(controlPin[i], OUTPUT);
    digitalWrite(controlPin[i], LOW);
  }
  for (int i = 0; i < LEDPIN_COUNT; i++) {
    pinMode(LEDPIN[i], OUTPUT);
  }
}

void loop() {
  int juzu[5];
  int pinread [5];
  for (int i = 0; i < 5; i++) {
    pinread[i] = readMux(PIN[i]);
    //    Serial.print(pinread[i]);
    //    Serial.print(" ");
    if (pinread[i] >= Threshold) {
      juzu[i] = 1;
    } else {
      juzu[i] = 0;
    }
  }
  //  Serial.println("");

  int ledswitch[LEDPIN_COUNT] = {1, 1, 1, 1, 1, 1, 1};
  if (juzu[1] == 0) {
    ledswitch[2] = 0;
  } else if (juzu[2] == 0) {
    ledswitch[3] = 0;
  } else if (juzu[3] == 0) {
    ledswitch[4] = 0;
  } else if (juzu[4] == 0) {
    ledswitch[5] = 0;
  } else {
    ledswitch[6] = 0;
  }
  if (juzu[0] == 1) {
    ledswitch[0] = 0;
    ledswitch[1] = 1;
  } else {
    ledswitch[0] = 1;
    ledswitch[1] = 0;
  }

  for (int i = 0; i < LEDPIN_COUNT; i++) {
    digitalWrite(LEDPIN[i], ledswitch[i]);
  }

  int count = 0;
  if (juzu[1] == 0) {
    count = 0;
  } else if (juzu[2] == 0) {
    count = 1;
  } else if (juzu[3] == 0) {
    count = 2;
  } else if (juzu[4] == 0) {
    count = 3;
  } else {
    count = 4;
  }
  if (juzu[0] == 1) {
    count += 5;
  }

  Serial.println(count);
  Serial.write(count);
  delay(100);
}

int readMux(int channel) {
  //loop through the 4 sig
  for (int i = 0; i < 4; i ++) {
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  //read the value at the SIG pin
  int val = analogRead(SIG_pin);
  //return the value
  return val;
}
