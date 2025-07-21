#pragma once
#include "SequenceBase.h"

class Title : public SequenceBase
{
    void Enter() override;

    SequenceBase* Execute(ScoreManager& scoreManager) override;

    void Exit() override;
};

