#include "WiFi.h"
#include "AsyncUDP.h"
#include <Adafruit_NeoPixel.h>

AsyncUDP udp;

int position = 0;
int red = 100;
int green = 100;
int blue = 100;
int iterate = 0;
int oneChar = 8;
#define rows  8 
word columns = 0;
#define PIN        4 
#define NUMPIXELS 64 /

//Comment the 3 lines below out if you want to use DHCP(see setup)
IPAddress ip(192, 168, 1, 57);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); //if you are using RGB
//Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800); //if you are using RGBW


void testOn(int i, int RED, int GREEN, int BLUE)
{
  if(NUMPIXELS == 64){pixels.setPixelColor(i, pixels.Color(RED, GREEN, BLUE));}
  if(NUMPIXELS == 256){pixels.setPixelColor(i, pixels.Color(RED, GREEN, BLUE, 0));}
}

void testOff(int i)
{
  if(NUMPIXELS == 64){pixels.setPixelColor(i, pixels.Color(0, 0, 0));}
  if(NUMPIXELS == 256){pixels.setPixelColor(i, pixels.Color(0, 0, 0, 0));}
  pixels.show(); 
}

void setup()
{
  Serial.begin(115200);
  pixels.begin();
  WiFi.setSleep(false);
  WiFi.config(ip, gateway, subnet); //Also need to comment this line out if you want to use DHCP
  for(int u=0; u<NUMPIXELS; u++)
  {
    testOff(u);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin("SSID", "Password");
  if(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while(1) 
    {
      delay(1000);
    }
  }
  if(udp.listen(1234)) 
  {
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
    
    udp.onPacket([](AsyncUDPPacket packet) 
    {
     // Serial.println(packet.length());
     if(packet.length() == 88){columns = 0; position = 0;}
      oneChar = 8;
      for(int i=0; i<rows; i++)
      {  
        iterate = 0;
        if(iterate == 0){red    = 100 * (((char)*(packet.data() + oneChar)) -'0'); oneChar++; iterate++;}
        if(iterate == 1){red   += 10  * (((char)*(packet.data() + oneChar)) -'0'); oneChar++; iterate++;}
        if(iterate == 2){red   +=       (((char)*(packet.data() + oneChar)) -'0'); oneChar++; iterate++;}
        if(iterate == 3){green  = 100 * (((char)*(packet.data() + oneChar)) -'0'); oneChar++; iterate++;}
        if(iterate == 4){green += 10  * (((char)*(packet.data() + oneChar)) -'0'); oneChar++; iterate++;}
        if(iterate == 5){green +=       (((char)*(packet.data() + oneChar)) -'0'); oneChar++; iterate++;}
        if(iterate == 6){blue   = 100 * (((char)*(packet.data() + oneChar)) -'0'); oneChar++; iterate++;}
        if(iterate == 7){blue  += 10  * (((char)*(packet.data() + oneChar)) -'0'); oneChar++; iterate++;}
        if(iterate == 8){blue  +=       (((char)*(packet.data() + oneChar)) -'0'); oneChar++; iterate++;}
        testOn(position, red-100, green-100,blue-100);
        //Serial.print("position: "); Serial.println(position);
        //Serial.print("oneChar: "); Serial.println(oneChar);
        //Serial.print("iterate: "); Serial.println(iterate);
        //Serial.print("red: "); Serial.println(red-100);
        //Serial.print("green: "); Serial.println(green-100);
        //Serial.print("blue: "); Serial.println(blue-100);  
        position++;
        if(position >= NUMPIXELS){position = 0;}    
      }            
    columns++;
    if(columns == rows){pixels.show(); packet.flush(); columns = 0;}
    
  });
  }
}

void loop(){}
