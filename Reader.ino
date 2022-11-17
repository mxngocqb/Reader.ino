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
  Serial.println("Connect Port Succesful");
#endif

#ifdef SIOT_DATA  
  // Khởi tạo kết nối với máy chủ SIOT
  core.init();
  Serial.println("Connect Wifi Succesful");
#endif
}

void loop() {
  // Kích hoạt đèn của board
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
  if (Serial.available()) {
    String TxBuffer = "";         // Lưu trữ chuỗi dữ liệu từ máy đọc thẻ.
    // Khi nhận được tín hiệu từ 2 chân TX, RX (RS232) -> đọc dữ liệu là gán vào RxBuffer.
    while (Serial.available()) {
      TxBuffer = Serial.readString();
    }
    // In ra màn hình ngoài.
    Serial.print("h =  ");
    Serial.print(TxBuffer);
    // Upload len sever.
    #ifdef SIOT_DATA
     core.updateData(URL_ID, TxBuffer, response, POST); // Upload lên địa chỉ URL_ID nằm trên web siot.soict.ai
    #endif
 }
}
