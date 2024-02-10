#include "LE.h"

bool LE::output_mat(void)
{
    if (!check_sys_size())
    {
        this->error = "System hasn't correct format";
        return false;
    }

    std::string str;
    size_t row_size;

    for (const auto& row : this->mat)
    {
        str.clear();
        row_size = row.size();

        for (size_t i = 0; i < row_size; ++i)
        {
            if (i == 0)
            {
                str += std::to_string(row[i]);
                str += " X";
                str += std::to_string(i);
                str += "\t";
            }
            else if (i < row_size - 1)
            {
                if (row[i] < 0.0)
                {
                    str += "-\t";
                    str += std::to_string(-row[i]);
                }
                else
                {
                    str += "+\t";
                    str += std::to_string(row[i]);
                }

                str += " X";
                str += std::to_string(i);
                str += "\t";
            }
            else
            {
                str += "=\t";
                str += std::to_string(row[i]);
            }
        }

        std::cout << str << std::endl;
    }

    return true;
}

void LE::output_solution(void) const
{
    size_t nomer = 0;
    for (const auto& el : this->solution)
        std::cout << "X" << nomer++ << " = " << el << "\n";
}

bool LE::solve(void)
{
    if (!check_sys_size())
    {
        this->error = "System hasn't correct format";
        return false;
    }

    if (!(LE_IS_ZERO(determinant())))
    {
        this->error = "System hasn't single solution";
        return false;
    }

    calc();

    return true;
}

const char *LE::get_last_error(void) const
{
    return this->error.data();
}

bool LE::check_sys_size(void) const
{
    size_t m = mat.size();
    bool rt = m;

    for(size_t i = 0; rt && i < m; ++i)
        rt = (m == (mat[i].size() - 1));

    return rt;
}

double LE::determinant() const
{
    int n = this->mat.size();
    std::vector<std::vector<double>> temp = this->mat;
    double det = 1.0;
    double ratio;

    // Приведение матрицы к верхнетреугольному виду методом Гаусса
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            ratio = LE_IS_ZERO(temp[i][i]) ? temp[j][i] / temp[i][i] : 0.f;

            for (int k = i; k < n; ++k)
                temp[j][k] -= ratio * temp[i][k];

        }
    }

    // Детерминант равен произведению элементов главной диагонали полученной верхнетреугольной матрицы
    for (int i = 0; i < n; ++i)
        det *= temp[i][i];

    return det;
}

void LE::calc(void)
{
    std::vector<std::vector<double>> temp_mat = this->mat;
    int n = temp_mat.size();
    int maxRow;
    double factor;

    for (int i = 0; i < n; ++i)
    {
        // Поиск максимального элемента в столбце
        maxRow = i;

        for (int j = i + 1; j < n; ++j)
        {
            if (std::abs(temp_mat[j][i]) > std::abs(temp_mat[maxRow][i]))
                maxRow = j;
        }

        // Обмен строк, чтобы максимальный элемент был наверху
        std::swap(temp_mat[i], temp_mat[maxRow]);

        // Приведение матрицы к верхнетреугольному виду
        for (int j = i + 1; j < n; ++j)
        {
            if (LE_IS_ZERO(temp_mat[i][i]))
            {
                factor = temp_mat[j][i] / temp_mat[i][i];

                for (int k = i; k < n + 1; ++k)
                    temp_mat[j][k] -= factor * temp_mat[i][k];
            }
        }
    }

    // Обратный ход метода Гаусса
    solution.resize(n);

    for (int i = n - 1; i >= 0; --i)
    {
        solution[i] = LE_IS_ZERO(temp_mat[i][i]) ? temp_mat[i][n] / temp_mat[i][i] : 0.0;

        for (int j = i - 1; j >= 0; --j)
            temp_mat[j][n] -= temp_mat[j][i] * solution[i];
    }
}
