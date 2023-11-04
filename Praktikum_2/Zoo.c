#include <stdio.h>
#include "Zoo.h"

animal zoo[ANIMALCOUNT] = {
    {MAMMAL, "Elephant", 20, 500.0},
    {FISH, "Goldfish", 1, 0.2},
    {BIRD, "Eagle", 5, 0.3},
    {AMPHIBIAN, "Frog", 2, 0.1}
};

float calculate_average_age() {
    unsigned int total_age = 0;
    for (int i = 0; i < ANIMALCOUNT; i++) {
        total_age += zoo[i].age;
    }
    return (float)total_age / ANIMALCOUNT;
}

void more_food() {
    float food_increase_arr[] = {0.10f, 0.04f, 0.01f, 0.02f, 0.0f};
    for (int i = 0; i < ANIMALCOUNT; i++) {
        int index = zoo[i].species;
        zoo[i].food_weight *= (1 + food_increase_arr[index]);
    }
}

void print_animal(animal a) {
    const char* species_names[] = {"MAMMAL", "FISH", "BIRD", "AMPHIBIAN", "REPTILES"};
    printf("| %-10s | %-20s | %-4d | %.2f kg |\n", species_names[a.species], a.name, a.age, a.food_weight);
}

void print_zoo() {
    printf("| %-10s | %-20s | %-4s | %s |\n", "Species", "Name", "Age", "Food Weight");
    for (int i = 0; i < ANIMALCOUNT; i++) {
        if (zoo[i].species != 0) {
            print_animal(zoo[i]);
        }
    }
}
