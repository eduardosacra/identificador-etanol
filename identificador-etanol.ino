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
int valorSensor = 150;
boolean ligaMotor = false;

boolean motorLigado = false;

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
  //1- aperta uma vez btIniciaTeste e acender ledAmarelo e inicia o teste
  //2- aperta btLigaMotor teste negativo para alcool ? liga motor : nao liga motor
  //1.1- motor ja ligado o teste  continua funcionando se identificar alcool nao desliga mortor, notifica que foi detectado.
  //3.- se detectado e motor desligado, nao consegue ligar o carro

    //botao inicial
  auxA1 = digitalRead(btIniciaTeste);   
  if((auxA1 == 1) && (auxA2 == 0)){ // ler o valor enviado pelo botao.    
   estadoA = 1 - estadoA;
    delay (5); // de-bouncing.
  }
  auxA2 = auxA1;
  
  //botao2
  auxB1 = digitalRead(btLigaMotor);   
  if((auxB1 == 1) && (auxB2 == 0)){ // ler o valor enviado pelo botao.    
   estadoB = 1 - estadoB;
    delay (5); // de-bouncing.
  }
  auxB2 = auxB1;

 
  if(estadoA == 1){//APERTADO PELA PRIMEIRA VEZ
    
    digitalWrite(ledAmarelo, HIGH);
  
    //Iniicia o teste de alcool
    int maior_valor = 0;
    int valor_sensor = 0;
    for (int temp = 0; temp <= 3000; temp++) {
      valor_sensor = analogRead(sensor);
      if (valor_sensor > maior_valor) {
        maior_valor = valor_sensor;
        
      }
      valorSensor = maior_valor; 
     }//finaliza o teste
     
    Serial.print("Leitura do sensor: ");
    Serial.println(valorSensor);
    if(valor_sensor <=  150){//verifica se o nivel de alcool esta acima do permitido
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledVermelho, LOW);
      ligaMotor = true; //Se estiver abaixo do permitido libera ligar o carro
    }else{
     // se estivar acima do permitido nao permite dar a partida do motor 
    
    if(!motorLigado){
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, HIGH);
      ligaMotor = false;
    }else{
    //alerta condutor que detectou alcool depois de ligado o carro
      digitalWrite(ledVerde, LOW);
      for(int aux = 0 ; aux < 3; aux ++){
        digitalWrite(ledVermelho, HIGH);
        delay(30);
        digitalWrite(ledVermelho, LOW);
      }
      digitalWrite(ledVerde, HIGH);
   }

    }  
    
  }else{// APERTADO PELA SEGUNDA VEZ
    digitalWrite(ledAmarelo, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(ledVerde, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(ledVermelho, LOW);    // turn the LED off by making the voltage LOW
    
     estadoB = 0;
  }
 
  if(estadoB == 1 && estadoA == 1 && ligaMotor == true){//Nao identificado o nivel de alcool
   
    digitalWrite(motorD, LOW);
    digitalWrite(motorE, HIGH);
    motorLigado = true;
    
  }else{
      
    motorLigado = false;
    digitalWrite(motorD, LOW);
    digitalWrite(motorE, LOW);
  } 
  
}
