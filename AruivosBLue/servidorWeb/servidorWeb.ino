#include <ESP8266WiFi.h>//Biblioteca que gerencia o WiFi.
#include <WiFiServer.h>//Biblioteca que gerencia o uso do TCP.

WiFiServer servidor(80);//Cria um objeto "servidor" na porta 80 (http).
WiFiClient cliente;//Cria um objeto "cliente".

String html;//String que armazena o corpo do site.
String comandos;

void setup()
{
  Serial.begin(9600);//Inicia comunicaçao Serial.

  WiFi.mode(WIFI_STA);//Habilita o modo STATION.
  WiFi.begin("Cabo82", "mat0154059");//Conecta no WiFi (COLOQUE O NOME E SENHA DA SUA REDE!).

  Serial.println(WiFi.localIP());//Printa o IP que foi consebido ao ESP8266 (este ip que voce ira acessar).
  servidor.begin();//Inicia o Servidor.

  pinMode(13, OUTPUT);//Define o LED_BUILTIN como Saida.
}

void loop()
{
  //Serial.println(WiFi.localIP());
  http();//Sub rotina para verificaçao de clientes conectados.
}

void http()//Sub rotina que verifica novos clientes e se sim, envia o HTML.
{
  cliente = servidor.available();//Diz ao cliente que há um servidor disponivel.

  if (cliente == true)//Se houver clientes conectados, ira enviar o HTML.
  {
    String req = cliente.readStringUntil('\r');//Faz a leitura do Cliente.
    Serial.println(req);//Printa o pedido no Serial monitor.

    Serial.print("index = ");
    Serial.println(req.indexOf("/"));

    comandos = req.substring(req.indexOf("/"));

    Serial.println(comandos);

    for (int i = 0; i < comandos.length(); i++) {
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

    if (req.indexOf("/dc") > -1)//Caso o pedido houver led, inverter o seu estado.
    {
      digitalWrite(13, !digitalRead(13));//Inverte o estado do led.
    }

    html = "";//Reseta a string.
    html += "HTTP/1.1 Content-Type: text/html\n\n";//Identificaçao do HTML.
    html += "<!DOCTYPE html><html><head><title>ESP8266 WEB</title>";//Identificaçao e Titulo.
    html += "<meta name='viewport' content='user-scalable=no'>";//Desabilita o Zoom.
    html += "<style>h1{font-size:2vw;color:black;}</style></head>";//Cria uma nova fonte de tamanho e cor X.
    html += "<body bgcolor='ffffff'><center><h1>";//Cor do Background

    //Estas linhas acima sao parte essencial do codigo, só altere se souber o que esta fazendo!

    html += "<form action='/dc' method='get'>";//Cria um botao GET para o link /LED
    html += "<input type='submit' value='LED' id='frm1_submit'/></form>";

    html += "</h1></center></body></html>";//Termino e fechamento de TAG`s do HTML. Nao altere nada sem saber!
    cliente.print(html);//Finalmente, enviamos o HTML para o cliente.
    cliente.stop();//Encerra a conexao.
  }
}
