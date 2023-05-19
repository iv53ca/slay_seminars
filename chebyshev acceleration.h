#include <iostream>
#include <vector>

std::vector<double> chebyshevAcceleration(const std::vector<double>& x, const std::vector<double>& xPrev, double lambda) {
    int n = x.size();
    std::vector<double> xNext(n);

    for (int i = 0; i < n; ++i) {
        xNext[i] = x[i] + lambda * (x[i] - xPrev[i]);
    }

    return xNext;
}

std::vector<double> jacobiMethodChebyshev(const std::vector<std::vector<double>>& A, const std::vector<double>& b, int maxIterations = 100, double tolerance = 1e-6) {
    int n = A.size();

    std::vector<double> x(n, 0.0);          // Начальное приближение x
    std::vector<double> xPrev(n, 0.0);      // Предыдущее приближение x

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    sum += A[i][j] * xPrev[j];
                }
            }
            x[i] = (b[i] - sum) / A[i][i];
        }

        // Проверка на достижение необходимой точности
        double maxDiff = 0.0;
        for (int i = 0; i < n; ++i) {
            double diff = abs(x[i] - xPrev[i]);
            if (diff > maxDiff) {
                maxDiff = diff;
            }
        }
        if (maxDiff < tolerance) {
            break;
        }

        xPrev = x;

        // Вычисление параметра ускорения Чебышева (lambda)
        double alpha = 0.0;
        double beta = 0.0;
        for (int i = 0; i < n; ++i) {
            double diff = x[i] - xPrev[i];
            alpha += diff * diff;
            beta += xPrev[i] * xPrev[i];
        }
        double lambda = alpha / beta;

        x = chebyshevAcceleration(x, xPrev, lambda);
    }

    return x;
}

