/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/

#include <ESP8266WiFi.h>

const char* ssid = "12345678g";
const char* password = "12345678g";

#define me1 D1
#define me2 D3
#define md1 D2
#define md2 D4
#define tempo 1000
#define tempogiro 100
int i = 0;

String comandos;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void parar() {
  digitalWrite(me1, 0);
  digitalWrite(me2, 0);
  digitalWrite(md1, 0);
  digitalWrite(md2, 0);
  delay(tempogiro);
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(me1, OUTPUT);
  pinMode(me2, OUTPUT);
  pinMode(md1, OUTPUT);
  pinMode(md2, OUTPUT);
  parar();

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void frente() {
  digitalWrite(me1, 1);
  digitalWrite(me2, 0);
  digitalWrite(md1, 1);
  digitalWrite(md2, 0);
  delay(tempo);
  parar();
}

void tras() {
  digitalWrite(me1, 0);
  digitalWrite(me2, 1);
  digitalWrite(md1, 0);
  digitalWrite(md2, 1);
  delay(tempo);
  parar();
}

void direita() {
  digitalWrite(me1, 1);
  digitalWrite(me2, 0);
  digitalWrite(md1, 0);
  digitalWrite(md2, 1);
  delay(tempogiro);
  parar();
}

void esquerda() {
  digitalWrite(me1, 0);
  digitalWrite(me2, 1);
  digitalWrite(md1, 1);
  digitalWrite(md2, 0);
  delay(tempogiro);
  parar();
}

void compiler(String comandos, int i) {
  for (i; i < comandos.length(); i++) {
    switch (comandos.charAt(i)) {
      case 'd':
        // girar para direita
        Serial.println("Direita");
        direita();
        frente();
        break;
      case 'e':
        // girar para esquerda
        Serial.println("Esquerda");
        esquerda();
        frente();
        break;
      case 'f':
        // ir em frente
        Serial.println("Frente");
        frente();
        break;
      case 't':
        // ir para tras
        Serial.println("Tras");
        tras();
        break;
      case 'c':
        // BREAK!
        Serial.println("Parar");
        parar();
        break;
      case 'i':
        // executa o if (Execute the next command)
        i++;
        compiler(comandos, i);
        break;
      case 'l':
        // Loop (Execute the command 3 times)
        i++;
        for (int j = 0; j < 3; j++) {
          compiler(comandos, i);
        }
        break;
      default:
        // Break too
        break;
    }
  }
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);

  comandos = req.substring(req.indexOf("/"));
  Serial.print("Comandos = "); Serial.println(comandos);

  client.flush();

  i = 0;
  // Match the request
  compiler(comandos, i);


  client.flush();
  int val;
  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val) ? "high" : "low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}
