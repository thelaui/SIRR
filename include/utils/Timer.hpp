#ifndef TIMER_HPP
#define TIMER_HPP

#include "SFML/System.hpp"

#include "utils/debug.hpp"

namespace SIRR {

class Timer {

    public:
        Timer():
            clock_() {}

        double get_elapsed_time() const {
            return clock_.GetElapsedTime();
        }

        void print_elapsed_time() const {
            MESSAGE("%f seconds elapsed.", clock_.GetElapsedTime());
        }

        void reset() {
            clock_.Reset();
        }


    private:
        sf::Clock clock_;
};

}

#endif //TIMER_HPP


