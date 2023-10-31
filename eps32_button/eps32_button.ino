const byte LED[] = {4, 0, 2, 15};

void setup() {
  for (int i=0;i<4;i++){
    pinMode(LED[i], OUTPUT);
    pinMode(36,INPUT);
    pinMode(34, INPUT);
  }
}

void loop() {
  if (digitalRead(36) == false){
    digitalWrite(LED[0], HIGH);
  }
  else{
    digitalWrite(LED[0], LOW);
  }
  if (digitalRead(34) == false){
    digitalWrite(LED[1], LOW);
  }
  else{
    digitalWrite(LED[1], HIGH);
  }

}