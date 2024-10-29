#include "utils.hpp"

int chooseAlg(const std::string& input) {
    if (input == "-bfs") return 1;
    if (input == "-idfs") return 2;
    if (input == "-astar") return 3;
    if (input == "-idastar") return 4;
    if (input == "-gbfs") return 5;
    return 0;
}

void printResults(const std::vector<Result>& results) {
    for (int i = 0; i < results.size(); ++i) {
        printf("%d,%d,%f,%f,%d\n", results[i].expandedNodes, results[i].resultLength, results[i].timeElapsed, results[i].meanHeuristic, results[i].initialHeuristic);
    }
}

int getZeroPos(long long state) {
    for (int i = 0; i < 9; ++i) {
        if ((state & 0xF) == 0) {
            return i; 
        }
        state >>= 4;
    }
    return -1;
}

int getZeroPos15P(long long state) {
    for (int i = 0; i < 16; ++i) {
        if ((state & 0xF) == 0) {
            return i; 
        }
        state >>= 4;
    }
    return -1;
}

std::vector<long long> parseInput(char** argv, int argc, int *puzzleSize) {
    std::vector<long long> result;
    // Combine all arguments from argv[2] onward into a single string
    std::ostringstream inputStream;
    for (int i = 2; i < argc; ++i) {
        inputStream << argv[i];
        if (i < argc - 1) {
            inputStream << " ";
        }
    }

    std::istringstream iss(inputStream.str());
    std::string token;
    while (std::getline(iss, token, ',')) {
        std::istringstream tokenStream(token);
        long long state = 0;
        long long num;
        int i = 0;
        while (tokenStream >> num) {
            state |= (num << (4 * i));
            ++i;
        }
        *puzzleSize = i;
        result.push_back(state);
    }
    
    return result;
}

void printVecOfVec(const std::vector<long long>& results) {
    for (int j = 0; j < results.size(); ++j) {
        for (int i = 0; i < 9; ++i) {
            // Extract the 4-bit chunk representing the tile at position i
            int tile = (results[j] >> (i * 4)) & 0xF;
            // Print the tile value
            printf("%d ", tile);
            
            // Print a newline after every 3 tiles to form a 3x3 grid
            if (i % 3 == 2) {
                printf("\n");
            }
        }
    }
}

void printVecOfVec15P(const std::vector<long long>& results) {
    for (int j = 0; j < results.size(); ++j) {
        printState15P(results[j]);
    }
}

void printState(long long state) {
    for (int i = 0; i < 9; ++i) {
        printf("%d ", state & 0xF);
        state >>= 4;
        if (i % 3 == 2) {
            printf("\n");
        }
    }
    printf("\n");
}

void printState15P(long long state) {
    for (int i = 0; i < 16; ++i) {
        printf("%d ", state & 0xF);
        state >>= 4;
        if (i % 4 == 3) {
            printf("\n");
        }
    }
    printf("\n");
}

int getManhattanDistance8P(long long state) {
    int distance = 0;
    for (int i = 0; i < 9; ++i) {
        // Extract the value of the tile at position i
        int tileValue = (state >> (4 * i)) & 0xF;

        // Skip if it is the zero tile
        if (tileValue == 0) {
            continue;
        }

        // Calculate the current row and column
        int row = i / 3;
        int col = i % 3;

        // Calculate the goal row and column for this tile value
        int goalRow = (tileValue) / 3;
        int goalCol = (tileValue) % 3;

        // Accumulate the Manhattan distance for this tile
        distance += abs(row - goalRow) + abs(col - goalCol);
    }
    return distance;
}

int getManhattanDistance15P(long long state) {
    int distance = 0;
    for (int i = 0; i < 16; ++i) {
        // Extract the value of the tile at position i
        int tileValue = (state >> (4 * i)) & 0xF;

        // Skip if it is the zero tile
        if (tileValue == 0) {
            continue;
        }

        // Calculate the current row and column
        int row = i / 4;
        int col = i % 4;

        // Calculate the goal row and column for this tile value
        int goalRow = (tileValue) / 4;
        int goalCol = (tileValue) % 4;

        // Accumulate the Manhattan distance for this tile
        distance += abs(row - goalRow) + abs(col - goalCol);
    }
    return distance;
}

int getPossibleMoves8P(long long state, int lastMove) {
    int moves = 0; 
    int zeroPos = getZeroPos(state);
    // 3+, can move upward
    if (zeroPos / 3 != 0 && lastMove != DOWN) {
        moves |= UP;
    }
    // Not 0, 3, 6, can move to the left
    if (zeroPos % 3 != 0 && lastMove != RIGHT) {
        moves |= LEFT;
    }
    // Not 2, 5, 8, can move to the right
    if (zeroPos % 3 != 2 && lastMove != LEFT) {
        moves |= RIGHT;
    }
    // 5-, can move downward
    if (zeroPos / 3 != 2 && lastMove != UP) {
        moves |= DOWN;
    }
    return moves;
}

int getPossibleMoves15P(long long state, int lastMove) {
    int moves = 0; 
    int zeroPos = getZeroPos15P(state);
    // 4+, can move upward
    if (zeroPos / 4 != 0 && lastMove != DOWN) {
        moves |= UP;
    }
    // Not 0, 3, 6, can move to the left
    if (zeroPos % 4 != 0 && lastMove != RIGHT) {
        moves |= LEFT;
    }
    // Not 2, 5, 8, can move to the right
    if (zeroPos % 4 != 3 && lastMove != LEFT) {
        moves |= RIGHT;
    }
    // 5-, can move downward
    if (zeroPos / 4 != 3 && lastMove != UP) {
        moves |= DOWN;
    }
    return moves;
}

int isGoalState(long long state) {
    for (int i = 0; i < 9; ++i) {
        if ((state & 0xF) != i) return 0;
        state >>= 4;
    }
    return 1;
}

int isGoalState15P(long long state) {
    for (int i = 0; i < 16; ++i) {
        if ((state & 0xF) != i) return 0;
        state >>= 4;
    }
    return 1;
}

long long getNextState(long long state, int move) {
    long long newState = state;
    int zeroIndex = getZeroPos(state);
    int targetIndex = zeroIndex; // The index of the tile to swap with

    // Determine the index of the tile to swap with based on the move
    switch (move) {
        case UP:
            targetIndex -= 3;
            break;
        case LEFT:
            targetIndex -= 1;
            break;
        case RIGHT:
            targetIndex += 1;
            break;
        case DOWN:
            targetIndex += 3;
            break;
    }

    // Extract the value of the tile at the target index
    long long targetTile = (state >> (4 * targetIndex)) & 0xF;

    // Clear the bits at the current zero position
    newState &= ~(0xFLL << (4 * zeroIndex));

    // Set the target tile at the zero's original position
    newState |= (targetTile << (4 * zeroIndex));

    // Clear the bits at the target position
    newState &= ~(0xFLL << (4 * targetIndex));

    // Set zero (0) at the target position
    newState |= (0LL << (4 * targetIndex));

    return newState;
}

long long getNextState15P(long long state, int move) {
    long long newState = state;
    int zeroIndex = getZeroPos15P(state);
    int targetIndex = zeroIndex; // The index of the tile to swap with

    // Determine the index of the tile to swap with based on the move
    switch (move) {
        case UP:
            targetIndex -= 4;
            break;
        case LEFT:
            targetIndex -= 1;
            break;
        case RIGHT:
            targetIndex += 1;
            break;
        case DOWN:
            targetIndex += 4;
            break;
    }

    // Extract the value of the tile at the target index
    long long targetTile = (state >> (4 * targetIndex)) & 0xF;

    // Clear the bits at the current zero position
    newState &= ~(0xFLL << (4 * zeroIndex));

    // Set the target tile at the zero's original position
    newState |= (targetTile << (4 * zeroIndex));

    // Clear the bits at the target position
    newState &= ~(0xFLL << (4 * targetIndex));

    // Set zero (0) at the target position
    newState |= (0LL << (4 * targetIndex));

    return newState;
}