#pragma once
#include <SFML/Graphics.hpp>
#include "CConfigurationData.h"
#include "CController.h"

class CView {
public:
    virtual void SetSceneProperties() = 0;
};