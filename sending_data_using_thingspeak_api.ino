#include <ESP8266WiFi.h>
 
const char* mynetwork = “<Wi-Fi Network Name>”;
 
const char* mypassword = “<Wi-Fi Network Mypassword>”;
 
const char* thingspeakhost = “api.thingspeak.com”;
 
char tsaddress[] = “api.thingspeak.com”;
 
String ThingSpeakAPI = “<ThingSpeak Write Key>”;
 
const int UpdateInterval = 30 * 1000;
 
long ConnectionTime = 0;
 
boolean connectedlast = false;
 
int fcounter = 0;
 
float value = 100;
 
WiFiClient client;
 
void setup()
 
{
 
Serial.begin(9600);
 
startEthernet();
 
}
 
void loop()
 
{
 
String RecordedAnalogInput0 = String(value++, DEC);
 
if (client.available())
 
{
 
char c = client.read();
 
}
 
if (!client.connected() && connectedlast)
 
{
 
client.stop();
 
}
 
if(!client.connected() && (millis() - ConnectionTime > UpdateInterval))
 
{
 
updateThingSpeak(“field1=”+RecordedAnalogInput0);
 
}
 
if (fcounter > 3) {startEthernet();}
 
connectedlast = client.connected();
 
}
 
void updateThingSpeak(String tsData)
 
{
 
if (client.connect(tsaddress, 80))
 
{
 
client.print(“POST /update HTTP/1.1\n”);
 
client.print(“Thingspeakhost: api.thingspeak.com\n”);
 
client.print(“Connection: close\n”);
 
client.print(“X-THINGSPEAKAPIKEY: “+ThingSpeakAPI+”\n”);
 
client.print(“Content-Type: application/x-www-form-urlencoded\n”);
 
client.print(“Content-Length: “);
 
client.print(tsData.length());
 
client.print(“\n\n”);
 
client.print(tsData);
 
ConnectionTime = millis();
 
if (client.connected())
 
{
 
Serial.println(“Connecting to ThingSpeak...”);
 
Serial.println();
 
fcounter = 0;
 
}
 
else
 
{
 
fcounter++;
 
Serial.println(“Connection to ThingSpeak failed (“+String(fcounter, DEC)+”)”);
 
Serial.println();
 
}
 
}
 
else
 
{
 
fcounter++;
 
Serial.println(“Connection to ThingSpeak Failed (“+String(fcounter, DEC)+”)”);
 
Serial.println();
 
ConnectionTime = millis();
 
}
 
}
 
void startEthernet()
 
{
 
fcounter = 0;
 
client.stop();
 
Serial.println(“Connecting”);
 
WiFi.begin(mynetwork, mypassword);
 
while (WiFi.status() != WL_CONNECTED) {
 
delay(500); }
 
}
