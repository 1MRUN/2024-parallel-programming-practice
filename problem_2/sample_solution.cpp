//First implementation
#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <thread>
#include <mutex>
#include <iomanip>


std::vector<size_t> read_array() {
    size_t length, a, b, p;
    std::cin >> length >> a >> b >> p;
    std::vector<size_t> result(length);
    result[0] = a % p;
    for (size_t i = 1; i < result.size(); ++i) {
        result[i] = (result[i - 1] * a + b) % p;
    }
    return result;
}

void merge_sort(std::vector<size_t>::iterator begin, std::vector<size_t>::iterator end) {
    if (end - begin <= 1) {
        return;
    }

    auto middle = begin + (end - begin) / 2;
    std::thread left_thread([&]() { merge_sort(begin, middle); });
    std::thread right_thread([&]() { merge_sort(middle, end); });

    left_thread.join();
    right_thread.join();

    std::vector<size_t> buffer(end - begin);
    auto left = begin, right = middle;
    for (size_t i = 0; i < buffer.size(); ++i) {
        if (left == middle || (right != end && *right < *left)) {
            buffer[i] = *right++;
        } else {
            buffer[i] = *left++;
        }
    }

    std::copy(buffer.begin(), buffer.end(), begin);
}


void boost() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

int main() {
    boost();
    auto array = read_array();
    size_t k;
    std::cin >> k;
    merge_sort(array.begin(), array.end());
    for (size_t i = k - 1; i < array.size(); i += k) {
        std::cout << array[i] << ' ';
    }
    std::cout << "\n";

    return 0;
}



/*Second implementation
#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <thread>
#include <mutex>
#include <iomanip>
#include <random>


std::vector<size_t> read_array() {
    size_t length, a, b, p;
    std::cin >> length >> a >> b >> p;
    std::vector<size_t> result(length);
    result[0] = a % p;
    for (size_t i = 1; i < result.size(); ++i) {
        result[i] = (result[i - 1] * a + b) % p;
    }
    return result;
}

size_t k;
std::vector<size_t> arr;

void quick_sort(size_t begin, size_t end) {
    if (begin >= end) {
        return;
    }

    auto pivot_index = begin + rand() % (end - begin);
    std::swap(arr[begin], arr[pivot_index]);
    auto pivot = arr[begin];
    size_t left = begin + 1;
    size_t right = end;
    //std:: cout << "begin: " << begin << " end: " << end << " pivot: " << pivot << std::endl;
    while (left < right) {
        while(left < right && arr[left] <= pivot) {
            ++left;
        }
        while (right > left && arr[right] > pivot) {
            --right;
        }
        if (left < right) {
            std::swap(arr[left], arr[right]);
        }
    }
    if (arr[left] > pivot) {
        --left;
    }
    std::swap(arr[begin], arr[left]);
    //std::cout << "left: " << left <<"arr[left]: " << arr[left] << std::endl;
    std::thread left_thread([&]() { 
        if ((left - begin + 1) >= k || (left % k == k - 1) || (left % k < begin % k)) {
            quick_sort(begin, left); 
        }
    });
    std::thread right_thread([&]() { 
        if (end > left + 1 && ((end - left) >= k || ((left + 1) % k == k - 1) || ((left + 1) % k < end % k))) {
            quick_sort(left + 1, end); 
        }
    });
    left_thread.join();
    right_thread.join();
}


void boost() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

std::vector<size_t> normal_input() {
    size_t length;
    std::cin >> length;
    std::vector<size_t> result(length);
    for (size_t i = 0; i < length; ++i) {
        std::cin >> result[i];
    }
    return result;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    boost();
    //arr = normal_input();
    arr = read_array();
    std::cin >> k;
    quick_sort(0, arr.size() - 1);
    for (size_t i = k - 1; i < arr.size(); i += k) {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n";

    return 0;
}
*/