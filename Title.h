#pragma once
#include "SequenceBase.h"

class Title : public SequenceBase
{
    void Enter() override;

    SequenceBase* Execute() override;

    void Exit() override;
};

