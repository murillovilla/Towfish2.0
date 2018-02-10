#include <SPI.h>
#include <UIPEthernet.h>

EthernetUDP udp;


class Towfish{
  
 
  public:
        Towfish(int PressSensorPin);
        void EthernetBegin(uint8_t mac);
        void EthernetSend(byte enviabuffer[]);
        void EthernetRead();
        void SensorRead();
        void MotorControl();
        void Sdlog();

   private:

           unsigned long next;
           int success;
           int _PressSensorPin;
           int size;
  
  };

  Towfish::Towfish(int PressSensorPin){

          PressSensorPin = _PressSensorPin;

    
    }
    
  void Towfish::EthernetBegin(uint8_t mac){

           Ethernet.begin(mac,IPAddress(192,168,0,1)); 

           success = udp.begin(5000); //Inicializa a biblioteca UDP. Recebe como parâmetro a porta local. 
                                               //A variável sucesso recebe valor "1" caso a inicialização tenha sido bem sucedida e "0" caso contrário. 
           next = millis()+100;
    
    }

  void Towfish::EthernetSend(byte enviabuffer[]){
    
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

  void Towfish::EthernetRead(){

              size = udp.parsePacket(); //Checa pela presença de um pacote UDP e retorna o tomanho do pacote.
          
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

  void Towfish::SensorRead(){

              //Leitura Sensor de Pressão          
            analogRead(_PressSensorPin);

          //Leitura Giroscópio e Acelerômetro  
          
    }

  void Towfish::MotorControl(){
    }

  void Towfish::Sdlog(){
    }

    





void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
