#include "ControllerFactory.h"
#include "Controller.h"
#include "AIController.h"
#include "WorkDesk.h"
#include "Player.h"

Controller *ControllerFactory::createController(ControllerType type, Player* player)
{
    Controller* controller = nullptr;
    switch (type) {
    case CT_CUSTOM:
        controller = new WorkDesk(player);
        break;
    case CT_AI:
        controller = new AIController(player);
        break;
    default:
        break;
    }
    return controller;
}
