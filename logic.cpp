#include "logic.h"
#include <QClipboard>
#include <QApplication>

#include <QDebug>

#include <cstring>
#include <cstdlib>
#include <cstdio>

void translate(AppContext* context, const char* newValue, const char* fromBase, const char* toBase) {
    context->errorLine[0] = '\0';
    if (strcmp(fromBase, toBase) == 0) {
        context->translatedValue = newValue;
    } else if (strcmp(fromBase, "Десятичная") == 0 && strcmp(toBase, "Двоичная") == 0) {
        context->translatedValue = decimalToBinary(newValue);
    } else if (strcmp(fromBase, "Десятичная") == 0 && strcmp(toBase, "Восьмеричная") == 0) {
        context->translatedValue = decimalToOctal(newValue);
    } else if (strcmp(fromBase, "Двоичная") == 0 && strcmp(toBase, "Десятичная") == 0) {
        context->translatedValue = binaryToDecimal(newValue);
    } else if (strcmp(fromBase, "Двоичная") == 0 && strcmp(toBase, "Восьмеричная") == 0) {
        context->translatedValue = binaryToOctal(newValue);
    } else if (strcmp(fromBase, "Восьмеричная") == 0 && strcmp(toBase, "Десятичная") == 0) {
        context->translatedValue = octalToDecimal(newValue);
    } else if (strcmp(fromBase, "Восьмеричная") == 0 && strcmp(toBase, "Двоичная") == 0) {
        context->translatedValue = octalToBinary(newValue);
    } else {
        snprintf(context->errorLine, sizeof(context->errorLine), "Не удалось выполнить перевод");
    }
}

void initialize(AppContext* context) {
    context->translatedValue = DEFAULT_VALUE;
    strcpy(context->errorLine, ERROR_LINE);
}

void copyToClipboard(AppContext* context) {
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(context->translatedValue);

    qDebug() << "Copied to clipboard:" << clipboard;
}

char* intToString(long long value) {
    char* buffer = (char*)malloc(BIT_LIMIT);
    if (buffer != NULL) {
        snprintf(buffer, BIT_LIMIT, "%lld", value);
    }
    return buffer;
}

long long stringToInt(const char *str) {
    return (int)atoll(str);
}

char* decimalToBinary(const char* decimalStr) {
    long long decimal = stringToInt(decimalStr);
    unsigned int num = decimal;
    char binaryValue[BIT_LIMIT + 1];
    int index = 0;
    while (num > 0 && index < BIT_LIMIT) {
        binaryValue[index++] = (num % 2) + '0';
        num /= 2;
    }
    if (decimal >= 0)
    {
        while (index < BIT_LIMIT)
        {
            binaryValue[index++] = '0';
        }
    }
    binaryValue[BIT_LIMIT] = '\0';
    char* result = (char*)malloc(BIT_LIMIT + 1);
    for (int i = 0; i < BIT_LIMIT; ++i) {
        result[i] = binaryValue[BIT_LIMIT - 1 - i];
    }
    result[BIT_LIMIT] = '\0';
    return result;
}

char* decimalToOctal(const char* decimalStr) {
    long long decimal = stringToInt(decimalStr);
    unsigned int num = decimal;
    char octalValue[BIT_LIMIT_OCTAL +1];
    int index = 0;
    while (num > 0 && index < BIT_LIMIT_OCTAL) {
        octalValue[index++] = (num % 8) + '0';
        num /= 8;
    }
    if (decimal >= 0)
    {
        while (index < BIT_LIMIT_OCTAL)
        {
            octalValue[index++] = '0';
        }
    }
    octalValue[BIT_LIMIT_OCTAL] = '\0';
    char* result = (char*)malloc(BIT_LIMIT_OCTAL + 1);
    for (int i = 0; i < BIT_LIMIT_OCTAL; ++i) {
        result[i] = octalValue[BIT_LIMIT_OCTAL - 1 - i];
    }
    result[BIT_LIMIT_OCTAL] = '\0';
    return result;
}

char* binaryToDecimal(const char* binaryStr) {
    long long decimal = 0;
    int base = 1;
    int length = strlen(binaryStr);
    for (int i = length - 1; i >= 0; i--) {
        if (binaryStr[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }
    char* result = (char*)malloc(BIT_LIMIT + 1);
    snprintf(result, BIT_LIMIT + 1, "%lld", decimal);
    return result;
}

char* binaryToOctal(const char* binaryStr) {
    char* decimal = binaryToDecimal(binaryStr);
    char* result = decimalToOctal(decimal);
    free(decimal);
    return result;
}

char* octalToDecimal(const char* octalStr) {
    long long decimal = 0;
    int base = 1;
    int length = strlen(octalStr);

    for (int i = length - 1; i >= 0; i--) {
        decimal += (octalStr[i] - '0') * base;
        base *= 8;
    }
    char* result = (char*)malloc(BIT_LIMIT + 1);
    snprintf(result, BIT_LIMIT + 1, "%lld", decimal);
    return result;
}

char* octalToBinary(const char* octalStr) {
    char* decimal = octalToDecimal(octalStr);
    char* result = decimalToBinary(decimal);
    free(decimal);
    return result;
}
