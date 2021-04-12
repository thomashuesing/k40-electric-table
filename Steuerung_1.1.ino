
#include <Stepper.h>
#include <SPI.h>
#include <Adafruit_SSD1306.h>

      //Fuer das Display
      #define OLED_RESET 4
      Adafruit_SSD1306 display(OLED_RESET);

//Fuer den Motor
const int stepsPerRevolution = 4000;  // Schritte die der Motor für eine Umdrehung braucht
Stepper myStepper(stepsPerRevolution, 9, 10); //step und dir pins am Arduino



//Fuer die Berechnungen
int stepCount = 0;  // Schritzähler
int umdrehung = 0;  // Drehung
int tasterstatus3=0;
int tasterstatus4=0;
int oldPosition=0;
int newPosition=0;


//Taster
const int Button1 = 2;
const int Button2 = 3;
const int Button3 = 7;
const int Button4 = 8;



void setup() {



              
              //Fuer das Display
              display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
              #define DRAW_DELAY 118
              #define D_NUM 47


              //Test Referenzfahrt
              display.clearDisplay();
              display.setTextSize(2);             //Textgroesse setzen
              display.setTextColor(WHITE);        //Textfarbe setzen
              display.setCursor(0,0);
              display.println("Referenzfahrt");
              display.display();
              int max = 100;  // ... Schritte bis Endschaltersuche aufgegeben wird
              while ( digitalRead(Button4) != HIGH ) {
              myStepper.setSpeed(25); //Setzt die Geschwindigkeit
              myStepper.step(200);
              delay(10);
              myStepper.step(-5080);
              umdrehung = 5080;



              
              //startet die Serielle Schnitstelle
              Serial.begin(9600); //Starte die Serielle übertragung

              //Fuer die Taster
              pinMode(Button3, INPUT);
              pinMode(Button4, INPUT);
              }


 


void loop() {     

              tasterstatus3=digitalRead(Button3);
              if (tasterstatus3 == HIGH)              //Verarbeitung: Wenn der taster gedrückt ist (Das Spannungssignal ist hoch)
              {
              umdrehung = umdrehung + stepCount;  
              myStepper.step(stepCount);              //Beweght den Motor mit den Werten aus stepCount
              stepCount = 0;
              }
              
              tasterstatus4=digitalRead(Button4);
              if (tasterstatus4 == HIGH)              //Verarbeitung: Wenn der taster gedrückt ist (Das Spannungssignal ist hoch)
              {  
              stepCount = umdrehung - 5080;              //Beweght den Motor mit den Werten aus stepCount
              myStepper.step(-stepCount);
              stepCount = 0;
              umdrehung = 5080;
              }

  
              //Display
              display.clearDisplay();
              display.setTextSize(1);             //Textgroesse setzen
              display.setTextColor(WHITE);        //Textfarbe setzen
              display.setCursor(0,0);             //Textstartposition einstellen
              display.println("Focusabstand");    //Text anzeigen

              //Display Text
              display.setCursor(1,8);
              display.println("Abstand");
              display.setCursor(50,8);
              display.println(stepCount);
              display.setCursor(1,16);
              display.println("Taster");
              display.setCursor(50,16);
              display.println(tasterstatus3);
              display.setCursor(80,16);
              display.println(tasterstatus4);
              display.setCursor(1,24);
              display.println(umdrehung);

              //Display löschen
              display.display();
              display.clearDisplay();
  
}
