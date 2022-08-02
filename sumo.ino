#define obstaclePin A0 // Sensor de obstaculos
#define reflet1Pin A1 // Sensor de refletancia 1 (Esquerda)
#define reflet2Pin A2 // Sensor de refletancia 2 (Direita)
#define lMotorPin D3 // Conecta na pH (Motor Esquerdo)
#define lDirPin D4 // pH Motor Esquerdo sentido direto (primeira entrada)
#define lRevPin D2 // pH Motor Esquerdo sentido inverso (segunda entrada)
#define rMotorPin D6 // Conecta na pH (Motor Direito)
#define rDirPin D7 // pH Motor Direito sentido direto (primeira entrada)
#define rRevPin D8 // pH Motor Direito sentido inverso (segunda entrada)

int obstacle, reflet1, reflet2, lMotorSpeed, rMotorSpeed;
bool rDirect, rReverse, lDirect, lReverse;

void setup() {
    pinMode(lMotorPin, OUTPUT);
    pinMode(rMotorPin, OUTPUT);
    pinMode(lDirPin, OUTPUT);
    pinMode(rDirPin, OUTPUT);
    pinMode(lRevPin, OUTPUT);
    pinMode(rRevPin, OUTPUT);
}

void sendMotors(int lmotor, bool ldir, bool lrev, int rmotor, bool rdir, bool rrev) {
    // Sentido do motor esquerdo
    digitalWrite(lDirPin, ldir);
    digitalWrite(lRevPin, lrev);
    
    // Velocidade do motor esquerdo
    analogWrite(lMotorPin, lmotor);

    // Sentido do motor direito
    digitalWrite(rDirPin, rdir);
    digitalWrite(rRevPin, rrev);

    // Velocidade do motor direito
    analogwrite(rMotorPin, rmotor);
}

void loop() {
    // Leitura de sensores
    obstacle = analogRead(obstaclePin);
    reflet1 = analogRead(reflet1Pin);
    reflet2 = analogRead(reflet2Pin);

    // Reset de orientações
    rDirect = 0;
    rReverse = 0;
    lDirect = 0;
    lReverse = 0;

    if (obstacle <= 500 && obstacle != 0) {
      lMotorSpeed = 255;
      lDirect = 1;
      rMotorSpeed = 255;
      rDirect = 1;
    }
    else { // Gira no próprio eixo para procurar o robô adversário
      lMotorSpeed = 127;
      lDirect = 1;
      rMotorSpeed = 127;
      rReverse = 1;
    }

    if (reflet1 >= 920) { // Se a reflexão for maior que 90%
      lMotorSpeed = 0;
      lDirect = 1; lReverse = 1; // Freio
    }
    
    if (reflet2 >= 920) {
      rMotorSpeed = 0;
      rDirect = 1; rReverse = 1;
    }
    
    sendMotors(lMotorSpeed, lDirect, lReverse, rMotorSpeed, rDirect, rReverse);
}