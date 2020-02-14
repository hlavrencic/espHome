#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>

#include "IR.h"

//#include "avdweb_VirtualDelay.h"
#include "Songs.h"

const char* host = "esp32";
const char* ssid = "HUAWEI-165B";
const char* password = "marcopolo12";

WebServer server(80);

const int BUZZER_PIN = 16;
const int RECV_PIN = 15;

// Melody (liberated from the toneMelody Arduino example sketch by Tom Igoe).
int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };

const int NOTE_B0 = 31;
const int NOTE_CS1 = 35;
const int NOTE_C1  = 33;
const int NOTE_D1  = 37;
const int NOTE_DS1 = 39;
const int NOTE_E1  = 41;
const int NOTE_F1  = 44;
const int NOTE_FS1 = 46;
const int NOTE_G1  = 49;
const int NOTE_GS1 = 52;
const int NOTE_A1  = 55;
const int NOTE_AS1 = 58;
const int NOTE_B1  = 62;
const int NOTE_C2  = 65;
const int NOTE_CS2 = 69;
const int NOTE_D2  = 73;
const int NOTE_DS2 = 78;
const int NOTE_E2  = 82;
const int NOTE_F2  = 87;
const int NOTE_FS2 = 93;
const int NOTE_G2  = 98;
const int NOTE_GS2 = 104;
const int NOTE_A2  = 110;
const int NOTE_AS2 = 117;
const int NOTE_B2  = 123;
const int NOTE_C3  = 131;
const int NOTE_CS3 = 139;
const int NOTE_D3  = 147;
const int NOTE_DS3 = 156;
const int NOTE_E3  = 165;
const int NOTE_F3  = 175;
const int NOTE_FS3 = 185;
const int NOTE_G3  = 196;
const int NOTE_GS3 = 208;
const int NOTE_A3  = 220;
const int NOTE_AS3 = 233;
const int NOTE_B3  = 247;
const int NOTE_C4  = 262;
const int NOTE_CS4 = 277;
const int NOTE_D4  = 294;
const int NOTE_DS4 = 311;
const int NOTE_E4  = 330;
const int NOTE_F4  = 349;
const int NOTE_FS4 = 370;
const int NOTE_G4  = 392;
const int NOTE_GS4 = 415;
const int NOTE_A4  = 440;
const int NOTE_AS4 = 466;
const int NOTE_B4  = 494;
const int NOTE_C5  = 523;
const int NOTE_CS5 = 554;
const int NOTE_D5  = 587;
const int NOTE_DS5 = 622;
const int NOTE_E5  = 659;
const int NOTE_F5  = 698;
const int NOTE_FS5 = 740;
const int NOTE_G5  = 784;
const int NOTE_GS5 = 831;
const int NOTE_A5  = 880;
const int NOTE_AS5 = 932;
const int NOTE_B5  = 988;
const int NOTE_C6  = 1047;
const int NOTE_CS6 = 1109;
const int NOTE_D6  = 1175;
const int NOTE_DS6 = 1245;
const int NOTE_E6  = 1319;
const int NOTE_F6  = 1397;
const int NOTE_FS6 = 1480;
const int NOTE_G6  = 1568;
const int NOTE_GS6 = 1661;
const int NOTE_A6  = 1760;
const int NOTE_AS6 = 1865;
const int NOTE_B6  = 1976;
const int NOTE_C7  = 2093;
const int NOTE_CS7 = 2217;
const int NOTE_D7  = 2349;
const int NOTE_DS7 = 2489;
const int NOTE_E7  = 2637;
const int NOTE_F7  = 2794;
const int NOTE_FS7 = 2960;
const int NOTE_G7  = 3136;
const int NOTE_GS7 = 3322;
const int NOTE_A7  = 3520;
const int NOTE_AS7 = 3729;
const int NOTE_B7  = 3951;
const int NOTE_C8  = 4186;
const int NOTE_CS8 = 4435;
const int NOTE_D8  = 4699;
const int NOTE_DS8 = 4978;
 
#define melodyPin 3
//Mario main theme melody
int melodyMario[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempoMario[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};


IR ir(RECV_PIN);  // do not change the objectname, it must be "ir"
Songs songs(BUZZER_PIN);

/*
 * Login page
 */

const char* loginIndex = 
 "<form name='loginForm'>"
    "<table width='20%' bgcolor='A09F9F' align='center'>"
        "<tr>"
            "<td colspan=2>"
                "<center><font size=4><b>ESP32 Login Page</b></font></center>"
                "<br>"
            "</td>"
            "<br>"
            "<br>"
        "</tr>"
        "<td>Username:</td>"
        "<td><input type='text' size=25 name='userid'><br></td>"
        "</tr>"
        "<br>"
        "<br>"
        "<tr>"
            "<td>Password:</td>"
            "<td><input type='Password' size=25 name='pwd'><br></td>"
            "<br>"
            "<br>"
        "</tr>"
        "<tr>"
            "<td><input type='submit' onclick='check(this.form)' value='Login'></td>"
        "</tr>"
    "</table>"
"</form>"
"<script>"
    "function check(form)"
    "{"
    "if(form.userid.value=='admin' && form.pwd.value=='admin')"
    "{"
    "window.open('/serverIndex')"
    "}"
    "else"
    "{"
    " alert('Error Password or Username')/*displays error message*/"
    "}"
    "}"
"</script>";
 
/*
 * Server Index Page
 */
 
const char* serverIndex = 
"<h1>UPLOADER</h1>"
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
   "<input type='file' name='update'>"
        "<input type='submit' value='Update'>"
    "</form>"
 "<div id='prg'>progress: 0%</div>"
 "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')" 
 "},"
 "error: function (a, b, c) {"
 "}"
 "});"
 "});"
 "</script>";

void pageSetup(){
// Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");


  auto intentos = 3;

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED && intentos > 0) {
    delay(500);
    Serial.print(".");
    intentos--;
  }

  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("mDNS responder started");
  /*return index page which is stored in serverIndex */
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });
  server.on("/version", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/json", "{ version: '0.0.0.1' }");
  });  
  server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    songs.Tone();
    auto upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      songs.StartSong(melody, noteDurations, 8);
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
  server.begin();
  
}

void setup(void) {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  
  digitalWrite(LED_BUILTIN, HIGH);
  
  pageSetup();

  ir.begin();  // Init InfraredDecoder
  
  digitalWrite(LED_BUILTIN, LOW);
}

int button0;

void loop(void) {
  
  songs.Tone(); 
  ir.loop(); 
  
  
  if(button0 && !digitalRead(0)){
    songs.StartSong(melodyMario, tempoMario, 78);
  }
  button0 = digitalRead(0);

  server.handleClient();
}

//--------------------------------------------------------------
//   events called from IR Library
//--------------------------------------------------------------
void ir_res(uint32_t res){
  Serial.print("ir_res: ");
  Serial.println(res);

  if(res == 0x20DF22DD){
    songs.StartSong(melody, noteDurations, 8);
  }
}

void ir_number(const char* num){
    Serial.print("ir_number: ");
    Serial.println(num);
}

void ir_key(const char* key){
    Serial.print("ir_key: ");
    Serial.println(key);
}