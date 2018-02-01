/*
 * 
 *Esse programa inicializa utiliza a comunicação Ethernet para leitura de mensagens.
 *É inicializado um dispositivo com IP 192.168.0.1 e endereço MAC {0x00, 0x01, 0x02, 0x03, 0x04, 0x05}
 *A porta utilizada é a 500.
 *O programa fica checando se existe mensagem no buffer de entrada. Caso exista a mensagem é imprimida na porta serial.
 *
 *  
 * Copyright (C) 2013 by Norbert Truchsess (norbert.truchsess@t-online.de)
 */

#include <SPI.h>
#include <UIPEthernet.h>

EthernetUDP udp;

void setup() {

  Serial.begin(9600);

  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};

  Ethernet.begin(mac,IPAddress(192,168,0,1));

  int success = udp.begin(5000); //Inicializa a biblioteca UDP. Recebe como parâmetro a porta local. A variável sucesso recebe valor "1" caso a inicialização tenha sido bem sucedida e "0" caso contrário. 

  Serial.print("initialize: ");
  Serial.println((success = 1) ? "success" : "failed"); //Aqui caso sucesso seja 1 é imprimido sucesso, caso contrário é imprimido failed

}

void loop() {

  //check for new udp-packet:
  int size = udp.parsePacket(); //Checa pela presença de um pacote UDP e retorna o tomanho do pacote.

  
  if (size > 0) {
    do
      {
        byte* msg = (byte*)malloc((size+1)*sizeof(byte)); //msg recebe o endereço inicial de uma área alocada na mémoria de tamanho ((size+1)* bytes de uma variável char)
        int len = udp.read(msg,size+1); //len recebe o número de caracteres armazenados no buffer msg, ou seja, (o tamanho de msg)-1

        msg[len]=0; //o último espaço da memória de len é limpado

        int numero = ((msg[0]*256) + msg[1]);


      Serial.print("received: ""\n" );

      Serial.print(numero);
        
        Serial.print("\n");

        free(msg);
      }
    while ((size = udp.available())>0); //udp.avaiable retorna o número de bytes prontos para serem lidos
    
    //finish reading this packet:
    udp.flush(); //limpa o buffer    

    udp.stop();

    //restart with new connection to receive packets from other clients
    Serial.print("restart connection: " "\n");
    Serial.println ((udp.begin(5000)==1) ? "success" : "failed" "\n");  
    
     } 

}
