#include "entrypoint.h"
#include "logic.h"

void doOperation(Operation operation, AppContext* context, AppParams* param) {
    switch(operation) {
    case Translation:
        translate(context, param->newValue);
        break;
    case Initialization:
        initialize(context);
        break;
    case Validation:
        validate(context, param->newValue);
        break;
    case SwapReplace:
        swapReplace(context, param->newValue);
        break;
    }
}
