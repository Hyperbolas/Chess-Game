#ifndef calc_hyperbola
#define calc_hyperbola

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>
#include "lang.h"
typedef std::pair<State, std::vector<int>> Step;

class Minimax {
   private:
    const int depth;
    Record record;
    double (*h)(const State&);
    double next_o(const State&, const double, const int);
    double next_x(const State&, const double, const int);

   public:
    Minimax(int d, double (*_h)(const State&), const Record& rec = {}) : depth(d), h(_h), record(rec) {}
    const Record& explored() const { return record; }
    const Step& best_step(const State& s);
};

double simple_heuristic(const State& s);

#endif