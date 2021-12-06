//Bibliotheken für die Kommunikation mit WiFi Geräten
#include "vhdplus_remote.h"

const char* ssid = "SSID"; //SSID aus dem Router
const char* password = "Passwort"; //Passwort für den Zugang zum WLAN

VHDPlusRemote remote;

void setup() {
  Serial.begin(115200);
  delay(10);
 
  Serial.print("\nConnect to ");
  Serial.println(ssid);

  remote.begin(ssid, password);

  remote.onButtonHandler(&onButton);
  remote.onSwitchHandler(&onSwitch);
  remote.onSliderHandler(&onSlider);
  remote.onConsoleHandler(&onConsole);

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

bool led = false;
long l = 0;

void loop(){
  remote.run();

  long t = millis();
  if (t-l > 1000){
    l = t;
    led = !led;
    remote.setLED("l1", led);
    if(led){
      remote.setRGBLED("r1", "FF0000");
      remote.setRGBLED("r2", "00FF00");
      remote.setConsole("1", "Hi");
    }
    else{
      remote.setRGBLED("r1", "FF00FF");
      remote.setRGBLED("r2", "FFFF00");
      remote.setConsole("1", "Was geht");
    }
  }
}

void onButton(String hook){
  Serial.println("Button " + hook);
}

void onSwitch(String hook, bool value){
  Serial.println("Switch " + hook + " " + value);
}

void onSlider(String hook, int value){
  Serial.println("Slider " + hook + " " + value);
}

String onConsole(String hook, String value){
  Serial.println("Console " + hook + " " + value);
  return value;
}

