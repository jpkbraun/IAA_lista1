#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include "node.hpp"
#include "result.hpp"

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

int chooseAlg(const std::string& input);

int getManhattanDistance15P(const std::vector<int>& state);

void printResults(const std::vector<Result>& results);

int getZeroPos(long long state);

std::vector<long long> parseInput(char** argv, int argc);

void printVecOfVec(const std::vector<long long>& results);

void printState(long long state);

int getManhattanDistance8P(long long state);

std::vector<int> getPossibleMoves8P(long long state, int lastMove);

int isGoalState(long long state);

long long getNextState(long long state, int move);

#endif // UTILS_HPP