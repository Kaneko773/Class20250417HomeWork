#pragma once
#include "SequenceBase.h"

class Title : public SequenceBase
{
public:
    Title();
    ~Title();

    void Enter() override;

    SequenceBase* Execute() override;

    void Exit() override;

    void Draw() override;
};

