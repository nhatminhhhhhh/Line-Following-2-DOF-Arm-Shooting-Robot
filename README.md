# LINE-FOLLOWING & 2 DOF ARM SHOOTING ROBOT
Robot dò line + gắp/ bắn bóng.
## Transmitter/ MASTER
Robot sử dụng ESP-NOW làm giao thức truyền nhận không dây giữa TX và RX. Sử dụng ESP-NOW sẽ tiết kiệm chi phí khi phát triền giao thức kết nối không dây mà không cần phải thêm các module khác như Bluetooth/BLE/ LoRa,..  
Tay cầm sẽ đọc các tín hiệu từ nút nhấn 100ms/lần và gửi tín hiệu đến RX 
## Receiver/ SLAVE  
RX nhận tín hiệu điều khiển từ TX và điều khiển các chức năng tương ứng
### Line-folling mode  
Mình sử dụng 9 cảm biến IF digital. Cách sắp xếp cảm biến có thể tuỳ chỉnh để phù hợp với độ rộng của line 
....................................................|sensor 9|..............................................  
....................................................|sensor 8|..............................................    
|sensor 1|  |sensor2|  |sensor 3|  |sensor4|  |sensor 5|  |sensor 6|  |sensor 7|    

Trạng thái lệch vạch được xác định như sau:  
> -2 * (sensor 1) - (sensor 2) + sensor 6 + 2 * sensor 7

Khi cảm biến nằm trên line, giá trị trả về sẽ là 1 (ngược lại là 0).   
> Nếu cảm biến của bạn trả về giá trị 0 khi nằm trên line, chỉ cần return (!digitalRead (PinNumb)) ở hàm IFSensor().

Khi đó, ta có các độ lệch line tương ứng là -3, -2, -1, 0, 1, 2, 3  
Nếu độ lệch line là 0, chúng ta sẽ có các trường hợp sau:  
* Robot văng khỏi line -> đi lùi
* Cảm biến 8/9 phát hiện line ngắt đoạn phía trước -> tiếp tục đi thẳng
* 7 cảm biến đều nằm trên line -> dừng lại
* Cảm biến 3/4/5 nằm trên line -> đi thẳng



