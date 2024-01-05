//============================================
//===================Pin======================
//============================================
//=========NodeMcu==========Raspberry=========
//===========RX================GP0======UART==
//===========TX================GP1======UART==
//==========3v3==============3v3(OUT)===POWER=
//==========GND================GND======POWER=
//============================================
#include <ESP8266WiFi.h>

//Variables
const char* ssid = "HOST";
const char* password = "753159Maruf";

const pc_ip = "192.168.0.108";  // Pc Server ip

WiFiServer server(80);

void setup() {
    Serial.begin(115200); // Set the baud rate
    delay(100);
    //CONNECT TO WIFI
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED){
      delay(500);
    }

    // Start the Server
    server.begin();

    // Print the IP address
    Serial.print(WiFi.localIP());
}

void loop() {
  // READ DATA FROM PICO PICO->NODEMCU
  if (Serial.available()) {
    String pico_received = Serial.readString();  // Read incoming data from RP PI PICO
    
  }


  
//  =======================================================
  WiFiClient client = server.available();
  if (!client){
    return;
  }
  while(!client.available()){
    delay(1);
  }
  String web_received = client.readStringUntil('\r');
  client.flush();
//==========================================================
  //  Process data
  web_received.replace("GET /", "");
  web_received.replace(" HTTP/1.1", "");
  web_received.replace("\n", "");
  web_received.replace("/", " ");

  //  Conditions
  if(web_received){
    //  Send data to raspberry
    client.print("Data Recieved.");
    Serial.println(web_received);
  }

  else{
    client.stop();
    return;
  }

  client.flush();
  delay(1000);
}
