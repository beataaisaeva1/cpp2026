#pragma once

#include "Gem.h"

class NormalGem : public Gem {
public:
    NormalGem(int color);

    void activate(GameField& field, int row, int col) override;
};

