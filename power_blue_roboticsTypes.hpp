#ifndef power_blue_robotics_TYPES_HPP
#define power_blue_robotics_TYPES_HPP

#include <base/Float.hpp>
#include <base/Time.hpp>

namespace power_blue_robotics {
    struct Voltage {
        base::Time time;
        double value = base::unknown<double>();
    };
    struct Current {
        base::Time time;
        double value = base::unknown<double>();
    };
}

#endif
