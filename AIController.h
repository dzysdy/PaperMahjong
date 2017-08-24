#ifndef AICONTROLLER_H
#define AICONTROLLER_H
#include "Controller.h"

class AIController : public Controller
{
public:
    AIController(Player* p, QObject *parent = 0);
};

#endif // AICONTROLLER_H
