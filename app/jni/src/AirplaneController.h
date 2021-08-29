#include "HPlayerController.h"

class Canvas;
class AirplaneController: public HPlayerController
{
public:
    AirplaneController(HPawn* controlledPawn);
    virtual ~AirplaneController();
    void createCanvases();
    void changeShop();

public:
    Canvas* shopCanvas = nullptr;
    Canvas* inGameCanvas = nullptr;
    Canvas* cashShopCanvas = nullptr;
    bool isShopCanvasShow = true;
    int curMoney = 99999;
};