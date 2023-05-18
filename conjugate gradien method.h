#include <iostream>
#include <vector>

double dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    int n = a.size();
    double result = 0.0;
    for (int i = 0; i < n; ++i) {
        result += a[i] * b[i];
    }
    return result;
}

std::vector<double> multiply(const std::vector<std::vector<double>>& A, const std::vector<double>& v) {
    int n = A.size();
    std::vector<double> result(n, 0.0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] += A[i][j] * v[j];
        }
    }
    return result;
}

std::vector<double> conjugateGradient(const std::vector<std::vector<double>>& A, const std::vector<double>& b, double tolerance = 1e-6) {
    int n = A.size();

    std::vector<double> x(n, 0.0);              // Начальное приближение x
    std::vector<double> r = b;                  // Невязка r = b - Ax
    std::vector<double> p = r;                  // Направление спуска p
    double rsold = dotProduct(r, r);       // Квадрат нормы невязки r

    while (rsold > tolerance * tolerance) {
        std::vector<double> Ap = multiply(A, p); // A * p
        double alpha = rsold / dotProduct(p, Ap);

        // Обновляем приближение и невязку
        for (int i = 0; i < n; ++i) {
            x[i] += alpha * p[i];
            r[i] -= alpha * Ap[i];
        }

        double rsnew = dotProduct(r, r);   // Новый квадрат нормы невязки
        double beta = rsnew / rsold;       // Коэффициент бета для обновления направления спуска

        // Обновляем направление спуска
        for (int i = 0; i < n; ++i) {
            p[i] = r[i] + beta * p[i];
        }

        rsold = rsnew;
    }

    return x;
}