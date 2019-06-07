#define Threshold 550 //センサーの域値
#define LEDPIN_COUNT 7 //出力するLEDのピン数
#define SENSOR 15 //フォトリフレクタの数
//桁の設定
const int DATAPIN[3] = {13, 26, 21};
const int LATCHPIN[3] = {14, 25, 22};
const int CLOCKPIN[3] = {17, 33, 23};

//7セグの配列
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
//MUX 設定
const int controlPin[4] = {16, 17, 18, 19};
const int SIG_pin = 4;
const int muxChannel[16][4] = {  //MUXのチャネル
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

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 3; i++) {
    pinMode(DATAPIN[i], OUTPUT);
    pinMode(LATCHPIN[i], OUTPUT);
    pinMode(CLOCKPIN[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(controlPin[i], OUTPUT);
    digitalWrite(controlPin[i], LOW);
  }
}

void loop() {
  int juzu[SENSOR];
  int pinread [SENSOR];
  for (int i = 0; i < SENSOR; i++) {
    pinread[i] = map(readMux(i), 0, 5000, 0, 1023);
    Serial.print(pinread[i]);
    Serial.print(" ");
    if (pinread[i] >= Threshold) { //センサーに珠があるかどうか
      juzu[i] = 1; //ある
    } else {
      juzu[i] = 0; //ない
    }
  }
  Serial.println("");

  //数字に変換するプログラム
  int count[SENSOR / 5]; //数字の桁ごとの配列
  int amount = 0; //合計
  for (int i = 0; i < SENSOR / 5; i++) {
    if (juzu[1 + i * 5] == 0) { //0
      count[i] = 0;
    } else if (juzu[2 + i * 5] == 0) { //1
      count[i] = 1;
    } else if (juzu[3 + i * 5] == 0) { //2
      count[i] = 2;
    } else if (juzu[4 + i * 5] == 0) { //3
      count[i] = 3;
    } else { //4
      count[i] = 4;
    }
    if (juzu[0 + i * 5] == 1) { //5を足すかどうか
      count[i] += 5;
    }
  }
  for (int i = 0; i < SENSOR / 5; i++) {
    seven_seg(count[i], i);
  }
  Serial.println();
  //  delay(50);
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

void seven_seg(int num, int keta) {
  digitalWrite(LATCHPIN[keta], LOW);
  for (int i = 8; i >= 0; i--) {
    digitalWrite(DATAPIN[keta], number[num][i] ? HIGH : LOW);
    onoff(CLOCKPIN[keta]);
  }
  digitalWrite(LATCHPIN[keta], HIGH);
}

void onoff(int Pin) {
  digitalWrite(Pin, HIGH);
  digitalWrite(Pin, LOW);
}
