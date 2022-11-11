#include <iostream>
#include <cstddef>

using namespace std;

/* Экспоненциальный поиск, если цель больше макс. элемента в отсортированном массиве,
то вернет индекс за массивом, то есть равный n, иначе вернет end равный
концу диапозона не включительно, таким образом элемент будет в диапозоне [end << 1; end) */
size_t exponential_search(int *arr, size_t n, int target) {
    if (n == 0) {
        return 0;
    }
    size_t end = 1;
    while (end < n && arr[end] <= target) {
        end <<= 1;
    }
    if (end > n) {
        end = n;
    }
    return end;
}

/* Возвращает позицию вставки, если цель не найдена,
в противном случае возвращается индекс цели в массиве */
size_t binary_search(int *arr, size_t n, size_t left, size_t right, int target) {
    size_t begin = left;
    size_t end = right;
    while (begin != end - 1) {
        size_t middle = begin + (end - begin) / 2;
        if (arr[middle] > target) {
            end = middle;
        } else {
            begin = middle;
        }
    }
    return (arr[begin] >= target) ? begin : end;
}

void run_process(istream& in = cin, ostream& out = cout) {
    size_t n = 0;
    size_t m = 0;
    cin >> n >> m;
    int arr_a[n];
    {
        for (size_t i = 0; i < n; ++i) {
            int elem = 0;
            in >> elem;
            arr_a[i] = elem;
        }
    }
    int arr_b[m];
    {
        for (size_t i = 0; i < m; ++i) {
            int elem = 0;
            in >> elem;
            arr_b[i] = elem;
        }
    }

    for (size_t i = 0; i < m; ++i) {
        size_t right = exponential_search(arr_a, n, arr_b[i]);
        size_t left = right >> 1;
        size_t pos_insert = binary_search(arr_a, n, left, right, arr_b[i]);
        cout << ((i == 0) ? "" : " ") << pos_insert;
    }
    cout << endl;
}


int main() {
    run_process();
    return 0;
}