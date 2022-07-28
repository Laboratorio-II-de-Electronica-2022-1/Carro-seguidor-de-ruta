#include <ESP8266WiFi.h>

//const char* ssid     = "StivenMolina";      // SSID
//const char* password = "12345678";      // Password
//const char* ssid     = "PISO-1";      // SSID
//const char* password = "torreal000";      // Password
//const char* host = "192.168.1.108";  // Dirección IP local o remota, del Servidor Web
const char* ssid     = "StivenMolina";      // SSID
const char* password = "12345678";      // Password
const char* host = "192.168.104.134";  // Dirección IP local o remota, del Servidor Web
const int   port = 80;            // Puerto, HTTP es 80 por defecto, cambiar si es necesario.
const int   watchdog = 2000;        // Frecuencia del Watchdog
unsigned long previousMillis = millis();

#define BUTTON 12 //D6
#define BUTTON2 14 //D5

String ARUTA[1000];
String line;
String ADELANTE="ADELANTE";
int consul;
int auxruta=0;
int secuencias=0;
int HacerRuta=0;
String rutaC;

char dato;
volatile int  DER=0;
volatile int  IZQ=0;

//MOTOR DERECHA
int OUTPUT4= 5; //D1
int OUTPUT3= 4; //D2
//MOTOR IZQUIERDA
int OUTPUT2= 0;
int OUTPUT1= 2;


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
        consul=1;
        auxruta=0;
        Serial.print("Consulta terminada");
        IZQ=0;
        DER=0;
        rutaC=line;
        secuencias=rutaC.length();
     }

     if(rutaC.toInt() != 1){
        if (consul==1 && HacerRuta==0){
          char ruta[rutaC.length()+1];
         rutaC.toCharArray(ruta, rutaC.length()+1); 
         delay(2000);
          
          for(int i=1;  i < (rutaC.length()-1) ; i+=2) {
    
              int a=String(ruta[i]).toInt()*10;
              int b=String(ruta[i+1]).toInt();
              int c=a+b;
              Serial.println(c);
              switch(c) {
                  case 51: 
                  case 73:
                  case 15:
                  case 37: ARUTA[HacerRuta]="ADELANTE";HacerRuta+=1;break;
                  
                  case 62:
                  case 84:
                  case 26:
                  case 48: ARUTA[HacerRuta]="AVANZANDOH";HacerRuta+=1;break;
        
                  case 52: 
                  case 74:
                  case 16:
                  case 38: ARUTA[HacerRuta]="DERECHA45";ARUTA[HacerRuta+1]="AVANZANDOH";HacerRuta+=2;break;
                  
                  case 63:
                  case 85:
                  case 27:
                  case 41: ARUTA[HacerRuta]="DERECHA45";ARUTA[HacerRuta+1]="ADELANTE";HacerRuta+=2;break;
                  
                  case 53: 
                  case 75:
                  case 17:
                  case 31: ARUTA[HacerRuta]="RIGHT90";ARUTA[HacerRuta+1]="ADELANTE";HacerRuta+=2;break;
                  
                  case 64:
                  case 86:
                  case 28:
                  case 42: ARUTA[HacerRuta]="RIGHT90";ARUTA[HacerRuta+1]="AVANZANDOH";HacerRuta+=2;break;

                  case 54:
                  case 76:
                  case 18:
                  case 32: ARUTA[HacerRuta]="CERTO135";ARUTA[HacerRuta+1]="AVANZANDOH";HacerRuta+=2;break;

                  case 65:
                  case 87:
                  case 21:
                  case 43: ARUTA[HacerRuta]="CERTO135";ARUTA[HacerRuta+1]="ADELANTE";HacerRuta+=2;break;

                  case 58:
                  case 72:
                  case 14:
                  case 36: ARUTA[HacerRuta]="IZQUIERDA45";ARUTA[HacerRuta+1]="AVANZANDOH";HacerRuta+=2;break;

                  case 61:
                  case 83:
                  case 25:
                  case 47: ARUTA[HacerRuta]="IZQUIERDA45";ARUTA[HacerRuta+1]="ADELANTE";HacerRuta+=2;break;

                  case 57: 
                  case 71:
                  case 13:
                  case 35: ARUTA[HacerRuta]="LEFT90";ARUTA[HacerRuta+1]="ADELANTE";HacerRuta+=2;break;

                  case 68:
                  case 82:
                  case 24:
                  case 46: ARUTA[HacerRuta]="LEFT90";ARUTA[HacerRuta+1]="AVANZANDOH";HacerRuta+=2;break;

                  case 56:
                  case 78:
                  case 12:
                  case 34: ARUTA[HacerRuta]="DEIXEI135";ARUTA[HacerRuta+1]="AVANZANDOH";HacerRuta+=2;break;
 
                  case 67:
                  case 81:
                  case 23:
                  case 45: ARUTA[HacerRuta]="DEIXEI135";ARUTA[HacerRuta+1]="ADELANTE";HacerRuta+=2;break;

                  case 66:
                  case 88:
                  case 22:
                  case 44: ARUTA[HacerRuta]="180";ARUTA[HacerRuta+1]="AVANZANDOH";HacerRuta+=2;break;

                  case 55:
                  case 77:
                  case 11:
                  case 33: ARUTA[HacerRuta]="180";ARUTA[HacerRuta+1]="ADELANTE";HacerRuta+=2;break;

                  
              }
           }
        }
    }

if(rutaC.toInt() != 1){
    if (consul==1){
        if(secuencias>auxruta){
                if (ARUTA[auxruta]=="ADELANTE"){
                    if(IZQ>=60 && DER>=60){
                      parar();
                      auxruta++;
                      delay(200);
                      IZQ=0;
                      DER=0;
                    }else{
                        if(IZQ < DER || DER>=60){
                          adelanteruedaizquierda();
                        
                        }else if(IZQ > DER || IZQ>=60){
                          adelanteruedaderecha();
                        }else if(IZQ == DER){
                          adelante();
                          Serial.print("Pulsos en rueda derecha=");
                          Serial.println(DER);
                          Serial.print("Pulsos en rueda izquierda=");
                          Serial.println(IZQ);
                          Serial.println("+++++++++++++++");
                        }
                    }
                }else if (ARUTA[auxruta]=="AVANZANDOH"){
                        
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
              }else if (ARUTA[auxruta]=="DERECHA45"){
                   
                     if(IZQ>=9 && DER>=9){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=9){
                                adelanteruedaizquierda();
                              }else if (IZQ > DER || IZQ>=9){
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
              }else if (ARUTA[auxruta]=="RIGHT90"){
                
                     if(IZQ>=19 && DER>=19){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=19){
                                adelanteruedaizquierda();
                              }else if (IZQ > DER || IZQ>=19){
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
                
              }else if (ARUTA[auxruta]=="CERTO135"){
                
                     if(IZQ>=27 && DER>=27){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=27){
                                adelanteruedaizquierda();
                              }else if (IZQ > DER || IZQ>=27){
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
                
              }else if (ARUTA[auxruta]=="IZQUIERDA45"){
                
                     if(IZQ>=9 && DER>=9){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=9){
                                atrasruedaizquierda();
                              }else if (IZQ > DER || IZQ>=9){
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
                     
              }else if (ARUTA[auxruta]=="LEFT90"){
                
                     if(IZQ>=18 && DER>=18){
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
                
              }else if (ARUTA[auxruta]=="DEIXEI135"){
               
                     if(IZQ>=27 && DER>=27){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=27){
                                atrasruedaizquierda();
                              }else if (IZQ > DER || IZQ>=27){
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
                
              }else if (ARUTA[auxruta]=="180"){
         
                     if(IZQ>=36 && DER>=36){
                      parar();
                      auxruta++;
                      delay(500);
                      IZQ=0;
                      DER=0;
                    }else{
                       if(IZQ < DER || DER>=36){
                                atrasruedaizquierda();
                              }else if (IZQ > DER || IZQ>=36){
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
               
              }else{
                  secuencias=0;
                  auxruta=0;
                  rutaC ="1";
                  consul=0;
                  HacerRuta=0;
                  for(int i=1;  i <100 ; i+=1) {
                     ARUTA[HacerRuta]="0";
                  }
                  //modifica();
             } 
                      
          
        }else{
              secuencias=0;
              auxruta=0;
              rutaC ="1";
              consul=0;
              HacerRuta=0;
              //modifica();
        }
      
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

     String url = "/programas_phpLab2/proceso_eventos/ConsultarRuta.php";

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

