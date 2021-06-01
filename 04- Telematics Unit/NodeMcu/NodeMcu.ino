#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FS.h>
#include <SoftwareSerial.h>

/* States */
#define     WAIT_NEW_UPADTE     0
#define     NEW_UPDATE_DWN      1
#define     RQST_NEW_UPDATE     2
#define     SEND_HEADER         0x50
#define     SEND_CODE           0x74
#define     NEW_UPDATE_DENIED   0x06


/* NodeMcu To Gateway messages */
#define   NEW_UPDATE_REQUEST     0x01u

/* Gateway To NodeMCU errors */
#define   SYSTEM_STATE_UNDIFINED     0x02u
#define   GATEWAY_BUSY               0x03u
#define   INVALID_REQUEST            0X04u
#define   REQUEST_ACCPETED           0x05u
#define   REQUEST_REFUSED            0x06u
#define   ESP_SEND_HEADER            0x07u
#define   HEADR_RECEIVED             0x08u
#define   HEADR_ERROR                0x09u
#define   PACKET_RECEIVED            0x0Au
#define   LAST_PACKET_RECEIVED       0x0Bu
#define   SEND_NEXT_PACKET           0x0Cu
#define   ESP_DOWNLOAD_DONE          0x0Du

/* Server data */
#define FIREBASE_HOST "ota-test1.firebaseio.com"             // the project name address from firebase id
#define FIREBASE_AUTH "Uqw7UoTw9v1ZZUPr16vAdTKdy6MCwVehXKiHIsor"       // the secret key generated from firebase



SoftwareSerial S( 14 , 12);  // rx- tx

const char* ssid = "tedata";
const char* password = "mosad5019";
const char* filename = "/samplefile.hex";
char new_flag ;
int state  = WAIT_NEW_UPADTE ; 
unsigned int app_crc , app_size ;
unsigned char app_nodeId ;
unsigned char header[9] ;
File f ;

String FIRMWARE_URL = "" ;
String Fingerprint = "" ;

void setup()
{
  /* Intitialize Serial Communication */
  Serial.begin(9600);
  S.begin(9600);     
  SPIFFS.begin();
  
  /* Connect to Wifi */
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  /* Connect to Firebase */
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH) ;
  delay(500);
}

void loop() { 
  switch (state){
    /************* Check for new Update ***************/
    case WAIT_NEW_UPADTE :
    {
      new_flag = Firebase.getInt("NewUpdate");
      if (new_flag == 1){
        Serial.println (new_flag);
        state = RQST_NEW_UPDATE ;
        } 
    } 
      break ;
      
    /************* Send the update request ***************/
    case RQST_NEW_UPDATE : 
    {
      Serial.println(" Send requast ");
      /* open update session */
      S.write(NEW_UPDATE_REQUEST);
      delay(50);
      while ( S.available() == 0);
      unsigned char response = S.read();
      Serial.println(response);
      if (response == SYSTEM_STATE_UNDIFINED){
        delay(100);
       }
       else if (response == GATEWAY_BUSY)
       {
       delay(10000) ;
       }
       else if (response == INVALID_REQUEST)
       {
        /* Drop request */
        state = WAIT_NEW_UPADTE ;
       }
       else if (response == REQUEST_ACCPETED)
       {
        state = NEW_UPDATE_DWN ;
       }
       else if (response == REQUEST_REFUSED)
       {
        state = NEW_UPDATE_DENIED ;
       }
       
    }
      break ;

     /*********************NEW_UPDATE_DENIED**************/
    case NEW_UPDATE_DENIED :
    {
      Firebase.setInt("NewUpdate" , 0);
      Firebase.setInt("NewUpdate" , 0);
      Firebase.setInt("NewUpdate" , 0);
      Firebase.setInt("NewUpdate" , 0);
      state = WAIT_NEW_UPADTE ;
    }
    break ; 
     /************* Download the new update ***************/
    case NEW_UPDATE_DWN : 
    {
      /* Get the header */
      app_crc  = Firebase.getInt("App_crc");
      app_nodeId = Firebase.getInt("Node_ID");
      Serial.println(app_crc);
      Serial.println(app_nodeId);

      /* Get the code  */
      FIRMWARE_URL=Firebase.getString("url");
      Serial.println(FIRMWARE_URL);
      Fingerprint=Firebase.getString("Fingerprint");
      Serial.println(Fingerprint);
      int download_check = 1 ;
      while (download_check){
        download_check = Download_Firmware();
      }
      state = SEND_HEADER ;
    }
      break ;
/***********************************************************************************************************************/
      
 /************* Send Header ***************/
    case SEND_HEADER : 
    {
        int Ack = 0 ;
        while ( S.available() == 0);
        Ack = S.read();
        if (Ack == ESP_SEND_HEADER)
        {
          Serial.println("Sending header");
          header[0] = app_size & 0xff ;
          header[1] = (app_size>>8) & 0xff ;
          header[2] = (app_size>>16) & 0xff ;
          header[3] = (app_size>>24) & 0xff ;
  
          header[4] = app_crc & 0xff ;
          header[5] = (app_crc>>8) & 0xff ;
          header[6] = (app_crc>>16) & 0xff ;
          header[7] = (app_crc>>24) & 0xff ;
  
          header[8] = app_nodeId ;
  
          /* Send header */
          for (int i = 0 ; i < 9 ; i++){
            S.write(header[i]);
          }
          
          /* wait for ACK*/
          while ( S.available() == 0);
          Ack = S.read();
          Serial.println(state);
          if (Ack == HEADR_RECEIVED) {state = SEND_CODE ;}
       }
    }
        break ;
       

        /************* Send code ***************/
        case SEND_CODE : 
        {
          /* Send new file and clear flag */    
          send_file();
          while ( S.available() == 0);
          unsigned char Ack = S.read();
          Serial.println (Ack); 
          if (Ack == ESP_DOWNLOAD_DONE )
          {
            Firebase.setInt("NewUpdate" , 0);
            Firebase.setInt("NewUpdate" , 0);
            Firebase.setInt("NewUpdate" , 0);
            Firebase.setInt("NewUpdate" , 0); 
          }
          state = WAIT_NEW_UPADTE ;
        }
        break;
        
    }
}


int Download_Firmware() {
  int error_code = 0 ;
  HTTPClient http;
  SPIFFS.format();
  f = SPIFFS.open(filename, "w");
  if(f)
  {
    http.begin(FIRMWARE_URL ,Fingerprint);
    int httpCode = http.GET();
    if (httpCode <= 0)
    {
        Serial.printf("HTTP failed, error: %s\n", 
        http.errorToString(httpCode).c_str());
        error_code = 1 ;
    return error_code ;
    }
    if (httpCode == HTTP_CODE_OK) 
    {
        Serial.println("d check");
        http.writeToStream(&f);
    }
    Serial.printf("Content-Length: %d\n", (http.getSize()));
    app_size = f.size();
    Serial.printf("file-size: %d\n", app_size);
    f.close();
    http.end();
   }
   return error_code ;
}

void send_file(void){
   unsigned char x = 0 ;
   unsigned char y = 0 ;
   Serial.print("here");
   f = SPIFFS.open(filename, "r");
   if (!f) 
   {
     Serial.println("file open failed");
      return;
   }
   else
   {
       Serial.println("Reading Data from File:");
       Serial.println(app_size);
       Serial.println((f.size()));
       int xsize = app_size ;
       int num_packets = (app_size / 1024) + 1 ;
       int Ack = 0 ;
       //Data from file
       for(int i=0;i<num_packets;i++) //Read upto complete file size
       {
        while ( S.available() == 0);
        Ack = S.read();
        Serial.println (Ack);
        if (Ack == SEND_NEXT_PACKET)  
        {
          if (xsize > 1024){
               for (int j = 0; j <1024 ; j++)
               {
                    x = f.read();
                    Serial.println (x);
                    S.write(x);
                }
                xsize -= 1024 ;
                while ( S.available() == 0);
                Ack = S.read();
                Serial.println (Ack);  
            }
            else if ((xsize < 1024) ,(xsize > 0) ) 
            {
              int remaining = app_size % 1024 ;
              for (int j = 0 ; j <remaining ; j++ )
              {
                x = f.read();
                S.write(x);
                Serial.println (x);
              }
              xsize -= remaining ;
              while ( S.available() == 0);
              Ack = S.read();
              Serial.println (Ack); 
            }
        }
       }
       f.close();  //Close file
       Serial.println("File Closed");
   }
  }


  
