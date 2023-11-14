const byte LED[] = {4, 0, 2, 15};
int num = 0;
bool light = false;
void setup(){
  for (int i=0;i<4;i++){
    pinMode(LED[i], OUTPUT);
  }
  pinMode(36,INPUT);
  pinMode(34, INPUT);
}

void loop() {
  if (digitalRead(36) == false){
    delay(20);

    if (digitalRead(36) == false){
      while (digitalRead(36) == false);
      num = num + 1;
      if (num % 2 == 0){
        light = !light;
      }
    }

  }
  digitalWrite(LED[0],light);
}