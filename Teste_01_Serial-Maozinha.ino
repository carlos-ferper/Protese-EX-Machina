// --------------------------------
// INCLUDES E PINOS DE CONEXÃO
// --------------------------------

#include <Servo.h>

#define MOTOR1 3    // pino do indicador
#define MOTOR2 5    // pino do médio
#define MOTOR3 6    // pino do anelar
#define MOTOR4 9    // pino do mínimo
#define MOTOR5 10   // pino do polegar


// --------------------------------
// VARIÁVEIS GLOBAIS E DEFINES
// --------------------------------

#define POSI1 30    // posição inicial do indicador
#define POSI2 50    // posição inicial do médio
#define POSI3 0     // posição inicial do anelar
#define POSI4 15    // posição inicial do mínimo
#define POSI5 0     // posição inicial do polegar

#define POSF1 150   // posição final do indicador
#define POSF2 160   // posição final do médio
#define POSF3 180   // posição final do anelar
#define POSF4 160   // posição final do mínimo
#define POSF5 180   // posição final do polegar

#define DELAY 5     // delay do movimento do motor

Servo motor[5];

volatile byte acionado = LOW;

int ang[5] = {POSI1, POSI2, POSI3, POSI4, POSI5}; //angulo atual - Deve iniciar igual ao angulo inicial
int angi[5] = {POSI1, POSI2, POSI3, POSI4, POSI5}; //angulo mínimo
int angf[5] = {POSF1, POSF2, POSF3, POSF4, POSF5}; //ângulo máximo

bool posicao[5] = {1, 1, 1, 1, 1}; //vetor que vai guardar a posicao do dedo como fechada ou aberta - inicia como todo mundo aberto
bool joinha[5] = {1, 0, 0, 0, 0};
bool meio[] = {0, 0, 1, 0, 0};

char comando;

// --------------------------------
// PROTÓTIPO DAS FUNÇÕES
// --------------------------------

void Dedo(int dedo, bool posicao);
void Movimento();



// --------------------------------
// CONFIGURAÇÕES INICIAIS
// --------------------------------

void setup () {
  Serial.begin(9600);


  motor[0].attach(MOTOR1);
  motor[1].attach(MOTOR2);
  motor[2].attach(MOTOR3);
  motor[3].attach(MOTOR4);
  motor[4].attach(MOTOR5);

  motor[0].write(POSI1);
  motor[1].write(POSI2);
  motor[2].write(POSI3);
  motor[3].write(POSI4);
  motor[4].write(POSI5);

}

// --------------------------------
// REPETIÇÃO
// --------------------------------

void loop() {
  if (Serial.available()) {
    comando = Serial.read();

    if (comando == 'j') {
      for (int i=0; i < 5; i++)
        posicao[i] = joinha[i];
    }
    else if (comando == 'm') {
      for (int i=0; i < 5; i++)
        posicao[i] = meio[i];
    }

    Movimento();
    comando=0;

  }
}

// --------------------------------
// MOVIMENTO
// --------------------------------

void Movimento() {
  for (int i = 0; i < 5; i++)
    Dedo(i, posicao[i]);

}

void Dedo(int dedo, bool aberto) {
  if (!aberto) {
    for (ang[dedo]; ang[dedo] <= angf[dedo]; ang[dedo]++) {
      motor[dedo].write(ang[dedo]);
      delay(DELAY);
    }
  }
  else {
    for (ang[dedo]; ang[dedo] >= angi[dedo]; ang[dedo]--) {
      motor[dedo].write(ang[dedo]);
      delay(DELAY);
    }
  }

}
//Dessa forma, ele economiza comparação e fica mais simples definir as posições de cada dedo
