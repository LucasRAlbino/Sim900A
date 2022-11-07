#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);

void setup(){
  mySerial.begin(9600);
  Serial.begin(9600);    
  delay(100);
  Serial.println("SIM900A - NUTES");
}

String RecebeNumero(){
  String numero = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      numero.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  Serial.print("Numero: ");
  Serial.println(numero);
    
  return numero;
}

void loop(){
  if(Serial.available() > 0){
    String numero = RecebeNumero();

    mySerial.println("AT+CMGF=1");
    delay(1000);

    String snd = "AT+CMGS=\"";
    snd += ""+numero+"";
    snd += "\"";

    mySerial.println(snd);
    delay(100);

    mySerial.println("Teste do sms");
    delay(100);

    mySerial.println((char)26);
    delay(1000);
  }
}