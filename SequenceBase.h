#pragma once

class SequenceBase
{
public:
    virtual void Enter() = 0;

    virtual SequenceBase* Execute() = 0;

    virtual void Exit() = 0;
};

