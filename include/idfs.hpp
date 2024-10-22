#ifndef IDFS_HPP
#define IDFS_HPP

#include "utils.hpp"

std::vector<Result> idfs(const std::vector<long long>& input);

Result idfs_solver(long long input, int depthLimit);

#endif // IDFS_HPP