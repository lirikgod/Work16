#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "list.h"

int main() {
    setlocale(LC_ALL, "RUS");

    List* StudentList = InitList();
    StudentList->append(StudentList, InitStudent(23, "Ksenia", "Tfgd", "???", "ghgjf4", 4, 5, 5));
    StudentList->append(StudentList, InitStudent(14, "Vaho", "Tfgd", "???", "ghgjf4", 4, 4, 3));
    StudentList->append(StudentList, InitStudent(17, "Timur", "Tfgd", "???", "ghgjf4", 4, 3, 3));
    StudentList->append(StudentList, InitStudent(13, "Tim", "Ted", "M", "ISP-test", 5, 5, 5));

    // Сохранение списка студентов в текстовый файл
    StudentList->save(StudentList, "students.txt");

    // Загрузка списка студентов из текстового файла
    List* LoadedStudentList = InitList();
    LoadedStudentList->load(LoadedStudentList, "students.txt");

    // Печать загруженного списка студентов
    LoadedStudentList->print(LoadedStudentList);

    // Очистка загруженного списка студентов
    LoadedStudentList->free(LoadedStudentList);

    // Сохранение списка студентов в бинарный файл
    StudentList->saveBinary(StudentList, "students.bin");

    // Очистка списка студентов
    StudentList->free(StudentList);

    // Загрузка списка студентов из бинарного файла
    List* LoadedStudentListBinary = InitList();
    LoadedStudentListBinary->loadBinary(LoadedStudentListBinary, "students.bin");

    // Печать загруженного списка студентов из бинарного файла
    LoadedStudentListBinary->print(LoadedStudentListBinary);

    // Очистка загруженного списка студентов из бинарного файла
    LoadedStudentListBinary->free(LoadedStudentListBinary);

    return 0;
}
