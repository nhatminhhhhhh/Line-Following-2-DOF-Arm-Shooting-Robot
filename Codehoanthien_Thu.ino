#include <HardwareSerial.h> //.
#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

HardwareSerial espSerial(2); //.

const int enA = 4;
const int enB = 19;


  

const int freq = 5000;
const int resolution = 8; 

  Servo servo2;
  Servo servo3;  
  Servo servo4;

byte SpMaxL = 240;
byte SpMaxR = 240;

 


struct __attribute__((packed)) dataPacket {
    int huong = 0;
};


void onReceiveData(const esp_now_recv_info *recvInfo, const uint8_t *incomingData, int len) {
    dataPacket packet;
    memcpy(&packet, incomingData, sizeof(packet));
    Serial.print("Huong di:  "); Serial.println(packet.huong); 
    // 0 dung, 1 tien, 2 lui, 3 trai, 4 phai, 5 ban bong, 6 day bong, 7 gap bong, 8 truc y, 9 do line
   
    switch (packet.huong) {
      case 1:
        Tien(SpMaxL, SpMaxR);  
        break;
      case 2:
        Lui(SpMaxL, SpMaxR);
        break;
      case 3:
        Trai(190,190);
        break;
      case 4:
        Phai(190,190);
        break;
      case 5:
        if(packet.huong == 5){
          espSerial.println("Relay"); }
        break;
      case 6: // day bong - vao nong
        if(packet.huong == 6){
            servo2.write(0); 
        }
        break;
      case 7:  // thả tay gắp xuống
        servo3.write(10);    
        delay(20);         
        break;
      case 8: // đưa tay gắp len
        servo3.write(143);  
        delay(20);           
        break;
      case 9: // kep bong
        espSerial.println("Kep bong");
        delay(20);
        break;
      case 10: // tha bong
        espSerial.println("Tha bong");
        delay(20);
        break;
      case 11:
        if (packet.huong == 11){
            delay(10);
            if (packet.huong == 11){
                doline();
            }
            else {
                Dung();}
            }  
        break;
      default:
        servo2.write(140);
        Dung();
        break;
    }
   
}


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() == ESP_OK) {
        esp_now_register_recv_cb(onReceiveData);
  } 

  espSerial.begin(9600, SERIAL_8N1, 22, 23); // TX=23, RX=22

  servo2.attach(2); // day bong
  servo3.attach(21); // gap bong truc y 
  //servo4.attach(22); // gap bong truc x, góc set up 90*, góc kẹp 62* 
  pinMode(16, OUTPUT);//Set chân in1 của dc A là output ****
  pinMode(17, OUTPUT);//Set chân in2 của dc A là output
  pinMode(5,  OUTPUT);//Set chân in1 của dc B là output
  pinMode(18, OUTPUT);//Set chân in2 của dc B là output

  pinMode(34, INPUT);//Set chân cảm biến 1 là input
  pinMode(35, INPUT);//Set chân cảm biến 2 là input
  pinMode(32, INPUT);//Set chân cảm biến 3 là input
  pinMode(33, INPUT);//Set chân cảm biến 4 là input
  pinMode(25, INPUT);//Set chân cảm biến 5 là input
  pinMode(26, INPUT);//Set chân cảm biến 6 là input
  pinMode(27, INPUT);//Set chân cảm biến 7 là input
  pinMode(14, INPUT); // cảm biến phụ 1
  pinMode(12, INPUT);// cảm biến phụ 2 
 
  ledcAttach(enA, freq, resolution);
  ledcAttach(enB, freq, resolution);

  servo2.write(140); // day bong - o tren cao
  servo3.write(143);//y  ban đầu cất tay gắp vào nòng 143 tren cao  -> 10 dat 

}



void Tien(byte speedL, byte speedR){
  ledcWrite(enA, SpMaxL);
  ledcWrite(enB, SpMaxR);
  digitalWrite(18, 1);
  digitalWrite(5, 0);
  digitalWrite(17, 1);
  digitalWrite(16, 0);
}
void Lui(byte SpeedL, byte SpeedR)
{
  ledcWrite(enA, SpMaxL);
  ledcWrite(enB, SpMaxR);
  digitalWrite(18, 0);
  digitalWrite(5, 1);
  digitalWrite(17, 0);
  digitalWrite(16, 1);
}
void Trai(byte SpeedL, byte SpeedR){
  ledcWrite(enA, SpMaxL);
  ledcWrite(enB, SpMaxR);
  digitalWrite(18, 0);
  digitalWrite(5, 1);
  digitalWrite(17, 1);
  digitalWrite(16, 0);
}
void Phai(byte SpeedL, byte SpeedR){
  digitalWrite(18, 1);
  digitalWrite(5, 0);
  //ledcWrite(enB, 200);
  digitalWrite(17, 0);
  digitalWrite(16, 1);
  //ledcWrite(enA, 200);
  ledcWrite(enA, SpMaxL);
  ledcWrite(enB, SpMaxR);
}
void Dung()
{
  digitalWrite(18, 0);
  digitalWrite(5, 0);
  digitalWrite(17, 0);
  digitalWrite(16, 0);
}
void doline()
{
  switch (trangThai5CamBien())
  { 
    case 200:// văng
      //Tien(SpMaxL,SpMaxR-70);
      Lui(80,80);
      break;
    case 0:
      Tien(SpMaxL, SpMaxR);
      break;
    case 1:
     
     // Phai();
     Tien(SpMaxL, SpMaxR);
      break;
    case 2:
      //Tien(SpMaxL, 0);
      Phai(230,230);   
      break;
    case 3:
      //Tien(SpMaxL, 0);
      Phai(230, 230);      
      break;
    case -1:
      //Tien(0, SpMaxR);
      // Trai();
      Tien(SpMaxL, SpMaxR);   
      break;
    case -2:
     // Tien(0, SpMaxR);
      Trai(190,190);  
      break;
    case -3:
      //Tien(0, SpMaxR);
      Trai(190,190);  
      break;
    case 100:
      Dung(); 
      break;
    default:
      Dung();
      break; 
  }
  
}

boolean IFSensor (byte PinNumb)   // Có line là 1
{
  return (digitalRead (PinNumb));
} 

int trangThai5CamBien ()
{
  /*
      Âm là lệch phải
      Dương là lệch trái
      Mức độ lệch giảm tăng dần : 1 2 3
  */

  int sens1 = IFSensor(34);
  int sens2 = IFSensor(35);
  int sens3 = IFSensor(32);
  int sens4 = IFSensor(33);
  int sens5 = IFSensor(25);
  int sens6 = IFSensor(26);  
  int sens7 = IFSensor(27);  
  int sens8 = IFSensor(14); 
  int sens9 = IFSensor(12); 

  switch (lechvach5mat())
  {
    case -3:
      return -3;
      break;
    case -2:
      return -2;
      break;
    case -1:
      return -1;
      break;
    case 0:
      if ( (abs(sens1) + abs(sens2) + abs(sens3) + abs(sens4) + abs(sens5) + abs(sens6)+ abs(sens7) + abs(sens8) + abs(sens9))== 0  )
        return 200; // 7 cảm biến chính vượt line, 2 cảm biến phụ không có line ngắt 
      else if ( (abs(sens1) + abs(sens2) + abs(sens3) + abs(sens4) + abs(sens5) + abs(sens6)+ abs(sens7)) == 7)
       return 100;   // 7 mat nam tren line den => dung lai
      else if ( (abs(sens1) + abs(sens2) + abs(sens3) + abs(sens4) + abs(sens5) + abs(sens6)+ abs(sens7) ) == 0 && (abs(sens8) + abs(sens9))== 1)
        return 0; // 7 cảm biến chính không bắt được line nào nhưng 1 trong 2 cảm biến phụ bắt được line phía trước (line ngắt) thì tiếp tục đi thẳng  
      else if ( (abs(sens1) + abs(sens2) + abs(sens3) + abs(sens4) + abs(sens5) + abs(sens6)+ abs(sens7)) == 1)
        return 0;
      else if ( (abs(sens1) + abs(sens2) + abs(sens3) + abs(sens4) + abs(sens5) + abs(sens6)+ abs(sens7)) == 2)
        return 0;
      break;
    case 1:
      return 1;
      break;
    case 2:
      return 2;
      break;
    case 3:
      return 3;
      break;
  }
}

int lechvach5mat()
{
  /*
      Âm là lệch phải
      Dương là lệch trái
      Mức độ lệch giảm tăng dần : 1 3 2
  */
  int sens1 = IFSensor(34);
  int sens2 = IFSensor(35);
  int sens3 = IFSensor(32);
  int sens4 = IFSensor(33);
  int sens5 = IFSensor(25);
  int sens6 = IFSensor(26);  
  int sens7 = IFSensor(27);
  int sens8 = IFSensor(14); 
  int sens9 = IFSensor(12); 
  int lechvach = -2 * sens1 - sens2 + sens6 + 2 * sens7;
  switch (lechvach)
    {
      case -3:// cái này là do 2 mắt biên đều chạm vạch
        return -2;
        break;
      case -2:
        return -3;
        break;
      case -1:
        return -1;
        break;
      case 0:
        return 0;
        break;
      case 1:
        return 1;
        break;
      case 2:
        return 3;
        break;
      case 3:
        return 2;
        break;

    }

}


void loop() {
 
}