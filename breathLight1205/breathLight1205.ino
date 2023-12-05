#include <analogWrite.h>
void setup() {
}

void loop() {
  for (int i=0;i<=50;i++){
    analogWrite(2,i);
    delay(50);
  }
  for (int i=50;i>=0;i--){
    analogWrite(2,i);
    delay(50);
  }
 
}
