#include <ESP8266WiFi.h>

//const char* ssid     = "StivenMolina";      // SSID
//const char* password = "12345678";      // Password
const char* ssid     = "PISO-1";      // SSID
const char* password = "torreal000";      // Password
const char* host = "192.168.1.108";  // Dirección IP local o remota, del Servidor Web
const int   port = 80;            // Puerto, HTTP es 80 por defecto, cambiar si es necesario.
const int   watchdog = 2000;        // Frecuencia del Watchdog
unsigned long previousMillis = millis();

#define BUTTON 12 //D6
#define BUTTON2 14 //D5

String ruta[1000];
String line;
String ADELANTE="ADELANTE";
int consul;
int auxruta=0;
int secuencias=0;

char dato;
volatile int  DER=0;
volatile int  IZQ=0;

//MOTOR DERECHA
int OUTPUT4= 0; //D1
int OUTPUT3= 2; //D2
//MOTOR IZQUIERDA
int OUTPUT2= 5;
int OUTPUT1= 4;


//funciones de la interrupcion
void IRAM_ATTR RUEDADER(){
  DER++; //INCREMENTAR +1
  }

 void IRAM_ATTR RUEDAIZQ(){
  IZQ++; //INCREMENTAR +1
  }

void setup() {
  Serial.begin(9600);
  
  pinMode (OUTPUT1, OUTPUT);
  pinMode (OUTPUT2, OUTPUT);
  pinMode (OUTPUT3, OUTPUT);
  pinMode (OUTPUT4, OUTPUT);
  pinMode(BUTTON,INPUT);
  pinMode(BUTTON2,INPUT);

  digitalWrite (BUTTON, LOW);
  digitalWrite (BUTTON2, HIGH);

  Serial.println();
  Serial.print("CONECTANDO WIFI: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");  
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());

  //pinMode(BUTTON, INPUT);
  attachInterrupt(BUTTON, RUEDADER,CHANGE); //INT0 EN PIN12 
  //pinMode(BUTTON2, INPUT);
  attachInterrupt(BUTTON2,RUEDAIZQ,CHANGE); //INT0 EN PIN13

  consul=0;
  espera(5); //espera 5 segundos
}

void loop() {

     if(consul==0){
      consulta();
      Serial.print(line);
      if (line.toInt()==1){
        consul=1;
        secuencias=auxruta;
        auxruta=0;
        Serial.print("Consulta terminada");
        IZQ=0;
        DER=0;
      }else{
        ruta[auxruta]=line;
        auxruta++;
      }
     }
    if (consul==1){
    
        if(secuencias>auxruta){
                if (ruta[auxruta].indexOf("ADELANTE")>0){
                    if(IZQ>=72 && DER>=72){
                      parar();
                      auxruta++;
                      delay(200);
                      IZQ=0;
                      DER=0;
                    }else{
                        if(IZQ > DER || IZQ>=72){
                          adelanteruedaderecha();
                        }else if(IZQ < DER || DER>=72){
                          adelanteruedaizquierda();
                        }else if(IZQ == DER){
                          adelante();
                          Serial.print("Pulsos en rueda derecha=");
                          Serial.println(DER);
                          Serial.print("Pulsos en rueda izquierda=");
                          Serial.println(IZQ);
                          Serial.println("+++++++++++++++");
                        }
                    }  
              }else if (ruta[auxruta].indexOf("ADELANTEH")>0){
                        
                          if(IZQ>=57 && DER>=57){
                            parar();
                            auxruta++;
                            delay(500);
                            IZQ=0;
                            DER=0;
                          }else{
                              if(IZQ < DER || DER>=57){
                                adelanteruedaizquierda();
                              }else if (IZQ > DER || IZQ>=57){
                                adelanteruedaderecha();
                              }else{
                                
                                Serial.print("Pulsos en rueda derecha=");
                                Serial.println(DER);
                                Serial.print("Pulsos en rueda izquierda=");
                                Serial.println(IZQ);
                                Serial.println("+++++++++++++++");
                                adelante();
                              }
                          }
              }else if (ruta[auxruta].indexOf("DERECHA45")>0){
                   
                     if(IZQ>=4 && DER>=4){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=4){
                                adelanteruedaizquierda();
                              }else if (IZQ > DER || IZQ>=4){
                                atrasruedaderecha();
                              }else{
                                
                                Serial.print("Pulsos en rueda derecha=");
                                Serial.println(DER);
                                Serial.print("Pulsos en rueda izquierda=");
                                Serial.println(IZQ);
                                Serial.println("+++++++++++++++");
                                derecha();
                              }
                     }
              }else if (ruta[auxruta].indexOf("DERECHA90")>0){
                
                     if(IZQ>=8 && DER>=8){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=8){
                                adelanteruedaizquierda();
                              }else if (IZQ > DER || IZQ>=8){
                                atrasruedaderecha();
                              }else{
                                
                                Serial.print("Pulsos en rueda derecha=");
                                Serial.println(DER);
                                Serial.print("Pulsos en rueda izquierda=");
                                Serial.println(IZQ);
                                Serial.println("+++++++++++++++");
                                derecha();
                              }
                     }
                
              }else if (ruta[auxruta].indexOf("DERECHA135")>0){
                
                     if(IZQ>=12 && DER>=12){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=12){
                                adelanteruedaizquierda();
                              }else if (IZQ > DER || IZQ>=12){
                                atrasruedaderecha();
                              }else{
                                
                                Serial.print("Pulsos en rueda derecha=");
                                Serial.println(DER);
                                Serial.print("Pulsos en rueda izquierda=");
                                Serial.println(IZQ);
                                Serial.println("+++++++++++++++");
                                derecha();
                              }
                     }
                
              }else if (ruta[auxruta].indexOf("IZQUIERDA45")>0){
                
                     if(IZQ>=4 && DER>=4){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=4){
                                atrasruedaizquierda();
                              }else if (IZQ > DER || IZQ>=4){
                                adelanteruedaderecha();
                              }else{
                                
                                Serial.print("Pulsos en rueda derecha=");
                                Serial.println(DER);
                                Serial.print("Pulsos en rueda izquierda=");
                                Serial.println(IZQ);
                                Serial.println("+++++++++++++++");
                                izquierda();
                              }
                     }
                     
              }else if (ruta[auxruta].indexOf("IZQUIERDA90")>0){
                
                     if(IZQ>=8 && DER>=8){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=8){
                                atrasruedaizquierda();
                              }else if (IZQ > DER || IZQ>=8){
                                adelanteruedaderecha();
                              }else{
                                
                                Serial.print("Pulsos en rueda derecha=");
                                Serial.println(DER);
                                Serial.print("Pulsos en rueda izquierda=");
                                Serial.println(IZQ);
                                Serial.println("+++++++++++++++");
                                izquierda();
                             }
                     }
                
              }else if (ruta[auxruta].indexOf("IZQUIERDA135")>0){
               
                     if(IZQ>=12 && DER>=12){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=12){
                                atrasruedaizquierda();
                              }else if (IZQ > DER || IZQ>=12){
                                adelanteruedaderecha();
                              }else{
                                
                                Serial.print("Pulsos en rueda derecha=");
                                Serial.println(DER);
                                Serial.print("Pulsos en rueda izquierda=");
                                Serial.println(IZQ);
                                Serial.println("+++++++++++++++");
                                izquierda();
                              }
                     }
                
              }else if (ruta[auxruta].indexOf("180")>0){
         
                     if(IZQ>=16 && DER>=16){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=18){
                                atrasruedaizquierda();
                              }else if (IZQ > DER || IZQ>=18){
                                adelanteruedaderecha();
                              }else{
                                
                                Serial.print("Pulsos en rueda derecha=");
                                Serial.println(DER);
                                Serial.print("Pulsos en rueda izquierda=");
                                Serial.println(IZQ);
                                Serial.println("+++++++++++++++");
                                izquierda();
                              }
                       }
              }
          
        }else{
              secuencias=0;
              auxruta=0;
              consul=0;
              //modifica();
        }
      
    }
    
    
}



void modifica(){
  unsigned long currentMillis = millis();

  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;
  
    if (!client.connect(host, port)) {
      Serial.println("Conexión falló...");
      return;
    }

    String url = "/programas_phpLab2/proceso_eventos/ModificaEnable.php?enable=";
    url += 1;

    // Envío de la solicitud al Servidor
    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Superado tiempo de espera!");
        client.stop();
        return;
      }
    }
    // Lee respuesta del servidor
    while(client.available()){
      line = client.readStringUntil('\r');
      Serial.print(line);
    }

    Serial.print("Dato ENVIADO");
 }
}

void consulta(){
   unsigned long currentMillis = millis();

 if ( currentMillis - previousMillis > watchdog ){
    previousMillis = currentMillis;
    WiFiClient client;
  
    if (!client.connect(host, port)) {
      Serial.println("Conexión falló...");
      return;
    }

     String url = "/programas_phpLab2/proceso_eventos/ConsultarRuta.php?posicionRuta=";
    url += auxruta;

    // Envío de la solicitud al Servidor
    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Superado tiempo de espera!");
        client.stop();
        return;
      }
    }
    // Lee respuesta del servidor
    while(client.available()){
      line = client.readStringUntil('\r');
    }
 }
}

void espera(float seg){
  delay(seg*1000);
}

void adelante(){
      digitalWrite(OUTPUT1, 0);
      digitalWrite(OUTPUT2, 1);
      digitalWrite(OUTPUT3, 1);
      digitalWrite(OUTPUT4, 0);
}

void derecha(){
      digitalWrite(OUTPUT1, 0);
      digitalWrite(OUTPUT2, 1);
      digitalWrite(OUTPUT3, 0);
      digitalWrite(OUTPUT4, 1);
}

void izquierda(){
      digitalWrite(OUTPUT1, 1);
      digitalWrite(OUTPUT2, 0);
      digitalWrite(OUTPUT3, 1);
      digitalWrite(OUTPUT4, 0);
}

void parar(){
      digitalWrite(OUTPUT1, 0);
      digitalWrite(OUTPUT2, 0);
      digitalWrite(OUTPUT3, 0);
      digitalWrite(OUTPUT4, 0);
}

void adelanteruedaizquierda(){
      digitalWrite(OUTPUT1, 0);
      digitalWrite(OUTPUT2, 1);
      digitalWrite(OUTPUT3, 0);
      digitalWrite(OUTPUT4, 0);
}

void adelanteruedaderecha(){
      digitalWrite(OUTPUT1, 0);
      digitalWrite(OUTPUT2, 0);
      digitalWrite(OUTPUT3, 1);
      digitalWrite(OUTPUT4, 0);
}

void atrasruedaderecha(){
      digitalWrite(OUTPUT1, 0);
      digitalWrite(OUTPUT2, 0);
      digitalWrite(OUTPUT3, 0);
      digitalWrite(OUTPUT4, 1);
}

void atrasruedaizquierda(){
      digitalWrite(OUTPUT1, 1);
      digitalWrite(OUTPUT2, 0);
      digitalWrite(OUTPUT3, 0);
      digitalWrite(OUTPUT4, 0);
}
