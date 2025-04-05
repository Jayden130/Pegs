#pragma once

/*
Compact (16bit) move representation to preserve memory during search.

The format is as follows (fffffftttttsssss)
Bits 0-5: start square index
Bits 6-10: target square index
Bits 11-15: capture index
*/

struct Move
{
    // 16bit move value
    unsigned short moveValue = 0;

    // Masks
    const unsigned short startSquareMask = 0b0000000000011111;
    const unsigned short targetSquareMask = 0b0000001111100000;
public:
    Move(int startSquare, int targetSquare, int capture = 0)
    {
        moveValue = (unsigned short)(startSquare | targetSquare << 5 | capture << 10);
    }

    Move(int value)
    {
        moveValue = (unsigned short)value;
    }
    Move() {}

    int GetStartSquare() const { return moveValue & startSquareMask; }
    int GetTargetSquare() const { return (moveValue & targetSquareMask) >> 5; }
    int GetCapture() const { return moveValue >> 10; }
    int GetDirection() const { return GetTargetSquare() - GetStartSquare(); }
    bool IsEmpty() const { return moveValue == 0; }

    Move& operator=(Move const& copy)
    {
        moveValue = copy.moveValue;
        return *this;
    }
    friend bool operator==(Move const& lhs, Move const& rhs)
    {
        bool same = lhs.moveValue == rhs.moveValue;
        return same;
    }
};