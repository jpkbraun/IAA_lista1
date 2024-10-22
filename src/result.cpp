#include "result.hpp"

Result::Result(int expandedNodes, int resultLength, float timeElapsed, float meanHeuristic, int initialHeuristic) {
    this->expandedNodes = expandedNodes;
    this->resultLength = resultLength;
    this->timeElapsed = timeElapsed;
    this->meanHeuristic = meanHeuristic;
    this->initialHeuristic = initialHeuristic;
}