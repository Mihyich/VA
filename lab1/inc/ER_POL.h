#ifndef ER_POL_H
#define ER_POL_H

#include <iostream>
#include <vector>
#include "definers.h"

class ER_POL
{
private:
    size_t power = 0;
    std::vector<std::vector<double>> p_coef; // коэффициенты при производных
    std::vector<std::vector<double>> c_coef; // коэффициенты при производных точек

public:
    void set_power(size_t power);

    size_t get_need_der_count(void) const;

    void find_derivatives(size_t power);

    void calc_arg(double x);

    void output_p_coef(void) const;

    void output_c_coef(void) const;
};

#endif // ER_POL_H
