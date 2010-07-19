#ifndef __GOCUP_HILLCLIMBER_HH_
#define __GOCUP_HILLCLIMBER_HH_

#include <vector>
#include <set>
#include <map>

#include "pmedproblem.hh"
#include "pmedsolver.hh"
#include "options.hh"
#include "solution.hh"

class GLHillClimber : PMedSolver {
    typedef std::vector<int> Vector_int;
    typedef std::set<int> Set_int;
    typedef std::map<int, double> Map_int_dbl;
    // typedef std::vector<Solution> Population;

    public:
        GLHillClimber(PMedProblem* pmp) :
            PMedSolver(pmp),
            _best_soln(pmp->N()),
            _current_soln(pmp->N()),
            _probs(),
            N(pmp->N())
        { ; }

        virtual ~GLHillClimber() { ; }

        virtual void solve(const Options& opt);

        virtual const Solution &best_solution() {
            return _best_soln;
        }

    private:
        void update_probs(Solution& soln);
        Solution _best_soln;
        Solution _current_soln;
        Map_int_dbl _probs;
        int N;
        // Population _pop;
};

#endif
