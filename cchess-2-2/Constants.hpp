#pragma once

namespace space
{
    // Boardspace
    namespace board
    {
        // The number of spaces in a row
        const constexpr int sideTileCount = 8;

        // The total spaces on the board
        const constexpr int boardArea = sideTileCount * sideTileCount;
    }

    // Pixelspace
    namespace screen
    {
        // The number of pixels on the side of a space
        const constexpr int tileWidth = 16;

        // The total pixels in a space
        const constexpr int tileArea = tileWidth * tileWidth;

        // The number of pixels on the side of the board
        const constexpr int boardWidth = tileWidth * board::sideTileCount;

        // The total pixels in the board
        const constexpr int totalArea = boardWidth * boardWidth;

        namespace output
        {
            // Scale of the game
            const constexpr int gameScale = 2;

            // The number of pixels on the side of a space, scaled by render output
            const constexpr int otileWidth = tileWidth * gameScale;

            // The number of pixels on the side of the entire board, scaled by render output
            const constexpr int oboardWidth = boardWidth * gameScale;

            // The number of pixels on the side of the entire board, scaled by render output, minus one tile to act as an index
            const constexpr int oboardLIndex = boardWidth - tileWidth;
        }
    }
}
