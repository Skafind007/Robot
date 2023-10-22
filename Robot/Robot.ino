const int MOTOR_IZQ_MASTER = 3;
const int MOTOR_IZQ_DELANTERO = 5;
const int MOTOR_IZQ_TRASERO = 6;
const int MOTOR_DER_MASTER = 10;
const int MOTOR_DER_DELANTERO = 9;
const int MOTOR_DER_TRASERO = 11;

const int trigIzq = 13;
const int echoIzq = 4;
const int trigFro = 7;
const int echoFro = 2;
const int trigDer = 12;
const int echoDer = 8;

const int VELOCIDAD = 130;

void setup() {
  pinMode(MOTOR_IZQ_MASTER, OUTPUT);
  pinMode(MOTOR_IZQ_DELANTERO, OUTPUT);
  pinMode(MOTOR_IZQ_TRASERO, OUTPUT);
  pinMode(MOTOR_DER_MASTER, OUTPUT);
  pinMode(MOTOR_DER_DELANTERO, OUTPUT);
  pinMode(MOTOR_DER_TRASERO, OUTPUT);
  
  Serial.begin(9600);
  
  pinMode(trigIzq, OUTPUT);
  pinMode(echoIzq, INPUT);
  pinMode(trigFro, OUTPUT);
  pinMode(echoFro, INPUT);
  pinMode(trigDer, OUTPUT);
  pinMode(echoDer, INPUT);
}
void loop() {
  int distanciaIzq = medirDistancia(trigIzq, echoIzq);
  int distanciaFro = medirDistancia(trigFro, echoFro);
  int distanciaDer = medirDistancia(trigDer, echoDer);

  Serial.print("Distancia Izquierda: ");
  Serial.print(distanciaIzq);
  Serial.print(" cm, Distancia Frente: ");
  Serial.print(distanciaFro);
  Serial.print(" cm, Distancia Derecha: ");
  Serial.print(distanciaDer);
  Serial.println(" cm");

 
 if (distanciaFro > 10) {
    // Si no hay obstáculos en frente (a más de 10 cm), avanzar
    avanzar();
    delay(1000);
    detener();
    delay(500);
    Serial.println("voy pal frente");
} else {
    // Si hay un obstáculo en frente
    if ((distanciaIzq > 10) && (distanciaDer > 10)) {
        // Si hay espacio a ambos lados, retroceder
        retroceder();
        delay(1000);
        detener();
        delay(500);
        Serial.println("atras");
    } else if (distanciaIzq > distanciaDer) {
        // Si hay más espacio a la izquierda, girar a la izquierda
        girarIzquierda();
        delay(400);
        detener();
        delay(500);
        Serial.println("voy pa la izquierda");
    } else {
        // Si hay más espacio a la derecha o igual en ambos lados, girar a la derecha
        girarDerecha();
        delay(300);
        detener();
        delay(500);
        Serial.println("voy pa la derecha");
    }
}


  delay(500);  // Esperar un momento antes de realizar la siguiente lectura
}

void avanzar() {
  analogWrite(MOTOR_IZQ_MASTER, VELOCIDAD);
  analogWrite(MOTOR_IZQ_DELANTERO, VELOCIDAD);
  analogWrite(MOTOR_IZQ_TRASERO, LOW);
  analogWrite(MOTOR_DER_MASTER, VELOCIDAD);
  analogWrite(MOTOR_DER_DELANTERO, VELOCIDAD);
  analogWrite(MOTOR_DER_TRASERO, LOW);
}

void retroceder() {
  analogWrite(MOTOR_IZQ_MASTER, VELOCIDAD);
  analogWrite(MOTOR_IZQ_DELANTERO, LOW);
  analogWrite(MOTOR_IZQ_TRASERO, VELOCIDAD);
  analogWrite(MOTOR_DER_MASTER, VELOCIDAD);
  analogWrite(MOTOR_DER_DELANTERO, LOW);
  analogWrite(MOTOR_DER_TRASERO, VELOCIDAD);
}

void girarIzquierda() {
  analogWrite(MOTOR_IZQ_MASTER, 0);
  analogWrite(MOTOR_IZQ_DELANTERO, 0);
  analogWrite(MOTOR_IZQ_TRASERO, 0);
  analogWrite(MOTOR_DER_MASTER, VELOCIDAD);
  analogWrite(MOTOR_DER_DELANTERO, VELOCIDAD);
  analogWrite(MOTOR_DER_TRASERO, 0);
}

void girarDerecha() {
  analogWrite(MOTOR_IZQ_MASTER, VELOCIDAD);
  analogWrite(MOTOR_IZQ_DELANTERO, VELOCIDAD);
  analogWrite(MOTOR_IZQ_TRASERO, 0);
  analogWrite(MOTOR_DER_MASTER, 0);
  analogWrite(MOTOR_DER_DELANTERO, 0);
  analogWrite(MOTOR_DER_TRASERO, 0);
}
void detener() {
  analogWrite(MOTOR_IZQ_MASTER, 0);
  analogWrite(MOTOR_IZQ_DELANTERO, 0);
  analogWrite(MOTOR_IZQ_TRASERO, 0);
  analogWrite(MOTOR_DER_MASTER, 0);
  analogWrite(MOTOR_DER_DELANTERO, 0);
  analogWrite(MOTOR_DER_TRASERO, 0);
}

int medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;  // Convertir el tiempo en distancia (cm)
}