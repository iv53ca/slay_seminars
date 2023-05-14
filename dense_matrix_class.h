#include <iostream>
#include <cstdlib> // для функции rand()

class DenseMatrix {
private:
    double *data; // одномерный массив для хранения матрицы
    int rows, cols; // размеры матрицы

public:
    // конструктор
    DenseMatrix(int rows_, int cols_) {
        rows = rows_;
        cols = cols_;
        data = new double[rows * cols];
    }

    // метод для инициализации матрицы случайными значениями
    void init_random() {
        for (int i = 0; i < rows * cols; ++i) {
            data[i] = rand() % 10; // случайное значение от 0 до 9
        }
    }

    // метод для изменения значения элемента матрицы по заданным координатам
    void set(int i, int j, double value) {
        data[i * cols + j] = value;
    }

    // метод для получения значения элемента матрицы по заданным координатам
    double get(int i, int j) const {
        return data[i * cols + j];
    }

    // метод для вывода матрицы на экран
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i * cols + j] << ' ';
            }
            std::cout << '\n';
        }
    }

    // деструктор
    ~DenseMatrix() {
        delete[] data;
    }
};