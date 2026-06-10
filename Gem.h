#pragma once

class GameField;

class Gem {
protected:
    int color;
public:
    void setColor(int color);

    Gem(int color);

    virtual ~Gem();

    int getColor() const;

    virtual bool isBonus() const;

    virtual void activate(GameField& field, int row, int col);
};

