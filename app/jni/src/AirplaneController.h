#include "HPlayerController.h"

class Canvas;
enum class WHICH_CASH_SELECTED;
class AirplaneController: public HPlayerController
{
public:
    AirplaneController(HPawn* controlledPawn);
    AirplaneController() = delete;
    AirplaneController(const AirplaneController&) = delete;
    AirplaneController& operator=(const AirplaneController&) = delete;
    virtual ~AirplaneController();
    void createCanvases();
    void changeShop();
    void showYesNoWindow();
    int getMoney();
    void setMoney(int newMoney);
    void processingBuyProtocol();

public:
    Canvas* shopCanvas = nullptr;
    Canvas* inGameCanvas = nullptr;
    Canvas* cashShopCanvas = nullptr;
    Canvas* yesNoCanvas = nullptr;
    bool isShopCanvasShow = true;
    int curMoney = 0;
};