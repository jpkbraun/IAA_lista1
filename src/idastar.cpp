#include "idastar.hpp"

std::vector<Result> idastar(const std::vector<long long>& input) {
    std::vector<Result> result;
    for (int i = 0; i < input.size(); ++i) {
        result.push_back(idastar_solver(input[i]));
    }
    return result;
}

std::chrono::time_point<std::chrono::high_resolution_clock> IDASTAR_start;
int IDASTAR_expandedNodes;
int IDASTAR_resultLength;
float IDASTAR_timeElapsed;
double IDASTAR_meanHeuristic;
int IDASTAR_initialHeuristic;
int IDASTAR_totalHeuristic;
int IDASTAR_calculatedHeuristic;

std::tuple<int, std::unique_ptr<Result>> idastar_recursive(long long state, int path, int move, int fLimit){
    int f = path + getManhattanDistance8P(state);
    if (f > fLimit){
        return std::make_tuple(f, nullptr);
    }
    if (isGoalState(state)) {
        auto end = std::chrono::high_resolution_clock::now();
        IDASTAR_timeElapsed = std::chrono::duration<float>(end - IDASTAR_start).count();
        IDASTAR_resultLength = path;
        IDASTAR_meanHeuristic = (double)IDASTAR_totalHeuristic / (double)IDASTAR_calculatedHeuristic;
        return std::make_tuple(INT_MAX, std::make_unique<Result>(IDASTAR_expandedNodes, IDASTAR_resultLength, IDASTAR_timeElapsed, IDASTAR_meanHeuristic, IDASTAR_initialHeuristic)); 
    }
    int possibleMoves = getPossibleMoves8P(state, move);
    IDASTAR_expandedNodes++;
    int movement = 1;
    int nextLimit = INT_MAX;
    while (possibleMoves != 0) {
        int rec_limit = INT_MAX;
        if (possibleMoves & 0x1){
            long long nextState = getNextState(state, movement);
            std::unique_ptr<Result> solution;
            int h = getManhattanDistance8P(nextState);
            IDASTAR_calculatedHeuristic++;
            IDASTAR_totalHeuristic += h;
            std::tie(rec_limit, solution) = idastar_recursive(nextState, path + 1, movement, fLimit);
            if (solution != nullptr){
                return std::make_tuple(INT_MAX, std::move(solution));
            }
        }
        movement *= 2;
        possibleMoves = possibleMoves >> 1;
        nextLimit = std::min(nextLimit, rec_limit);
    }
    return std::make_tuple(nextLimit, nullptr);
}

Result idastar_solver(long long input) {
    IDASTAR_start = std::chrono::high_resolution_clock::now();
    IDASTAR_expandedNodes = 0;
    IDASTAR_resultLength = 0;
    IDASTAR_timeElapsed = 0.0;
    IDASTAR_meanHeuristic = 0.0;
    IDASTAR_initialHeuristic = getManhattanDistance8P(input);
    IDASTAR_totalHeuristic = IDASTAR_initialHeuristic;
    IDASTAR_calculatedHeuristic = 1;
    int fLimit = IDASTAR_initialHeuristic;

    while (fLimit < INT_MAX) {
        auto result = idastar_recursive(input, 0, -1, fLimit);

        if (std::get<1>(result) != nullptr){
            return Result(IDASTAR_expandedNodes, IDASTAR_resultLength, IDASTAR_timeElapsed, IDASTAR_meanHeuristic, IDASTAR_initialHeuristic);
        }
        fLimit = std::get<0>(result);
    }
    throw std::runtime_error("Unsolvable state");
}