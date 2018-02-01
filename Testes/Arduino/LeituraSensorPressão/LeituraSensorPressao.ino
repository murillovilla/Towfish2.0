/*
  LeituraSensor
  O programa faz a leitura de uma entrada analógica no pino 0.
  A leitura vem do sensão de pressão. O sensor tem uma saída de 4 à 20mA.
  Será utilizado um resistor de 250 ohms para conversão da corrente em tensão.
  Assim teremos um valor de 1 à 5V.
  É necessário converter a leitura da função analogueRead, que nos fornece um valor inteiro entre 0 e 1023, para um valor de tensão.
  Temos a seguinte equação para tal conversão.

  Saída em Tensão = (analogueRead*(5-1))/(1024) + 1
  
  Temos a seguinte equação para converter a saída do sensor em valores reais

  Valor Real = (Saída - 1) * 10 /(5-1)
  */
  
unsigned char saidadosensor, pressao; //saída do sensor é o valor de tensão que vem do sensor (1-5V para resistor de 250 ohms). Valordamedida será o valor convertido em pressão


// the setup routine runs once when you press reset:
void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);
 
}

// the loop routine runs over and over again forever:
void loop() {


  int analog = analogRead(A5);
  
   saidadosensor = ((analogRead(A5)*(4.74-0.948))/1024) +1; //Faz a leitura da entrada analógica e converte o número inteiro para um valor de tensão

   pressao = ((saidadosensor - 1) * 10)/(4.74-0.948); //Converte a tensão para um valor de pressão

   

  // Manda o valor para a porta serial:
  Serial.println(analog);
  Serial.println(saidadosensor);  
  Serial.println("Pressao");
  Serial.println(pressao);
  delay(1000);        // delay in between reads for stability
}
