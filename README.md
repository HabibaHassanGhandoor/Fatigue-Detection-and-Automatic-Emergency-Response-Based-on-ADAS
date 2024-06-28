# Fatigue-Detection-and-Automatic-Emergency-Response-Based-on-ADAS
o	Target Group: Cardiac patients on the road as well as sleepy and drained drivers. 
o	Project Scopes: Deep Learning (CNN), Embedded Systems, and Embedded Linux.
o	Project Idea: Building an Advanced Driver Assistance System unit that serves seven use cases, and these are: 
1)	Fatigue Detection via Transfer Learning based on a ResNet50v2 deep learning model. The achieved validation accuracy was 96.92%. This model was trained on a dataset that we have collected, and split ourselves. It collects real-time images that are captured via USB CAM and processed on a Raspberry-Pi and identifies them. The CNN model itself runs on the R-Pi. It is also able to classify random drowsy, active, and sleeping driver images from the internet.
2)	A Smart Alert System on standby whenever the driver gets sleepy or drowsy it fires an alarm. 
3)	An IFTTT Alerting Notification is sent from the R-Pi to the driver’s emergency contacts through Wi-Fi to notify them that he is sleeping and not responding to any stimulation.
4)	Early Heart Attack Detection using a pulse sensor that keeps track of the driver’s heart rate provided it defers from the normal range (60 to 100 BPM).
5)	 The exact Geo-Location of the car with the sleeping driver or one that is suffering from a cardiac arrest is sent through an Emergency SMS Message to the nearest emergency unit in order to save his or her life.
6)	If the driver does not respond to the stimulation (alarm) the car immediately shifts into the Adaptive Cruise Control mode in which it follows the speed of the front car and maintains a safe distance on the road. 
7)	The ADAS unit also provides Blind Spot Assistance in case the car is mounting a bridge or entering a tunnel. 
o	Used Microcontrollers: ATmega32 AVR and Raspberry-Pi communicating through SPI.
o	Used communication protocols: UART for GPS/GSM Module, SPI for communication with R-Pi, and I2C for MPU6050 IMU module.
