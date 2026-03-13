#include "matrix.h"
#include <cassert>
#include <iostream>
#include <iomanip>
#include <random>

Matrix::Matrix() : rows(0), cols(0) {};

Matrix::Matrix(int r, int c, float value) : rows(r), cols(c) {
    assert(r > 0 && c > 0);
    data.resize(r * c, value);
}

Matrix::Matrix(int r, int c, const std::vector<float>& input_data) : rows(r), cols(c) {
    assert(input_data.size() == r * c);
    data = input_data;
}


int Matrix::getRows() const { return rows;}

int Matrix::getCols() const { return cols;} 

int Matrix::getSize() const { return rows * cols;}

const std::vector<float>& Matrix::getData() const { return data;}


float& Matrix::at(int r, int c) { 
    return data[r * cols + c];
}

float Matrix::at(int r, int c) const {
    return data[r * cols + c];
}


Matrix Matrix::matmul(const Matrix& A, const Matrix& B) {
    assert(A.cols == B.rows);

    Matrix result(A.rows, B.cols);

    for (size_t i{0}; i < A.rows; ++i) {
        for (size_t j{0}; j < B.cols; ++j) {
            float sum = 0.0f;
            for (size_t q{0}; q < A.cols; ++q) {
                sum += A.at(i, q) * B.at(q, j);
            }
            result.at(i, j) = sum;
        }
    }

    return result;

}


Matrix Matrix::mul(const Matrix& A, const Matrix& B) {
    assert(A.rows == B.rows && A.cols == B.cols);

    Matrix result(A.rows, B.cols);

    for (size_t i{0}; i < A.data.size(); ++i) {
        result.data[i] = A.data[i] * B.data[i];
    }

    return result;

}


Matrix Matrix::add(const Matrix& A, const Matrix& B) {
    assert(A.rows == B.rows && A.cols == B.cols);

    Matrix result(A.rows, B.cols);

    for (size_t i{0}; i < A.data.size(); ++i) {
        result.data[i] = A.data[i] + B.data[i];
    }

    return result;

}


Matrix Matrix::sub(const Matrix& A, const Matrix& B) {
    assert(A.rows == B.rows && A.cols == B.cols);

    Matrix result(A.rows, B.cols);

    for (size_t i{0}; i < A.data.size(); ++i) {
        result.data[i] = A.data[i] - B.data[i];
    }

    return result;

}


Matrix Matrix::t(const Matrix& A) {

    Matrix result(A.cols, A.rows);

    for (size_t i{0}; i < A.rows; ++i) {
        for (size_t j{0}; j < A.cols; ++j) {
            result.at(j, i) = A.at(i, j);
        }
    }

    return result;   

}


Matrix Matrix::apply(const Matrix& A, std::function<float(float)> func) {

    Matrix result = A;

    result.apply_(func);

    return result;

}


Matrix& Matrix::add_(const Matrix& other) {
    assert(rows == other.rows && cols == other.cols);

    for (size_t i{0}; i < data.size(); ++i) {
        data[i] += other.data[i];
    }

    return *this;

}


Matrix& Matrix::add_(float scalar) {

    for (size_t i{0}; i < data.size(); ++i) {
        data[i] += scalar;
    }

    return *this;

}


Matrix& Matrix::mul_(const Matrix& other) {
    assert(rows == other.rows && cols == other.cols);

    for (size_t i{0}; i < data.size(); ++i) {
        data[i] *= other.data[i];
    }
    
    return *this;

}


Matrix& Matrix::mul_(float scalar) {

    for (size_t i{0}; i < data.size(); ++i) {
        data[i] *= scalar;
    }
    
    return *this;

}


Matrix& Matrix::apply_(std::function<float(float)> func) {

    for (size_t i{0}; i < data.size(); ++i) {
        data[i] = func(data[i]);
    }

    return *this;

}


void Matrix::randomize() {

    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

    for (size_t i{0}; i < data.size(); ++i) {
        data[i] = dis(rng);
    }

}
