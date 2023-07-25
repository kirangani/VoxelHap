//************************************************************
// This is a simple example that uses the painlessMesh library
// 
// This the master which recieves and sends information to the base cubes.
//
//************************************************************
#include "namedMesh.h"


#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

Scheduler     userScheduler; // to control your personal task
namedMesh  mesh;
SimpleList<uint32_t> nodes;
String nodeName = "Master"; // Name needs to be unique
void newConnectionCallback(uint32_t nodeId);
uint32_t flag=0;
uint32_t connecetd_flag=0;
int j=0;
String a;

/*
 * 3194200704 - 1
 * 3194190884 - 2
 * 2888137588 - 3
 * 3194169936 - 4 
 * 3194161803 - 5
 * 2887994867 - 6
 * 2468277855 - 7
 * 1614425655 - 8
 * 2888176893 - 9
 */

Task taskSendMessage( TASK_SECOND, TASK_FOREVER, []() {
           /* mesh.onNewConnection(&newConnectionCallback);*/
           // Serial.printf("--> startHere: New Connection, nodeId = %u\n", flag);
           String x = "";
           if(flag !=0)
           {
                //Serial.printf("--> startHere: New Connection, nodeId = %u\n", flag);
                if (int(flag-3194200704) ==0)
                x = "Cube1";
                if (int(flag-3194190884) ==0)
                x = "Cube2";
                if (int(flag-2888137588) ==0)
                x = "Cube3";
                if (int(flag-3194169936) ==0)
                x = "Cube4";
                if (int(flag-3194161803) ==0)
                x = "Cube5";
                if (int(flag-2887994867) ==0)
                x = "Cube6";
                if (int(flag-2468277855) ==0)
                x = "Cube7";
                if (int(flag-1614425655) ==0)
                x = "Cube8";
                if (int(flag-2888176893) ==0)
                x = "Cube9";
                Serial.println(x);
                String msg = String("Connected");
                String to = x;
                mesh.sendSingle(to, msg);
                flag= 0; 
             
              }
      
              if (connecetd_flag==1)
              {
                String msg1 = String("1");
                String to = "Cube1";
                mesh.sendSingle(to, msg1);
                String msg2 = String("1");
                to = "Cube2";
                mesh.sendSingle(to, msg2);
                connecetd_flag=0;
              }
          
              if (connecetd_flag==2)
              {
                String msg1 = String("2");
                String to = "Cube1";
                mesh.sendSingle(to, msg1);
                String msg2 = String("2");
                to = "Cube3";
                mesh.sendSingle(to, msg2);
                connecetd_flag=0;
              }
              
              if (connecetd_flag==3)
              {
                String msg1 = String("3");
                String to = "Cube3";
                mesh.sendSingle(to, msg1);
                String msg2 = String("3");
                to = "Cube4";
                mesh.sendSingle(to, msg2);
                connecetd_flag=0;
              }
              
              if (connecetd_flag==4)
              {
                String msg1 = String("4");
                String to = "Cube4";
                mesh.sendSingle(to, msg1);
                String msg2 = String("4");
                to = "Cube5";
                mesh.sendSingle(to, msg2);
                connecetd_flag=0;
              }
          
              if (connecetd_flag==5)
              {
                String msg1 = String("5");
                String to = "Cube5";
                mesh.sendSingle(to, msg1);
                String msg2 = String("5");
                to = "Cube6";
                mesh.sendSingle(to, msg2);
                connecetd_flag=0;
              }
              
               if (connecetd_flag==6)
              {
                String msg1 = String("6");
                String to = "Cube6";
                mesh.sendSingle(to, msg1);
                String msg2 = String("6");
                to = "Cube7";
                mesh.sendSingle(to, msg2);
                connecetd_flag=0;
              }
              
               if (connecetd_flag==7)
              {
                String msg1 = String("7");
                String to = "Cube7";
                mesh.sendSingle(to, msg1);
                String msg2 = String("7");
                to = "Cube8";
                mesh.sendSingle(to, msg2);
                connecetd_flag=0;
              }
              
              if (connecetd_flag==8)
              {
                String msg1 = String("8");
                String to = "Cube8";
                mesh.sendSingle(to, msg1);
                String msg2 = String("8");
                to = "Cube9";
                mesh.sendSingle(to, msg2);
                connecetd_flag=0;
              }
  }); 



void setup() 

{
  
      Serial.begin(115200);
      //pinMode(LED_BUILTIN, OUTPUT);
      //digitalWrite(LED_BUILTIN, HIGH);
      //mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);  // set before init() so that you can see startup messages
      mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);
      mesh.setName(nodeName); // This needs to be an unique name! 
  
      //mesh.onReceive([](uint32_t from, String &msg) {
      //Serial.printf("Received message by id from: %u, %s\n", from, msg.c_str());
      //});
  

      mesh.onReceive([](String &from, String &msg) 
      {
          //Serial.println(from.c_str());
          DynamicJsonDocument doc(1024) ;
          deserializeJson(doc,msg.c_str());
          for (uint8_t i=0; i<12; i++)
          {
            j = doc[String(i)];
            Serial.print(j);Serial.print(",");
          }
          j = doc[String(13)];
          Serial.print(j);
          Serial.println();
          // Serial.println(msg.c_str());
          //, msg.c_str());
      });
      
      //mesh.onNewConnection([](uint32_t nodeId) {
      //});
      mesh.onChangedConnections([]() 
      {
          nodes = mesh.getNodeList();
          SimpleList<uint32_t>::iterator node = nodes.begin();
          while (node != nodes.end()) 
          {
             //Serial.printf(" %u", *node);
             flag= *node;
             node++;
          }
          //flag=uint32_t(*node);
          //Serial.printf("Changed connection %u \n", flag);
          
       });
        
       userScheduler.addTask(taskSendMessage);
       taskSendMessage.enable();

}

void loop() 
{
  
    mesh.update();
    char aa = Serial.read();
    Serial.print(a);
    if(aa == 'y')
    { 
      connecetd_flag = 1;
      digitalWrite(LED_BUILTIN, LOW);
     }
     
     else if (aa == 'q')
     { 
      connecetd_flag = 2;
      digitalWrite(LED_BUILTIN, LOW);
     }
     
      else if(aa == 'w')
     { 
       connecetd_flag = 3;
       digitalWrite(LED_BUILTIN, LOW);
     }
     
      else if(aa == 'e')
     { 
      connecetd_flag = 4;
      digitalWrite(LED_BUILTIN, LOW);
     }
     
      else if(aa == 'r')
      { 
        connecetd_flag = 5;
        digitalWrite(LED_BUILTIN, LOW);
      }
      
      else if(aa == 's')
      {  
        connecetd_flag = 6;
         digitalWrite(LED_BUILTIN, LOW);
      }
     
      else if(aa == 't')
      { 
        connecetd_flag = 7;
        digitalWrite(LED_BUILTIN, LOW);
      }
      
      else if(aa == 'u')
      { 
        connecetd_flag = 8;
        digitalWrite(LED_BUILTIN, LOW);
      }
    
}
