#include "GemFactory.h"
#include "Gem.h"
#include "NormalGem.h"
#include "BombBonus.h"
#include "RepaintBonus.h"
#include <random>

static std::random_device dev;
static std::mt19937 rng(dev());

std::unique_ptr<Gem>

GemFactory::createNormalGem() {
    static const int COLORS = 6;
    std::uniform_int_distribution<int> dist(0, COLORS - 1);
    return std::make_unique<NormalGem>(dist(rng));
}

std::unique_ptr<Gem>

GemFactory::createBombBonus(int color) {
    return std::make_unique<BombBonus>(color);
}

std::unique_ptr<Gem>

GemFactory::createRepaintBonus(int color) {
    return std::make_unique<RepaintBonus>(color);
}

