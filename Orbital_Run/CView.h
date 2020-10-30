#pragma once
#include <SFML/Graphics.hpp>
#include "CConfigurationData.h"
#include "CController.h"

class CView {
private:

public:
    CView() {}
    virtual ~CView() {}
    virtual void SetSceneProperties() = 0;
};