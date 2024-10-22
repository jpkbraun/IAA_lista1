#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "utils.hpp"
#include <deque>
#include <unordered_set>
#include "result.hpp"
#include <bits/stdc++.h>

std::vector<Result> astar(const std::vector<long long>& input);

Result astar_solver(long long input);

#endif // ASTAR_HPP