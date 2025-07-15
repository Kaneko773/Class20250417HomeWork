#pragma once
#include "SequenceBase.h"

class Result : public SequenceBase
{
    void Enter() override;

    SequenceBase* Execute() override;

    void Exit() override;

private:

};

