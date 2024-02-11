#include <iostream>
#include "ER_POL.h"
#include "LE.h"

int main(void)
{
    ER_POL pol;
    LE lin_sys;

    pol.set_power(5);
    std::cout << pol.get_need_der_count() << std::endl;
    pol.find_derivatives(pol.get_need_der_count());
    pol.output_p_coef();
    std::cout << std::endl;
    pol.calc_arg(2.0);
    pol.output_c_coef();


    // lin_sys.mat = {
    //     {1, 3, 4},
    //     {4, 2, 8}
    // };

    // // решение системы
    // if (lin_sys.solve())
    // {
    //     lin_sys.output_mat();
    //     lin_sys.output_solution();
    // }
    // else
    // {
    //     std::cout << lin_sys.get_last_error() << std::endl;
    // }

    std::cout << std::endl;

    system("PAUSE");

    return 0;
}
