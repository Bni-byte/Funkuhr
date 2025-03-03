//Bibliotheken
#include <DCF77.h>
#include <TimeLib.h>

//Sieben-Segment-Anzeige -> Zahl Definition
//           A  B  C  D  E  F  G
char n0[] = {1, 1, 1, 1, 1, 1, 0};
char n1[] = {0, 1, 1, 0, 0, 0, 0};
char n2[] = {1, 1, 0, 1, 1, 0, 1};
char n3[] = {1, 1, 1, 1, 0, 0, 1};
char n4[] = {0, 1, 1, 0, 0, 1, 1};
char n5[] = {1, 0, 1, 1, 0, 1, 1};
char n6[] = {1, 0, 1, 1, 1, 1, 1};
char n7[] = {1, 1, 1, 0, 0, 0, 0};
char n8[] = {1, 1, 1, 1, 1, 1, 1};
char n9[] = {1, 1, 1, 1, 0, 1, 1};

char *zahlen[] = {n0, n1, n2, n3, n4, n5, n6, n7, n8, n9};
char segmente[] = {6, 9, 4, 5, 8, 7, 3, A0, A1, A2, A3, A4, A5};

//Funktion zum anzeigen von Sieben-Segment Zahlen
void zahlDefinition(int zahl, int anzeige){
  analogWrite(A0 + anzeige, 255);
  char* segmentZahlen = zahlen[zahl];

  for (int segment = 0; segment <= 6; segment++){
    digitalWrite(segmente[segment], segmentZahlen[segment]);
  }
  delay(1);
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  digitalWrite(9, 0);
  analogWrite(A0 + anzeige, 0);
}

//DCF77 Modul
#define dcfPin 2
#define dcfInterrupt digitalPinToInterrupt(dcfPin)
DCF77 DCF = DCF77(dcfPin, dcfInterrupt);
time_t aktuelleUhrzeit;


void setup() {
  // Sieben-Segment-Anzeigen
  for(int pin = 0; pin <=12; pin++){
    pinMode(segmente[pin], OUTPUT);
  }

  //Bewegungsmelder
  pinMode(10, INPUT);

  //DCF77 Modul
  DCF.Start();
}


void loop() {
  //aktuelle Uhrzeit von DCF77 Modul
  time_t neueUhrzeit = DCF.getTime();
  if (neueUhrzeit != 0) {
    setTime(neueUhrzeit);
  }

//Ziffern aktualisieren
  int stundeZehner;
  int stundeEiner;
  int minuteZehner;
  int minuteEiner;
  int sekundeZehner;
  int sekundeEiner;

  int stundeStellen = (hour() < 10) ? 1 : 2;
  int minuteStellen = (minute() < 10) ? 1 : 2;
  int sekundeStellen = (second() < 10) ? 1 : 2;

if(stundeStellen == 1){
  stundeZehner = 0;
  stundeEiner = hour();
} else{
  stundeZehner = hour() / 10;
  stundeEiner = hour() % 10;
}

if(minuteStellen == 1){
  minuteZehner = 0;
  minuteEiner = minute();
} else{
  minuteZehner = minute() / 10;
  minuteEiner = minute() % 10;
}

if(sekundeStellen == 1){
  sekundeZehner = 0;
  sekundeEiner = second();
} else{
  sekundeZehner = second() / 10;
  sekundeEiner = second() % 10;
}
  int ziffern[] = {sekundeEiner, sekundeZehner, minuteEiner, minuteZehner, stundeEiner, stundeZehner};


//Ziffern ausgeben
  int bewegung = digitalRead(10);
  if(bewegung == 1){      //Bewegungsmelder
    for (int anzeigen = 0; anzeigen < 6; anzeigen++){
        zahlDefinition(ziffern[anzeigen], anzeigen);  //Zahl anzeigen
    }
  }
  else{
    for(int digital = 0; digital <=6; digital++){
      digitalWrite(segmente[digital], 0);
    }
    for(int analog = 7; analog <=12; analog++){
      analogWrite(segmente[analog], 0);
    }
  }
}
