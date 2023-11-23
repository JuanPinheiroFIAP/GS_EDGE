/* ESP32 WiFi Scanning example */
#include <LiquidCrystal.h>
#include "WiFi.h"
#include <HTTPClient.h>

HTTPClient client;

char nomeWifi[] = "Wokwi-GUEST";
char senhaWifi[] = "";
char serverAddress[] = "https://api.tago.io/data";
char contentHeader[] = "application/json";
char tokenHeader[] = "19c01251-758a-48d5-abfd-1d8fa4e0c781";

LiquidCrystal lcd(0, 2, 4, 5, 16, 17);

int const pinoTemperaturaCorporal = 33;
int const pinoBatimentoCardiaco = 32;
int const pinoPressaoSanguinea = 35;

int valorTemperatura;
int valorBatimento;
int valorPressao;

void setup() {
  lcd.begin(16,2);
  pinMode(pinoTemperaturaCorporal, INPUT);
  pinMode(pinoBatimentoCardiaco, INPUT);
  pinMode(pinoPressaoSanguinea, INPUT);
  Serial.begin(115200);
  init_wifi();
}

void loop() {
  int valorTemperaturaCorporal = analogRead(pinoTemperaturaCorporal);
  valorTemperaturaCorporal = map(valorTemperaturaCorporal, 0, 4095, 0, 100);
  valorTemperatura = valorTemperaturaCorporal;
  
  if (valorTemperaturaCorporal > 0 && valorTemperaturaCorporal < 25){
    lcd.clear(); 
    lcd.print("Temp Corp OK ");
    lcd.setCursor(0, 1);
    lcd.print("Temperatura: ");
    lcd.print(valorTemperaturaCorporal);
    lcd.print("C");
    send_valorTemperaturaCorporal();
  }if (valorTemperaturaCorporal > 25 && valorTemperaturaCorporal < 50){
    lcd.clear(); 
    lcd.print("Temp Corp ruim ");
    lcd.setCursor(0, 1);
    lcd.print("Temperatura: ");
    lcd.print(valorTemperaturaCorporal);
    lcd.print("C");
    send_valorTemperaturaCorporal();
  }if (valorTemperaturaCorporal > 50){
    lcd.clear(); 
    lcd.print("Temp Corp pessima ");
    lcd.setCursor(0, 1);
    lcd.print("Temperatura: ");
    lcd.print(valorTemperaturaCorporal);
    lcd.print("C");
    send_valorTemperaturaCorporal();
  }

  Serial.print("Temperatura corporal: ");
  Serial.println(valorTemperaturaCorporal);
  delay(1000);

  //-------------------------------------------------------------------------------

  int valorBatimentoCardiaco = analogRead(pinoBatimentoCardiaco);
  valorBatimentoCardiaco = map(valorBatimentoCardiaco, 0, 4095, 0, 100);
  valorBatimento = valorBatimentoCardiaco;

  if (valorBatimentoCardiaco > 0 && valorBatimentoCardiaco < 25){
    lcd.clear(); 
    lcd.print("Batimentos OK ");
    lcd.setCursor(0, 1);
    lcd.print("Batimentos: ");
    lcd.print(valorBatimentoCardiaco);
    lcd.print("bpm");
    send_valorBatimentoCardiaco();
  }if (valorBatimentoCardiaco > 25 && valorBatimentoCardiaco < 50){
    lcd.clear(); 
    lcd.print("Batimentos ruim ");
    lcd.setCursor(0, 1);
    lcd.print("Batimentos: ");
    lcd.print(valorBatimentoCardiaco);
    lcd.print("bpm");
    send_valorBatimentoCardiaco();
  }if (valorBatimentoCardiaco > 50){
    lcd.clear(); 
    lcd.print("Batimentos pessimo ");
    lcd.setCursor(0, 1);
    lcd.print("Batimentos: ");
    lcd.print(valorBatimentoCardiaco);
    lcd.print("bpm");
    send_valorBatimentoCardiaco();
  }

  Serial.print("Valor batimento cardiaco: ");
  Serial.println(valorBatimentoCardiaco);
  delay(1000);

  //-------------------------------------------------------------------------------
  
  int valorPressaoSanguinea = analogRead(pinoPressaoSanguinea);
  valorPressaoSanguinea = map(valorPressaoSanguinea, 0, 4095, 0, 100);
  valorPressao = valorPressaoSanguinea;
  

  if (valorPressaoSanguinea > 0 && valorPressaoSanguinea < 25){
    lcd.clear(); 
    lcd.print("Pressao OK ");
    lcd.setCursor(0, 1);
    lcd.print("Pressao: ");
    lcd.print(valorPressaoSanguinea);
    lcd.print("mmHg");
    send_valorPressaoSanguinea();
  }if (valorPressaoSanguinea > 25 && valorPressaoSanguinea < 50){
    lcd.clear(); 
    lcd.print("Pressao ruim ");
    lcd.setCursor(0, 1);
    lcd.print("Pressao: ");
    lcd.print(valorPressaoSanguinea);
    lcd.print("mmHg");
    send_valorPressaoSanguinea();
  }if (valorPressaoSanguinea > 50){
    lcd.clear(); 
    lcd.print("Pressao pessima ");
    lcd.setCursor(0, 1);
    lcd.print("Pressao: ");
    lcd.print(valorPressaoSanguinea);
    lcd.print("mmHg");
    send_valorPressaoSanguinea();
  }

  Serial.print("Valor pressao sanguinea: ");
  Serial.println(valorPressaoSanguinea);
  delay(1000);

  //-------------------------------------------------------------------------------
  
}



void init_wifi() {
  Serial.println("Conectando WiFi");
  Serial.print("Wifi: ");
  Serial.println(nomeWifi);
  WiFi.begin(nomeWifi, senhaWifi);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println("WiFi Conectado");
  Serial.print("Meu IP eh: ");
  Serial.println(WiFi.localIP());
}

void send_valorTemperaturaCorporal() {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;

  strcpy(postData, "{\n\t\"variable\": \"valorTemperatura\",\n\t\"value\": ");
  dtostrf(valorTemperatura, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat(postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(2000);

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}

void send_valorBatimentoCardiaco() {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;

  strcpy(postData, "{\n\t\"variable\": \"valorBatimento\",\n\t\"value\": ");
  dtostrf(valorBatimento, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat(postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(2000);

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}

void send_valorPressaoSanguinea() {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;

  strcpy(postData, "{\n\t\"variable\": \"valorPressao\",\n\t\"value\": ");
  dtostrf(valorPressao, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat(postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(2000);

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}