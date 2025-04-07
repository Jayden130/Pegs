#pragma once

#include <cstdint>

const int Infinity = 2147000000;

constexpr uint64_t FileA = 0x111111;
constexpr uint64_t FileB = 0x222222;
constexpr uint64_t FileC = 0x444444;
constexpr uint64_t FileD = 0x888888;

constexpr uint64_t Rank1 = 0b1111;
constexpr uint64_t Rank2 = Rank1 << 4;
constexpr uint64_t Rank3 = Rank2 << 4;
constexpr uint64_t Rank4 = Rank3 << 4;
constexpr uint64_t Rank5 = Rank4 << 4;
constexpr uint64_t Rank6 = Rank5 << 4;

constexpr uint64_t notAFile = ~FileA;
constexpr uint64_t notDFile = ~FileD;
constexpr uint64_t innerFileMask = notAFile & notDFile;
constexpr uint64_t outerFileMask = ~innerFileMask;

constexpr uint64_t LightSquares = 0xAAAAAA;
constexpr uint64_t DarkSquares = 0x555555;

int PopLSB(uint64_t& value);
int GetLSB(uint64_t& value);
int CountBits(uint64_t value);
void SetSquare(uint64_t& bitboard, int squareIndex);
void ClearSquare(uint64_t& bitboard, int squareIndex);
void ToggleSquares(uint64_t& bitboard, int squareA, int squareB);
bool SquareIsSet(uint64_t bitboard, int squareIndex);
bool ValidSquare(int x, int y);
bool ValidSquare(int x, int y, int& index);
int GetSquareIndex(int x, int y);
int FileIndex(int squareIndex);
int RankIndex(int squareIndex);