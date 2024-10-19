#ifndef BFS_HPP
#define BFS_HPP

#include "utils.hpp"
#include <deque>
#include <unordered_set>

std::vector<std::vector<float>> bfs(const std::vector<std::vector<int>>& input);

std::vector<float> bfs_solver(const std::vector<int>& input);

#endif // BFS_HPP