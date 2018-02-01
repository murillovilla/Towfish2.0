
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <UIPEthernet.h>

// Pinos do Display
LiquidCrystal lcd(8, 7, 6, 5 ,4 , 3);       //Configura o display de LCD(RS,E,D4,D5,D6,D7) 

EthernetUDP udp;

//Variáveis para Conversão
float valor_tensao, pressao, profundidade;

//Variáveis para o display 
unsigned char centena, dezena, unidade, milhar;

void setup() {

  Serial.begin(9600);

 //Inicializando display LCD
 lcd.begin(16, 2);
 lcd.clear();  
 lcd.print("Profundidade(m)"); 

  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};

  Ethernet.begin(mac,IPAddress(192,168,0,1));

  int success = udp.begin(5000); //Inicializa a biblioteca UDP. Recebe como parâmetro a porta local. 
                                 //A variável sucesso recebe valor "1" caso a inicialização tenha sido bem sucedida e "0" caso contrário. 

  Serial.print("initialize: ");
  Serial.println((success = 1) ? "success" : "failed"); //Aqui caso sucesso seja 1 é imprimido sucesso, caso contrário é imprimido failed

}

void loop() {

  //check for new udp-packet:
  int size = udp.parsePacket(); //Checa pela presença de um pacote UDP e retorna o tomanho do pacote.

  
  if (size > 0) {
    do
      {
        byte* msg = (byte*)malloc((size+1)*sizeof(byte)); //msg recebe o endereço inicial de uma área alocada 
                                                          //na mémoria de tamanho ((size+1)* bytes de uma variável char)
        int len = udp.read(msg,size+1); //len recebe o número de caracteres armazenados no buffer msg, ou seja, (o tamanho de msg)-1

        msg[len]=0; //o último espaço da memória de len é limpado

        int leiturasensor = ((msg[0]*256) + msg[1]);


      Serial.print("Numero recebido:""\n" );

      Serial.print(leiturasensor);

      Serial.print("\n");          
            
      lcd.setCursor(1,1);
      lcd.print(conversao_Profundidade(leiturasensor)); 

      ;
        
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

float conversao_Profundidade(int analog){

  valor_tensao = (analog*(5.0/1024)) ; //Faz a leitura da entrada analógica e converte o número inteiro para um valor de tensão

  Serial.print("Valor da tensão convertida:""\n");

  Serial.print(valor_tensao,4);  

  Serial.print("\n");
    

  pressao = ((valor_tensao)*2.4645 - 2.3225); //Converte a tensão para um valor de pressão em Bar  

  Serial.print("Valor convertido em pressao:""\n") ;

  Serial.print(pressao,4);  

  Serial.print("\n");  
    

  profundidade = pressao*10.1974;

    Serial.print("Valor convertido de profundidade:""\n") ;

  Serial.print(profundidade,4);

 
  Serial.print("\n");

  if (profundidade <= 0){

    profundidade =0;
    
    }
    delay(200);  

  return profundidade;
  
  
  }
