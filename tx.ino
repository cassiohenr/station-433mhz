//CÓDIGO DO MÓDULO TRANSMISSOR - WEATHER_ONE

#include <VirtualWire.h>

const int ldr = A1;   //Declaração do número do pino do sensor de luminosidade LDR - entrada analógica A1.
const int solo = A0;  //Declaração do número do pino atribuido a variável solo (moisture sensor) - entrada analógica A0.
const int lm35 = A2;  //Declaração do número do pino do sensor de luminosidade Lm35 - entrada analógica A2.

const int LED = 13;   //Declarando número do pino atribuido a variável LED.
const int TX = 7;     // Declarando o pinos para transmissao (RF TX 433 MHz), Pino 7.

void setup() 
{
  pinMode(8, OUTPUT);    //Nestas linhas, estamos utilizando os pinos do ATMEGA328...
  pinMode(6, OUTPUT);    //...para alimentar o transmissor RF link que está ligado... 
  digitalWrite(8, LOW);  //...em pararelo com os pinos 8( colocado em LOW para ser o GND)...
  digitalWrite(6, HIGH); //...e o pino 6 (colocado como HIGH para ser o VCC [5v]).
  
                                // Comunicacao com o Serial Monitor
  Serial.begin(9600);           //Abertura da comunicação serial com o PC. Permite amostrar por meio de "Serial.Print" no monitor serial os dados. 
  Serial.println("Transmissor");//Escreve transmissor no monitor serial (Apenas para averiguar funcionamento.

  vw_set_tx_pin(TX);            // Inicialização de Entrada/Saída do transmissor
  vw_set_ptt_inverted(true);    // Requerido para DR3100, transreceptor muito utilizado para transmissões wireless em aplicações short-range.
  vw_setup(2000);               // Seta velocidade em Bits por segundo.
}

void loop() 
{
  int lumi = analogRead(ldr)/10;    //Dividindo valor da leitura do Ldr (luminosidade) (0-1023) por 10. Objetivo: Facilitar visualização no Matlab.
  int umid = analogRead(solo)/10;   //Dividindo valor da leitura do Moisture Sensor (0-1023) por 10. Objetivo: Facilitar visualização no Matlab.
  int temp = analogRead(lm35) * 0.48875855327468; //Dividindo valor da leitura do Lm35 (0-1023) por 10. Objetivo: Facilitar visualização no Matlab.
  
  char valorlumi[10];           //Lendo e armazenando o valor da temperatura
  itoa(lumi, valorlumi,10);     // Converte int  --> char
  
  char valorumid[10];           //Lendo e armazenando o valor da temperatura
  itoa(umid, valorumid,10);     // Converte int --> char
  
  char valortemp[10];           //Lendo e armazenando o valor da temperatura
  itoa(temp, valortemp,10);     // Converte int --> char
  
  digitalWrite(LED, HIGH);      //Led do pino 13 pisca (HIGH) enquanto transmite
  vw_send((uint8_t *)valorlumi, strlen(valorlumi));  //Envio de dados (do Char). vw_send(oitobits(valorlumi), tamanhodastring(valorlumi))
  vw_wait_tx();                 // Espera o envio da informacao.
  digitalWrite(LED, LOW);       //Led do pino 13 apaga, fim da transmissão do dado.
  delay(10);
  
  digitalWrite(LED, HIGH);      //Led do pino 13 pisca (HIGH) enquanto transmite
  vw_send((uint8_t *)valorumid, strlen(valorumid));  //Envio de dados (do Char). vw_send(oitobits(valorlumi), tamanhodastring(valorlumi)) 
  vw_wait_tx();                // Espera o envio da informacao.
  digitalWrite(LED, LOW);      //Led do pino 13 apaga, fim da transmissão do dado.
  delay(10);
  
  digitalWrite(LED, HIGH);     //Led do pino 13 pisca (HIGH) enquanto transmite
  vw_send((uint8_t *)valortemp, strlen(valortemp));  //Envio de dados (do Char). vw_send(oitobits(valorlumi), tamanhodastring(valorlumi)) 
  vw_wait_tx();                // Espera o envio da informacao.
  digitalWrite(LED, LOW);      //Led do pino 13 apaga, fim da transmissão do dado.
  delay(10);
 
