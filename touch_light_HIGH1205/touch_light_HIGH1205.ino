int sum = 0;
int a = 0 ;

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
}

void loop() {
  for (int i=0;i<=20;i++)
    {sum= sum+ touchRead(T5);}
  a = sum/20;
  sum = 0;
  Serial.println(a);
  
  if (a>30)
  {
    digitalWrite(4,HIGH);
  }
  else 
    digitalWrite(4,LOW);
}
