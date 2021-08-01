#include <Arduino.h>
#include <WiFiManager.h>


/*
   @brief Web de configuración para conectar un ESP32 a una wifi existente

   Por defecto, se levanta un portal cautivo con SSID "ESP32" y pass "12345678"
   Una vez conectados al ESP, podremos configurar la wifi y desaparecerá el portal

   Para borrar la Wifi configurada se puede hacer un puente entre el pin establecido en 
   PIN_RESET_BUTTON y 3.3V
   
*/

#define DEFAULTSSID "ESP32"
#define DEFAULTPASSW "12345678"
#define PIN_RESET_BUTTON 4        




void InitWifi(WiFiManager *wm)
{

  //Try to connect WiFi, then create AP
  wm->autoConnect(DEFAULTSSID, DEFAULTPASSW);

  //the library is blocking. Once connected, the program continues
  Serial.println("ESP32 is connected to Wi-Fi network");

}

int main()
{
  int reset = 0; 
  pinMode(PIN_RESET_BUTTON, INPUT);
  
  WiFiManager wm;

  Serial.begin(115200);
  InitWifi(&wm);

  while (1) {
    //reset WiFi Settings from PIN_RESET_BUTTONin to 3.3V 
    reset = digitalRead(PIN_RESET_BUTTON);
    if ( reset == HIGH) {
      Serial.println("Erase settings and restart ...");
      wm.resetSettings();
      ESP.restart();
    }
  }
}



//Infinite hate to void setup and void loop functions!!
void setup() {} void loop() {}
