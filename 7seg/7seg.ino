const int SEVENSEG[7] = {7, 8, 9, 10, 11, 12, 13};

const int number[10][7] = {
  {0, 1, 1, 1, 1, 1, 1}, //0
  {0, 0, 0, 1, 0, 0, 1}, //1
  {1, 0, 1, 1, 1, 1, 0}, //2
  {1, 0, 1, 1, 0, 1, 1}, //3
  {1, 1, 0, 1, 0, 0, 1}, //4
  {1, 1, 1, 0, 0, 1, 1}, //5
  {1, 1, 1, 0, 1, 1, 1}, //6
  {0, 1, 1, 1, 0, 0, 1}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {1, 1, 1, 1, 0, 1, 1}  //9
};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 7; i++) {
    pinMode(SEVENSEG[i], OUTPUT);
  }
}

void loop() {
  while (Serial.available() >= sizeof(int) ) {
    char buff = char(Serial.read());
    int num = int(buff) - 48;
    Serial.println(num);
    if (0 <= num && num <= 9) {
      for (int i = 0; i < 7; i++) {
        digitalWrite(SEVENSEG[i], number[num][i]);
      }
    }
    delay(10);
  }
}
