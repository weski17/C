#include "student_list.h"
#include <stdio.h>

 
int main() {
    int counter = 0;
    node_p head = NULL;

    addToList(&head, createStudent("Alice", IFM, 394), &counter);
    addToList(&head, createStudent("Bob", ELM, 8), &counter);
    addToList(&head, createStudent("Charlie", IFM, 10), &counter);

    printf("Anzahl der Studierenden in der Hauptliste: %d\n", counter);

    // Filtere die Liste nach einem bestimmten Studiengang
    int filteredCounter = 0;
    node_p ifmList = filterStudentsBySubject(head, IFM, &filteredCounter);
    printf("Anzahl der IFM-Studierenden in der gefilterten Liste: %d\n", filteredCounter);

    // Lösche die gefilterte Liste
    deleteList(&ifmList, 0, &filteredCounter);
    printf("Gefilterte Liste gelöscht. Anzahl der Knoten: %d\n", filteredCounter);

    // Lösche die Hauptliste 
    deleteList(&head, 1, &counter);
    printf("Hauptliste gelöscht. Anzahl der Knoten: %d\n", counter);

    return 0;
}