#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FS.h>
#include <SoftwareSerial.h>

/* States */
#define     WAIT_NEW_UPADTE   0
#define     NEW_UPDATE_DWN    1
#define     RQST_NEW_UPDATE   2
#define     SEND_HEADER       0x50
#define     SEND_CODE        0x74

#define UDS_CONTROL_SEESION                         0X10
#define UDS_PROGRAM_CONTROL_SESSION                 0x03
#define UDS_GWY_PROVIDE_HEADER                      0x34
#define UDS_GWY_REQUEST_SENDING_LINE_OF_CODE        0x36
#define UDS_GWY_ACKNOWLEDGE_FINISHING               0x4
#define UDS_MCU_ACKNOWLEDGE_FINISHING               0x77

/* Server data */
#define FIREBASE_HOST "ota-test1.firebaseio.com"             // the project name address from firebase id
#define FIREBASE_AUTH "Uqw7UoTw9v1ZZUPr16vAdTKdy6MCwVehXKiHIsor"       // the secret key generated from firebase



SoftwareSerial S( 14 , 12);  // rx- tx

const char* ssid = "tedata";
const char* password = "blank5019";
const char* filename = "/samplefile.hex";
char new_flag ;
int state  = WAIT_NEW_UPADTE ; 
unsigned int app_crc , app_size ;
unsigned char header[8] ;
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
    
      new_flag = Firebase.getInt("NewUpdate");
      if (new_flag == 1){
        Serial.println (new_flag);
        state = NEW_UPDATE_DWN ;
        }  
      break ;


    /************* Send the update request ***************/
    case RQST_NEW_UPDATE : 
      Serial.println(" Send requast ");
      /* open update session */
      S.write(UDS_CONTROL_SEESION);
      delay(50);
      S.write(UDS_PROGRAM_CONTROL_SESSION);

      while ( S.available() == 0);
      state = S.read();
      if (state == 0x79){
        while ( S.available() == 0);
        state = S.read();
        }
      Serial.println(state);
      break ;
      
      
    /************* Download the new update ***************/
    case NEW_UPDATE_DWN : 
    {
      /* Get the header */
      app_crc  = Firebase.getInt("App_crc");
      app_size = Firebase.getInt("App_size");
      Serial.println(app_crc);
      Serial.println(app_size);

      /* Get the code  */
      FIRMWARE_URL=Firebase.getString("url");
      Serial.println(FIRMWARE_URL);
      Fingerprint=Firebase.getString("Fingerprint");
      Serial.println(Fingerprint);
      int download_check = 1 ;
      while (download_check){
        download_check = Download_Firmware();
        }
      state = RQST_NEW_UPDATE ;
    }
      break ;


        /************* Send Header ***************/
       case SEND_HEADER : 
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

        /* Send ACK at first */
        S.write(UDS_GWY_PROVIDE_HEADER);

        /* Send header */
        for (int i = 0 ; i < 8 ; i++){
          S.write(header[i]);
        }

        /* wait for ACK*/
        while ( S.available() == 0);
        state = S.read();
        Serial.println(state);
        
       }
        break ;
       

        /************* Send code ***************/
        case SEND_CODE : 
        {
          S.write(UDS_GWY_REQUEST_SENDING_LINE_OF_CODE);
          /* Send new file and clear flag */    
          send_file();
          
          /* Send AKC finsishing */
          S.write(UDS_GWY_ACKNOWLEDGE_FINISHING);

          /* Recieve ack */
          while ( S.available() == 0);
          unsigned char m = S.read();
          Serial.println(m);
          state = WAIT_NEW_UPADTE ;
          Firebase.setInt("NewUpdate" , 0);
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
    Serial.printf("file-size: %d\n", (f.size()));
    f.close();
    http.end();
   }
   return error_code ;
}

void send_file(void){
   char x = 0 ;
   char y = 0 ;
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
       //Data from file
       for(int i=0;i<f.size();i++) //Read upto complete file size
       {
         x = f.read();
         if (x == '\r')
         {
          x = f.read();
          S.write(x);
          Serial.println ("f");
          while ( S.available() == 0);
          y = S.read();
          Serial.println (y);
         }
         else {
        S.write(x);
          }
       }
       f.close();  //Close file
       Serial.println("File Closed");
   }
  }


  
