#include "idastar.hpp"

std::vector<Result> idastar(const std::vector<long long>& input) {
    std::vector<Result> result;
    for (int i = 0; i < input.size(); ++i) {
        result.push_back(idastar_solver(input[i]));
    }
    return result;
}

Result idastar_solver(long long input) {
    auto start = std::chrono::high_resolution_clock::now();
    int expandedNodes = 0;
    int resultLength = 0;
    float timeElapsed = 0.0;
    float meanHeuristic = 0.0;
    int initialHeuristic = getManhattanDistance8P(input);
    int totalHeuristic = 0;
    int whenInserted = 0;

    if (initialHeuristic == INTMAX_MAX) {
        return Result(0, -1, 0.0, 0.0, initialHeuristic);  // Return invalid result for unsolvable puzzles
    }

    Node root(input, 0, initialHeuristic, -1, 0);
    int threshold = initialHeuristic;  // Start with initial heuristic as the threshold

    std::unordered_set<long long> closed;  // Closed set to avoid re-expansion of nodes

    while (true) {
        // Perform a depth-limited search up to the current threshold
        int temp = dfs(root, 0, threshold, expandedNodes, closed, totalHeuristic, whenInserted);
        
        if (temp == -1) {  // Goal state found
            auto end = std::chrono::high_resolution_clock::now();
            timeElapsed = std::chrono::duration<float>(end - start).count();
            meanHeuristic = (float)totalHeuristic / (float)expandedNodes;
            return Result(expandedNodes, resultLength, timeElapsed, meanHeuristic, initialHeuristic);
        }

        if (temp == INTMAX_MAX) {  // No solution exists
            return Result(expandedNodes, -1, timeElapsed, meanHeuristic, initialHeuristic);
        }

        // Update the threshold to the next minimum bound
        threshold = temp;
    }
}

int dfs(Node& n, int g, int threshold, int& expandedNodes, std::unordered_set<long long>& closed, int& totalHeuristic, int& whenInserted) {
    int f = g + n.h;  // Calculate f(n) = g(n) + h(n)
    if (f > threshold) return f;  // Prune if f exceeds the current threshold

    if (isGoalState(n.state)) return -1;  // Goal found, return success signal

    closed.insert(n.state);  // Mark node as expanded
    totalHeuristic += n.h;
    expandedNodes++;

    int minThreshold = INTMAX_MAX;  // Track the next threshold for future iterations

    int possibleMoves = getPossibleMoves8P(n.state, n.lastMove);
    int movement = 1; 
    while (possibleMoves != 0) {
        if (movement & 0x1) {
            long long nextState = getNextState(n.state, movement);
            if (closed.find(nextState) == closed.end()) {
                int nextH = getManhattanDistance8P(nextState);
                if (nextH < INTMAX_MAX) {
                    Node newNode = Node(nextState, n.g + 1, nextH, movement, whenInserted);
                    whenInserted++;
                    
                    int temp = dfs(newNode, g + 1, threshold, expandedNodes, closed, totalHeuristic, whenInserted);
                    if (temp == -1) return -1;  // Propagate success signal upwards

                    minThreshold = std::min(minThreshold, temp);  // Track the minimum threshold
                }
            }
        }
        movement *= 2;
        possibleMoves = possibleMoves >> 1;
    }

    closed.erase(n.state);  // Unmark the node (important for iterative deepening)
    return minThreshold;
}