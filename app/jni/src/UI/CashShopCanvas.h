#include "Canvas.h"


class ImageWidget;
class ButtonWidget;
class TextWidget;

class CashShopCanvas :public Canvas
{
public:
    CashShopCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    virtual ~CashShopCanvas();
    virtual void canvasRender();
    virtual void render();
    virtual bool handleEvent(SDL_Event& e);
    virtual void update(float deltaTime);

private:
    void initWindowImageWidgets();
    void initButtonWidgets();
    void initTextWidgets();

private:
    ImageWidget* bgImg = nullptr;
    ImageWidget* shopTitleImage = nullptr;
    ImageWidget* crystalImage = nullptr;
    ImageWidget* moneyWindowImage = nullptr;
    std::vector<ImageWidget*> smallWindows;
    std::vector<ImageWidget*> crystals;
    std::vector<ButtonWidget*> buyButtons;
    ButtonWidget* changeButton = nullptr;
    TextWidget* moneyText = nullptr;
    std::vector<TextWidget*> crystalNumTexts;
    std::vector<TextWidget*> priceTexts;
    static const int sellItemNum;
    static const std::array<std::string, 6> crystalNums;
    static const std::array<std::string, 6> prices;
};