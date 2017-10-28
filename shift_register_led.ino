int latchPin = 3;  // 74HC595のST_CPへ
int clockPin = 4; // 74HC595のSH_CPへ
int dataPin = 2;  // 74HC595のDSへ
unsigned int val;
unsigned int j;
unsigned int k;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // LED1からLED10までを順に光らせます
  for (int i = 0; i < 10; i++) {
  // 送信中のlatchPinはグランド(LOW)レベル
  digitalWrite(latchPin, LOW);
  // シフト演算を使って点灯するLEDを選択しています
  val = 1<<i;

  //MSBFIRST, 74HC595_0_QA-QH->74HC595_1_QA-QB
  j = val;
  k = val>>8;
  shiftOut(dataPin, clockPin, MSBFIRST, k);//上位バイトを送信
  shiftOut(dataPin, clockPin, MSBFIRST, j);//2バイトの下位を送信
  
  //LSBFIRST, 74HC595_1_QB-QA->74HC595_0_QH-QA
  /*
  j = val<<6;
  k = val<<6>>8;
  shiftOut(dataPin, clockPin, LSBFIRST, j);//2バイトの下位を送信
  shiftOut(dataPin, clockPin, LSBFIRST, k);//上位バイトを送信
  */
  
  // 送信終了後latchPinをHIGHにする
  digitalWrite(latchPin, HIGH);
  delay(100);
  }
}
