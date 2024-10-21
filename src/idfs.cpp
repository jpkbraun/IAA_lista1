#include "idfs.hpp"

std::vector<Result> idfs(const std::vector<long long>& input) {
    std::vector<Result> result;
    int depthLimit = 0;
    for (int i = 0; i < input.size(); ++i) {
        Result subResult = idfs_solver(input[i], depthLimit);
        // while(subResult.resultLength == -1) {
        //     depthLimit++;
        //     subResult = idfs_solver(input[i], depthLimit);
        // }
        result.push_back(subResult);
    }
}

Result idfs_solver(long long input, int depthLimit) {
    auto start = std::chrono::high_resolution_clock::now();
    float expandedNodes = 0;
    float resultLength = -1; // Use -1 to indicate failure to find a solution
    float timeElapsed = 0.0f;
    float meanHeuristic = 0.0f;
    float initialHeuristic = (float)getManhattanDistance8P(input);

    // // Check if the input is already the goal state
    // if (isGoalState(input)) {
    //     auto end = std::chrono::high_resolution_clock::now();
    //     timeElapsed = std::chrono::duration<float>(end - start).count();
    //     Result result = Result(expandedNodes, 0, timeElapsed, meanHeuristic, initialHeuristic);
    //     return result;
    // }

    // // If depth limit is exhausted, return failure
    // if (depthLimit <= 0) {
    //     return Result(expandedNodes, resultLength, timeElapsed, meanHeuristic, initialHeuristic);
    // }

    // // Try all possible moves from the current state
    // std::vector<int> possibleMoves = getPossibleMoves8P(input, -1);
    // expandedNodes++; // Increment expanded nodes counter

    // for (int move : possibleMoves) {
    //     long long nextState = getNextState(input, move);
    //     // Recursively solve with decreased depth limit
    //     Result subResult = idfs_solver(nextState, depthLimit - 1);
    //     if (subResult.resultLength != -1) { // If a solution is found
    //         resultLength = subResult.resultLength + 1; // Increment the solution path length
    //         auto end = std::chrono::high_resolution_clock::now();
    //         timeElapsed = std::chrono::duration<float>(end - start).count();
    //         Result result = Result(expandedNodes + subResult.expandedNodes, resultLength, timeElapsed, meanHeuristic, initialHeuristic);
    //         return result;
    //     }
    // }

    return Result(expandedNodes, resultLength, timeElapsed, meanHeuristic, initialHeuristic); // Return failure result if no solution found
}