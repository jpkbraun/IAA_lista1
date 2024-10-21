#include "utils.hpp"

int chooseAlg(const std::string& input) {
    if (input == "-bfs") return 1;
    if (input == "-idfs") return 2;
    if (input == "-astar") return 3;
    if (input == "-idastar") return 4;
    if (input == "-gbfs") return 5;
    return 0;
}

int getManhattanDistance15P(const std::vector<int>& state) {
    int distance = 0;
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] == 0) continue;
        int row = i / 4;
        int col = i % 4;
        int goalRow = state[i] / 4;
        int goalCol = state[i] % 4;
        distance += abs(row - goalRow) + abs(col - goalCol);
    }
    return distance;
}

void printResults(const std::vector<Result>& results) {
    for (int i = 0; i < results.size(); ++i) {
        printf("%d,%d,%f,%f,%d\n", results[i].expandedNodes, results[i].resultLength, results[i].timeElapsed, results[i].meanHeuristic, results[i].initialHeuristic);
    }
}

int getZeroPos(long long state) {
    int zeroPos = -1;
    for (int i = 0; i < 9; ++i) {
        if ((state & 0xF) == 0) {
            zeroPos = i;
            break;
        }
        state >>= 4;
    }
    return zeroPos;
}

std::vector<long long> parseInput(char** argv, int argc) {
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

std::vector<int> getPossibleMoves8P(long long state, int lastMove) {
    std::vector<int> moves;
    int zeroPos = getZeroPos(state);
    // 3+, can move upward
    if (zeroPos / 3 != 0 && lastMove != DOWN) {
        moves.push_back(UP);
    }
    // Not 0, 3, 6, can move to the left
    if (zeroPos % 3 != 0 && lastMove != RIGHT) {
        moves.push_back(LEFT);
    }
    // Not 2, 5, 8, can move to the right
    if (zeroPos % 3 != 2 && lastMove != LEFT) {
        moves.push_back(RIGHT);
    }
    // 5-, can move downward
    if (zeroPos / 3 != 2 && lastMove != UP) {
        moves.push_back(DOWN);
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