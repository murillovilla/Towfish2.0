/*
 * Implementação de um Robo. ELe tem um sensor de temperatura
 * Pino 3, aquecedor/resfriador
 * 0 -> resfriando (MAX)
 * 50 -> desligar
 * 100 -> aquecendo (MAX)
 * 
 * Temperatura: A1 (0 - 1024)
 * 0:0
 * 1024:100
 */

class PID{
  public:

        //Valores das constantes do controlador
         double kP, kI, kD ;
         double P, I, D;
         double PID;
    
        //Erro na entrada do controlador
         double sample;
         double lastsample;
         double error;       
    
        //setPoint é o valor de referência do sistema
         double setPoint;
         long lastProcess;
    
         PID(double _kP, double _kI, double _kD){
            kP =_kP;
            kI = _kP;
            kD = _kD;
      }

      void addNewSample(double _sample){

            sample = _sample;      
        
        };

      void setSetPoint(double _setPoint){
           setPoint = _setPoint;
        
        };

      double process(){        
              
              //Implementação PID
              error = setPoint - sample;
              float deltaTime = (millis() - lastProcess)/1000.0;
              lastProcess = millis();
        
              //P
              P = error * kP;
        
              //I
              I += (error * kI)*(deltaTime);
        
              //D
              D = ((lastsample - sample) * kD) * (deltaTime);
        
              lastsample = sample;
        
              //PID
        
              PID = P + I + D;
              
              return PID;
        }
  
};

#define pSENSOR A1
#define pCONTROLE 3

PID meuPid(1.0, 0.0, 0.0);

int controlePwm = 50;

double temperature;

void setup() {
     Serial.begin(9600);

     pinMode(pSENSOR, INPUT);
     pinMode(pCONTROLE, OUTPUT);

 }

void loop() {

       //Lê temperatura
        temperature =  map(analogRead(pSENSOR),0, 1023, 0, 100);

       //Adiciona a temperatura como amostra

           meuPid.addNewSample(temperature);

      //Converte para controle

          controlePwm = (meuPid.process() + 50);   


      //Saída do controle
           analogWrite(pCONTROLE, controlePwm);
  

}
