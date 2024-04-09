#ifndef LIST_H
#define LIST_H

#define LINE_MAX_LENGHT 1024
#define DEFAULT_METRICS_VALUE 0
#define NO_FILE ""

struct fileLine {
    int year;
    char region[LINE_MAX_LENGHT];
    double nPG;
    double birthRate;
    double deathRate;
    double gDW;
    double urbanisation;
};

struct Node {
    fileLine data;
    Node* next;
};

struct List {
    Node* first;
};

List* init(fileLine line);
void pushEnd(List* list, fileLine line);

#endif // LIST_H
