#include "utils.hpp"

int chooseAlg(const std::string& input) {
    if (input == "-bfs") return 1;
    if (input == "-idfs") return 2;
    if (input == "-astar") return 3;
    if (input == "-idastar") return 4;
    if (input == "-gbfs") return 5;
    return 0;
}

int getManhattanDistance8P(const std::vector<int>& state) {
    int distance = 0;
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] == 0) continue;
        int row = i / 3;
        int col = i % 3;
        int goalRow = state[i] / 3;
        int goalCol = state[i] % 3;
        distance += abs(row - goalRow) + abs(col - goalCol);
    }
    return distance;
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

void printResults(const std::vector<std::vector<float>>& results) {
    for (int i = 0; i < results.size(); ++i) {
        printf("%f,%f,%f,%f,%f\n", results[i][0], results[i][1], results[i][2], results[i][3], results[i][4]);
    }
}

std::vector<float> populateResult(float expandedNodes, float resultLength, float timeElapsed, float meanHeuristic, float initialHeuristic) {
    std::vector<float> result;
    result.push_back(expandedNodes);
    result.push_back(resultLength);
    result.push_back(timeElapsed);
    result.push_back(meanHeuristic);
    result.push_back(initialHeuristic);
    return result;
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
        if ((state & 0xF) == 0) {
            continue;
        }
        int row = i / 3;
        int col = i % 3;
        long long position = state & 0xF;
        int goalRow = position / 3;
        int goalCol = position % 3;
        distance += abs(row - goalRow) + abs(col - goalCol);
        state >>= 4;
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

int isGoalState(long long state) {
    for (int i = 0; i < 9; ++i) {
        if ((state & 0xF) != i) return 0;
        state >>= 4;
    }
    return 1;
}

