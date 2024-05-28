#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "list.h"

int main() {
    setlocale(LC_ALL, "RUS");

    List* StudentList = InitList();
    if (!StudentList) {
        fprintf(stderr, "Failed to initialize StudentList\n");
        return EXIT_FAILURE;
    }

    StudentList->append(StudentList, InitStudent(23, strdup("Ksenia"), strdup("Tfgd"), strdup("???"), strdup("ghgjf4"), 4, 5, 5));
    StudentList->append(StudentList, InitStudent(14, strdup("Vaho"), strdup("Tfgd"), strdup("???"), strdup("ghgjf4"), 4, 4, 3));
    StudentList->append(StudentList, InitStudent(17, strdup("Timur"), strdup("Tfgd"), strdup("???"), strdup("ghgjf4"), 4, 3, 3));
    StudentList->append(StudentList, InitStudent(13, strdup("Tim"), strdup("Ted"), strdup("M"), strdup("ISP-test"), 5, 5, 5));

    StudentList->save(StudentList, "students.txt");

    List* LoadedStudentList = InitList();
    if (!LoadedStudentList) {
        fprintf(stderr, "Failed to initialize LoadedStudentList\n");
        StudentList->free(StudentList);
        return EXIT_FAILURE;
    }
    LoadedStudentList->load(LoadedStudentList, "students.txt");

    LoadedStudentList->print(LoadedStudentList);

    LoadedStudentList->free(LoadedStudentList);

    StudentList->saveBinary(StudentList, "students.bin");

    StudentList->free(StudentList);

    List* LoadedStudentListBinary = InitList();
    if (!LoadedStudentListBinary) {
        fprintf(stderr, "Failed to initialize LoadedStudentListBinary\n");
        return EXIT_FAILURE;
    }
    LoadedStudentListBinary->loadBinary(LoadedStudentListBinary, "students.bin");

    LoadedStudentListBinary->print(LoadedStudentListBinary);

    LoadedStudentListBinary->free(LoadedStudentListBinary);

    return 0;
}
