#include "entrypoint.h"
#include "errors.h"
#include "logic.h"

const char* doOperation(Operation operation, AppContext* context, AppParams* param) {
    switch(operation) {
    case Translation:
        translate(context, param->newValue, param->fromBase, param->toBase);
        break;
    case Initialization:
        initialize(context);
        break;
    case ErrorOperation:
        return getErrorMessage(errorify(context, param->fromBase));
        break;
    case SwapOperation:
        break;
    case CopyOperation:
        copyToClipboard(context);
        break;
    }
    return nullptr;
}
