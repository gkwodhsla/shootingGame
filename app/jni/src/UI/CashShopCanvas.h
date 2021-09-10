#include "Canvas.h"


class ImageWidget;
class ButtonWidget;
class TextWidget;

enum class WHICH_CASH_SELECTED
{
    ITEM1 = 0,
    ITEM2,
    ITEM3,
    ITEM4,
    ITEM5,
    ITEM6
};

class CashShopCanvas :public Canvas
{
public:
    CashShopCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    virtual ~CashShopCanvas();
    virtual void canvasRender();
    virtual void render();
    virtual bool handleEvent(const SDL_Event& e);
    virtual void update(const float deltaTime);
    void updateCrystalText();
    int getCrystal();
    void setCrystal(int crystal);
    void buyCrystal();
    WHICH_CASH_SELECTED getWhichCashItemSelected();

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
    int curCrystal = 0;
    WHICH_CASH_SELECTED whichSelected = WHICH_CASH_SELECTED::ITEM1;
};