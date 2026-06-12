# esp32-security-system
Security system using an esp32, lcd screen, passive buzzer, HC-SR04 ultrasonic distance sensor, HC-SR501 PIR motion sensor and a button.
Acest proiect utilizeaza o placa de dezvoltare ESP32 cu 30 de pini pentru a afisa mesaje pe un ecran LCD 1602 prin intermediul unui modul de comunicare I2C. Proiectul include, de asemenea, circuite de control pe breadboard, cum ar fi un senzor si un buton.

Componente Utilizate
Placa de dezvoltare: ESP32 Dev Module cu 30 de pini
Afisaj: Ecran LCD 1602 (2 linii si 16 caractere) cu adaptor I2C atasat
Altele: Breadboard, fire de conexiune tip Jumper, senzor PIR si buton

Schema de Conexiuni
Conexiunile electrice sunt realizate pe breadboard conform listei de mai jos:

Pin Ecran LCD I2C
GND - GND - Alimentare minus 
VCC - VIN - Alimentare plus 5V
SDA - D21 - Linia de date pentru comunicare
SCL - D22 - Linia de ceas pentru sincronizare

HC-SR501 PIR
OUT - D13
VCC - 5V
GND - GND

HC-SR04 distance sensor
VCC - 5V
TRIG - D12
ECHO - D14
GND - GND

BUZZER
+ D25
- GND

BUTON
D26
GND

Nota: Daca ecranul este pornit dar apar doar blocuri luminate pe ecran, trebuie sa reglati potentiometrul albastru de pe spatele modulului I2C pana cand textul devine vizibil.

Configurare Software si Biblioteci
Pentru a rula codul din acest proiect, aveti nevoie de Arduino IDE configurat pentru placile din familia ESP32.

Biblioteci necesare de instalat din Library Manager:

#include <Wire.h>
#include <LiquidCrystal_I2C.h>


Adresa I2C implicita:
Codul este configurat in mod normal pentru adresa 0x27. Daca ecranul ramane blocat, verificati daca adresa modulului dumneavoastra este 0x3F si modificati linia corespunzatoare in codul sursa.

Cum se foloseste proiectul
Realizati conexiunile hardware pe breadboard conform schemei.

Conectati placa ESP32 la calculator folosind un cablu Micro-USB.

Deschideți fisierul cu extensia .ino in Arduino IDE.

Selectati placa corecta din meniu: Tools, Board, ESP32 Arduino, ESP32 Dev Module.

Selectati portul COM corespunzator placii dumneavoastra.

Apasati butonul Upload pentru a trimite codul pe placa. Daca incarcarea se blocheaza la mesajul Connecting, tineti apasat butonul BOOT de pe placa ESP32 pana cand porneste scrierea.(PS: Senzorul DIR are nevoie de cateva minute pentru a capta imaginea caldurii din camera)
