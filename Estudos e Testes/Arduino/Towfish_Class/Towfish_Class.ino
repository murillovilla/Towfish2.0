/*
 * Código que implementa a classe Arduino_Towfish
 * Todas as funções necessárias para implementação do controle de profundidade do Towfish serão implementadas nessa classe.
 */
#include <SPI.h>
#include <UIPEthernet.h>

class Towfish{    
        
  public:

          EthernetUDP udp;
          unsigned long next;   //Variável para contagem do tempo para envio da mensagem UDP
          int success;          //Variável que verifica se a Ethernet foi iniciada corretamente
          int PressPin;          //Pino analógico em que está o sensor de pressão

          Towfish(int _PressSensorPin){

            Serial.begin(9600);

            PressSensorPin = _PressSensorPin;      //Pino analógico em que está o sensor de pressão
          }
            
                 
        
          void EthernetBegin(uint8_t mac){
                       
                Ethernet.begin(mac,IPAddress(192,168,0,1)); 

                success = udp.begin(5000); //Inicializa a biblioteca UDP. Recebe como parâmetro a porta local. 
                                               //A variável sucesso recebe valor "1" caso a inicialização tenha sido bem sucedida e "0" caso contrário. 
                next = millis()+100;
                        
            }
            
          void EthernetSend(byte enviabuffer[]){

              if (((signed long)(millis()-next))>0){
                 do
                    { 
                      success = udp.beginPacket(IPAddress(192,168,0,1),5000);
                      Serial.print("beginPacket: ");
                      Serial.println(success ? "success" : "failed");
                      //beginPacket fails if remote ethaddr is unknown. In this case an
                      //arp-request is send out first and beginPacket succeeds as soon
                      //the arp-response is received.
                    }
                  while (!success && ((signed long)(millis()-next))<0);
                  if (!success ){
                    goto stop;
                  }
            
               success = udp.write(enviabuffer,sizeof(enviabuffer));      //Envia a mensagem pela Ethernet

               stop:
               udp.stop();
               next = millis() + 100;
            
            }

          }


        void EthernetRead(){

              int size = udp.parsePacket(); //Checa pela presença de um pacote UDP e retorna o tomanho do pacote.
          
              if (size > 0) {
                  do
                    {
                      byte* msg = (byte*)malloc((size+1)*sizeof(byte)); //msg recebe o endereço inicial de uma área alocada 
                                                                        //na mémoria de tamanho ((size+1)* bytes de uma variável char)
                      int len = udp.read(msg,size+1); //len recebe o número de caracteres armazenados no buffer msg, ou seja, (o tamanho de msg)-1
              
                      msg[len]=0; //o último espaço da memória de len é limpado
              
                      int EthernetMsg = ((msg[0]*256) + msg[1]);                     
                        
                  }
  
                  while ((size = udp.available())>0); //udp.avaiable retorna o número de bytes prontos para serem lidos
  
                  udp.flush(); //limpa o buffer 
  
                  udp.stop();
  
              }
        }

        void SensorsRead(){
          
          //Leitura Sensor de Pressão          
            analogRead(PressPin);

          //Leitura Giroscópio e Acelerômetro                
          
          }


      void MotorControl(){
        }


      void SdLog(){
        }    
  
};


//Towfish meuTowfish(4);
  

//void setup() {
//  // put your setup code here, to run once:
//
//}

//void loop() {
//}
