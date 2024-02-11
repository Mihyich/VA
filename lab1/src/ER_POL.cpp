#include "ER_POL.h"

void ER_POL::set_power(size_t power)
{
    this->power = power;
}

size_t ER_POL::get_need_der_count(void) const
{
    size_t un = this->power + 1;
    if (un % 2) ++un;
    return un / 2 - 1;
}

void ER_POL::find_derivatives(size_t power)
{
    p_coef.resize(power + 1, std::vector<double>(this->power + 1));

    // первый проход
    for (double &el : p_coef[0])
        el = 1.0;

    // все остальное
    for (size_t j = 0; j < this->power + 1; ++j)
        for (size_t i = 1; i < power + 1; ++i)
            p_coef[i][j] = p_coef[i - 1][j] * double(j + 1 > i ? (j + 1) - i : 0);
}

void ER_POL::calc_arg(double x)
{
    if (!p_coef.size())
        return;

    c_coef.clear();
    c_coef = p_coef;

    size_t i;
    size_t j;

    for (size_t t = 1; t < p_coef[0].size(); ++t)
    {
        j = t;

        for (size_t i = 0; j < p_coef[t].size() && i < p_coef.size(); ++i, ++j)
            c_coef[i][j] *= x;

        x *= x;
    }
}

void ER_POL::output_p_coef(void) const
{
    for (const auto &row : p_coef)
    {
        for (const double &el : row)
            std::cout << el << "\t";

        std::cout << std::endl;
    }
}

void ER_POL::output_c_coef(void) const
{
    for (const auto &row : c_coef)
    {
        for (const double &el : row)
            std::cout << el << "\t";

        std::cout << std::endl;
    }
}
