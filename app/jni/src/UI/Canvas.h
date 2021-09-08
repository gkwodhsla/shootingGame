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

class Canvas: public HObject
{
public:
    Canvas() = delete;
    Canvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    virtual ~Canvas();
    void addToViewport();
    void removeFromViewport();
    void addWidgetToBuffer(Widget* newWidget);
    void addButtonToBuffer(ButtonWidget* newWidget);
    void addEditBoxToBuffer(EditBoxWidget* newWidget);
    virtual void canvasRender();
    virtual void render();
    virtual bool handleEvent(SDL_Event& e) = 0;
    virtual void update(float deltaTime);
    void changeWindowAlphaValue(__uint8_t alpha);
    float getCanvasXRatio()const;
    float getCanvasYRatio()const;
    float getCanvasInterpValue()const;
    template<typename T, typename ...Types>
    static T* makeCanvas(Types ...args)
    {
        T* newItem = new T(args...);
        newItem->setID(GlobalFunction::GetClassTypeUniqueID<T>());
        Framework::worldUI.push_back(newItem);
        return newItem;
    }

protected:
    template<typename T, typename ...Types>
    T* makeWidget(Types ...args)
    {
        T* newItem = new T(args...);

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


