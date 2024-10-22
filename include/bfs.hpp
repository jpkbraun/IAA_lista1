#ifndef BFS_HPP
#define BFS_HPP

#include "utils.hpp"
#include <deque>
#include <unordered_set>
#include "result.hpp"

std::vector<Result> bfs(const std::vector<long long>& input);

Result bfs_solver(long long input);

#endif // BFS_HPP