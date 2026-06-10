#pragma once

#include "Gem.h"

class RepaintBonus : public Gem {
public:
    RepaintBonus(int color);

    bool isBonus() const override;

    void activate(GameField& field, int row, int col) override;
};




