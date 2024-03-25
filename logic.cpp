#include "logic.h"
#include "entrypoint.h"
#include <QClipboard>
#include <QApplication>
#include <cstring>
#include <cstdlib>
#include <cstdio>

void translate(AppContext* context, const char* newValue, const char* fromBase, const char* toBase) {
    if (strcmp(fromBase, toBase) == 0) {
        context->translatedValue = newValue;
    } else if (strcmp(fromBase, Десятичная) == 0 && strcmp(toBase, Двоичная) == 0) {
        context->translatedValue = decimalToAll(newValue, 2);
    } else if (strcmp(fromBase, Десятичная) == 0 && strcmp(toBase, Восьмеричная) == 0) {
        context->translatedValue = decimalToAll(newValue, 8);
    } else if (strcmp(fromBase, Двоичная) == 0 && strcmp(toBase, Десятичная) == 0) {
        context->translatedValue = AllToDecimal(newValue, 2);
    } else if (strcmp(fromBase, Двоичная) == 0 && strcmp(toBase, Восьмеричная) == 0) {
        context->translatedValue = binaryToOctal(newValue);
    } else if (strcmp(fromBase, Восьмеричная) == 0 && strcmp(toBase, Десятичная) == 0) {
        context->translatedValue = AllToDecimal(newValue, 8);
    } else if (strcmp(fromBase, Восьмеричная) == 0 && strcmp(toBase, Двоичная) == 0) {
        context->translatedValue = octalToBinary(newValue);
    }
}

void setErrorCode(AppContext* context, const char* base, const char* input) {
    context->errorCode = NoErrors;
    if (strcmp(input,"") == 0)
    {
        context->errorCode = NothingEnteredOrTranslated;
    }
    if (strcmp(base, Десятичная) == 0) {
        for (int i = 0; input[i] != '\0'; ++i) {
            if ((i == 0 && !(input[i] == '-' || isdigit(input[i]))) || (i > 0 && !isdigit(input[i]))) {
                context->errorCode = BadDigit;
                break;
            } else if (stringToInt(input) > pow(2, BIT_LIMIT_OVERALL - 1) || stringToInt(input) < -pow(2, BIT_LIMIT_OVERALL - 1)) {
                context->errorCode = BitOverload;
                break;
            }
        }
    } else if (strcmp(base, Двоичная) == 0) {
        for (int i = 0; input[i] != '\0'; ++i) {
            if (input[i] != '0' && input[i] != '1') {
                context->errorCode = BadDigit;
                break;
            } else if (strlen(input) > BIT_LIMIT_BINARY) {
                context->errorCode = BitOverload;
                break;
            }
        }
    } else if (strcmp(base, Восьмеричная) == 0) {
        for (int i = 0; input[i] != '\0'; ++i) {
            if (input[i + 1] > '7' || input[i] == '-') {
                context->errorCode = BadDigit;
                break;
            } else if (strlen(input) > BIT_LIMIT_OCTAL || input[0] > '3') {
                context->errorCode = BitOverload;
                break;
            }
        }
    }
}

void initialize(AppContext* context) {
    context->translatedValue = DEFAULT_VALUE;
    context->errorCode = NoErrors;
}

char* intToString(long long value) {
    char* buffer = (char*)malloc(BIT_LIMIT_OVERALL);
    if (buffer != NULL) {
        snprintf(buffer, BIT_LIMIT_OVERALL, "%lld", value);
    }
    return buffer;
}

long long stringToInt(const char *str) {
    return (long long)atoll(str);
}

void swapReplace(AppContext* context, const char* newValue)
{
    context->translatedValue = newValue;
}

char* decimalToAll(const char* decimalStr, int baseTo)
{
    int decimal = stringToInt(decimalStr);
    unsigned int num = decimal;
    char newValue[BIT_LIMIT_OVERALL + 1];
    int index = 0;
    while (num > 0 && index < BIT_LIMIT_OVERALL)
    {
        newValue[index++] = (num % baseTo) + '0';
        num /= baseTo;
    }
    newValue[index] = '\0';
    char* result = (char*)malloc(index + 1);
    for (int i = 0; i < index; ++i)
    {
        result[i] = newValue[index - 1 - i];
    }
    result[index] = '\0';
    return result;
}

char* AllToDecimal(const char* AllStr, int baseFrom)
{
    long long decimal = 0;
    int base = 1;
    int length = strlen(AllStr);
    for (int i = length - 1; i >= 0; --i)
    {
        decimal += (AllStr[i] - '0') * base;
        base *= baseFrom;
    }
    char* result = (char*)malloc(BIT_LIMIT_DECIMAL + 1);
    snprintf(result, BIT_LIMIT_DECIMAL + 1, "%lld", decimal);
    return result;
}

char* binaryToOctal(const char* binaryStr)
{
    char* decimal = AllToDecimal(binaryStr, 2);
    char* result = decimalToAll(decimal, 8);
    free(decimal);
    return result;
}

char* octalToBinary(const char* octalStr)
{
    char* decimal = AllToDecimal(octalStr, 8);
    char* result = decimalToAll(decimal, 2);
    free(decimal);
    return result;
}
