#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int anz = 10;
int array[anz];

byte Dec[8] = {
  B01110,
  B11111,
  B01110,
  B01110,
  B00100,
  B00100,
  B01010,
  B10001
};


void setup() {
  randomSeed(analogRead(A0));

  for (int i = 0; i < anz; i++) {
    array[i] = random(0, 10);
  }
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.createChar(0, Dec);

  ausgabe();
}

void loop() {
  static bool pruef = true;
  static int pass = 0;

  if (pruef) {
    pruef = bubble_sort(pass);
    pass++;
  }
}

void animation() {
  for (int i = 15; i > 1; i--) {
    lcd.setCursor(i + 1, 1);
    lcd.print(" ");
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
    delay(200);
  }
}

bool bubble_sort(int pass) {
  bool p = false;
  for (int i = 0; i < anz - 1 - pass; i++) {
    lcd.setCursor(0, 1);
    lcd.print(array[i]);
    lcd.print(array[i + 1]);
    animation();
    //delay(1000);
    if (array[i] > array[i + 1]) {
      p = true;
      int tmp = array[i];
      array[i] = array[i + 1];
      array[i + 1] = tmp;
      lcd.setCursor(3, 1);
      lcd.print(array[i]);
      lcd.print(array[i + 1]);
      delay(700);
    }
    ausgabe();
  }
  return p;
}

void ausgabe() {
  lcd.clear();
  lcd.setCursor(0, 0);
  for (int i = 0; i < anz; i++) {
    lcd.print(array[i]);
  }
}
