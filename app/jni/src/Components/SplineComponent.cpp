#include "SplineComponent.h"
#include "../Framework.h"
#include <SDL.h>
#include <initializer_list>
#include <utility>
#include <cmath>
#include <android/log.h>

SplineComponent::SplineComponent(const std::initializer_list<std::pair<int, int>> &points, float tension, HActor* owner)
{
    controlPoints.reserve(points.size());
    for(auto& point : points)
    {
        controlPoints.push_back(point);
    }

    this->tension = tension;

    velocities.reserve(points.size());
    velocities.push_back(std::make_pair(0.0f, 0.0f));
    for(int i = 1; i < points.size() - 1; ++i)
    {
        velocities.push_back(calcVelocityOfNPoint(i));
    }
    velocities.push_back(std::make_pair(0.0f, 0.0f));

    this->owner = owner;
}

SplineComponent::~SplineComponent()
{

}

void SplineComponent::update(float deltaTime)
{

}

void SplineComponent::drawDebugLine()
{
    SDL_SetRenderDrawColor(Framework::renderer, 0, 0xFF, 0, 0xFF);
    for(float i = 0.0f; i < float(controlPoints.size()) - 1.0f; i+=0.01f)
    {
        curLocalCurveIndex = int(floor(i));
        float t = i - float(curLocalCurveIndex);
        auto curPoint = calcPointOfLocalHermiteCurve(curLocalCurveIndex, t);

        SDL_RenderDrawPoint(Framework::renderer, curPoint.first, curPoint.second);
    }
}

std::pair<int, int> SplineComponent::getCurrentLocation(float t)
{
    curLocalCurveIndex = int(floor(t));
    float localT = t - float(curLocalCurveIndex);
    auto curPoint = calcPointOfLocalHermiteCurve(curLocalCurveIndex, localT);

    return {curPoint.first, curPoint.second};
}

int SplineComponent::getControlPointSize()
{
    return controlPoints.size();
}

void SplineComponent::setIncTPerSec(float value)
{
    incTPerSec = value;
}

std::pair<float, float> SplineComponent::calcVelocityOfNPoint(int n)
{
    float vX = 0.0f;
    float vY = 0.0f;
    float steep = 1.0f - tension;
    vX = steep * (controlPoints[n + 1].first - controlPoints[n - 1].first) / 2.0f;
    vY = steep * (controlPoints[n + 1].second - controlPoints[n - 1].second) / 2.0f;

    return std::make_pair(vX, vY);
}

std::pair<int, int> SplineComponent::calcPointOfLocalHermiteCurve(int n, float t)
{
    float pX = 0.0f;
    float pY = 0.0f;
    float s = (1.0f - t);
    float ss = s * s;
    float tt = t * t;

    pX = (ss*(1 + 2 * t) * float(controlPoints[n].first)) +
            (tt * (1 + 2 * s) * float(controlPoints[n + 1].first)) +
            (ss * t * velocities[n].first) -
            (s * tt * velocities[n + 1].first);

    pY = (ss*(1 + 2 * t) * float(controlPoints[n].second)) +
         (tt * (1 + 2 * s) * float(controlPoints[n + 1].second)) +
         (ss * t * velocities[n].second) -
         (s * tt * velocities[n + 1].second);

    //이 계산을 매 프레임마다 하면 좀 부담이 될 것 같으니 precomputed 해놓자.
    return std::make_pair(int(pX), int(pY));
}