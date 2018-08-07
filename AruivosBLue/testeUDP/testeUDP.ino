#include <ESP8266WiFi.h>

const char *ssid = "12345678g";
const char *password = "12345678g";

#define vele D1
#define sente D3
#define veld D2
#define sentd D4
#define tempo 1000
#define tempogiro 100
#define tempopara 500
//#define tam 15

int i = 0;
int flag = 1;
int tam;

WiFiClient client;

String comandos;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

bool delay2(int max)
{
  int tmp = millis();
  while (millis() - tmp < max)
  {
    if (client.available())
    {
      return true;
    }
  }
  return false;
}

void parar()
{
  digitalWrite(vele, 0);
  digitalWrite(sente, 0);
  digitalWrite(veld, 0);
  digitalWrite(sentd, 0);
  delay2(tempopara);
}

void setup()
{
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(vele, OUTPUT);
  pinMode(sente, OUTPUT);
  pinMode(veld, OUTPUT);
  pinMode(sentd, OUTPUT);
  parar();

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
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

// void startServer()
// {
//   // Check if a client has connected
//   client = server.available();

//   if (!client)
//   {
//     return;
//   }

//   // Wait until the client sends some data
//   Serial.println("new client");
//   while (!client.available())
//   {
//     delay(1);
//   }
// }

void frente()
{
  digitalWrite(vele, 128);
  digitalWrite(sente, 0);
  digitalWrite(veld, 128);
  digitalWrite(sentd, 0);
  delay2(tempo);
}

void tras()
{
  digitalWrite(vele, 128);
  digitalWrite(sente, 1);
  digitalWrite(veld, 128);
  digitalWrite(sentd, 1);
  delay2(tempo);
}

void direita()
{
  digitalWrite(vele, 128);
  digitalWrite(sente, 0);
  digitalWrite(veld, 128);
  digitalWrite(sentd, 1);
  delay2(tempogiro);
}

void esquerda()
{
  digitalWrite(vele, 128);
  digitalWrite(sente, 1);
  digitalWrite(veld, 128);
  digitalWrite(sentd, 0);
  delay2(tempogiro);
}

void pulaAteC(int &PC, String comandos)
{
  int cont = -1;
  while (1)
  {
    if (comandos.charAt(PC) == 'l' || comandos.charAt(PC) == 'i')
    {
      cont++;
    }
    else if (comandos.charAt(PC) == 'c' && cont > 0)
    {
      cont--;
    }
    else if (comandos.charAt(PC) == 'c' && cont == 0)
    {
      break;
    }
    PC++;
  }
}
bool ifLOOP(char COND)
{
  switch (COND)
  {
  case 'y':
    return true;
    break;
  case 'n':
    return false;
    break;
  }
}
bool ifIF(char COND)
{
  switch (COND)
  {
  case 'y':
    return true;
    break;
  case 'n':
    return false;
    break;
  }
}
void compiler(String comandos, int i)
{
  int S[tam];
  int SP = 0;
  for (int PC = 0; PC < tam; PC++)
  {
    switch (comandos.charAt(PC))
    {
    //...
    case 'd':
      // girar para direita
      Serial.println("Direita");
      direita();
      //frente();
      parar();
      break;
    case 'e':
      // girar para esquerda
      Serial.println("Esquerda");
      esquerda();
      //frente();
      parar();
      break;
    case 'f':
      // ir em frente
      Serial.println("Frente");
      frente();
      parar();
      break;
    case 't':
      // ir para tras
      Serial.println("Tras");
      tras();
      parar();
      break;
    case 'i':
      if (ifIF(comandos.charAt(PC + 1)))
      {
        PC++;
        SP++;
        S[SP] = PC;
      }
      else
      {
        pulaAteC(PC, comandos);
      }
      break;
    case 'l':
      if (ifLOOP(comandos.charAt(PC + 1)))
      {
        PC++;
        SP++;
        S[SP] = PC;
      }
      else
      {
        pulaAteC(PC, comandos);
      }
      break;
    case 'c':
      if (comandos.charAt(S[SP] - 1) == 'l')
      {
        if (ifLOOP(comandos.charAt(S[SP])))
        {
          PC = S[SP];
        }
        else
        {
          SP--;
        }
      }
      else if (comandos.charAt(S[SP] - 1) == 'l')
      {
        SP--;
      }
      break;
    default:
      Serial.print("EXECUTA: ");
      Serial.println(PC);
      break;
    }
  }
}

void servidor()
{

  client = server.available();

  if (!client)
  {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available())
  {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);

  comandos = req.substring(req.indexOf("/"));
  Serial.print("Comandos = ");
  Serial.println(comandos);

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
  delay2(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}

void loop()
{
  //startServer();
  servidor();
  i = 0;

  if (flag == 1)
    compiler(comandos, i);
  flag = 0;
}
