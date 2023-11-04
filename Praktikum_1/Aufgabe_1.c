#include <stdio.h>
#include <math.h>

int main() {
    
   var1_For();
   var2_While();
    
    return 0;
}

void var1_For(){
 
 for(int i = 0; i <= 360; i += 10){
        float bogenmass = (2 * M_PI * i) /360;
        float sinfw = sin(bogenmass);
        printf("Winkel:  %d Grad => Sinus-Funktionswert: %.3f",i, sinfw);
        printf("\n");
    }

}

void var2_While(){
 int number = 0;
    while (number >= 0 && number <= 360) {
        float radian = number * M_PI / 180.0;
        float sinfw = sin(radian);

        
        printf("Winkel:  %d Grad => Sinus-Funktionswert: %.3f\n", number, sinfw);
         
        number += 10;

  }
}




