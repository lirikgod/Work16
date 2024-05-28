#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

List* InitList() {
    List* list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->append = (void (*)(void *, void *)) Append;
    list->print = (void (*)(void *)) PrintList;
    list->free = (void (*)(void *)) FreeList;
    list->printE = (void (*)(void *)) PrintExcellentFemaleStudents;
    list->printEtwo = (void (*)(void *)) PrintExcellentStudentsWithoutTwos;
    list->save = (void (*)(void*, const char*)) SaveListToFile;
    list->load = (void (*)(void*, const char*)) LoadListFromFile;
    list->saveBinary = (void (*)(void*, const char*)) SaveListToBinaryFile;
    list->loadBinary = (void (*)(void*, const char*)) LoadListFromBinaryFile;
    return list;
}

void* Append(void* list, void* student) {
    List* l = (List*)list;
    Student* s = (Student*)student;
    Node* newNode = malloc(sizeof(Node));
    newNode->student = s;
    newNode->next = NULL;

    if (l->size == 0) {
        l->head = newNode;
        l->tail = l->head;
    } else {
        l->tail->next = newNode;
        l->tail = newNode;
    }
    l->size++;
    return NULL;
}

void* PrintExcellentFemaleStudents(void* list) {
    List* l = (List*)list;
    Node* current = l->head;
    while (current != NULL) {
        if (strcmp(current->student->gender, "???") == 0 &&
            current->student->physicGrade == 5 &&
            current->student->chemistryGrade == 5) {
            printf("Name: %s %s\n", current->student->name, current->student->surname);
            printf("Group: %s\n", current->student->group);
            printf("Age: %d\n", current->student->age);
            printf("Math Grade: %d\n", current->student->mathGrade);
            printf("Physic Grade: %d\n", current->student->physicGrade);
            printf("Chemistry Grade: %d\n\n", current->student->chemistryGrade);
        }
        current = current->next;
    }
    return NULL;
}

void* PrintExcellentStudentsWithoutTwos(void* list) {
    List* l = (List*)list;
    Node* current = l->head;
    while (current != NULL) {
        if (current->student->mathGrade != 2 &&
            current->student->physicGrade != 2 &&
            current->student->chemistryGrade != 2) {
            printf("Name: %s %s\n", current->student->name, current->student->surname);
            printf("Group: %s\n", current->student->group);
            printf("Age: %d\n", current->student->age);
            printf("Math Grade: %d\n", current->student->mathGrade);
            printf("Physic Grade: %d\n", current->student->physicGrade);
            printf("Chemistry Grade: %d\n\n", current->student->chemistryGrade);
        }
        current = current->next;
    }
    return NULL;
}

void* PrintList(void* list) {
    List* l = (List*)list;
    Node* current = l->head;
    while (current != NULL) {
        printf("%s - %d\n", current->student->name, current->student->physicGrade);
        current = current->next;
    }
    return NULL;
}

void* FreeList(void* list) {
    List* l = (List*)list;
    Node* current = l->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp->student->name);
        free(temp->student->surname);
        free(temp->student->gender);
        free(temp->student->group);
        free(temp->student);
        free(temp);
    }
    free(l);
    return NULL;
}

void SaveListToFile(void* list, const char* filename) {
    List* l = (List*)list;
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    Node* current = l->head;
    while (current != NULL) {
        Student* s = current->student;
        fprintf(file, "%d,%s,%s,%s,%s,%d,%d,%d\n", s->age, s->name, s->surname, s->gender, s->group, s->mathGrade, s->physicGrade, s->chemistryGrade);
        current = current->next;
    }
    fclose(file);
    printf("Data successfully saved to %s\n", filename);
}

void LoadListFromFile(void* list, const char* filename) {
    List* l = (List*)list;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int age, mathGrade, physicGrade, chemistryGrade;
        char name[50], surname[50], gender[10], group[50];

        sscanf(line, "%d,%49[^,],%49[^,],%9[^,],%49[^,],%d,%d,%d", &age, name, surname, gender, group, &mathGrade, &physicGrade, &chemistryGrade);

        Student* student = InitStudent(age, strdup(name), strdup(surname), strdup(gender), strdup(group), mathGrade, physicGrade, chemistryGrade);
        l->append(l, student);
    }
    fclose(file);
    printf("Data successfully loaded from %s\n", filename);
}

void SaveListToBinaryFile(void* list, const char* filename) {
    List* l = (List*)list;
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    Node* current = l->head;
    while (current != NULL) {
        Student* s = current->student;
        fwrite(&(s->age), sizeof(int), 1, file);
        fwrite(s->name, sizeof(char), 50, file);
        fwrite(s->surname, sizeof(char), 50, file);
        fwrite(s->gender, sizeof(char), 10, file);
        fwrite(s->group, sizeof(char), 50, file);
        fwrite(&(s->mathGrade), sizeof(int), 1, file);
        fwrite(&(s->physicGrade), sizeof(int), 1, file);
        fwrite(&(s->chemistryGrade), sizeof(int), 1, file);
        current = current->next;
    }
    fclose(file);
    printf("Data successfully saved to %s\n", filename);
}

void LoadListFromBinaryFile(void* list, const char* filename) {
    List* l = (List*)list;
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    while (!feof(file)) {
        int age, mathGrade, physicGrade, chemistryGrade;
        char name[50], surname[50], gender[10], group[50];

        fread(&age, sizeof(int), 1, file);
        fread(name, sizeof(char), 50, file);
        fread(surname, sizeof(char), 50, file);
        fread(gender, sizeof(char), 10, file);
        fread(group, sizeof(char), 50, file);
        fread(&mathGrade, sizeof(int), 1, file);
        fread(&physicGrade, sizeof(int), 1, file);
        fread(&chemistryGrade, sizeof(int), 1, file);

        if (feof(file)) break;

        Student* student = InitStudent(age, strdup(name), strdup(surname), strdup(gender), strdup(group), mathGrade, physicGrade, chemistryGrade);
        l->append(l, student);
    }
    fclose(file);
    printf("Data successfully loaded from %s\n", filename);
}
