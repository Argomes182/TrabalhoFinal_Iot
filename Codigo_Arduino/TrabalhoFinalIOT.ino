// Musica 1 - Liga a Bomba de Agua
int melodia[] = {660,660,660,510,660,770,380};
int duracaoNotas[] ={100,100,100,100,100,100,100};
int pausaNotas[] = {150,300,300,100,300,550,575};


// Musica 2 - NÃ£o contem agua no reservatÃ³rio
int melodia2[] = {523,523,523,494,440,392};
int duracaoNotas2[] ={100,100,70,70,70,70};
int pausaNotas2[] = {300,200,200,200,200,200};

int portSpeak(3);

int pino2=2; //Bomba de Agua
int pino4=4; // led Reservatorio Vazio
int pino5=5; // Alimenta sensor de umidade
int pino6=6; // Alimenta Sensor de Nivel de Agua
int pino13=13; // Alimenta Sensor Bluetooth
int limiteUmidade = 25; // Limite de Umidade
int limiteReserv = 350; 
int sensorVaso;
int sensorReserv;
int i = 0;


void setup() {
  // put your setup code here, to run once:
  // Inicializa a Serial
  Serial.begin(9600);
  pinMode(pino2, OUTPUT);
  pinMode(pino4, OUTPUT);    
  pinMode(pino5, OUTPUT);
  pinMode(pino6, OUTPUT);
  pinMode(pino13, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorVaso = leSensorVaso();
  sensorReserv = leSensorReserv();

  Serial.println(sensorVaso);
  int cerebro = Serial.read();
  
  delay(10);  

  // Verifica se hÃ¡ agua suficente no Reservatorio
  if(sensorReserv < limiteReserv) {
    ligaLedReserv();
    tocaMusica(2);
  } else {
  desligaLedReserv();
  while (i < 2) {
    tocaMusica(1);
    ligaBomba();
    delay(300);
    desligaBomba();
    i++;
  } 
  
  // Verifica se a Planta precisa de Agua
  //if(leSensorVaso() < limiteUmidade) {
    //tocaMusica(1);
    //ligaBomba();
    //delay(300);
    //desligaBomba();
  //}
  }
  delay(1000);
 
  sensorVaso = leSensorVaso();
  sensorReserv = leSensorReserv();

  
  if(cerebro == 'v') {
  if (sensorVaso < limiteUmidade) {
    Serial.println("Umidade abaixo do recomendado");
  } else if(sensorVaso > limiteUmidade && sensorVaso < 600){
    Serial.println("Umidade dentro do recomendado");
  } else {
    Serial.println("Umidade acima do recomendado");
  }
  }

  if(cerebro == 'r') {
  if (sensorReserv < limiteReserv) {
    Serial.println("Reservatorio abaixo do recomendado");
  } else if(sensorReserv > limiteReserv && sensorReserv < 600){
    Serial.println("Reservatorio até a metade");
  } else {
    Serial.println("Reservatorio Cheio");
  }
  }
  
  if(cerebro == 0) {
  ligaBomba();
  desligaBomba();
  Serial.println("Bomba acionada");
  }
}

int leSensorVaso() {
  ligaSensores();
  delay(10);
  return analogRead(A0);
  desligaSensores();
}

int leSensorReserv() {
  ligaSensores();
  delay(10);
  return analogRead(A1);
  desligaSensores();
}

void ligaSensores() {
  digitalWrite(pino5,HIGH);
  digitalWrite(pino6,HIGH);
  digitalWrite(pino13, HIGH);  
}
void desligaSensores() {
  digitalWrite(pino5,LOW);
  digitalWrite(pino6,LOW);
  digitalWrite(pino13, LOW);  
}
void ligaLedReserv() {
  digitalWrite(pino4,HIGH);
}

void desligaLedReserv() {
  digitalWrite(pino4,LOW);
}
void ligaBomba() {
  digitalWrite(pino2,HIGH);
}

void desligaBomba() {
  delay(2000);
  digitalWrite(pino2,LOW);
}
void tocaMusica(int musica) {
  switch (musica) {
    case 1:
    for(int nota=0; nota < 7; nota++) {
      tone(portSpeak, melodia[nota], duracaoNotas[nota]);
      delay(pausaNotas[nota]);
    }
    noTone(portSpeak);
    break;
    
    case 2:
    for(int nota=0; nota < 6; nota++) {
      tone(portSpeak, melodia2[nota], duracaoNotas2[nota]);
      delay(pausaNotas2[nota]);
    }
    noTone(portSpeak);
    break;
  }
}


