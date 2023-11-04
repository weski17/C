#ifndef ZOO_H
#define ZOO_H

#define ANIMALCOUNT 10

typedef enum {
    MAMMAL,
    FISH,
    BIRD,
    AMPHIBIAN,
    REPTILES
} viech;

typedef struct {
    viech species;
    char name[50];
    unsigned int age;
    float food_weight;
} animal;

float calculate_average_age();
void more_food();
void print_animal(animal a);
void print_zoo();

#endif
