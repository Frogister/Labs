#include "entrypoint.h"
#include "logic.h"

void doOperation(Operation operation, AppContext* context, AppParams* param) {
    switch(operation) {
    case Translation:
        translate(context, param->newValue, context->fromBase, context->toBase);
        break;
    case Initialization:
        initialize(context);
        break;
    case GetErrorCode:
        setErrorCode(context, context->fromBase, param->newValue);
        break;
    }
}
