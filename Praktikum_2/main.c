#include <stdio.h>
#include "Zoo.h"

int main() {
    printf("Initial Zoo:\n");
    print_zoo();

    printf("\nAverage age in the zoo: %.2f\n", calculate_average_age());

    more_food();
    printf("\nAfter feeding the animals:\n");
    print_zoo();

    return 0;
}
