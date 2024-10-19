#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include "node.hpp"

enum Algorithm {
    BFS,
    IDFS,
    ASTAR,
    IDASTAR,
    GBFS
};

enum move {
    UP,
    LEFT,
    RIGHT,
    DOWN
};

// Custom hash function for std::vector<int>
struct VectorHash {
    std::size_t operator()(const std::vector<int>& vec) const {
        std::size_t hash = 0;
        for (int num : vec) {
            hash ^= std::hash<int>()(num) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

// Equality function for std::vector<int>
struct VectorEqual {
    bool operator()(const std::vector<int>& a, const std::vector<int>& b) const {
        return a == b;
    }
};

int chooseAlg(const std::string& input);

std::vector<std::vector<int>> parseInput(char** argv, int argc);

void printVecOfVec(const std::vector<std::vector<int>>& vec);

void printState(const std::vector<int>& state);

int getManhattanDistance8P(const std::vector<int>& state);

int getManhattanDistance15P(const std::vector<int>& state);

int isGoalState(const std::vector<int>& state);

void printResults(const std::vector<std::vector<float>>& results);

std::vector<int> getPossibleMoves8P(const std::vector<int>& state, int lastMove);

std::vector<float> populateResult(float expandedNodes, float resultLength, float timeElapsed, float meanHeuristic, float initialHeuristic);

#endif // UTILS_HPP