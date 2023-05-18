#include <iostream>
#include <vector>

std::vector<double> jacobiMethod(const std::vector<std::vector<double>>& A, const std::vector<double>& b, int maxIterations = 100, double tolerance = 1e-6) {
    int n = A.size();

    std::vector<double> x(n, 0.0);          // Начальное приближение x
    std::vector<double> xNext(n, 0.0);      // Следующее приближение x

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            xNext[i] = (b[i] - sum) / A[i][i];
        }

        // Проверка на достижение необходимой точности
        double maxDiff = 0.0;
        for (int i = 0; i < n; ++i) {
            double diff = abs(xNext[i] - x[i]);
            if (diff > maxDiff) {
                maxDiff = diff;
            }
        }
        if (maxDiff < tolerance) {
            break;
        }

        x = xNext;
    }

    return x;
}

int main() {
    std::vector<std::vector<double>> A = {{4, -1, 1}, {-1, 4, -2}, {1, -2, 4}}; // Матрица A
    std::vector<double> b = {12, -1, 5};                                 // Вектор правых частей b

    std::vector<double> x = jacobiMethod(A, b);

    std::cout << "Solution x:" << std::endl;
    for (double val : x) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
