void setup() {
  pinMode(13, OUTPUT);
  for (int i = 2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(1200);
  Serial.println("ola mundo");
}

void loop() {

  digitalWrite(13, HIGH);

  int maior_valor = 0;
  int valor_sensor = 0;
  for (int temp = 0; temp <= 3000; temp++) {
    valor_sensor = analogRead(A1);
    if (valor_sensor > maior_valor) {
      maior_valor = valor_sensor;
    }
  }
  valor_sensor = maior_valor;
  Serial.println(valor_sensor);
  Serial.flush();
  
  digitalWrite(13, LOW);

  if (valor_sensor <= 50)
  {
    digitalWrite(7, HIGH);
    delay(2000);
    digitalWrite(7, LOW);
  }
  else if (valor_sensor > 50 and valor_sensor <= 100)
  {
    digitalWrite(2, HIGH);
    delay(2000);
    digitalWrite(2, LOW);
  }
  else if (valor_sensor > 100 and valor_sensor <= 300)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    delay(2000);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
  }
  else if (valor_sensor > 300 and valor_sensor <= 350)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    delay(2000);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  else if (valor_sensor > 350 and valor_sensor <= 400)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(2000);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  else if (valor_sensor > 400)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    delay(2000);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
  //  delay(1000);
  //   for(int i =2;i<=7;i++){
  //    digitalWrite(i,LOW);
  //
  //  }
}
