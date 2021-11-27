/*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server con acceso a SPIFFS
  Basándose en los ejemplos de:
  https://github.com/khoih-prog/WiFiWebServer
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://github.com/luisllamasbinaburo/ESP32-Examples
  https://www.luisllamas.es/esp8266-esp32/
**************************************************************************************************/
//************************************************************************************************
// Librerías
//************************************************************************************************
#include <WiFi.h>
#include <SPIFFS.h>
#include <WebServer.h>
//************************************************************************************************
// Variables globales
//************************************************************************************************
// SSID & Password
const char* ssid = "PROYECTO3_BYM";  // Enter SSID here
const char* password = "12345678";  //Enter Password here
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)


//************************************************************************************************
// Variables 
//************************************************************************************************

String group1_status = "";
String group2_status = "";

int verificador[4]={0,0,0,0};
int verificador2[4]={0,0,0,0};
int cont = 0;

int a = 13;
int b = 12;
int c = 14;
int d = 27;
int e = 26;
int f = 25;
int g = 33;

int bandera = 0;

void escribirEnElDisplay(int va, int vb, int vc, int vd, int ve, int vf, int vg);
void desplegar_valor(uint8_t val);



//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  Serial.begin(115200); // se inicializa el baudrate de la consola 


//************************************************************************************************
// Estados iniciales
//************************************************************************************************

//DISPLAY
pinMode(a, OUTPUT);
pinMode(b, OUTPUT);
pinMode(c, OUTPUT);
pinMode(d, OUTPUT);
pinMode(e, OUTPUT);
pinMode(f, OUTPUT);
pinMode(g, OUTPUT);

//PINES GRUPO 1
pinMode(15, INPUT_PULLUP);
pinMode(2, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
pinMode(5, INPUT_PULLUP);


//PINES GRUPO 2
pinMode(18, INPUT_PULLUP);
pinMode(19, INPUT_PULLUP);
pinMode(21, INPUT_PULLUP);
pinMode(22, INPUT_PULLUP);
  

 // if (!SPIFFS.begin()) {
   // Serial.println("An Error has occurred while mounting SPIFFS");
    //return;
  //}
  
  WiFi.softAP(ssid, password); // se configura con el modo de access point
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  Serial.print("SSID: "); // se imprimen los valores del SSID y pass
  Serial.println(ssid);
  Serial.print("password: ");
  Serial.println(password);



//************************************************************************************************
// Rutas para request
//************************************************************************************************
  server.on("/", handle_OnConnect); // página de inicio
  server.on("/group1", handle_group1); // handler para ver status grupo de parqueos 1
  server.on("/group2", handle_group2); // handler para ver status grupo de parqueos 2


  
  server.onNotFound([]() {                  // si el cliente solicita una uri desconocida
    if (!HandleFileRead(server.uri()))      // enviar archivo desde SPIFF, si existe
      handleNotFound();             // sino responder con un error 404 (no existe)
  });
  //server.onNotFound(handle_NotFound); //si no se encuentra el uri, responder con error 404 (no existe)

  server.begin(); // iniciar servidor
  Serial.println("HTTP server started");
  delay(100);
}
//************************************************************************************************
// loop principal
//************************************************************************************************
void loop() {
  server.handleClient(); // escuchar solicitudes de clientes


  // put your main code here, to run repeatedly:
 
  if(digitalRead(15) == HIGH){
   verificador[0] = 0;
  }else{
   verificador[0] = 1;
  }
  if(digitalRead(2) == HIGH){
   verificador[1] = 0;
  }else{
   verificador[1] = 1;
  }
  if(digitalRead(4) == HIGH){
   verificador[2] = 0;
  }else{
   verificador[2] = 1;
  }
  if(digitalRead(5) == HIGH){
   verificador[3] = 0;
  }else{
   verificador[3] = 1;
  }

  if(digitalRead(18) == HIGH){
   verificador2[0] = 0;
  }else{
   verificador2[0] = 1;
  }
  if(digitalRead(19) == HIGH){
   verificador2[1] = 0;
  }else{
   verificador2[1] = 1;
  }
  if(digitalRead(21) == HIGH){
   verificador2[2] = 0;
  }else{
   verificador2[2] = 1;
  }
  if(digitalRead(22) == HIGH){
   verificador2[3] = 0;
  }else{
   verificador2[3] = 1;
  }

 cont = 0;
 for (int i = 0; i < 4; i++){
  int val = verificador[i];  
  if(val == 1){
    cont++;
  }
 }

 for (int i = 0; i < 4; i++){
  int val = verificador2[i];  
  if(val == 1){
    cont++;
  }
 }
  
  uint8_t libres = 8 - cont;
  desplegar_valor(libres);
    
    /*group1_status = "";
    group2_status = "";*/
    
 //  for(int i = 0; i < 4; i++){
   // group1_status= String(verificador);
//    Serial.println(group1_status);
  // }

 //  for(int i = 0; i < 4; i++){
   // group2_status= String(verificador2);
 //   Serial.println(group2_status);
   //}

  /*if(bandera == 1){
     server.send(200, "text/plane", verificador);
   }else if (bandera == 2) {
      server.send(200, "text/plane", verificador2);
    }*/


}


//************************************************************************************************
// Subrutinas para display
//************************************************************************************************

void escribirEnElDisplay(int va, int vb, int vc, int vd, int ve, int vf, int vg){

  digitalWrite(a,va);
  digitalWrite(b,vb);
  digitalWrite(c,vc);
  digitalWrite(d,vd);
  digitalWrite(e,ve);
  digitalWrite(f,vf);
  digitalWrite(g,vg);

} 


void desplegar_valor(uint8_t val){
  if(val == 0){
     //Cero
     escribirEnElDisplay(1,1,1,1,1,1,0);    
  }
  else if(val == 1){
     //Uno
     escribirEnElDisplay(0,1,1,0,0,0,0);   
  }
  else if(val == 2){
     //Dos
     escribirEnElDisplay(1,1,0,1,1,0,1);    
  }
  else if(val == 3){
    //Tres
    escribirEnElDisplay(1,1,1,1,0,0,1); 
  }
  else if(val == 4){
     //Cuatro
     escribirEnElDisplay(0,1,1,0,0,1,1);   
  }
  else if(val == 5){
     //Cinco
     escribirEnElDisplay(1,0,1,1,0,1,1);   
  }
  else if(val == 6){
     //Seis
     escribirEnElDisplay(1,0,1,1,1,1,1);   
  }
  else if(val == 7){
     //Siete
     escribirEnElDisplay(1,1,1,0,0,0,0);   
  }
  else if(val == 8){
     //Ocho
     escribirEnElDisplay(1,1,1,1,1,1,1);    
  }
  
 }


//************************************************************************************************
// Handler de página de inicio
//************************************************************************************************
void handle_OnConnect() {
  bandera = 0;
  server.send(200, "text/html", SendHTML());
}
//************************************************************************************************
// Handler de grupo 1
//************************************************************************************************
void handle_group1() {
  Serial.println("STATUS GRUPO 1");
  bandera = 1;
  server.send(200, "text/html", SendHTMLSTATUS(verificador,1)); //responde con un OK (200) y envía HTML
}
//************************************************************************************************
// Handler de grupo 2
//************************************************************************************************
void handle_group2() {
  bandera = 2;
  Serial.println("STATUS GRUPO 2");
  server.send(200, "text/html", SendHTMLSTATUS(verificador2,2)); //responde con un OK (200) y envía HTML
}





//************************************************************************************************
// Procesador de HTML
//************************************************************************************************
String SendHTML() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Welcome</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  //ptr += ".button-on {background-color: #3498db;}\n";
  //ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-o {background-color: #34495e;}\n";
  ptr += ".button-o:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Control de parqueo &#128664</h1>\n";
  ptr += "<h3>Proyecto 3</h3>\n";
  

  ptr += "<p>Ir a estado de:</p><a class=\"button button-o\" href=\"/group1\">Grupo 1</a>\n";

  ptr += "<a class=\"button button-o\" href=\"/group2\">Grupo 2</a>\n";

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

//RENDERIZAR ESTADO PARQUEOS  
String SendHTMLSTATUS(int inputString [], uint8_t grupo ) {
  
  String ptr = "<!DOCTYPE html> <html>\n";
 // http-equiv=\"refresh\" content=\"4\"
  ptr += "<head><meta http-equiv=\"refresh\" content=\"2\" name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Status Parqueo</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  //ptr += ".button-on {background-color: #3498db;}\n";
  //ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-o {background-color: #34495e;}\n";
  ptr += ".button-o:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Grupo" + String(grupo) + "</h1>\n";

  for(int i = 0; i < 4; i++){
    
    if(grupo==1){
      
      if(inputString [i]==1){
        ptr += "<p>Parqueo "+ String(i+1) + "  &#8594    &#9940 </p>\n";
      }else if(inputString [i]==0){
        ptr += "<p>Parqueo "+ String(i+1) + "  &#8594    &#9989 </p>\n";
      }
        
    }else if(grupo==2){

      if(inputString [i]==1){
        ptr += "<p>Parqueo "+ String(i+1) + "  &#8594    &#9940 </p>\n";
      }else if(inputString [i]==0){
        ptr += "<p>Parqueo "+ String(i+1) + "  &#8594    &#9989 </p>\n";
      }
      
    }
    
  }

  
  
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
  
}


//************************************************************************************************
// Handler de not found
//************************************************************************************************
void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}
//************************************************************************************************
// Obtener el tipo de contenido del archivo
//************************************************************************************************
String GetContentType(String filename)
{
  if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
//************************************************************************************************
// Enviar al servidor el archivo desde SPIFFS
//************************************************************************************************
void ServeFile(String path)
{
  File file = SPIFFS.open(path, "r");
  size_t sent = server.streamFile(file, GetContentType(path));
  file.close();
}
//************************************************************************************************
// Enviar al servidor el archivo desde SPIFFS
//************************************************************************************************
void ServeFile(String path, String contentType)
{
  File file = SPIFFS.open(path, "r");
  size_t sent = server.streamFile(file, contentType);
  file.close();
}
//************************************************************************************************
// Handler de not found
//************************************************************************************************
bool HandleFileRead(String path)
{
  if (path.endsWith("/")) path += "index.html";
  Serial.println("handleFileRead: " + path);

  if (SPIFFS.exists(path))
  {
    ServeFile(path);
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;
}
