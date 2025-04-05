#pragma once

#include <cstdint>
#include <array>

// Helper class for the calculation of zobrist hash.
// This is a single 32bit value that (non-uniquely) represents the current state of the game.

// It is mainly used for quickly detecting positions that have already been evaluated, to avoid
// potentially performing lots of duplicate work during game search.

class Zobrist
{
	static constexpr uint64_t seed = 0x6C62272E07BB0142ULL;

public:
	static void Init();
	static uint64_t CalculateZobristKey(Board& board);
	static uint64_t RandomUnsigned64BitNumber() noexcept;
	static const std::array<std::array<uint64_t, 24>, 2>& GetPiecesArray();
	static const uint64_t& GetSideToMove();

private:
	// Random numbers are generated for each aspect of the game state, and are used for calculating the hash
	inline static std::array<std::array<uint64_t, 24>, 2> piecesArray = {}; // color, square index
	inline static uint64_t sideToMove = 0;
};