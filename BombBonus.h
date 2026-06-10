#pragma once

#include "Gem.h"

class BombBonus : public Gem {
public:
    BombBonus(int color);

    bool isBonus() const override;

    void activate(GameField& field, int row, int col) override;
};


