#include <iostream>
#include <vector>
#include <cmath>

typedef std::vector<std::vector<double>> Matrix;

void printMatrix(const Matrix& mat) {
    for (const auto& row : mat) {
        for (const auto& val : row) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }
}

Matrix multiply(const Matrix& mat1, const Matrix& mat2) {
    int m = mat1.size();
    int n = mat2[0].size();
    int p = mat2.size();

    Matrix result(m, std::vector<double>(n, 0.0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < p; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}

Matrix transpose(const Matrix& mat) {
    int m = mat.size();
    int n = mat[0].size();

    Matrix result(n, std::vector<double>(m, 0.0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result[j][i] = mat[i][j];
        }
    }

    return result;
}

Matrix createIdentityMatrix(int size) {
    Matrix identity(size, std::vector<double>(size, 0.0));
    for (int i = 0; i < size; ++i) {
        identity[i][i] = 1.0;
    }
    return identity;
}

Matrix performHouseholder(const Matrix& mat) {
    int m = mat.size();
    int n = mat[0].size();

    Matrix q = createIdentityMatrix(m);
    Matrix r = mat;

    for (int k = 0; k < n; ++k) {
        std::vector<double> x(m, 0.0);
        for (int i = k; i < m; ++i) {
            x[i] = r[i][k];
        }

        double norm_x = 0.0;
        for (int i = k; i < m; ++i) {
            norm_x += x[i] * x[i];
        }
        norm_x = sqrt(norm_x);

        std::vector<double> v(m, 0.0);
        for (int i = k; i < m; ++i) {
            v[i] = (i == k) ? x[i] + norm_x : x[i];
        }

        double norm_v = 0.0;
        for (int i = k; i < m; ++i) {
            norm_v += v[i] * v[i];
        }
        norm_v = sqrt(norm_v);

        if (norm_v == 0.0) {
            continue;
        }

        for (int i = k; i < m; ++i) {
            v[i] /= norm_v;
        }

        Matrix vt = transpose({v});

        Matrix H = createIdentityMatrix(m);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                H[i][j] -= 2.0 * v[i] * v[j];
            }
        }
        q = multiply(q, H);
        r = multiply(H, r);
    }
    std::cout << "Q:" << std::endl;
    printMatrix(q);

    std::cout << "R:" << std::endl;
    printMatrix(r);
    return (q,r);
}
