#define SERIAL_COMMUNICATION   // Giao tiếp thiết bị-máy tính dạng console: Serial 9600
#define SIOT_DATA              // Có gửi dữ liệu về server


#ifdef SIOT_DATA
  #include "src\SiotCore.h"
  SiotCore core;
#endif

String response;
String RxBuffer; // Biến chữa dữ liệu đêm
String Modify; // tinh chỉnh lại dữ liệ
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);

// Chuyển dữ liệu ra máy tính và kết nối với USB CP2102
#ifdef SERIAL_COMMUNICATION
  // start serial port at 9600 bps:
  Serial.begin(9600);
  Serial.println("Port is connected");
#endif

#ifdef SIOT_DATA  
  // Khởi tạo kết nối với máy chủ SIOT
  core.init();
  Serial.println("Wifi is connected");
  core.updateData(URL_ID, "Hello, you have successfully connected", response, POST);
#endif

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
  if (Serial.available()) {
    RxBuffer = "";
    while (Serial.available()) {
      RxBuffer = Serial.readString();
    }
    Modify = RxBuffer.substring(1,9);
    Serial.print("h =  ");
    Serial.print(Modify);
    // Upload len sever.
    core.updateData(URL_ID, Modify, response, POST);
 }
}