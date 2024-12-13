#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <thread>
#include <mutex>
#include <iomanip>

std::vector<std::vector<double>> read_matrix() {
    size_t rows, cols;
    std::cin >> rows >> cols;

    size_t a, b, x, y, z, p;
    std::cin >> a >> b >> x >> y >> z >> p;
    std::vector<std::vector<size_t>> intermediate(rows, std::vector<size_t>(cols, b % p));
    intermediate[0][0] = a % p;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (i > 0 && j > 0) {
                intermediate[i][j] = (intermediate[i][j] + intermediate[i - 1][j - 1] * x) % p;
            }
            if (i > 0) {
                intermediate[i][j] = (intermediate[i][j] + intermediate[i - 1][j] * y) % p;
            }
            if (j > 0) {
                intermediate[i][j] = (intermediate[i][j] + intermediate[i][j - 1] * z) % p;
            }
        }
    }
    size_t max_value = 0;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            max_value = std::max(max_value, intermediate[i][j]);
        }
    }

    std::vector<std::vector<double>> result(rows, std::vector<double>(cols));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = static_cast<double>(intermediate[i][j]) / static_cast<double>(max_value);
        }
    }

    return result;
}

void boost() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

int main() {
    boost();
    auto left = read_matrix();
    auto right = read_matrix();
    auto left_rows = left.size();
    auto left_cols = left[0].size();
    auto right_cols = right[0].size();

    if (left.empty() || right.empty() || left[0].size() != right.size()) {
        std::cerr << "Wrong matrices";
        return 1;
    }

    std::vector<std::vector<long double>> result(left_rows, std::vector<long double>(right_cols));    
    std::vector<std::thread> threads;
    for (int i = 0; i < left_rows; ++i) {
        for (int j = 0; j < right_cols; ++j) {
            threads.emplace_back([i, j, &left, &right, &result] {
                for (size_t k = 0; k < left[0].size(); ++k) {
                    result[i][j] += left[i][k] * right[k][j];
                }
            });
        }
    }
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << left_rows << ' ' << right_cols << "\n";
    for (int i = 0; i < left_rows; ++i) {
        for (int j = 0; j < right_cols; ++j) {
            std::cout << std::setprecision(12) << result[i][j] << ' ';
        }
        std::cout << "\n";
    }

    return 0;
}