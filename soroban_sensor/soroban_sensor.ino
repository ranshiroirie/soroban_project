#define Threshold 600
#define LEDPIN_COUNT 7

const int PIN[5] = {14, 15, 16, 17, 18};
const int LEDPIN[LEDPIN_COUNT] = {7, 8, 9, 10, 11, 12, 13};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < LEDPIN_COUNT; i++) {
    pinMode(LEDPIN[i], OUTPUT);
  }
}

void loop() {
  int juzu[5];
  int pinread [5];
  for (int i = 0; i < 5; i++) {
    pinread[i] = analogRead(PIN[i]);
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
