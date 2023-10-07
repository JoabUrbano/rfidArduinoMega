// Inclui as bibliotecas do SPI e do RC522
#include <SPI.h>
#include <MFRC522.h>

// Definição dos pinos de conexão do projeto 
#define PINO_SS 10
#define PINO_RST 9
#define PINO_LED_RED 22
#define PINO_LED_GRE 24
#define PINO_BUZZER 26

// Cria o item para configurar o módulo RC522
MFRC522 mfrc522(PINO_SS, PINO_RST); 

int tentativasInvalidas = 0; // Variavel para gerenciar as tentativas falhas

void setup() {
  Serial.begin(9600); // Inicializa a serial
  SPI.begin(); // Inicializa a comunicação SPI
  mfrc522.PCD_Init(); // Inicializa o módulo MFRC522
  Serial.println("Sistema Inicializado: Aproxime o token");

  pinMode(PINO_LED_RED , OUTPUT); // Define PINO_LED_RED (pino 22) como saída
  pinMode(PINO_LED_GRE , OUTPUT); // Define PINO_LED_GRE (pino 24) como saída
  pinMode(PINO_BUZZER , OUTPUT); // Define PINO_BUZZER (pino 26) como saída
  digitalWrite(PINO_LED_RED, HIGH);  // Define o LED vermelho como alto por padrão
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return; // Aguarda a aproximação do token
  if (!mfrc522.PICC_ReadCardSerial()) return; // Seleciona qual token vai ser utilizado 
  Serial.print("UID da tag:"); // Mostra UID do token na serial
  String conteudo= ""; // Cria uma variável vazia, do tipo string byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if(mfrc522.uid.uidByte[i] < 0x10){
      Serial.print(" 0");
    }
    else{
      Serial.print(" ");
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX); // Printa a mensagem convertida em hexadecimal
    if(mfrc522.uid.uidByte[i] < 0x10){
      conteudo.concat(String(" 0"));
    }
    else{
      conteudo.concat(String(" "));
    }
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  conteudo.toUpperCase(); // Coloca todas as letras da string em maiúscula

  /* Verificação do cartão lido */
  if(conteudo.substring(1) == "73 2E 88 11") { // Verifica se o cartão colocado é o correto, esse código você substitui pelo do seu cartão
    // Vai imprimir a mensagem, apagar o LED vermelho e ascender o verde por 10 segundos e zera as tentativas erradas
    Serial.println("Acesso Permitido!");
    digitalWrite(PINO_LED_RED, LOW);
    digitalWrite(PINO_LED_GRE, HIGH);
    tentativasInvalidas = 0;
    delay(10000);
    digitalWrite(PINO_LED_GRE, LOW);
    digitalWrite(PINO_LED_RED, HIGH);
  }
  else { // Se o cartão é incorreto
    //Pisca o LED vermelho 3 vezes e adiciona 1 as tentativas inválidas
    Serial.println("Cartão inválido!");
    for(int c = 0; c < 3; c++) {
      digitalWrite(PINO_LED_RED, LOW);
      delay(300);
      digitalWrite(PINO_LED_RED, HIGH);
      delay(300);
    }
    tentativasInvalidas ++;
    Serial.print("Número de tentativas restantes: ");
    Serial.println(5 - tentativasInvalidas);
    delay(1000);
  }

  if (tentativasInvalidas >= 5) { // Se o número de tentativas incorretas exceder 5
    // Imprime a mensagem de sistema bloqueado enquanto liga o buzzer e pisca o LED vermelho por 30 segundos
    Serial.println("SISTEMA BLOQUEADO!");
    digitalWrite(PINO_BUZZER, HIGH);
    for(int c = 0; c < 30; c++) {
      digitalWrite(PINO_LED_RED, LOW);
      delay(500);
      digitalWrite(PINO_LED_RED, HIGH);
      delay(500);
    }
    digitalWrite(PINO_BUZZER, LOW);
    tentativasInvalidas = 0; // Zera as tentativas apos os 30 segundos para não nterromper o código
    // Nesse caso poderia bloquear o sistema e esperar o acionamento de algum botão para o código seguir
    // Dessa forma o sistema só liberaria quando esse botão que estaria em um lugar seguro fosse acionado
  }
  delay(1000);
}
