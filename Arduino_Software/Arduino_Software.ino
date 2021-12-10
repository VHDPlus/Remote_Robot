//Bibliotheken für die Kommunikation mit WiFi Geräten
#include "vhdplus_remote.h"

const char* ssid = "FRITZ!Box 7490"; //SSID aus dem Router
const char* password = "03643066197615603960"; //Passwort für den Zugang zum WLAN

VHDPlusRemote remote;

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(1);
    delay(10);
    
    Serial.print("\nConnect to ");
    Serial.println(ssid);

    remote.begin(ssid, password);

    remote.onButtonHandler(&onButton);
    remote.onSliderHandler(&onSlider);

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

bool led = false;
long l = 0;

int state = 0;
int speed = 0;
int lastState = -1;
int lastSpeed = -1;

void loop(){
    remote.run();

    if (Serial.available() > 0){
        String message = Serial.readString();
        if (message.length() > 0){
            String data = message.substring(1);
            if (data.length() > 0){
                int d = data.toInt();
                if (message.charAt(0) == 'u') state = d;
                else if (message.charAt(0) == 's') speed = d;
            }
        }
    }
    
    long t = millis();  //Update every 500ms
    if (t-l > 500){
        l = t;
        
        if (state != lastState){
            if (state == 0)      remote.setDisplay("1", "Waiting");
            else if (state == 1) remote.setDisplay("1", "Running");
            else                 remote.setDisplay("1", "Error");
        }
        
        if (speed != lastSpeed){
            remote.setDisplay("2", String(speed));
        }
        
        lastState = state;
        lastSpeed = speed;
    }
}

void onButton(String hook){
    Serial.print(hook);
}

void onSlider(String hook, int value){
    if (hook == "s") value = value*255/100;
    Serial.print(hook+value);
}

