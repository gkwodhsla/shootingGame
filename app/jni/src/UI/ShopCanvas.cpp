#include "ShopCanvas.h"
#include "TextWidget.h"
#include "ButtonWidget.h"
#include "ImageWidget.h"
#include "../Framework.h"
#include <android/log.h>

ShopCanvas::ShopCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY) :
Canvas(canvasW, canvasH, canvasWorldX, canvasWorldY)
{
    initWidgets();
}

ShopCanvas::~ShopCanvas()
{
    delete playButton;
    playButton = nullptr;

    delete incButton;
    incButton = nullptr;

    delete decButton;
    decButton = nullptr;

    delete stageText;
    stageText = nullptr;

    delete bgImage;
    bgImage = nullptr;
}

void ShopCanvas::canvasRender()
{
    if(visibility)
    {
        Canvas::canvasRender(); // 여기서 렌더타켓을 초기화 시켜준다.
        bgImage->render();
        playButton->render();
        incButton->render();
        decButton->render();
        stageText->render();
        SDL_SetRenderTarget(Framework::renderer, nullptr);
    }
}

void ShopCanvas::render()
{
    if(visibility)
    {
        Canvas::render();
    }
}

void ShopCanvas::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_FINGERDOWN)
    {
        int x = int(e.tfinger.x * float(Framework::rendererWidth));
        int y = int(e.tfinger.y * float(Framework::rendererHeight));
        playButton->checkIsClicked(x, y);
        incButton->checkIsClicked(x, y);
        decButton->checkIsClicked(x, y);
    }
    else if (e.type == SDL_FINGERMOTION)
    {
    }
    else if (e.type == SDL_FINGERUP)
    {

    }
    //위젯을 순회하며 발생한 이벤트가 있는지 검사하고 적절한 함수를 호출해준다.
}

bool ShopCanvas::getIsPlayButtonClicked()
{
    return isPlayButtonClicked;
}

void ShopCanvas::setIsPlayButtonClicked(bool isClicked)
{
    isPlayButtonClicked = isClicked;
}

void ShopCanvas::incMaxStage()
{
    ++maxStage;
}

int ShopCanvas::getCurStage()
{
    return curStage;
}

int ShopCanvas::getMaxStage()
{
    return maxStage;
}


void ShopCanvas::initWidgets()
{
    playButton = new ButtonWidget("image/UIbutton/playButton.png");
    playButton->buttonDown = [this]()mutable
            {
                isPlayButtonClicked = true;
            };
    playButton->setLocalPosition(w - 250, h - 300);

    incButton = new ButtonWidget("image/UIbutton/rightButton.png");
    incButton->buttonDown = [this]()mutable
            {
                if(curStage < maxStage)
                {
                    ++curStage;
                    std::string temp = "Stage: ";
                    temp += std::to_string(curStage);
                    stageText->changeText(temp);
                }
            };
    incButton->setLocalPosition(550, h - 300);

    decButton = new ButtonWidget("image/UIbutton/leftButton.png");
    decButton->buttonDown = [this]()mutable
            {
                if(curStage > minStage)
                {
                    --curStage;
                    std::string temp = "Stage: ";
                    temp += std::to_string(curStage);
                    stageText->changeText(temp);
                }
            };
    decButton->setLocalPosition(0, h - 300);

    stageText = new TextWidget("Stage: 1", 100, 0, 0, 0);
    stageText->setLocalPosition(200, h - 250);

    bgImage = new ImageWidget("image/misc/shopBG.png");
    bgImage->setLocalPosition(0, 0);
    bgImage->setScale(w, h);
}
