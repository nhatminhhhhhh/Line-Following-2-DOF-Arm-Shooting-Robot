# LINE-FOLLOWING & 2 DOF ARM SHOOTING ROBOT
I made this robot for my competiton. There are 2 ino file. One for receiver and one for transmitter.  
In this robot, I use ESP32 and Arduino to have more GPIO.  
## Transmitter/ MASTER
The controller read input every 100ms and send to receiver.  
## Receiver/ SLAVE  
The receiver receive control data and control GPIO  
### Line-folling mode  
I use simple algorithm in this robot. There are 9 IF Sensor, 7 sensors are used to detect error, 2 sensors placed in front of the robot to detect broken lines.
The sensors are arranged as follows:  
                                   |sensor 9|  
                                   |sensor 8|    
|sensor 1|  |sensor2|  |sensor 3|  |sensor4|  |sensor 5|  |sensor 6|  |sensor 7|  

