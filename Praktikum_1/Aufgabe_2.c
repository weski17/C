#include <stdio.h>


void ausgabe1(int zahl){

printf("Ausgabe 1:\n");

for(int i = 0 ; i < zahl; i++){
    printf("*");
 }
}

void ausgabe2(int zahl){

printf("\nAusgabe 2:\n");

 for(int i = 0; i <= zahl; i++){
    for (int j = 0; j < i; j++){
    printf("*");
    }
    printf("\n");
    }
    
  printf("\n");

}

void ausgabe3(int zahl){

if (zahl % 2 == 1) {
 printf("\nAusgabe 3:\n");

    for (int i = 1; i <= zahl; i += 2) {
        for (int j = 0; j < (zahl - i) / 2; j++) {
            printf(" ");
            // To generate spaces
        }
        for (int k = 0; k < i; k++) {
            printf("*");
        }
        printf("\n");
      }
    }
else {
    printf(" Die Zahl muss ungerade sein \n");
}    

}


int main (){

int zahl;
printf("Geben Sie eine Zahl ein\n");
scanf("%d",&zahl);


ausgabe1(zahl);
ausgabe2(zahl);
ausgabe3(zahl);

return 0;
}