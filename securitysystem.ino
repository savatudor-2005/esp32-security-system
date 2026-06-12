#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int PIR_PIN = 13;
const int TRIG_PIN = 12;
const int ECHO_PIN = 14;
const int BUZZER_PIN = 25;
const int BUTTON_PIN = 26;

enum StareSistem { DEZACTIVAT, ACTIVARE_IN_CURS, ACTIVAT, ALARMA };
StareSistem stareCurenta = DEZACTIVAT;

int stareButonAnterioara = HIGH;
unsigned long timpUltimaApasare = 0;
unsigned long timpInceputActivare = 0;

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  lcd.init();       
  lcd.backlight();  
  
  afiseazaMesajLCD("SISTEM PORNIT", "Asteapta...");
  delay(2000); 
}

long citesteDistanta() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long durata = pulseIn(ECHO_PIN, HIGH);
  long distanta = durata * 0.034 / 2; 
  
  if (distanta > 400 || distanta <= 0) return 999; 
  return distanta;
}

void afiseazaMesajLCD(String linia1, String linia2) {
  while(linia1.length() < 16) linia1 += " ";
  while(linia2.length() < 16) linia2 += " ";
  lcd.setCursor(0, 0); lcd.print(linia1);
  lcd.setCursor(0, 1); lcd.print(linia2);
}

void loop() {
  int citireButon = digitalRead(BUTTON_PIN);
  
  if (citireButon == LOW && stareButonAnterioara == HIGH) {
    if (millis() - timpUltimaApasare > 250) { 
      if (stareCurenta == DEZACTIVAT) {
        stareCurenta = ACTIVARE_IN_CURS;
        timpInceputActivare = millis();
      } else {
        stareCurenta = DEZACTIVAT;
        digitalWrite(BUZZER_PIN, LOW);
        lcd.backlight();
      }
      timpUltimaApasare = millis();
    }
  }
  stareButonAnterioara = citireButon;

  switch (stareCurenta) {
    
    case DEZACTIVAT: {
      afiseazaMesajLCD("STARE: DEZARMAT", "Asteptare...");
      digitalWrite(BUZZER_PIN, LOW);
      break;
    }

    case ACTIVARE_IN_CURS: {
      long timpScurs = (millis() - timpInceputActivare) / 1000;
      int timpRamas = 5 - timpScurs;
      
      String textTimp = String(timpRamas) + " SECUNDE";
      afiseazaMesajLCD("ACTIVARE IN:", textTimp);

      if (millis() % 1000 < 100) digitalWrite(BUZZER_PIN, HIGH);
      else digitalWrite(BUZZER_PIN, LOW);

      if (timpRamas <= 0) {
        stareCurenta = ACTIVAT;
        digitalWrite(BUZZER_PIN, HIGH); delay(400); digitalWrite(BUZZER_PIN, LOW); 
      }
      break;
    }

   case ACTIVAT: {
      afiseazaMesajLCD("SISTEM ARMAT", "> PAZA ACTIVA <");
      
      int miscareDetectata = digitalRead(PIR_PIN); 
      long distantaCurenta = 999;

      if (miscareDetectata == HIGH || distantaCurenta < 30) {
        stareCurenta = ALARMA;
      }
      break;
    }

    case ALARMA: {
      if (millis() % 500 < 250) {
        afiseazaMesajLCD("!!! ALARMA !!!", "INTRUS DETECTAT!");
        lcd.noBacklight(); 
      } else {
        lcd.backlight();   
      }

      if (millis() % 200 < 100) digitalWrite(BUZZER_PIN, HIGH);
      else digitalWrite(BUZZER_PIN, LOW);
      
      break;
    }
  }
}