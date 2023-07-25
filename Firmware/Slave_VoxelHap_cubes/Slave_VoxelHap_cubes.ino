#include <Wire.h>
#include "Adafruit_MPR121.h"
#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif


#include "namedMesh.h"
#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
#include <ArduinoJson.h>



#include <FastLED.h>

#define NUM_LEDS        6
#define LED_TYPE      NEOPIXEL
#define COLOR_ORDER     GRB
#define DATA_PIN        13
#define BRIGHTNESS      255

CRGB leds[NUM_LEDS];
// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;


Scheduler     userScheduler; // to control your personal task
namedMesh  mesh;
String msg =  String("hi");
String to = "Master";




// Each cube has a unique node name and doc["13"] key value.
// For example Cube1, doc["13"]=0; Cube2 , doc["13"] = 1;
// This code is for the Cube9, which will check for connection between cube8 and Cube9.



String nodeName = "Cube9"; // Name needs to be unique//  also change the key,  value of variable doc[13].
void sendMessage() ;
Task taskSendMessage( TASK_SECOND * 0.3 , TASK_FOREVER, &sendMessage );
int connection_flag=0;
bool a[12];
int t_flag=0;
const size_t CAPACITY = JSON_ARRAY_SIZE(3);

// allocate the memory for the document
StaticJsonDocument<CAPACITY> doc;

// create an empty array
JsonArray array = doc.to<JsonArray>();

int Touch_status[12]= {0,0,0,0,0,0,0,0,0,0,0,0};


void sendMessage() 
{   
  //Serial.println("test?");
  
  if(connection_flag==1)
    {
      //connection_flag=0;
      //String msg =  String("hi");
      //String to = "Master";
      //mesh.sendSingle(to, msg);
      DynamicJsonDocument doc(1024) ;
      currtouched = cap.touched();
      for (uint8_t i=0; i<12; i++) 
      {
        msg="";
        t_flag=0;
        // it if *is* touched and *wasnt* touched before, alert!
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) 
        {
            Touch_status[i]=1;
            a[i]= true;//doc[String(i)]=1;
            t_flag=1;
          // Serial.println(" touched");
        }
        // if it *was* touched and now *isnt*, alert!
        if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) 
        {
            Touch_status[i]=0;
            a[i]=false;
            t_flag=1;
            //serializeJson(doc,msg);
            //mesh.sendSingle(to,msg);
            //Serial.print(i); Serial.println(" released");
       
        }
        
        if(t_flag==1)
        {  
            for (uint8_t i=0; i<12; i++)
            doc[String(i)]=Touch_status[i];
            doc["13"]= 10;
            serializeJson(doc,msg);
            mesh.sendSingle(to,msg);
            //Serial.print(Touch_status[i]);
            Serial.println(msg);
        }
    
      }
  
      lasttouched = currtouched;
      //Serial.println(msg); 
    } 
  };

void setup() {
  
      Serial.begin(115200);
      if (!cap.begin(0x5A)) 
      {
        Serial.println("MPR121 not found, check wiring?");
        while (1);
      }
      FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      FastLED.setBrightness(BRIGHTNESS);
       //pinMode(LED_BUILTIN, OUTPUT);
       //digitalWrite(LED_BUILTIN, HIGH); 
       //mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);  // set before init() so that you can see startup messages
      mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);
      mesh.setName(nodeName); // This needs to be an unique name! 
      mesh.onReceive([](uint32_t from, String &msg) {
      // Serial.printf("Received message by id from: %u, %s\n", from, msg.c_str());
       });


        // For Cube1,  on side 4, connect Cube2 and on side 6 connect Cube3
        /*  mesh.onReceive([](String &from, String &msg) {
                Serial.printf("Received message by name from: %s, %s\n", from.c_str(), msg.c_str());
                if(String(msg.c_str())=="Connected")
                {
                //digitalWrite(LED_BUILTIN, LOW);
                leds[4] = (CRGB::Cyan);
                FastLED.show(); 
                Serial.printf("Received message by name from: %s, %s\n", from.c_str(), msg.c_str());
                connection_flag=1;
                }
                // Connection between Cube 1 and Cube2
                if(String(msg.c_str())=="1")
                {
                leds[4] = (CRGB::Black);
                leds[6] = (CRGB::Cyan);
                FastLED.show();
                }
                if(String(msg.c_str())=="2")
                {
                leds[6] = (CRGB::Black);
                FastLED.show();
                }
                
          });*/
        
        //For Cube 2, on side 4 connect Cube1
          /*  mesh.onReceive([](String &from, String &msg) {
                Serial.printf("Received message by name from: %s, %s\n", from.c_str(), msg.c_str());
                if(String(msg.c_str())=="Connected")
                {
                //digitalWrite(LED_BUILTIN, LOW);
                leds[4] = (CRGB::Cyan);
                FastLED.show(); 
                Serial.printf("Received message by name from: %s, %s\n", from.c_str(), msg.c_str());
                connection_flag=1;
                }
                if(String(msg.c_str())=="1")
                {
                leds[4] = (CRGB::Black);
                FastLED.show();
                }
                
          });*/
          
          //For Cube 3, on side 4 connect Cube1 and on side 0 connect Cube4
          /*  mesh.onReceive([](String &from, String &msg) {
                Serial.printf("Received message by name from: %s, %s\n", from.c_str(), msg.c_str());
                if(String(msg.c_str())=="Connected")
                {
                //digitalWrite(LED_BUILTIN, LOW);
                leds[4] = (CRGB::Cyan);
                FastLED.show(); 
                Serial.printf("Received message by name from: %s, %s\n", from.c_str(), msg.c_str());
                connection_flag=1;
                }
                if(String(msg.c_str())=="1")
                {
                leds[4] = (CRGB::Black);
                FastLED.show();
                }
                
          });*/
        // Similarly you have to change for every cube and upload it. 
        //This is for cube 9 , checks the connection between cube 8 and cube 9. 

        mesh.onReceive([](String &from, String &msg) 
        {
            Serial.printf("Received message by name from: %s, %s\n", from.c_str(), msg.c_str());
            if(String(msg.c_str())=="Connected")
            {
            //digitalWrite(LED_BUILTIN, LOW);
            leds[4] = (CRGB::Cyan);
            //leds[0] = CRGB::Red; 
            FastLED.show(); 
            Serial.printf("Received message by name from: %s, %s\n", from.c_str(), msg.c_str());
            connection_flag=1;
            }
            
            if(String(msg.c_str())=="8")
            {
             //digitalWrite(LED_BUILTIN, HIGH);
            leds[4] = (CRGB::Black);
            //leds[0] = (CRGB::Cyan);
            //leds[0] = CRGB::Red; 
            FastLED.show();
            }
          });
          
          //mesh.onChangedConnections([]() {
           // Serial.printf("Changed connection\n");
          //});
          userScheduler.addTask(taskSendMessage);
          taskSendMessage.enable();

          
    }

void loop() 
{
  mesh.update();
}
