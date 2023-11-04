#include <stdio.h>
#include <string.h>

typedef enum { minute, stunde, tag, monat, jahr } Zeiteinheit;
 
typedef enum { Niedrig , Normal , Hoch } Prioritaet;

typedef struct {
    int day;
    int month;
    int year;
    int hour;
    int minute;
} DateTime;

typedef struct {
    unsigned int wert;
    Zeiteinheit einheit;
} Zeitspannen;

typedef struct {
    
    DateTime datum;
    Zeitspannen dauer;
    char beschreibung[100];
    Prioritaet prioritaet; 
} Termin;


Termin verschiebeTermin(Termin termin, int days) {
    Termin newOne = termin;
    newOne.datum.day += days;


  while (newOne.datum.day > 30) {
        newOne.datum.day -= 30;
        newOne.datum.month++;
    }

    while (newOne.datum.month > 12) {
        newOne.datum.month -= 12;
        newOne.datum.year++;
    }

  

    return newOne;
}

int main() {
    Termin termin = {
        .datum = {.day = 26, .month = 10, .year = 2023 , .hour = 13, .minute = 30 },
        .dauer = {.wert = 30, .einheit = minute},
        .beschreibung = "Meeting",
        .prioritaet = Hoch
    };     

    int days = 42;
    printf("Der Alte Termin: %d.%d.%d um %d:%d\n", termin.datum.day, termin.datum.month, termin.datum.year, termin.datum.hour, termin.datum.minute);
  
    Termin neueTermin =  verschiebeTermin(termin, days);

    printf("Der Neue Termin: %d.%d.%d um %d:%d\n", neueTermin.datum.day, neueTermin.datum.month, neueTermin.datum.year, neueTermin.datum.hour, neueTermin.datum.minute);

    return 0;
}
