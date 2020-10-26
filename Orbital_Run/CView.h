#pragma once
#include <SFML/Graphics.hpp>
#include "CConfigurationData.h"
#include "CController.h"

class CView {
private:

public:
    virtual void SetSceneProperties() = 0;
};