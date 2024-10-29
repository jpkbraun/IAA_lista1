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


#define UP 1
#define LEFT 2
#define RIGHT 4
#define DOWN 8
#define PUZZLE_SIZE_8P 9
#define PUZZLE_SIZE_15P 16

int chooseAlg(const std::string& input);

int getManhattanDistance15P(long long state);

void printResults(const std::vector<Result>& results);

int getZeroPos(long long state);

int getZeroPos15P(long long state);

std::vector<long long> parseInput(char** argv, int argc, int *puzzleSize);

void printVecOfVec(const std::vector<long long>& results);

void printVecOfVec15P(const std::vector<long long>& results);

void printState(long long state);

void printState15P(long long state);

int getManhattanDistance8P(long long state);

int getPossibleMoves8P(long long state, int lastMove);

int getPossibleMoves15P(long long state, int lastMove);

int isGoalState(long long state);

int isGoalState15P(long long state);

long long getNextState(long long state, int move);

long long getNextState15P(long long state, int move);

#endif // UTILS_HPP