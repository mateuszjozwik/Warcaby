//
// Created by mateusz on 19.05.18.
//

#ifndef POSITION_H
#define POSITION_H


class Position {
public:
    Position();
    Position(unsigned int x_, unsigned int y_);
    unsigned  int getX() const;
    unsigned  int getY() const;

private:
    unsigned int x_;
    unsigned int y_;
};


#endif //POSITION_H
