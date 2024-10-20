#include "utils.hpp"

int chooseAlg(const std::string& input) {
    if (input == "-bfs") return 1;
    if (input == "-idfs") return 2;
    if (input == "-astar") return 3;
    if (input == "-idastar") return 4;
    if (input == "-gbfs") return 5;
    return 0;
}

std::vector<std::vector<int>> parseInput(char** argv, int argc) {
    std::vector<std::vector<int>> result;
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
        std::vector<int> state;
        int num;
        printf("token: %s\n", token.c_str());
        while (tokenStream >> num) {
            state.push_back(num);
        }
        
        result.push_back(state);
    }
    
    return result;
}

void printVecOfVec(const std::vector<std::vector<int>>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            printf("%d ", vec[i][j]);
        }
        printf("\n");
    }
}

void printState(const std::vector<int>& state) {
    for (int i = 0; i < state.size(); ++i) {
        printf("%d ", state[i]);
    }
    printf("\n");
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

int isGoalState(const std::vector<int>& state) {
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] != i) return 0;
    }
    return 1;
}

void printResults(const std::vector<std::vector<float>>& results) {
    for (int i = 0; i < results.size(); ++i) {
        printf("%f,%f,%f,%f,%f\n", results[i][0], results[i][1], results[i][2], results[i][3], results[i][4]);
    }
}

std::vector<int> getPossibleMoves8P(const std::vector<int>& state, int lastMove) {
    std::vector<int> moves;
    int zeroIndex = -1;
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] == 0) {
            zeroIndex = i;
            break;
        }
    }
    // 3+, can move upward
    if (zeroIndex / 3 != 0 && lastMove != DOWN) {
        moves.push_back(UP);
    }
    // Not 0, 3, 6, can move to the left
    if (zeroIndex % 3 != 0 && lastMove != RIGHT) {
        moves.push_back(LEFT);
    }
    // Not 2, 5, 8, can move to the right
    if (zeroIndex % 3 != 2 && lastMove != LEFT) {
        moves.push_back(RIGHT);
    }
    // 5-, can move downward
    if (zeroIndex / 3 != 2 && lastMove != UP) {
        moves.push_back(DOWN);
    }
    return moves;
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