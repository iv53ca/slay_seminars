#include <iostream>
#include <vector>

std::vector<double> gaussSeidel(const std::vector<std::vector<double>>& A, const std::vector<double>& b, int maxIterations = 100, double tolerance = 1e-6) {
    int n = A.size();

    std::vector<double> x(n, 0.0);          // Начальное приближение x

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        std::vector<double> xPrev = x;      // Предыдущее приближение x

        for (int i = 0; i < n; ++i) {
            double sum1 = 0.0;
            double sum2 = 0.0;

            for (int j = 0; j < i; ++j) {
                sum1 += A[i][j] * x[j];
            }

            for (int j = i + 1; j < n; ++j) {
                sum2 += A[i][j] * xPrev[j];
            }

            x[i] = (b[i] - sum1 - sum2) / A[i][i];
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
    }

    return x;
}

int main() {
    std::vector<std::vector<double>> A = {{4, -1, 1}, {-1, 4, -2}, {1, -2, 4}}; // Матрица A
    std::vector<double> b = {12, -1, 5};                                 // Вектор правых частей b

    std::vector<double> x = gaussSeidel(A, b);

    std::cout << "Solution x:" << std::endl;
    for (double val : x) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
