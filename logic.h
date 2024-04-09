#ifndef LOGIC_H
#define LOGIC_H

#include <stdio.h>
#include "appcontext.h"

void initialize(AppContext* context);
int readline(FILE* file, char* str);
void getData(AppContext* context);
void freeAppContext(AppContext* context);
void copyFilePath(AppContext* context, char *filePath);
void copyRegionName(AppContext* context, char *region);
void copyColumnIndex(AppContext* context, char *columnIndex);
int stringToInt(const char *str);
int isInt(const char* str);
int isDouble(const char* str);
double stringToDouble(const char* string);
int addLineToStruct(char* str, fileLine* line);
void calculate(AppContext* context);
int countRegionAppear(List* table, char* region);
double findfirstAppearance(List* table, char* region, int column);
double returnField(Node* p, int column);
void calculateData(List* table,char* region, int column, double* min, double* max, double* columnData);
double findMed(double* columnData, int counter);
void sort(double arr[], int size);
void swap(double* x, double* y);

#endif // LOGIC_H
