#include <SoftwareSerial.h>
#include <Arduino.h>


SoftwareSerial mySerial(10,11);

void setup() { 
  mySerial.begin(9600);
  Serial.begin(9600);    
  delay(100);
  Serial.println("SIM900A - NUTES");
  Serial.println("M - Para digitar a mensagem.");
}
  
/**
 * Função que lê uma string da Serial
 * e retorna-a
 */
String leStringSMS(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  Serial.print("Mensagem enviada: ");
  Serial.println(conteudo);
    
  return conteudo;
}


void loop() {
  // Se receber algo pela serial
  if (Serial.available() > 0){
    // Lê toda string recebida
    String recebido = leStringSMS();


    mySerial.println("AT+CMGF=1");
    delay(1000);

    // AT+CMGS = \"NUMERO\"
    mySerial.println("AT+CMGS=\"+5583981651468\"\r");
    delay(1000);

    mySerial.println(recebido);
    delay(100);

    mySerial.println((char)26);
    delay(1000);
  }
}