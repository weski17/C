#ifndef LIST_H
#define LIST_H

typedef enum {
    IFM,
    ELM
} subject;

typedef struct Student {
    char name[50];
    subject enrolled;
    int cps;
} Student;

typedef struct node {
    Student* student;
    struct node* next;
    struct node* prev;
} node, *node_p;

Student* createStudent(char name[50], subject sub, int cps);
void addToList(node_p* head, Student* student, int* counter);
void removeNode(node_p* head, node_p node_to_remove, int delete_student, int* counter);
void deleteList(node_p* head, int delete_students, int* counter);
node_p filterStudentsBySubject(node_p head, subject enrolled, int* filteredCounter);
#endif