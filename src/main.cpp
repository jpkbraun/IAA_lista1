#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "utils.hpp"
#include "bfs.hpp"
#include "idfs.hpp"
#include "astar.hpp"
#include "idastar.hpp"
#include "gbfs.hpp"

int main(int argc, char *argv[]) {
    int chosenAlg = 0;
    chosenAlg = chooseAlg(argv[1]);
    std::vector<long long> input = parseInput(argv, argc);
    std::vector<std::vector<float>> results;
    switch (chosenAlg) {
        case 1:
            results = bfs(input);
            break;
        case 2:
            // results = idfs(input);
            break;
        case 3:
            // results = astar(input);
            break;
        case 4:
            // results = idastar(input);
            break;
        case 5:
            // results = gbfs(input);
            break;
        default:
            printf("Invalid algorithm\n");
            break;
    }
    printResults(results);
    return 0;
}