#include "gbfs.hpp"

std::vector<Result> gbfs(const std::vector<long long>& input) {
    std::vector<Result> result;
    for (int i = 0; i < input.size(); ++i) {
        result.push_back(gbfs_solver(input[i]));
    }
    return result;
}

Result gbfs_solver(long long input) {
    auto start = std::chrono::high_resolution_clock::now();
    int expandedNodes = 0;
    int resultLength = 0;
    float timeElapsed = 0.0;
    float meanHeuristic = 0.0;
    int initialHeuristic = getManhattanDistance8P(input);
    int whenInserted = 0;

    std::priority_queue<Node, std::vector<Node>, CompareNode> open;
    if (initialHeuristic < INTMAX_MAX) {
        open.emplace(Node(input, 0, initialHeuristic, -1, 0));
    }
    std::unordered_set<long long> closed;

    while (!open.empty()) {
        Node n = open.top();
        open.pop();
        if (closed.find(n.state) == closed.end()) {
            closed.insert(n.state);
            if (isGoalState(n.state)) {
                resultLength = n.g;
                auto end = std::chrono::high_resolution_clock::now();
                timeElapsed = std::chrono::duration<float>(end - start).count();
                Result result = Result(expandedNodes, resultLength, timeElapsed, meanHeuristic, initialHeuristic);
                return result;
            }
            std::vector<int> possibleMoves = getPossibleMoves8P(n.state, n.lastMove);
            expandedNodes++;
            for (int i = 0; i < possibleMoves.size(); ++i) {
                long long nextState = getNextState(n.state, possibleMoves[i]);
                if (getManhattanDistance8P(nextState) < INTMAX_MAX) {
                    Node newNode = n.makeNode(n, possibleMoves[i], nextState, whenInserted);
                    whenInserted++;
                    open.push(newNode);
                }
            }
        }
    }
}