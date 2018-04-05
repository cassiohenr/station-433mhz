//CÓDIGO DO MÓDULO RECEPTOR - WEATHER_ONE
#include <VirtualWire.h>  //Incluindo biblioteca VirtualWire que permite gerar um canal de comunicação via RF (dados seriais).

const int LED = 13;       //Declarando número do pino atribuido a variável LED.
const int RX = 7;         // Declarando o pinos para recepção (RF RX 433 MHz), Pino 7.

void setup() 
{
  Serial.begin(9600);     // Abertura da comunicação serial com o PC. Será utilizada para envio de dados por USB/serial para o MatLab. 
  
  vw_set_rx_pin(RX);      // Inicializando E/S do receptor. Definindo que RX (pino 7) receberá os dados.
  vw_set_ptt_inverted(true); // Requerido para DR3100, transreceptor muito utilizado para transmissões wireless em aplicações short-range.
  vw_setup(2000);         // Seta velocidade em Bits por segundo.
  vw_rx_start();          // Inicia a recepcao.
}

void loop() 
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];   //Cria-se o vetor buf[i] que armazenará os elementos da string.
  uint8_t buflen = VW_MAX_MESSAGE_LEN; //buflen recebe o tamanho máximo da string recebida.

  if (vw_get_message(buf, &buflen))    // Sem bloqueios na recepcao
  { 
     digitalWrite(LED, HIGH);          // Pisca LED no pino 13 se receber a mensagem integra
     char CharMsg[10];                 // Cria uma variável CHAR de 10 posições. Onde se armazenará o conteudo da transmissao.
      
      for (int i = 0; i < buflen; i++) //Leitura posição após posição da string.
      {
        CharMsg[i] = (char)buf[i];     //Armazenagem nas sucessivas posições de CHAR[i].
      }
    
      CharMsg[buflen] = '\0';          //Verifica se terminou a transmissao.
  
    //Convertendo char para inteiro
    int valor = atoi(CharMsg);         //Conversão de CHAR para um valor em inteiro.
  
    Serial.println(valor);             //Valor final eh amostrado. 
    digitalWrite(LED, LOW);            //Led apaga. Como a string é lida muito rápido...
  }                                    //... a led tem efeito de pisca muito rápido.
} 
