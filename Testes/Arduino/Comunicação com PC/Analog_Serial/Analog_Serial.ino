
/*
 * Esse programa envia na porta serial dois valores separados por vírgula. O primeiro valor 
 * corresponde à leitura da porta analógica A0 e o segundo valor corresponde ao número 123. Após  
 * o número 123 é enviado também o caractere "\n" que representa a troca de linha.
 */


int SensorValue;

void setup() {
  

Serial.begin(9600);

}

void loop() {

  SensorValue = analogRead(A0);

  delay(100);

  
  Serial.print(SensorValue);
  Serial.print(",");
  Serial.print(123);
  Serial.print("\n");
  Serial.flush();
  
  

}
