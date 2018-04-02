#include <ESP8266WiFi.h>


extern "C" {
#include "user_interface.h"
}
const char* ssid = "HOME-2EAF-2.4";//type your ssid
const char* password = "Manga2006";//type your password
const int threshold = 90;

WiFiServer server(80);
//Client client("twilio.com", 80);

void setup()
{
  wifi_station_set_hostname( "zach" );
  
  Serial.begin(115200);
  Serial.println();
   WiFi.mode(WIFI_STA);
  delay(100);
 Serial.setDebugOutput(true); 
  
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  server.begin();
  Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}


// prepare a web page to be send to a client (web browser)
String prepareHtmlPage()
{
  String htmlPage =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "Analog input:  " + String(analogRead(A0)) +
            "</html>" +
            "\r\n";
  return htmlPage;
}

const char* host1 = "10.0.0.146";
const int port1 = 8888;
void callTwilioServer(String phoneNumber){
    WiFiClient client1;
    Serial.println("phoneNumberlength:::");
    Serial.println(phoneNumber.length());
    if(phoneNumber.length() > 0)
    {
      if(!client1.connect(host1, port1)){
        Serial.println("...connection failed!");
        Serial.println("Retrying in 5 seconds...");
        delay(1000);
        return;  
      }
      //http://127.0.0.1:8888/phoneNumber=6508229872
      if (client1.connect(host1,port1)) { 
          // We now create a URI for the request
          String url = "/alert/"+phoneNumber/"/"+(analogRead(A0);
        
          Serial.print("Client1 Requesting URL: ");
          Serial.println(url);
        
          // This will send the request to the server
          client1.print(String("GET ") + url + " HTTP/1.1\r\n" +
                       "Host: " + host1 + "\r\n" + 
                       "Connection: close\r\n\r\n");
          delay(10);
        
          // Read all the lines of the reply from server and print them to Serial
          Serial.println("Respond:");
          while(client1.available()){
            String line = client1.readStringUntil('\r');
            Serial.print(line);
          }
        
          Serial.println();
          Serial.println("closing connection client1 ");
        
       }
    }

    return;
}
void loop()
{
  WiFiClient client = server.available();
  String phoneNumber;
  handleClient(client,phoneNumber);
  
}

void handleClient(WiFiClient client ,String phoneNumber)
{
  //TODO var phoneNumber;
  // wait for a client (web browser) to connect
  if (client)
  {
    Serial.println("\n[Client connected]");
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        
        
        String line = client.readStringUntil('\n');
        if(line.length() > 0 && line.indexOf("POST"))
        {
          
          Serial.println(line);
          if(int x=line.indexOf("phoneNumber") >= 0)
          {
            Serial.println("phoneNumber:");
            phoneNumber = line.substring(22,33);
            Serial.println(phoneNumber);
            client.flush();
            //if temperature alert use phone number and call
            callTwilioServer(phoneNumber);
          }
        }
        if(line.length() > 0 && line.indexOf("getNumber"))
        {
        }
        
        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n')
        {
          //exceeds threshold post to twilio
          if(analogRead(A0) > threshold)
          {
            //post(client);
          }
          client.println(prepareHtmlPage());
          break;
        }
      }
    }
    delay(1); // give the web browser time to receive the data

    // close the connection:
    client.stop();
    Serial.println("[Client disonnected]");
    
      
  }
}
