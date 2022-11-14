#define SERIAL_COMMUNICATION   // Giao tiếp thiết bị-máy tính dạng console: Serial 9600
#define SIOT_DATA              // Có gửi dữ liệu về server


// #include "D:\HUST\Project I\src\Reader\src\SiotCore.h"
#ifdef SIOT_DATA
  #include "src\SiotCore.h"
  SiotCore core;
#endif

String response;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);

// Chuyển dữ liệu ra máy tính và kết nối với USB CP2102
#ifdef SERIAL_COMMUNICATION
  // start serial port at 9600 bps:
  Serial.begin(9600);
  Serial.println("port ok");
#endif

#ifdef SIOT_DATA  
  // Khởi tạo kết nối với máy chủ SIOT
  Serial.println("Ket noi wifi");
  core.init();
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
  if (Serial.available()) {
    String RxBuffer = "";
    while (Serial.available()) {
      RxBuffer = Serial.readString();
    }
    Serial.print("h =  ");
    Serial.print(RxBuffer);
    // Upload len sever.
    #ifdef SIOT_DATA
//      core.updateData(URL_ID, RxBuffer, response, POST);
    #endif
 }
}
