#include <stdio.h>
#include <stdlib.h>
#include "list.h"



Student* InitStudent(int age, char* name, char* surname, char* gender, char* group, int mathGrade, int physicGrade, int chemistryGrade) {
    Student* student = malloc(sizeof(Student));
    student->age = age;
    student->name = strdup(name);
    student->surname = strdup(surname);
    student->gender = strdup(gender);
    student->group = strdup(group);
    student->mathGrade = mathGrade;
    student->physicGrade = physicGrade;
    student->chemistryGrade = chemistryGrade;
    return student;
}
