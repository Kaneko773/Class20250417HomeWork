#pragma once

class SequenceBase
{
public:
    SequenceBase() {};
    virtual ~SequenceBase() {};

    virtual void Enter() = 0;

    virtual SequenceBase* Execute() = 0;

    virtual void Exit() = 0;

    virtual void Draw() = 0;
};

