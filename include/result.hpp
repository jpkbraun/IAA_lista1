#ifndef RESULT_HPP
#define RESULT_HPP

class Result {
    public:
        Result(int expandedNodes, int resultLength, float timeElapsed, float meanHeuristic, int initialHeuristic);
        int expandedNodes;
        int resultLength;
        float timeElapsed;
        float meanHeuristic;
        int initialHeuristic;
};

#endif // RESULT_HPP