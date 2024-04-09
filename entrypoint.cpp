#include "entrypoint.h"
#include "logic.h"

void doOperation(Operation operation, AppContext* context, AppParams *param)
{
    switch (operation) {
    case Initialization:
        initialize(context);
        break;
    case CopyFilePath:
        copyFilePath(context, param->filePath);
        break;
    case CopyRegionName:
        copyRegionName(context, param->region);
        break;
    case CopyColumnIndex:
        copyColumnIndex(context, param->column);
        break;
    case GetData:
        getData(context);
        break;
    case Calculation:
        calculate(context);
        break;
    }
}
