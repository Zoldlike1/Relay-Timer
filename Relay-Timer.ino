#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED-näytön leveys pikseleinä
#define SCREEN_HEIGHT 64 // OLED-näytön korkeus pikseleinä
#define OLED_RESET -1    // Nollauspinni # (tai -1, jos käytetään Arduinon nollauspinniä)
#define SCREEN_ADDRESS 0x3C ///< Katso ohjetta osoitteelle; 0x3D 128x64-näytölle, 0x3C 128x32-näytölle
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int aikasec = 0;  // Aika sekunteina
int aikamin = 0;  // Aika minuutteina
int sc = 0; // Näytön säästäjä


void setup() {
  pinMode(7, INPUT_PULLUP);  // Määritä pinni 7 sisääntuloksi ja käytä siihen vedä ylös -vastusta
  pinMode(5, OUTPUT);        // Määritä pinni 5 ulostuloksi
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306:n varaus epäonnistui"));
    for (;;); // Keskeytä, älä jatka, toista loputtomiin
  }
  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(12, 0);
  display.println("Time Left");  // Näytä "Jäljellä" OLED-näytöllä
  display.setTextSize(3);
  display.setCursor(20, 30);
  display.println("00:00");  // Näytä aluksi "00:00" aikaa OLED-näytöllä
  display.display();;
}

void piirros() {
  delay(100);
  if ((aikasec + aikamin) == 0) {
    nolla();
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(12, 0);
  display.println("Time Left");  // Näytä "Jäljellä" OLED-näytöllä
  display.setCursor(20, 30);
  display.setTextSize(3);
  display.setTextColor(WHITE, BLACK);
  display.println(String(aikamin) + ":" + String(aikasec));  // Näytä aika OLED-näytöllä
  display.display();
}

void nolla() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(12, 0);
  display.println("Time Left");  // Näytä "Jäljellä" OLED-näytöllä
  display.setTextSize(3);
  display.setCursor(20, 30);
  display.println("00:00");  // Näytä "00:00" OLED-näytöllä kun aika on nolla
  display.display();
  digitalWrite(5, HIGH);
}

void loop() {
  if (digitalRead(7) == LOW) {
    aikamin += 15;  // Lisää aikaa 15 minuuttia, kun painiketta painetaan
    if (aikamin > 60) {
      aikamin = 0;
      aikasec = 0;
      nolla();  // Nollaa näyttö, kun aika on yli 60 minuuttia
    }
    piirros();  // Päivitä näyttö
  }
  
  if (aikamin > 0 || aikasec > 0) {
    if (aikasec <= 0) {
      if (aikamin > 0) {
        aikamin -= 1;
        aikasec = 59;
        piirros();  // Päivitä näyttö, kun aika vähenee
        digitalWrite(5, LOW);
      }
    }
    aikasec -= 1;
    piirros();  // Päivitä näyttö
  }
  else {
    digitalWrite(5, HIGH);  // Sammuta rele, kun aika on nolla
  }
  if((aikasec+aikamin)==0){
    sc += 1;
  } else {
    sc = 0;
  }

  while(sc >= 30) {
    display.clearDisplay();
    display.display();
    if (digitalRead(7) == LOW) {
    aikamin += 15;  // Lisää aikaa 15 minuuttia, kun painiketta painetaan
    }
    if((aikamin+aikasec) != 0) {
      sc = 0;
    }
  }
  delay(1000);
}