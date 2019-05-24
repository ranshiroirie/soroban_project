const int DATAPIN[3] = {4, 7, 10};
const int LATCHPIN[3] = {5, 8, 11};
const int CLOCKPIN[3] = {6, 9, 12};
const int KETA = 3; //桁数
const int number[11][8] = { //7セグに表示する数字
  {0, 1, 1, 1, 1, 1, 1, 0}, //0
  {0, 0, 0, 1, 0, 0, 1, 0}, //1
  {1, 0, 1, 1, 1, 1, 0, 0}, //2
  {1, 0, 1, 1, 0, 1, 1, 0}, //3
  {1, 1, 0, 1, 0, 0, 1, 0}, //4
  {1, 1, 1, 0, 0, 1, 1, 0}, //5
  {1, 1, 1, 0, 1, 1, 1, 0}, //6
  {0, 1, 1, 1, 0, 0, 1, 0}, //7
  {1, 1, 1, 1, 1, 1, 1, 0}, //8
  {1, 1, 1, 1, 0, 1, 1, 0}, //9
  {0, 0, 0, 0, 0, 0, 0, 0} //OFF
};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 3; i++) {
    pinMode(DATAPIN[i], OUTPUT);
    pinMode(LATCHPIN[i], OUTPUT);
    pinMode(CLOCKPIN[i], OUTPUT);
  }
  delay(2000);
}

int keta = 1;
bool getdata = false;
void loop() {
  while (Serial.available() >= sizeof(int) ) {
    char buff = char(Serial.read());
    int num = int(buff) - 48;
    //    Serial.println(num);
    int kazu[4];
    if (0 <= num && num <= 9) {
      getdata = true;
      kazu[keta] = num;
      output(num, keta);
      keta++;
    } else {
      if (getdata == true) {
      }
      getdata = false;
      keta = 1;
    }
    if (kazu[3] == 0) {
        output(10, 3);
        if (kazu[2] == 0) {
          output(10, 2);
        }
      }
    delay(10);
  }
}

void output(int num, int keta) {
  digitalWrite(LATCHPIN[keta - 1], LOW);
  for (int i = 8; i >= 0; i--) {
    digitalWrite(DATAPIN[keta - 1], number[num][i] ? HIGH : LOW);
    onoff(CLOCKPIN[keta - 1]);
  }
  digitalWrite(LATCHPIN[keta - 1], HIGH);
}

void onoff(int Pin) {
  digitalWrite(Pin, HIGH);
  digitalWrite(Pin, LOW);
}
