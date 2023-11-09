#include "student_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// To create a new Student with the given data
Student* createStudent(char name[50], subject sub, int cps) {
    Student* student = (Student*)malloc(sizeof(Student));
    if (!student) {
        perror("Failed to allocate student");
        exit(EXIT_FAILURE);
    }
    strcpy(student->name, name);
    student->enrolled = sub;
    student->cps = cps;
    return student;
}
// To add a Student to the List
void addToList(node_p* head, Student* student, int* counter) {
    node_p new_node = (node_p)malloc(sizeof(node));
    if (!new_node) {
        perror("Failed to allocate new node");
        exit(EXIT_FAILURE);
    }
    new_node->student = student;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        node_p current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
    }
    (*counter)++;
}

node_p filterStudentsBySubject(node_p head, subject enrolled, int* filteredCounter) {
    node_p filteredHead = NULL;
    node_p current = head;
    while (current != NULL) {
        if (current->student->enrolled == enrolled) {
            addToList(&filteredHead, current->student, filteredCounter);
        }
        current = current->next;
    }
    return filteredHead;
}

void removeNode(node_p* head, node_p node_to_remove, int delete_student, int* counter) {
    //Leere Liste
    if (node_to_remove == NULL) {
        return; 
    }

    // Verbindungen zum vorherigen und nächsten Knoten aufheben
    if (node_to_remove->prev) {
        node_to_remove->prev->next = node_to_remove->next;
    } else {
        *head = node_to_remove->next; // Aktualisiere den Kopf der Liste
    }

    if (node_to_remove->next) {
        node_to_remove->next->prev = node_to_remove->prev;
    }

    // Wenn delete_student wahr ist, lösche den Studenten
    if (delete_student) {
        free(node_to_remove->student);
    }

    // Lösche den Knoten selbst
    free(node_to_remove);
    (*counter)--;
}
void deleteList(node_p* head, int delete_students, int* counter) {
    node_p current = *head;
    while (current != NULL) {
        node_p next = current->next;
        removeNode(head, current, delete_students, counter);
        current = next;
    }
    *head = NULL; // Setze den Kopf der Liste auf NULL
}
