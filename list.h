#ifndef LIST_H
#define LIST_H

typedef struct Student {
    int age;
    char* name;
    char* surname;
    char* gender;
    char* group;
    int mathGrade;
    int physicGrade;
    int chemistryGrade;
} Student;

typedef struct Node {
    Student* student;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
    int size;
    void (*append)(void*, void*);
    void (*print)(void*);
    void (*free)(void*);
    void (*printE)(void*);
    void (*printEtwo)(void*);
    void (*save)(void*, const char*);
    void (*load)(void*, const char*);
    void (*saveBinary)(void*, const char*);
    void (*loadBinary)(void*, const char*);
} List;

List* InitList();
Student* InitStudent(int age, char* name, char* surname, char* gender, char* group, int mathGrade, int physicGrade, int chemistryGrade);

void* Append(void* list, void* student);
void* PrintExcellentFemaleStudents(void* list);
void* PrintExcellentStudentsWithoutTwos(void* list);
void* PrintList(void* list);
void* FreeList(void* list);
void SaveListToFile(void* list, const char* filename);
void LoadListFromFile(void* list, const char* filename);
void SaveListToBinaryFile(void* list, const char* filename);
void LoadListFromBinaryFile(void* list, const char* filename);

#endif // LIST_H
