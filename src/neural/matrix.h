#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <functional>
#include <random>

class Matrix {
    private:
        int rows, cols;
        std::vector<float> data;

    public:
        Matrix();
        Matrix(int r, int c, float value = 0.0f);
        Matrix(int r, int c, const std::vector<float>& input_data);

        int getRows() const;
        int getCols() const;
        int getSize() const;
        const std::vector<float>& getData() const;

        float& at(int r, int c);
        float at(int r, int c) const;

        [[nodiscard]] static Matrix matmul(const Matrix& A, const Matrix& B);
        [[nodiscard]] static Matrix mul(const Matrix& A, const Matrix& B);
        [[nodiscard]] static Matrix add(const Matrix& A, const Matrix& B);
        [[nodiscard]] static Matrix sub(const Matrix& A, const Matrix& B);
        [[nodiscard]] static Matrix t(const Matrix& A);
        [[nodiscard]] static Matrix apply(const Matrix& A, std::function<float(float)> func);

        Matrix& add_(const Matrix& other);
        Matrix& add_(float scalar);

        Matrix& mul_(const Matrix& other);
        Matrix& mul_(float scalar);

        Matrix& apply_(std::function<float(float)> func);

        void randomize();

        void print() const;
};

#endif