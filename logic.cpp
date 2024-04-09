#include "logic.h"
#include "list.h"
#include <cstdlib>
#include <cstring>

void initialize(AppContext* context)
{
    context->min = DEFAULT_METRICS_VALUE;
    context->med = DEFAULT_METRICS_VALUE;
    context->max = DEFAULT_METRICS_VALUE;
    context->totalLines = DEFAULT_METRICS_VALUE;
    context->totalErrorLines = DEFAULT_METRICS_VALUE;
    context->totalSuccessfulLines = DEFAULT_METRICS_VALUE;
    strncpy(context->filePath, NO_FILE, sizeof(context->filePath) - 1);
    context->filePath[sizeof(context->filePath) - 1] = '\0';
    context->errorCode = NoErrors;
}

void getData(AppContext* context)
{
    FILE *file = fopen(context->filePath, "r");
    if (!file)
    {
        context->errorCode = FileOpenError;
    }

    char* infoLine = (char*)malloc(LINE_MAX_LENGHT);
    readline(file, infoLine);
    free(infoLine);

    char* line = (char*)malloc(LINE_MAX_LENGHT);
    int successfullyReadLine = readline(file, line);
    fileLine firstLine;
    int totalLines = 0;
    int totalErrorLines = 0;
    int totalSuccessfulLines = 0;
    if (addLineToStruct(line, &firstLine)) {
        totalSuccessfulLines++;
    } else {
        totalErrorLines++;
    }
    totalLines++;
    free(line);
    List* list = init(firstLine);
    while (!feof(file)) {
        fileLine currentLine;
        char* line = (char*)malloc(LINE_MAX_LENGHT);
        successfullyReadLine += readline(file, line);
        if (addLineToStruct(line, &currentLine)) {
            totalSuccessfulLines++;
            pushEnd(list, currentLine);
        } else {
            totalErrorLines++;
        }
        totalLines++;
        free(line);
    }
    context->table = list;
    context->totalLines = totalLines;
    context->totalSuccessfulLines = totalSuccessfulLines;
    context->totalErrorLines = totalErrorLines;
    fclose(file);
}

void copyFilePath(AppContext* context, char* filePath)
{
    if (strcmp(filePath, "") == 0)
    {
        context->errorCode = FileLoadError;
    }
    else {
        strncpy(context->filePath, filePath, sizeof(context->filePath) - 1);
        context->filePath[sizeof(context->filePath) - 1] = '\0';
        context->errorCode = NoErrorsFileLoaded;
    }
}

void copyRegionName(AppContext* context, char* region)
{
    strncpy(context->region, region, sizeof(context->region) - 1);
    context->region[sizeof(context->region) - 1] = '\0';
}

void copyColumnIndex(AppContext* context, char* columnIndex)
{
    strncpy(context->columnIndex, columnIndex, sizeof(context->columnIndex) - 1);
    context->columnIndex[sizeof(context->columnIndex) - 1] = '\0';
}

int readline(FILE* file, char* str)
{
    int successedLines = 0;
    successedLines += fgets(str, LINE_MAX_LENGHT, file) == NULL ? 0: 1;
    int len = strlen(str);
    if (str[len - 1] == '\n')
        str[len - 1] = '\0';
    return successedLines;
}

int addLineToStruct(char* str, fileLine* line) {
    int isSuccess = 1;
    char* token = strtok(str, ",");
    if (token != NULL && isInt(token)) {
        line->year = stringToInt(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess != 0) {

        strncpy(line->region, token, sizeof(line->region) - 1);
        line->region[sizeof(line->region) - 1] = '\0';
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess != 0 && isDouble(token)) {
        line->nPG = stringToDouble(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess != 0 && isDouble(token)) {
        line->birthRate = stringToDouble(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess != 0 && isDouble(token)) {
        line->deathRate = stringToDouble(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess != 0 && isDouble(token)) {
        line->gDW = stringToDouble(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess != 0 && isDouble(token)) {
        line->urbanisation = stringToDouble(token);
    } else {
        isSuccess = 0;
    }
    return isSuccess;
}

int stringToInt(const char *str) {
    return atoi(str);
}

int isInt(const char *str) {
    char* endptr;
    int isInt = 0;
    strtol(str, &endptr, 10);
    if (*endptr == '\0') {
        isInt = 1;
    }
    return isInt;
}

int isDouble(const char *str) {
    char* endptr;
    int isDouble = 0;
    strtod(str, &endptr);
    if (*endptr == '\0') {
        isDouble = 1;
    }

    return isDouble;
}

double stringToDouble(const char *str) {
    return atof(str);
}

void calculate(AppContext* context) {
    int doCalculate = 1;
    if (!isInt(context->columnIndex) ||(isInt(context->columnIndex) && (stringToInt(context->columnIndex) > 7 || stringToInt(context->columnIndex) < 3))){
        doCalculate = 0;
        context->errorCode = ColumnError;
    }
    if (doCalculate) {
        int counter = countRegionAppear(context->table, context->region);
        if (!counter) {
            context->errorCode = RegionError;
        } else {
            double min = findfirstAppearance(context->table, context->region, stringToInt(context->columnIndex));
            double max = findfirstAppearance(context->table, context->region, stringToInt(context->columnIndex));
            double* columnIndexData = (double*)malloc(sizeof(double) * counter);
            calculateData(context->table, context->region, stringToInt(context->columnIndex), &min, &max, columnIndexData);
            double median = findMed(columnIndexData, counter);
            free(columnIndexData);
            context->med = median;
            context->max = max;
            context->min = min;
        }
    }
}

int countRegionAppear(List* table, char* region) {
    Node* p = table->first;
    int counter = 0;

    do {
        if (!strcmp(p->data.region, region)) {
            counter++;
        }
        p = p->next;
    } while (p != NULL);
    return counter;
}

double findfirstAppearance(List* table, char* region, int column) {
    Node* p = table->first;
    double metric = 0;

    do {
        if (strcmp(p->data.region, region) == 0) {
            metric = returnField(p, column);
        }
        p = p->next;
    } while (p != NULL);
    return metric;
}

double returnField(Node* p, int column) {
    double field = 0;
    switch(column) {
    case 3:
        field = p->data.nPG;
        break;
    case 4:
        field = p->data.birthRate;
        break;
    case 5:
        field = p->data.deathRate;
        break;
    case 6:
        field = p->data.gDW;
        break;
    case 7:
        field = p->data.urbanisation;
        break;
    }
    return field;
}

void calculateData(List* table,char* region, int column, double* min, double* max, double* columnData) {
    Node* p = table->first;
    int counter = 0;

    do {
        if (strcmp(p->data.region, region) == 0) {
            double metric = returnField(p, column);
            if (metric > *max) {
                *max = metric;
            } else if (metric < *min) {
                *min = metric;
            }
            columnData[counter] = metric;
            counter++;
        }
        p = p->next;
    } while (p != NULL);
}

double findMed(double* columnData, int counter) {
    sort(columnData, counter);
    double median;

    if (counter % 2 != 0) {
        median = columnData[counter/2];
    } else {
        median = (columnData[counter/2 - 1]+columnData[counter/2]) / 2;
    }
    return median;
}

void sort(double arr[], int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (*(arr + i) > *(arr + j))
                swap(arr + i, arr + j);
}

void swap(double* x, double* y) {
    double temp = *x;
    *x = *y;
    *y = temp;
}
