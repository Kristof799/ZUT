
/*Autorzy:
Krzysztof Czerniak 41960
Grzegorz Gaworecki 41968
 Patryk Wisniewski 42029
 Grupa L2, AiR sem 4.2019 */
 
// Czesc, ktora trzeba wpisac w arduino
 
 
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
 
#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
 
#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
 
#define X_MAX_PIN          2
#define Y_MAX_PIN          15
#define Z_MAX_PIN          19
 
 
int krok1 = 0;
int krok2 = 0;
int krok3 = 0;
int kierunek1 = 0;
int kierunek2 = 0;
int kierunek3 = 0;
void setup() {
 
  // put your setup code here, to run once:
  Serial.begin(115200);
 
  //SILNIK X
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_PIN, INPUT_PULLUP);
  digitalWrite(X_DIR_PIN, HIGH);
  digitalWrite(X_ENABLE_PIN, LOW);
 
  //SILNIK Y
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  digitalWrite(Y_DIR_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, LOW);
 
  //SILNIK Z
  pinMode(Z_ENABLE_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  digitalWrite(Z_DIR_PIN, HIGH);
  digitalWrite(Z_ENABLE_PIN, LOW);
 
}
int krok = 0;
int kierunek = 1;
String a;
int flaga=0;
 
void loop() {
  // put your main code here, to run repeatedly:
 
  /*krok=krok+1;
    if(krok==500)
    {
    kierunek=!kierunek;
    digitalWrite(X_DIR_PIN, kierunek);
    digitalWrite(Y_DIR_PIN, kierunek);
    digitalWrite(Z_DIR_PIN, kierunek);
    krok=0;
    Serial.println("Zmiana Kierunku: \n");
    Serial.print(kierunek);
    Serial.println("\n");
    } */
  if (((digitalRead(X_MAX_PIN) == 0 && kierunek1 == 0) || kierunek1 == 1) && krok1 > 0) //silnik 1  krancowki
  {
    if (krok1 > 0) {
      digitalWrite(X_STEP_PIN, HIGH);
      krok1--;
    }
    //digitalWrite(X_STEP_PIN,HIGH);
  }
  if (((digitalRead(Y_MAX_PIN) == 0 && kierunek2 == 0) || kierunek2 == 1) && krok2 > 0) //silnik 2  krancowka
  {
    if (krok2 > 0) {
      digitalWrite(Y_STEP_PIN, HIGH);
      krok2--;
    }
    //digitalWrite(Y_STEP_PIN,HIGH);
  }
  if (((digitalRead(Z_MAX_PIN) == 0 && kierunek3 == 0) || kierunek3 == 1) && krok3 > 0) //silnik 3  krancowka
  {
    if (krok3 > 0) {
      digitalWrite(Z_STEP_PIN, HIGH);
      krok3--;
    }
    // digitalWrite(Z_STEP_PIN,HIGH);
  }
  delay(1);
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  delay(1);
  //Ponizej jest poprawiona komunikacja
  while (Serial.available())
  {
    a = Serial.readStringUntil('\n');
    sscanf(a.c_str(), "a %d b %d c %d", &krok1, &krok2, &krok3); // to co w konsoli ze zwrocic
    flaga=1;
    if (krok1 < 0) // minusy silniku 1
    {
      kierunek1 = 1;
      digitalWrite(X_DIR_PIN, kierunek1);
      krok1 = -krok1; 
 
    } else
    {
      kierunek1 = 0;
      digitalWrite(X_DIR_PIN, kierunek1);
    }
    if (krok2 < 0) // minusy na silniku 2
    {
      kierunek2 = 1;
      digitalWrite(Y_DIR_PIN, kierunek2);
      krok2 = -krok2;
 
    } else
    {
      kierunek2 = 0;
      digitalWrite(Y_DIR_PIN, kierunek2);
    }
    if (krok3 < 0) //minusy na silniku 3
    {
      kierunek3 = 1;
      digitalWrite(Z_DIR_PIN, kierunek3);
      krok3 = -krok3;
 
    } else
    {
      kierunek3 = 0;
      digitalWrite(Z_DIR_PIN, kierunek3);
    }
   // Serial.println("Kroki silnika 1");
    //Serial.println(krok1);
//    Serial.println("*********");
//    Serial.println("Kroki silnika 2");
//    Serial.println(krok2);
//    Serial.println("*********");
//    Serial.println("Kroki silnika 3");
//    Serial.println(krok3);
//    Serial.println("*********");
    
  } // koniec komunikacji - Serial.available()
  if(krok1==0 && krok2==0 && krok3==0 && flaga==1) {
    Serial.println("ok");
    flaga=0;
    }
    
}
 
 
 
// czesc, ktora trzeba wpisac w MatLab
 
 
krokia=0; krokib=0; krokic=0; stare_a=0; stare_b=0; stare_c=0;
for t=0:0.01:2*pi
    a=round(800*sin(t));
    b=round(800*sin(t+2*pi/3));
    c=round(800*sin(t+4*pi/3));
    
    krokia=a-stare_a;
    krokib=b-stare_b;
    krokic=c-stare_c;
    
    
    fprintf(drukarka, 'a %d b %d c %d \n' , [krokia, krokib, krokic ]);
    stare_a=a;
    stare_b=b;
    stare_c=c;
    while(drukarka.BytesAvailable==0)
        
    end
    while(drukarka.BytesAvailable>0)
       
        fscanf(drukarka);
    end
end
   
 
 
//Sterowanie temperatura. Zapozyczone od Erka Skrentnego, L2
 
#include <LiquidCrystal.h> 
#define A -7.06838854583390e-07
#define B 0.00122952244207904 
#define C -0.771196628876736 
#define D 262.628380344557
LiquidCrystal lcd(16,17,23,25,27,29); 
int i=0; 
int temperatura=0;
double y,x; 
void setup()
{ lcd.begin(20,4); pinMode(10,OUTPUT);
} void loop() { temperatura=analogRead(13); 
x=double(temperatura);
y=(A*pow(x,3))+(B*(pow(x,2)))+ (C*x) +D;
 lcd.setCursor(0,0); /*pierwsza linia*/ 
 lcd.print(y); 
 lcd.setCursor(0,2); 
 lcd.print("grzesiu pedal"); 
 lcd.setCursor(0,3); 
 lcd.print("Kalciatore"); 
if(i<50) { i++; digitalWrite(10,1); } else { digitalWrite(10,0); } delay(100); }
