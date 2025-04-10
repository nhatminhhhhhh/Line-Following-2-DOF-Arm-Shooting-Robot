// Mac phat 1:       1C:69:20:C6:EE:54 
// Mac thu 1 broad:  1C:69:20:C6:81:F4  

// Mac moi phat         : 1C:69:20:CA:90:9C
// Mac moi thu 2 board 2: 1C:69:20:C6:B7:98

#include <esp_now.h>
#include <WiFi.h>

int button1 = 34, button2 = 35, button3 = 32, button4 = 33, button5 = 16, button6 = 17, button7 = 5, button8 = 18, button9 = 12, button10 = 2, button11 = 4 ;
int hientai1 = 0, hientai2 = 0, hientai3 = 0, hientai4 = 0, hientai5 = 0, hientai6 = 0, hientai7 = 0, hientai8 = 0, hientai9 = 0, hientai10 = 0, hientai11 = 0; // doc huong xe

uint8_t receiverAddress[] = {0x1C, 0x69, 0x20, 0xC6, 0x81, 0xF4}; // Địa chỉ MAC của cũ - thu 1
//uint8_t receiverAddress[] = {0x1C, 0x69, 0x20, 0xC6, 0xB7, 0x98};  //  Địa chỉ MAC của mới - thu 2


struct __attribute__((packed)) dataPacket{
  int huong = 0;
};

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    pinMode(button3, INPUT);
    pinMode(button4, INPUT);
    pinMode(button5, INPUT);
    pinMode(button6, INPUT);
    pinMode(button7, INPUT);
    pinMode(button8, INPUT);
    pinMode(button9, INPUT);
    pinMode(button10, INPUT);
    pinMode(button11, INPUT);


    if (esp_now_init() == ESP_OK) {

        esp_now_peer_info_t peerInfo;
        memcpy(peerInfo.peer_addr, receiverAddress, 6);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;
        esp_now_add_peer(&peerInfo);

    } else {
        Serial.println("ESP-NOW init failed");
    }
}

void loop() {
    dataPacket packet;
    hientai1 = digitalRead(button1);
    hientai2 = digitalRead(button2);
    hientai3 = digitalRead(button3);
    hientai4 = digitalRead(button4);
    hientai5 = digitalRead(button5);
    hientai6 = digitalRead(button6);
    hientai7 = digitalRead(button7);
    hientai8 = digitalRead(button8);
    hientai9 = digitalRead(button9);
    hientai10 = digitalRead(button10);
    hientai11 = digitalRead(button11);

    
    // 0 dung, 1 tien, 2 lui, 3 trai, 4 phai, 5 ban bong, 6 day bong, 7 gap bong, 8 truc y, 9 do line
      if (hientai1 != 0){
          if (hientai1 == 1){
                packet.huong = 1; // tien
                esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet)); }
      }
      else if (hientai2 != 0){
           if (hientai2 == 1){
                packet.huong = 2; //lui
                esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet)); }
      }
      else if (hientai3 != 0){
           if (hientai3 == 1){
                packet.huong = 3; //trai
                esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet)); }
      }
      else if (hientai4 != 0){
           if (hientai4 == 1){
                packet.huong = 4; // phai
                esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet)); }
      }
      else if (hientai5 != 0){
           if (hientai5 == 1){
                packet.huong = 5; // ban bong
                esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet)); }
      }
      else if (hientai6 != 0){
           if (hientai6 == 1){
                packet.huong = 6; // day bong
                esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet)); }
      }
      else if (hientai7 != 0){
           if (hientai7 == 1){
                packet.huong = 7; // gap bong
                esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet)); }
      }
      else if (hientai8 != 0){
           if (hientai8 == 1){
                packet.huong = 8; // truc y
                esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet)); }
      }
      else if (hientai9 != 0){
           if (hientai9 == 1){
                packet.huong = 9; // do line
                esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet)); }
      }
      else if (hientai10 != 0){
           if (hientai10 == 1){
                packet.huong = 10; // 
                esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet)); }
      }
      else if (hientai11 != 0){
           if (hientai11 == 1){
                packet.huong = 11; // 
                esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet)); }
      }
      else {
            packet.huong = 0;//dung
            esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));
      }
    Serial.print(hientai1); Serial.print(hientai2); Serial.print(hientai3); Serial.print(hientai4); Serial.print(hientai5); Serial.print(hientai6); Serial.print(hientai7); Serial.print(hientai8); Serial.print(hientai9), Serial.print(hientai10); Serial.println(hientai11);
    Serial.print("Huong di: "); Serial.println(packet.huong); 
    delay(100);
    
}
