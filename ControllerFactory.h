#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

enum ControllerType {
    CT_CUSTOM,
    CT_AI
};

class Player;
class Controller;
class ControllerFactory
{
public:
    //ControllerFactory() = delete;

    static Controller* createController(ControllerType type, Player *player);
};

#endif // CONTROLLERFACTORY_H
