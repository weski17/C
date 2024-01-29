#include "stack.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Stack<std::string, 10> s1;
    s1.push("Sa"); 
    cout << s1.isEmpty() << endl; 

    int i = 2;
    int *iptr = &i;

    int *w;
    w =(int *) malloc(sizeof(*w));
    if(!w){
     return -1;
    }else{
        *w = 22;
        printf("%d",*w);
    free(w);
    }


    return EXIT_SUCCESS;
}
