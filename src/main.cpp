//======================================================================================================================================================================================
//======================================================================================================================================================================================
//======================================================================================================================================================================================
// #include <Arduino.h>
// #include <ArduinoJson.h>
// // String mensagem = "esp32 - string e json";
// // String mensagemAlterada;
// void setup()
// {
//   Serial.begin(115200);
//   Serial.setTimeout(5000);

//   // Serial.println("Digite uma mensagem: ");
// }

// void loop()
// {
//   // if (Serial.available()) // verifica se tem conteudo na serial
//   // {
//   //   mensagem = Serial.readStringUntil('\n');
//   // }
//   // Serial.print("mensagem recebida: ");
//   // Serial.println(mensagem);

//   // mensagemAlterada = "mensagem recebida: " + mensagem + "!";
//   // // oque é texto tem que estar dentro de aspas, e o que não é tem que estar fora de aspas e o sinal de mais ("+")

//   // Serial.println(mensagemAlterada);
//   // Serial.println(mensagemAlterada.length());
//   // // mostra o tamanho dessa mensagem

//   // String parte = mensagemAlterada.substring(18, 25);
//   // // vai receber uma parte da mensagem original || funciona a partir de tipo qual caracterer ccomeça e quatos vc quer
//   // Serial.print("mensagem retirada: ");
//   // Serial.println(parte);

//   // parte.toUpperCase(); // CAPS DESLIGADO || letra minuscula
//   // parte.toLowerCase(); // CAPS LIGADO || LETRA MAIÚSCULA
//   // ========================================================================================================================
//   // String msg = "Temp: 25.5";
//   // if (msg.startsWith("Temp"))//verifica se a mensagem é igual o que vc tem dentro entre "" || endsWith pega o final
//   // {
//   //   Serial.println("temperatura recebida");
//   // }
//   // ========================================================================================================================
//   // JSON - javascript object notation
//   {
//   //   "temperatura" : 25.5, // voce cria uma chave é o valor dela || o modelo é parecido com variavel
//   //   "umidade" : 50,       // porem aqui é como se fosse uma caixa que você pode armazenar varias coisas, você não precisa se preocupar como ela esta salva
//   //   "chovendo" : true,    //
//   //   "ceu" : "nublado"     // quando é um texto você precisa colocar aspas ("") || só precisa de virgula só pra separar elemento se ele é ultimo ele nao precisa ser separado
//   // }

//   delay(3500);
// }
// }
//======================================================================================================================================================================================
//======================================================================================================================================================================================
//====================================================================================================================================================================================
// #include <Arduino.h>
// #include <ArduinoJson.h>

// void setup()
// {
//   Serial.begin(115200);
//   Serial.setTimeout(5000);
//   // como criar um objeto de estilo JSON

//   JsonDocument doc;

//   // como adicionar os dados aos objetos

//   doc["temp"] = 25, 5; // dentro do doc cria um espaço chamado tempo e guarda esse valor ai pra mim
//   doc["umi"] = 60;     // sempre que vc for adicionar dados ao objeto tem que criar uma linha nova de codigo
//   doc["sensor"] = "DHT22";

//   // como por em praticar
//   doc["temp"] = "readTemperature"; // vai entregar a temperatura lida pelo dht em tempo real
//   //===============================
//   // quando vc monta um objeto de estilo json ele cria de pedaçinho em pedaçinho, esse "serializeJsonPretty" compacta pra virar um pacote na serial, ele SERIALIZA esse cara
//   serializeJsonPretty(doc, Serial);

//   // como você acessa os valores do JSON
//   float temperatura = doc["temp"];
//   float umidade = doc["umi"];
//   String sensor = doc["sensor"];
//   // a partir do momento que você salva eles dentro de uma variaveis vc pode usar pra qualquer coisa

//   // como exibir os dados
//   Serial.println(sensor);

//   // como DESERIALIZAR o pacote
// }

// void loop()
// {
// }
//======================================================================================================================================================================================
//======================================================================================================================================================================================
//====================================================================================================================================================================================
// #include <Arduino.h>
// #include <ArduinoJson.h>
// #include <BluetoothSerial.h>
// // voce precisa criar seu objeto json

// JsonDocument doc;
// void setup()
// {
//   Serial.begin(115200);

//   // inicia e configura o bluetooth
// }

// void loop()
// {
//   // le os dados e envia, porque quem vai pegar os dados vai ter que colocar dentro do pacote e depois enviar

//   // vai ler os dados do dht 22

//   // salvar os dados no doc
//   doc["temp"] = "readTemperature"; // valor lido no dht(temperatura)
//   doc["umi"] = "readHumidity";     // valor lido no dht(umidade)

//   // serializar o pacote
//   String mensagem;
//   serializeJson(doc, mensagem);
//   //voce montou o pacote, fechou e embalou, enviou via bluetooth
//   BT.println(mensagem);
// }
//======================================================================================================================================================================================
//======================================================================================================================================================================================
//======================================================================================================================================================================================

// #include <Arduino.h>
// #include <ArduinoJson.h>
// #include <BluetoothSerial.h>

// JsonDocument doc;
// void setup()
// {
//   Serial.begin(115200);
// }
// void loop()
// {
//   // recebe os dados do bluetooth

//   // como deserializar o pacote
//   String mensagem;
//   DeserializationError erro = deserializeJson(doc, mensagem); // deserializeJson(doc,mensagem); = responsavel por deserializar o pacote

//   if (erro)
//   {
//     Serial.println("erro ao tentar interpretar o JSON");
//   }

//   float temperatura = doc["temp"];

//   //objeto JSON é uma caixa que cabe varios valores la dentro, serializa pra mandar e deserializa pra abrir
// }
//======================================================================================================================================================================================
//======================================================================================================================================================================================
//======================================================================================================================================================================================

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <BluetoothSerial.h>
#include <DHT.h>
#define pinDHT 5
#define tipoDHT DHT22
LiquidCrystal_I2C lcd(0x27, 20, 4);
BluetoothSerial BT;
// dentro das {} é o endereço do slave
uint8_t endSlave[] = {0xF4, 0x65, 0x0B, 0x54, 0x70, 0x12};

unsigned long tempoAnterior = 0;
const unsigned long intervalo = 2000;

float tempC_anterior = 0;
float umidade_anterior = 0;

DHT medidor(pinDHT, tipoDHT);
void setup()
{
  Serial.begin(115200);
  medidor.begin();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   MASTER DHT22    ");
  lcd.setCursor(0, 1);
  lcd.print("temperatura: ");
  lcd.setCursor(0, 2);
  lcd.print("fahrenheit: ");
  lcd.setCursor(0, 3);
  lcd.print("umidade: ");

  if (BT.begin("BTMasterKaua", true)) // diferente do slave o true é depois da virgula
  {
    Serial.println("bluetooth iniciou corretamente");
  }
  else
  {
    Serial.println("erro ao iniciar o bluetooth");
  }
  if (BT.connect(endSlave))
  {
    Serial.println("Conectado com Sucesso");
  }
  else
  {
    Serial.println("erro ao conectar com bluetooth");
  }
}
void loop()
{
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= intervalo)
  {
    tempoAnterior = tempoAtual;

    float tempC = medidor.readTemperature();
    float tempF = medidor.readTemperature(true);
    float umidade = medidor.readHumidity();

    if (!isnan(tempC) && !isnan(umidade))
    {
      bool mudou = (tempC != tempC_anterior || umidade != umidade_anterior);
      bool passouTempo = (tempoAtual - tempoAnterior >= intervalo);

      // atualiza o lcd (SOMENTE SE HOUVER ALTERAÇÃO) 
      if (mudou)
      {
        lcd.setCursor(13, 1);
        lcd.print(tempC, 1);
        lcd.print("C  ");

        lcd.setCursor(13, 2);
        lcd.print(tempF, 1);
        lcd.print("F  ");

        lcd.setCursor(13, 3);
        lcd.print(umidade, 1);
        lcd.print("%  ");

        // atualiza os históricos para não escrever de novo no LCD até mudar
        tempC_anterior = tempC;
        umidade_anterior = umidade;
      }
      // adiciono os dados aos objetos e crio o pacote
      JsonDocument docDados;
      docDados["temperatura_c"] = tempC;
      docDados["temperatura_f"] = tempF;
      docDados["umidade"] = umidade;
      // serialização
      String pacoteJson;
      serializeJson(docDados, pacoteJson);
      // faço a leitura dos dados
      BT.println(pacoteJson);
      Serial.print("dados: ");
      Serial.println(pacoteJson);
    }

    if (BT.available()) // função que verifica se chegou algo no bluetooth e se sim é igual a true
    {
      // '\n' é usado pra verificar que chegou no final do texto
      String msgRecebida = BT.readStringUntil('\n'); // verifica se esta conectado, caso esteja conectado ele vai ler o que esta sendo recebido como texto
      msgRecebida.trim();                            // remove todos os caracteres em brancos e especiais
      Serial.printf("mensagem recebida: %s", msgRecebida);
    }
    if (Serial.available()) // verifica se tem algo na serial e mostra no bluetooth
    {
      String msgEnviar = Serial.readStringUntil('\n');
      msgEnviar.trim();      // remove todos os caracteres em brancos e especiais
      BT.println(msgEnviar); // envia pro bluetooth
    }
  }
}