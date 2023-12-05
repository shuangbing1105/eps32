#include <analogWrite.h>
void setup() {
  pinMode(25, INPUT);
  pinMode(26, OUTPUT);
  Serial.begin(9600);
}

double inputVal;
int outputVal;

void loop() {
  inputVal = analogRead(25);

  outputVal = inputVal / 16;

  
  analogWrite(26,outputVal);

  Serial.print("輸出電壓:");
  Serial.print(outputVal);
  Serial.print("輸入電壓:");
  Serial.println(inputVal);

  delay(10);
}
