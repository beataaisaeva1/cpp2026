#pragma once

#include <memory>

class Gem;

class GemFactory {
public:
    static std::unique_ptr<Gem> createNormalGem();

    static std::unique_ptr<Gem> createBombBonus(int color);

    static std::unique_ptr<Gem> createRepaintBonus(int color);
};





