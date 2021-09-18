#pragma once

#include <SDL.h>
#include <vector>
#include <string>
#include <type_traits>
#include <android/log.h>
#include "Widget.h"
#include "TextWidget.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"
#include "EditBoxWidget.h"
#include "../HObject.h"
#include "../Framework.h"
#include "../GlobalFunction.h"
//캔버스는 위젯을 담는 컨테이너이다.
//입력받은 사이즈만큼의 렌더타겟을 만들어주고 위젯은 이 렌더타겟에
//그려지고 최종 결과가 화면에 렌더링된다.
class Canvas: public HObject
{
public:
    Canvas() = delete;
    Canvas(const Canvas&) = delete;
    Canvas& operator=(const Canvas&) = delete;
    Canvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    virtual ~Canvas();
    void addToViewport();
    void removeFromViewport();
    void addWidgetToBuffer(Widget* newWidget);
    void addButtonToBuffer(ButtonWidget* newWidget);
    void addEditBoxToBuffer(EditBoxWidget* newWidget);
    virtual void canvasRender();
    virtual void render();
    virtual bool handleEvent(const SDL_Event& e) = 0;
    virtual void update(const float deltaTime);
    void changeWindowAlphaValue(__uint8_t alpha);
    float getCanvasXRatio()const;
    float getCanvasYRatio()const;
    float getCanvasInterpValue()const;

protected:
    template<typename T, typename ...Types>
    T* makeWidget(Types ...args)
    {
        T* newItem = GlobalFunction::createNewObject<T>(args...);

        addWidgetToBuffer(newItem);

        if constexpr(std::is_base_of<ButtonWidget, T>::value)
        {
            addButtonToBuffer(newItem);
        }
        else if constexpr(std::is_base_of<EditBoxWidget, T>::value)
        {
            addEditBoxToBuffer(newItem);
        }
        return newItem;
    }

protected:
    int w = 500;
    int h = 500;
    const int RTWidth = 1080;
    const int RTHeight = 1920;
    float canvasXRatio = 0.0f;
    float canvasYRatio = 0.0f;
    float canvasInterpolate = 0.0f;
    SDL_Texture* window = nullptr;
    int canvasWorldPosX = 0;
    int canvasWorldPosY = 0;
    bool visibility = false;
    std::vector<Widget*> canvasWidgets;
    std::vector<ButtonWidget*> canvasButtons;
    std::vector<EditBoxWidget*> editBoxes;

private:
    void createEmptyWindow();
};


