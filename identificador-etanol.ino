//defini pinagem dos leds
int ledAmarelo = 3;
int ledVerde = 4;
int ledVermelho = 5 ;

//defini pinagem dos botoes
int btIniciaTeste = 6;
int auxA1 = 0;
int auxA2 = 0;
int estadoA = 0;
int btLigaMotor = 7;
int auxB1 = 0;
int auxB2 = 0;
int estadoB = 0;

//defini pinagem do motor
int motorD = 8;
int motorE = 9;

//defini o pino do sensor MQ-3
int sensor = A5;
int valorSensor = 0;
boolean ligaMotor = false;
boolean primeitoTeste = true;

void setup() {
  Serial.begin(9600);
  Serial.flush();
  pinMode( ledAmarelo,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  pinMode(ledVermelho,OUTPUT);
  pinMode(btIniciaTeste, INPUT);
  pinMode(btLigaMotor, INPUT);
  pinMode(motorD,OUTPUT);
  pinMode(motorE,OUTPUT);
  pinMode(sensor,INPUT);
  
}

void loop() {

  //Verifica quando foi precionado o botao
  auxA1 = digitalRead(btIniciaTeste);
  if((auxA1 == 1) && (auxA2 == 0)){
   estadoA = 1 - estadoA;
    delay (5); // de-bouncing.
  }
  auxA2 = auxA1;
  
  if(estadoA == 1){//PRESSIONDADO PELA PRIMEIRA VEZ
    if(primeitoTeste){
      Serial.println("Teste iniciado...");
      digitalWrite(ledAmarelo, HIGH);
      delay(7000);
      //Inicia o teste de alcool
      int maior_valor = 0;
      int valor_sensor = 0;
      int temp = 0;
      
      while(temp <= 30000 ){
       valor_sensor = analogRead(sensor);
        if (valor_sensor > maior_valor) {
          maior_valor = valor_sensor;
        }
        //Verifica se o botao de desligar o carro foi pressionado pela segunda vez enquanto realiza o teste
        auxA1 = digitalRead(btIniciaTeste);   
        if((auxA1 == 1) && (auxA2 == 0)){ // ler o valor enviado pelo botao.
         estadoA = 1 - estadoA;
          delay (5); // de-bouncing.
        }
        auxA2 = auxA1;
        if(estadoA==0){
          Serial.print("Teste parado antes de terminar. ");
          ligaMotor = false;
          break;
        }
        temp++;

      }
      
      
      valorSensor = maior_valor;
      
      Serial.print("Leitura do sensor: ");
      Serial.println(valorSensor);
  
      if(valor_sensor <=  150){//verifica se o nivel de alcool esta acima do permitido
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledVermelho, LOW);
        ligaMotor = true; //Se estiver abaixo do permitido libera ligar o carro
      }else{
        digitalWrite(ledVermelho, HIGH);
        digitalWrite(ledVerde, LOW);
        ligaMotor = false; //Se estiver acima do nivel permitido, nao libera ligar o motor
      }
      primeitoTeste = false;// significa que o teste é feito apenas uma vez
    }
    
    //Verifica quando foi precionado o botao btLigaMotor
    auxB1 = digitalRead(btLigaMotor);   
    if((auxB1 == 1) && (auxB2 == 0)){ // ler o valor enviado pelo botao.    
      estadoB = 1 - estadoB;
      delay (5); // de-bouncing.
    }
    auxB2 = auxB1;
    if(estadoB == 1 && estadoA == 1 && ligaMotor == true){//Nao identificado o nivel de alcool
      digitalWrite(motorD, LOW);
      digitalWrite(motorE, HIGH);
          
    }else{
      digitalWrite(motorD, LOW);
      digitalWrite(motorE, LOW);
    }
    
  }else{//PRESSIONDADO pela segunda vez
    primeitoTeste = true;
    estadoA = 0;
    estadoB = 0;
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(motorD, LOW);
    digitalWrite(motorE, LOW);
  }
}
