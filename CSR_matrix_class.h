#include <iostream>
#include <vector>

class CSRMatrix {
private:
    std::vector<double> values; // значения ненулевых элементов
    std::vector<int> columns; // соответствующие им столбцы
    std::vector<int> row_ptrs; // указатели на начало каждой строки
    int rows, cols, nnz; // размеры матрицы и количество ненулевых элементов

public:
    // конструктор
    CSRMatrix(int rows_, int cols_, int nnz_) {
        rows = rows_;
        cols = cols_;
        nnz = nnz_;
        values.reserve(nnz);
        columns.reserve(nnz);
        row_ptrs.reserve(rows + 1);
    }

    // метод для установки элемента матрицы по заданным координатам
    void set(int i, int j, double value) {
        values.push_back(value);
        columns.push_back(j);
        if (i > row_ptrs.size() - 1) {
            row_ptrs.resize(i + 1, nnz);
        }
        ++row_ptrs[i];
    }

    // метод для получения значения элемента матрицы по заданным координатам
    double get(int i, int j) const {
        int row_start = row_ptrs[i];
        int row_end = row_ptrs[i + 1];
        for (int k = row_start; k < row_end; ++k) {
            if (columns[k] == j) {
                return values[k];
            }
        }
        return 0.0; // если элемент не найден, то возвращаем 0
    }

    // метод для вывода матрицы на экран
    void print() const {
        int k = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (j == columns[k] && k < row_ptrs[i + 1]) {
                    std::cout << values[k] << ' ';
                    ++k;
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << '\n';
        }
    }
};