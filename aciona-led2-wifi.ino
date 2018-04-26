
#include <ESP8266WiFi.h>

#define ledPin5 D5
#define ledPin7 D7
#define ledPin2 D2

const char* ssid = "NEOQEAVDLV";
const char* senha = "()casa2014";


int staLed5 = LOW;
int staLed2 = LOW;



WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  
  pinMode(ledPin5, OUTPUT);
  digitalWrite(ledPin5, LOW);
  pinMode(ledPin7, OUTPUT);
  digitalWrite(ledPin7, LOW);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);
  
  Serial.print("Conectando a rede:");
  Serial.println(ssid);

  WiFi.begin(ssid, senha);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");

  server.begin();
  Serial.println("Servidor iniciado");

  Serial.print("Use esta URL:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  WiFiClient cliente = server.available();
  if(!cliente){
    return;
  }
  Serial.println("Novo cliente");
  while(!cliente.available()){
    delay(1);
  }
  String requisicao = cliente.readStringUntil('\r');
  Serial.println(requisicao);
  cliente.flush();

  //
  if(requisicao.indexOf("/LED=ON") != -1) {
    staLed2 = HIGH;
  }
  if(requisicao.indexOf("/LED=OFF") != -1) {
    staLed2 = LOW;
  }

  if(requisicao.indexOf("/LED2=ON") != -1) {
    staLed5 = HIGH;
  }
  if(requisicao.indexOf("/LED2=OFF") != -1) {
    staLed5 = LOW;
  }
  
  Serial.print("Led2:");
  Serial.println(staLed2);
  Serial.print("Led5:");
  Serial.println(staLed5);
  digitalWrite(ledPin5, staLed5);
  digitalWrite(ledPin7, staLed5);
  
  digitalWrite(ledPin2, staLed2);

  cliente.println("HTTP/1.1 200 OK");
  cliente.println("Content-Type:text/html");
  cliente.println("");
  cliente.println("<!DOCTYPE HTML>");

  cliente.println("<html>");
  cliente.println("<br><br>");
  cliente.println("<a href=\"/LED=ON\"\"> <button> Ligar </button></a>");
  cliente.println("<a href=\"/LED=OFF\"\"> <button> Desligar </button></a><br/>");
  cliente.println("<br><br>");
  cliente.println("<a href=\"/LED2=ON\"\"> <button> Ligar2 </button></a>");
  cliente.println("<a href=\"/LED2=OFF\"\"> <button> Desligar2 </button></a><br/>");
  cliente.println("</html>");
  delay(1);
}
