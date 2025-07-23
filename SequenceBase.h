#pragma once
#include "ScoreManager.h"

class SequenceBase
{
public:
    virtual void Enter(ScoreManager& scoreManager) = 0;

    virtual SequenceBase* Execute() = 0;

    virtual void Exit(ScoreManager& scoreManager) = 0;

    virtual void Draw() = 0;
};

