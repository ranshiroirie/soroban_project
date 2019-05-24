#define Threshold 550 //センサーの域値
#define LEDPIN_COUNT 7 //出力するLEDのピン数
#define SENSOR 15 //フォトリフレクタの数
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

const int LEDPIN[LEDPIN_COUNT] = {13, 14, 27, 26, 25, 33, 32}; //LEDピンの設定

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
  int juzu[SENSOR];
  int pinread [SENSOR];
  for (int i = 0; i < SENSOR; i++) {
    pinread[i] = map(readMux(i), 0, 5000, 0, 1023);
//    Serial.print(pinread[i]);
//    Serial.print(" ");
    if (pinread[i] >= Threshold) { //センサーに珠があるかどうか
      juzu[i] = 1; //ある
    } else {
      juzu[i] = 0; //ない
    }
  }
//  Serial.println("");

  //LEDへ出力するプログラム
  int ledswitch[LEDPIN_COUNT] = {1, 1, 1, 1, 1, 1, 1}; //LEDの出力情報
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
  for (int i = 0; i < 3; i++) {
        Serial.print(count[i]);
  }
    Serial.println();
  //  amount = count[0] + count[1] * 10 + count[2] * 100;
  //  Serial.println(amount);
  Serial.write(amount); //シリアル送信
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
