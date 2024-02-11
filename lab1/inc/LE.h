#ifndef LE_H
#define LE_H

#include <vector>
#include <math.h>
#include <iostream>
#include "definers.h"

class LE
{
public:
    std::vector<std::vector<double>> mat;
    std::vector<double> solution;

    bool output_mat(void);

    void output_solution(void) const;

    bool solve(void);

    const char *get_last_error(void) const;

private:

    std::string error;

    bool check_sys_size(void) const;

    double determinant() const;

    void calc(void);

};

#endif // LE_CLASS_H
