#include <ESP8266WiFi.h>


const char* ssid = "12345678g";
const char* password = "12345678g";

#define me1 D1
#define me2 D3
#define md1 D2
#define md2 D4
#define tempo 1000
#define tempogiro 100
#define tempopara 500
//#define tam 15

int i = 0;
int flag = 1;
int tam;

String comandos;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void parar() {
  digitalWrite(me1, 0);
  digitalWrite(me2, 0);
  digitalWrite(md1, 0);
  digitalWrite(md2, 0);
  delay(tempopara);
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
  digitalWrite(me1, 128);
  digitalWrite(me2, 0);
  digitalWrite(md1, 128);
  digitalWrite(md2, 0);
  delay(tempo);
}

void tras() {
  digitalWrite(me1, 1);
  digitalWrite(me2, 1);
  digitalWrite(md1, 1);
  digitalWrite(md2, 1);
  delay(tempo);
  Serial.println("entrou na tras");
}

void direita() {
  digitalWrite(me1, 1);
  digitalWrite(me2, 0);
  digitalWrite(md1, 0);
  digitalWrite(md2, 1);
  delay(tempogiro);
}

void esquerda() {
  digitalWrite(me1, 1);
  digitalWrite(me2, 1);
  digitalWrite(md1, 0);
  digitalWrite(md2, 0);
  delay(tempogiro);
}

void pulaAteC(int& PC, char  comandos[]) {
  int cont = -1;
  while (1) {
    if (comandos[PC] == 'l' || comandos[PC] == 'i') {
      cont ++;
    } else if (comandos[PC] == 'c' && cont > 0) {
      cont --;
    } else if (comandos[PC] == 'c' && cont == 0) {
      break;
    }
    PC++;
  }
}
bool ifLOOP(char COND) {
  switch (COND) {
    case 'y':
      return true;
      break;
    case 'n':
      return false;
      break;
  }
}
bool ifIF(char COND) {
  switch (COND) {
    case 'y':
      return true;
      break;
    case 'n':
      return false;
      break;
  }
}
int compiler() {
  int S[tam];
  int SP = 0;
  for (int PC = 0; PC < tam; PC++) {
    switch (comandos[PC]) {
      //...
      case 'i':
        if (ifIF(comandos[PC + 1])) {
          PC++;
          SP++;
          S[SP] = PC;
        } else {
          pulaAteC(PC, comandos);
        }
        break;
      case 'l':
        if (ifLOOP(comandos[PC + 1])) {
          PC++;
          SP++;
          S[SP] = PC;
        } else {
          pulaAteC(PC, comandos);
        }
        break;
      case 'c':
        if (comandos[S[SP] - 1] == 'l') {
          if (ifLOOP(comandos[S[SP]])) {
            PC = S[SP];
          } else {
            SP--;
          }
        } else if (comandos[S[SP] - 1] == 'l') {
          SP--;
        }
        break;
      default:
        cout << "EXECUTA:" << PC << endl;
        break;
    }
  }
}


void servidor() {
  // Check if a client has connected
  WiFiClient client = server.available();
  //client = server.available();
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

  flag = 1;
  client.flush();



  //client.flush();
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

void loop() {
  servidor();
  i = 0;
  
  if (flag == 1)
    compiler(comandos, i);
  flag = 0;
}

