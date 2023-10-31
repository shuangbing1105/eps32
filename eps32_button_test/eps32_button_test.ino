const byte LED[] = {4, 0, 2, 15};
void setup() {
  for (int i=0;i<4;i++){
    pinMode(LED[i], OUTPUT);
  }
  pinMode(36, INPUT);
  pinMode(39, INPUT);
}
void loop() {
  if(digitalRead(36) == false){
    for (int i=0;i<4;i++){
      for (int n=0;n<4;n++){digitalWrite(LED[n], LOW);}
      digitalWrite(LED[i], HIGH);
      delay(100);
    }

    for (int i=2;i>=0;i--){
      for (int n=0;n<4;n++){digitalWrite(LED[n], LOW);}
      digitalWrite(LED[i], HIGH);
      delay(100);
    }
    for (int n=0;n<3;n++){digitalWrite(LED[n], LOW);}    
  }
  if(digitalRead(39) == false){
    digitalWrite(LED[0],HIGH);
    digitalWrite(LED[2],HIGH); 
  }
  else{
    digitalWrite(LED[0],LOW);
    digitalWrite(LED[2],LOW); 
  }
}