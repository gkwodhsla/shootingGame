#include "HPlayerController.h"

class Canvas;
class AirplaneController: public HPlayerController
{
public:
    AirplaneController(HPawn* controlledPawn);
    virtual ~AirplaneController();
    void createCanvases();

public:
    Canvas* shopCanvas = nullptr;
    Canvas* inGameCanvas = nullptr;
    Canvas* cashShopCanvas = nullptr;

    int curMoney = 99999;
};