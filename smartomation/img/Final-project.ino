//               Alle Libraries
#include <EEPROM.h>
#include <EEPROMRollingCodeStorage.h>
#include <SomfyRemote.h>
#include "EspMQTTClient.h"


//               Alle define's
#define EMITTER_GPIO 14
#define REMOTE1 0x5184c8
#define REMOTE2 0x25b5d5
#define REMOTE3 0xc6c78f
#define REMOTE4 0x59714b
#define DEBUG
#define ESP8266


//               Alle int's
int RS = 0; //idetificatie van de 4 remotes en de state



//               SETUP
EspMQTTClient client(
  "TMNL-AF1811",
  "ES3RBGHN8X6QMEVS",
  "192.168.1.97",  // MQTT Broker server ip
  "esp",   // Can be omitted if not needed
  "ESP-1171188",   // Can be omitted if not needed
  "TestESP",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

EEPROMRollingCodeStorage rollingCodeStorage1(0);
EEPROMRollingCodeStorage rollingCodeStorage2(2);
EEPROMRollingCodeStorage rollingCodeStorage3(4);
EEPROMRollingCodeStorage rollingCodeStorage4(6);
SomfyRemote somfyRemote1(EMITTER_GPIO, REMOTE1, &rollingCodeStorage1);
SomfyRemote somfyRemote2(EMITTER_GPIO, REMOTE2, &rollingCodeStorage2);
SomfyRemote somfyRemote3(EMITTER_GPIO, REMOTE3, &rollingCodeStorage3);
SomfyRemote somfyRemote4(EMITTER_GPIO, REMOTE4, &rollingCodeStorage4);



void setup() {
  Serial.begin(115200);
  pinMode(EMITTER_GPIO, OUTPUT);
	digitalWrite(EMITTER_GPIO, LOW);


  //somfy remote gedeelte
#if defined(ESP32)
	if (!EEPROM.begin(4)) {
		Serial.println("failed to initialise EEPROM");
	  delay(1000);
	}
  #elif defined(ESP8266)
	EEPROM.begin(4);
#endif




  //MQTT gedeelte:
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
}



// This function is called once everything is connected (Wifi and MQTT)
void onConnectionEstablished()
{
  // Subscribe to "somfy/state" and display received message to Serial
  client.subscribe("somfy/state", [](const String & payload) {
    Serial.println(payload);

    // Checkt de eerste karakter
    if (payload[0] == '1') {            // filtert signaal voor remote 1
        Serial.println("geslaagd");

        if (payload[1] == 'u'){         //bericht is up
          RS = 11;
          rolluikZending();
        }
        if (payload[1] == 'd'){        //bericht is down
          RS = 12;
          rolluikZending();
        }
        if (payload[1] == 'm'){        //bericht is my
          RS = 13;
          rolluikZending();
        }
        if (payload[1] == 'p'){        //bericht is prog
          RS = 14;
          rolluikZending();
        } 
      }
    

    if (payload[0] == '2') {            // filtert signaal voor remote 1
        Serial.println("geslaagd");

        if (payload[1] == 'u'){         //bericht is up
          RS = 21;
          rolluikZending();
        }
        if (payload[1] == 'd'){        //bericht is down
          RS = 22;
          rolluikZending();
        }
        if (payload[1] == 'm'){        //bericht is my
          RS = 23;
          rolluikZending();
        }
        if (payload[1] == 'p'){        //bericht is prog
          RS = 24;
          rolluikZending();
        } 
      }

      if (payload[0] == '3') {            // filtert signaal voor remote 3
        Serial.println("geslaagd");

        if (payload[1] == 'u'){         //bericht is up
          RS = 31;
          rolluikZending();
        }
        if (payload[1] == 'd'){        //bericht is down
          RS = 32;
          rolluikZending();
        }
        if (payload[1] == 'm'){        //bericht is my
          RS = 33;
          rolluikZending();
        }
        if (payload[1] == 'p'){        //bericht is prog
          RS = 34;
          rolluikZending();
        } 
      }

      if (payload[0] == '4') {            // filtert signaal voor remote 3
        Serial.println("geslaagd");

        if (payload[1] == 'u'){         //bericht is up
          RS = 41;
          rolluikZending();
        }
        if (payload[1] == 'd'){        //bericht is down
          RS = 42;
          rolluikZending();
        }
        if (payload[1] == 'm'){        //bericht is my
          RS = 43;
          rolluikZending();
        }
        if (payload[1] == 'p'){        //bericht is prog
          RS = 44;
          rolluikZending();
        } 
      }
  });

  client.publish("somfy/test", "This is a message"); // alleen voor testen
}



void loop() {
  client.loop();
  delay(400);
}



// hier worden de berichten voor de gevraagde actie gefilterd en verzonden
void rolluikZending(void) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  switch(RS) {
    //remote 1
    case 11:  // commmand 1
      somfyRemote1.sendCommand(Command::Up, 1);
      delay(100);
      break;

    case 12:  // commmand 2
      somfyRemote1.sendCommand(Command::Down, 1);
      delay(100);
      break;
    
    case 13:  // commmand 3
      somfyRemote1.sendCommand(Command::My, 1);
      delay(100);
      break;
    
    case 14:  // commmand 4
      somfyRemote1.sendCommand(Command::Prog, 1);
      delay(100);
      break;

    //remote 2
    case 21:
      somfyRemote2.sendCommand(Command::Up, 1);
      delay(100);
      break;

    case 22:
      somfyRemote2.sendCommand(Command::Down, 1);
      delay(100);
      break;
    
    case 23:
      somfyRemote2.sendCommand(Command::My, 1);
      delay(100);
      break;
    
    case 24:
      somfyRemote2.sendCommand(Command::Prog, 1);
      delay(100);
      break;
    
    //remote 3
    case 31:
      somfyRemote3.sendCommand(Command::Up, 1);
      display.display();
      delay(100);
      break;

    case 32:
      somfyRemote3.sendCommand(Command::Down, 1);
      delay(100);
      break;
    
    case 33:
      somfyRemote3.sendCommand(Command::My, 1);
      display.display();
      delay(100);
      break;
    
    case 34:
      somfyRemote3.sendCommand(Command::Prog, 1);
      display.display();
      delay(100);
      break;
    
    //remote 4
    case 41:
      somfyRemote4.sendCommand(Command::Up, 1);
      display.display();
      delay(100);
      break;

    case 42:
      somfyRemote4.sendCommand(Command::Down, 1);
      delay(100);
      break;
    
    case 43:
      somfyRemote4.sendCommand(Command::My, 1);
      delay(100);
      break;
    
    case 44:
      somfyRemote4.sendCommand(Command::Prog, 1);
      delay(100);
      break;
  }
}



