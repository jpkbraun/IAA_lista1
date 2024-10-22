#ifndef IDASTAR_HPP
#define IDASTAR_HPP

#include "utils.hpp"
#include <vector>
#include <unordered_set>
#include <chrono>
#include "node.hpp"

std::vector<Result> idastar(const std::vector<long long>& input);
Result idastar_solver(long long input);
int dfs(Node& n, int g, int threshold, int& expandedNodes, std::unordered_set<long long>& closed, int& totalHeuristic, int& whenInserted);

#endif // IDASTAR_HPP