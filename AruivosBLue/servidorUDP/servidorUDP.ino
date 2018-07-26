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

#define verde 12
#define azul 13
#define vermelho 15

String comandos;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(azul, OUTPUT);
  digitalWrite(azul, 0);
  pinMode(verde, OUTPUT);
  digitalWrite(verde, 0);
  pinMode(vermelho, OUTPUT);
  digitalWrite(vermelho, 0);

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

void compiler(String comandos) {
  for (int i = 0; i < comandos.length(); i++) {
    switch (comandos.charAt(i)) {
      case 'd':
        // girar para direita
        Serial.println("Girar para Direita");
        digitalWrite(azul, 1);
        delay(1000);
        digitalWrite(azul, 0);
        break;
      case 'e':
        // girar para esquerda
        Serial.println("Girar para Esquerda");
        digitalWrite(verde, 1);
        delay(1000);
        digitalWrite(verde, 0);
        break;
      case 'f':
        // ir em frente
        Serial.println("Ir para Frente");
        digitalWrite(vermelho, 1);
        delay(1000);
        digitalWrite(vermelho, 0);
        break;
      case 't':
        // ir para tras
        Serial.println("Ir para Tras");        
        break;
      case 'c':
        // BREAK!
        Serial.println("Parar");
        break;
      case 'i':
        // executa o if (Execute the next command)
        i++;
        switch (comandos.charAt(i)) {
          case 'd':
            // girar para direita
            Serial.println("Girar para Direita");
            break;
          case 'e':
            // girar para esquerda
            Serial.println("Girar para Esquerda");
            break;
          case 'f':
            // ir em frente
            Serial.println("Ir para Frente");
            break;
          case 't':
            // ir para tras
            Serial.println("Ir para Tras");
            break;
          case 'c':
            // BREAK!
            Serial.println("Parar");
            break;
          case 'l':
            // Loop
            break;
          default:
            // Break too
            break;
        }
        break;
      case 'l':
        // Loop (Execute the command 3 times)
        i++;
        for (int j = 0; j < 3; j++) {
          switch (comandos.charAt(i)) {
            case 'd':
              // girar para direita
              Serial.println("Girar para Direita");
              break;
            case 'e':
              // girar para esquerda
              Serial.println("Girar para Esquerda");
              break;
            case 'f':
              // ir em frente
              Serial.println("Ir para Frente");
              break;
            case 't':
              // ir para tras
              Serial.println("Ir para Tras");
              break;
            case 'c':
              // BREAK!
              Serial.println("Parar");
              break;
            case 'i':
              // statements
              break;
            case 'l':
              // Loop
              break;
            default:
              // Break too
              break;
          }
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

  // Match the request
  compiler(comandos);


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
