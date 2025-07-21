#pragma once
#include "ScoreManager.h"

class SequenceBase
{
public:
    virtual void Enter() = 0;

    virtual SequenceBase* Execute(ScoreManager& scoreManager) = 0;

    virtual void Exit() = 0;
};

