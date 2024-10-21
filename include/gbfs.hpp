#ifndef GBFS_HPP
#define GBFS_HPP

#include "utils.hpp"
#include <deque>
#include <unordered_set>
#include "result.hpp"
#include <bits/stdc++.h>

std::vector<Result> gbfs(const std::vector<long long>& input);

Result gbfs_solver(long long input);

#endif // GBFS_HPP