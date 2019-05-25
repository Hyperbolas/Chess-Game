#ifndef minimax_hyperbola
#define minimax_hyperbola

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include "calc.h"
#include "lang.h"

using std::max;
using std::min;
using std::pair;
using std::unordered_map;
using std::unordered_set;
using std::vector;


double Minimax::next_x(const State& s, const double lim_maxx, const int depth) {
    if (depth == 0) return h(s);
    const Expansion& expanded = expand_state(s.opposite(), record);
    
    // Check leaves
    for (const Step& e : expanded /* reversed */) {
        // Check whether player x has heuristic value -1, which means x must win.
        if (h(e.first) == MIN_HEURISTIC) return MAX_HEURISTIC;
    }

    // Search tree
    double maxx = h(s);  // Current o's heursistic (skip)
    for (const Step& e : expanded) {
        const double h = -1 * next_o(e.first, maxx, depth - 1);  // Convert player x's heuristic to o's heuristic
        if (h >= lim_maxx) return h;
        maxx = max(maxx, h);
    }
    return maxx;
}

double Minimax::next_o(const State& s /* reversed */, const double lim_minn, const int depth) {
    if (depth == 0) return -1.0 * h(s);  // Convert player x's heuristic ot o's heuristic
    const Expansion& expanded = expand_state(s.opposite(), record);

    // Check leaves
    for (const Step& e : expanded) {
        if (h(e.first) == MIN_HEURISTIC) return MIN_HEURISTIC;
    }

    // Search tree
    double minn = -1.0 * h(s);
    for (const Step& e : expanded) {
        const double h = next_x(e.first, minn, depth - 1);
        if (h <= lim_minn) return h;
        minn = min(minn, h);
    }
    return minn;
}

const Step& Minimax::best_step(const State& s) {
    const Expansion& expanded = expand_state(s, record);
    
    // Check leaves
    for (auto&& e : expanded) {
        if (h(e.first) == MIN_HEURISTIC) return (Step&)e;
    }

    double minn = h(s);
    vector<Step*> candidates;

    // Serach tree
    for (auto&& e : expanded) {
        double h = next_x(e.first, minn, depth - 1);

        // Check if this step must lead to winning
        if (h == MIN_HEURISTIC) {
            return (Step&)e;
        }
        if (h < minn) {
            minn = h;
            candidates.clear();
        }
        if (h == minn) {
            candidates.push_back((Step*)&e);
        }
    }

    int random_index = rand() % candidates.size();
    return *candidates[random_index];
}

#endif