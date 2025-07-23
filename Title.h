#pragma once
#include "SequenceBase.h"

class Title : public SequenceBase
{
    void Enter(ScoreManager& scoreManager) override;

    SequenceBase* Execute() override;

    void Exit(ScoreManager& scoreManager) override;

    void Draw() override;

private:
    int m_highScore;
};

