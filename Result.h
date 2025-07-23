#pragma once
#include "SequenceBase.h"

namespace ResultScene {
    enum NextScene {
        title = 0,
        mainGame = 1,
    };
}

class Result : public SequenceBase
{
    void Enter(ScoreManager& scoreManager) override;

    SequenceBase* Execute() override;

    void Exit(ScoreManager& scoreManager) override;

    void Draw() override;

private:
    ResultScene::NextScene m_nextScene{};

    int m_enduredTime;
};

