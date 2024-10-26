#ifndef IDASTAR_HPP
#define IDASTAR_HPP

#include "utils.hpp"
#include <deque>
#include <unordered_set>
#include "result.hpp"
#include <bits/stdc++.h>
#include <memory>
#include <tuple>

std::vector<Result> idastar(const std::vector<long long>& input);

Result idastar_solver(long long input);

#endif // IDASTAR_HPP