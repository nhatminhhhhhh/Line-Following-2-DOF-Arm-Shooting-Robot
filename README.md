# LINE-FOLLOWING & 2 DOF ARM SHOOTING ROBOT
Robot dò line + gắp/ bắn bóng.
## Transmitter/ MASTER
Robot sử dụng ESP-NOW làm giao thức truyền nhận không dây giữa TX và RX. Sử dụng ESP-NOW sẽ tiết kiệm chi phí khi phát triền giao thức kết nối không dây mà không cần phải thêm các module khác như Bluetooth/BLE/ LoRa,..  
Tay cầm sẽ đọc các tín hiệu từ nút nhấn 100ms/lần và gửi tín hiệu đến RX 
## Receiver/ SLAVE  
RX nhận tín hiệu điều khiển từ TX và điều khiển các chức năng tương ứng
### Line-folling mode  
I use simple algorithm in this robot. There are 9 IF Sensor, 7 sensors are used to detect error, 2 sensors placed in front of the robot to detect broken lines.
The sensors are arranged as follows:  
...................................|sensor 9|...................................  
...................................|sensor 8|...................................    
|sensor 1|  |sensor2|  |sensor 3|  |sensor4|  |sensor 5|  |sensor 6|  |sensor 7|    

Trạng thái lệch vạch được xác định như sau:  
> -2 * (sensor 1) - (sensor 2) + sensor 6 + 2 * sensor 7

Nếu cảm biến nằm trên line, giá trị trả về sẽ là 1 (ngược lại là 0). Khi đó, ta có các độ lệch line tương ứng là -2, -1, 0, 1, 2
  

