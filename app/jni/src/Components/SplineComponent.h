#pragma once
#include "HComponent.h"
#include <vector>

class HActor;

class SplineComponent :public HComponent
{
public:
    SplineComponent() = delete;
    SplineComponent(const std::initializer_list<std::pair<int, int>>& points, float tension, HActor* owner);
    virtual ~SplineComponent();
    virtual void update(float deltaTime) override;
    void drawDebugLine();
    std::pair<int, int> getCurrentLocation(float t);

public:
    void setIncTPerSec(float value);
    int getControlPointSize();
private:
    float tension = 0.0f; //기본적으로 catmull-rom spline 형태를 띤다.
    float incTPerSec = 0.1f;
    int curLocalCurveIndex = 0; //현재 몇 번째 로컬 커브를 그리고 있는지 나타낸다.
    std::vector<std::pair<int, int>> controlPoints;
    std::vector<std::pair<float, float>> velocities; //허밋 곡선은 베지어 곡선과 달리 Guide Point 대신 속도를 가진다.

private:
    std::pair<float, float> calcVelocityOfNPoint(int n); //이 함수는 N (0<N<NumOfPoint) 포인트의 속도를 구해준다.
    std::pair<int, int> calcPointOfLocalHermiteCurve(int n, float t);
    //이 함수는 N, N+1 사이의 허밋 곡선 즉, N번째 허밋 곡선에서 t 값(0.0f ~ 1.0f)을 대입했을 때 나오는 점의 위치를 계산해서
    //반환해준다.
};
