#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Monoblocks {
    char fabricator[10];
    char OS[10];
    int RAM;
    char CPU[20];
    float screenDiagonal;
} monoblock_t;

monoblock_t* fill_monoblocks(monoblock_t* monoblocks, int size) {
    for (int i = 0; i < size; i++) {
        printf("Производитель моноблока: ");
        scanf("%9s", monoblocks[i].fabricator);
        getchar();

        printf("Операционная система: ");
        scanf("%9s", monoblocks[i].OS);
        getchar();

        printf("Операционная память(в Гб): ");
        scanf("%d", &monoblocks[i].RAM);
        getchar();

        printf("Модель процессора: ");
        fgets(monoblocks[i].CPU, sizeof(monoblocks[i].CPU), stdin);
        monoblocks[i].CPU[strcspn(monoblocks[i].CPU, "\n")] = 0;

        printf("Диагональ экрана(в дюймах): ");
        scanf("%f", &monoblocks[i].screenDiagonal);
        getchar();
        printf("\n");
    }
    return monoblocks;
}

void print_monoblock(monoblock_t monoblocks) {
    printf("Производитель моноблока: %s\n", monoblocks.fabricator);
    printf("Операционная система: %s\n", monoblocks.OS);
    printf("Операционная память(в Гб): %d\n", monoblocks.RAM);
    printf("Модель процессора: %s\n", monoblocks.CPU);
    printf("Диагональ экрана(в дюймах): %f\n", monoblocks.screenDiagonal);
    printf("\n");
}

int* search_monoblock(monoblock_t* monoblocks, int SIZE, char* OS, int RAM) {
    int* countOfSeeked = malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        countOfSeeked[i] = -1;
    }
    if (OS[0] != '\0' && RAM != -1) {
        for (int i = 0; i < SIZE; i++) {
            if (strcmp(monoblocks[i].OS, OS) == 0 && monoblocks[i].RAM == RAM) countOfSeeked[i] = i;
        }
    }
    else if (OS[0] != '\0' && RAM == -1) {
        for (int i = 0; i < SIZE; i++) {
            if (strcmp(monoblocks[i].OS, OS) == 0) countOfSeeked[i] = i;
        }
    }
    else {
        for (int i = 0; i < SIZE; i++) {
            if (monoblocks[i].RAM == RAM) countOfSeeked[i] = i;
        }
    }
    return countOfSeeked;
}

int compare_fabricator(const void* a, const void* b) {
    const monoblock_t* monoblock1 = (const monoblock_t*)a;
    const monoblock_t* monoblocks2 = (const monoblock_t*)b;
    return strcmp(monoblock1->fabricator, monoblocks2->fabricator);
}

int compare_CPU(const void* a, const void* b) {
    const monoblock_t* monoblock1 = (const monoblock_t*)a;
    const monoblock_t* monoblock2 = (const monoblock_t*)b;
    return strcmp(monoblock1->CPU, monoblock2->CPU);
}

monoblock_t* sort_monoblocks(monoblock_t* monoblocks, int size, int criteria) {
    if (criteria == 1) {
        qsort(monoblocks, size, sizeof(monoblock_t), compare_fabricator);
    }
    else if (criteria == 2) {
        qsort(monoblocks, size, sizeof(monoblock_t), compare_CPU);
    }
    else if (criteria == 3) {
        qsort(monoblocks, size, sizeof(monoblock_t), compare_fabricator);
        qsort(monoblocks, size, sizeof(monoblock_t), compare_CPU);
    }
    else {
        printf("Ошибка: Неверный критерий сортировки\n");
    }
    return monoblocks;
}

char* WriteFile(monoblock_t* monoblocks, int size) {
    FILE* fp = fopen("kursproject.txt", "w");
    if (fp == NULL) {
        return "Ошибка при открытии файла для записи";
    }

    for (int i = 0; i < size; i++) {
        if (fprintf(fp, "Производитель моноблока: %s\n", monoblocks[i].fabricator) < 0 ||
            fprintf(fp, "Операционная система: %s\n", monoblocks[i].OS) < 0 ||
            fprintf(fp, "Операционная память(в Гб): %d\n", monoblocks[i].RAM) < 0 ||
            fprintf(fp, "Модель процессора: %s\n", monoblocks[i].CPU) < 0 ||
            fprintf(fp, "Диагональ экрана(в дюймах): %f\n\n", monoblocks[i].screenDiagonal) < 0) {
            fclose(fp);
            return "Ошибка при записи данных в файл";
        }
    }

    fclose(fp);
    return NULL;
}

char* ReadFile(monoblock_t* monoblocks, int size) {
    FILE* fp = fopen("kursproject.txt", "r");
    if (fp == NULL) {
        return "Не удалось открыть файл";
    }


    for (int i = 0; i < size; i++) {
        if (fscanf(fp, "Производитель моноблока: %9s\n", monoblocks[i].fabricator) != 1 ||
            fscanf(fp, "Операционная система: %9s\n", monoblocks[i].OS) != 1 ||
            fscanf(fp, "Операционная память(в Гб): %d\n", &monoblocks[i].RAM) != 1 ||
            fscanf(fp, "Модель процессора: %19[^\n]\n", monoblocks[i].CPU) != 1 ||
            fscanf(fp, "Диагональ экрана(в дюймах): %f\n\n", &monoblocks[i].screenDiagonal) != 1)
        {
            fclose(fp);
            return "Ошибка при чтении данных из файла";
        }
    }

    fclose(fp);
    return NULL;
}

monoblock_t* AddChangeNotes(monoblock_t* monoblocks, int num) {
    printf("Производитель моноблока: ");
    scanf("%9s", monoblocks[num].fabricator);
    getchar();

    printf("Операционная система: ");
    scanf("%9s", monoblocks[num].OS);
    getchar();

    printf("Операционная память(в Гб): ");
    scanf("%d", &monoblocks[num].RAM);
    getchar();

    printf("Модель процессора: ");
    fgets(monoblocks[num].CPU, sizeof(monoblocks[num].CPU), stdin);
    monoblocks[num].CPU[strcspn(monoblocks[num].CPU, "\n")] = 0;

    printf("Диагональ экрана(в дюймах): ");
    scanf("%f", &monoblocks[num].screenDiagonal);
    getchar();
    printf("\n");
    return monoblocks;
}

monoblock_t* DeleteNotes(monoblock_t* monoblocks, int num, int SIZE)
{
    int n = num - 1;
    int size = SIZE - 1;
    monoblock_t* temp = malloc(size * sizeof(monoblock_t));
    if (temp == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }
    for (int i = 0; i < SIZE; i++) {
        if (i < n) {
            temp[i] = monoblocks[i];
        }
        else if (i > n) {
            temp[i - 1] = monoblocks[i];
        }
    }
    monoblocks = realloc(monoblocks, size * sizeof(monoblock_t));
    for (int i = 0; i < size; i++) {
        monoblocks[i] = temp[i];
    }
    return monoblocks;
}

void main() {
    setlocale(LC_ALL, "Rus");
    int SIZE = 0;

    printf("Введите количество записей: ");
    scanf("%d", &SIZE);
    int* countOfSeeked = malloc(SIZE * sizeof(int));
    monoblock_t* monoblocks = malloc(SIZE * sizeof(monoblock_t));
    monoblock_t* temp;
    int num = 0;
    char searchOS[20];
    char* error = NULL;
    int a = 1;
    while (a) {
        ReadFile(monoblocks, SIZE);
        printf("**********************************************\n");
        printf("*                     Menu                   *\n");
        printf("**********************************************\n");
        printf("* 1. Создать запись файла.                   *\n");
        printf("* 2. Выполнить поиск по файлу.               *\n");
        printf("* 3. Запись и чтение файла.                  *\n");
        printf("* 4. Сортировка данных файлов.               *\n");
        printf("* 5. Завершить работу.                       *\n");
        printf("**********************************************\n");
        scanf("%d", &num);
        switch (num) {
        case 1:
            num = 0;
            fill_monoblocks(monoblocks, SIZE);
            error = WriteFile(monoblocks, SIZE);
            if (error) {
                printf("Ошибка: %s\n", error);
            }
            else {
                printf("Файл успешно записан\n");
            }
            break;
        case 2:
            num = 0;
            error = ReadFile(monoblocks, SIZE);
            if (error) {
                printf("Ошибка: %s\n", error);
                break;
            }
            int searchRAM;
            printf("**********************************************\n");
            printf("*                    Поиск по                *\n");
            printf("**********************************************\n");
            printf("* 1. Операционная система.                   *\n");
            printf("* 2. Оперативная память.                     *\n");
            printf("* 3. Процессор и операционная память.        *\n");
            printf("* 4. Вернуться в меню.                       *\n");
            printf("**********************************************\n");
            scanf("%d", &num);
            switch (num) {
            case 1:
                printf("Введите название операционной системы: ");
                getchar();
                fgets(searchOS, sizeof(searchOS), stdin);
                searchOS[strcspn(searchOS, "\n")] = 0;
                searchRAM = -1;
                break;
            case 2:
                printf("Введите объем операционной системы: ");
                scanf("%d", &searchRAM);
                searchOS[0] = '\0';
                break;
            case 3:
                getchar();
                printf("Введите название операционной системы: ");
                fgets(searchOS, sizeof(searchOS), stdin);
                searchOS[strcspn(searchOS, "\n")] = 0;
                printf("Введите объем операционной системы: ");
                scanf("%d", &searchRAM);
                break;
            case 4:
                break;
            }
            countOfSeeked = search_monoblock(monoblocks, SIZE, searchOS, searchRAM);
            for (int i = 0; i < SIZE; i++) {
                if (countOfSeeked[i] != -1) print_monoblock(monoblocks[i]);
            }
            break;
        case 3:
            num = 0;
            printf("**********************************************\n");
            printf("*             Запись и чтение файла          *\n");
            printf("**********************************************\n");
            printf("* 1. Добавить запись.                        *\n");
            printf("* 2. Изменить записи.                        *\n");
            printf("* 3. Удалить записи.                         *\n");
            printf("* 4. Чтение файла.                           *\n");
            printf("* 5. Вернуться в меню.                       *\n");
            printf("**********************************************\n");
            scanf("%d", &num);
            switch (num) {
            case 1:
                error = ReadFile(monoblocks, SIZE);
                if (error) {
                    printf("Ошибка: %s\n", error);
                    break;
                }
                printf("Введите количество записей для добавления: ");
                num = 0;
                scanf("%d", &num);
                SIZE += num;
                temp = malloc(SIZE * sizeof(monoblock_t));
                if (temp == NULL) {
                    printf("Ошибка выделения памяти\n");
                    continue;

                }
                for (int i = 0; i < SIZE - num; i++) {
                    temp[i] = monoblocks[i];
                }
                for (int i = SIZE - num; i < SIZE; i++)
                {
                    AddChangeNotes(temp, i);
                }
                monoblocks = malloc(SIZE * sizeof(monoblock_t));
                for (int i = 0; i < SIZE; i++) {
                    monoblocks[i] = temp[i];
                }
                error = WriteFile(monoblocks, SIZE);
                if (error) {
                    printf("Ошибка: %s\n", error);
                }
                else {
                    printf("Запись добавлена и файл обновлен¸í\n");
                }
                break;
            case 2:
                error = ReadFile(monoblocks, SIZE);
                if (error) {
                    printf("Ошибка: %s\n", error);
                    break;
                }
                num = 0;
                printf("Введите номер записи (%d) для ее изменения:", SIZE);
                scanf("%d", &num);
                AddChangeNotes(monoblocks, num - 1);
                error = WriteFile(monoblocks, SIZE);
                if (error) {
                    printf("Ошибка: %s\n", error);
                }
                else {
                    printf("Запись обновлена и файл обновлен¸í\n");
                }
                break;
            case 3:
                error = ReadFile(monoblocks, SIZE);
                if (error) {
                    printf("Ошибка: %s\n", error);
                    break;
                }
                num = 0;
                printf("Введите номер записи (%d) для ее удаления:", SIZE);
                scanf("%d", &num);
                DeleteNotes(monoblocks, num, SIZE);
                SIZE -= 1;
                error = WriteFile(monoblocks, SIZE);
                if (error) {
                    printf("Ошибка: %s\n", error);
                }
                else {
                    printf("Запись удалена и файл обновлен¸í\n");
                }
                break;
            case 4:
                error = ReadFile(monoblocks, SIZE);
                if (error) {
                    printf("Ошибка: %s\n", error);
                }
                else {
                    printf("Файл успешно прочитан\n");
                    printf("\n");

                }
                for (int i = 0; i < SIZE; i++) print_monoblock(monoblocks[i]);
                break;
            case 5:
                break;
            }
            break;
        case 4:
            num = 0;
            printf("**********************************************\n");
            printf("*             Сортировать по                 *\n");
            printf("**********************************************\n");
            printf("* 1. Производитель.                          *\n");
            printf("* 2. Процессор.                              *\n");
            printf("* 3. Производитель и процессор системы.      *\n");
            printf("* 4. Вернуться в меню.                       *\n");
            printf("**********************************************\n");
            scanf("%d", &num);
            ReadFile(monoblocks, SIZE);
            switch (num) {
            case 1:
                sort_monoblocks(monoblocks, SIZE, num);
                WriteFile(monoblocks, SIZE);
                break;
            case 2:
                sort_monoblocks(monoblocks, SIZE, num);
                WriteFile(monoblocks, SIZE);
                break;
            case 3:
                sort_monoblocks(monoblocks, SIZE, num);
                WriteFile(monoblocks, SIZE);
                break;
            case 4:
                break;
            }

            break;
        case 5:
            a = 0;
            break;
        default:
            printf("Неверный выбор. Попробуйте еще раз.\n");
        }
    }
    free(monoblocks);
    free(countOfSeeked);
}