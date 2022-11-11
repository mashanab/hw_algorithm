#include <iostream>
#include <random>

using namespace std;

size_t get_random_index(size_t begin, size_t end) {
    srand(time(NULL));
    return begin + rand() % (end - begin);
}

template <typename Comparator>
size_t partition(int *array, size_t begin, size_t end, Comparator comparator) {
    if (begin + 1 == end) {
        return begin;
    }
    size_t index_pivot = get_random_index(begin, end);
    const auto pivot = array[index_pivot];
    swap(array[index_pivot], array[end - 1]);
    // left <= index_pivot < right, нерассмотренные
    // i - индекс начала right
    // j - индекс начала нерассмотренных, j > i
    size_t i = begin;
    for (size_t j = begin; j < end - 1; ++j) {
        /* array[j] <= array[index_pivot] <->
            array[index_pivot] >= array[j] <->
                !(array[index_pivot] < array[j]) */
        if (!comparator(pivot, array[j])) {
            swap(array[i], array[j]);
            ++i;
        }
    }
    swap(array[i], array[end - 1]);
    return i;
}

template <typename Comparator>
int k_stat(int *array, size_t n, size_t k, Comparator comparator) {
    size_t begin = 0, end = n;
    size_t got_k = partition(array, begin, end, comparator);
    while (k != got_k) {
        if (k < got_k) {
            end = got_k;
        } else {
            begin = got_k + 1;
        }
        got_k = partition(array, begin, end, comparator);
    }
    return array[k];
}

void run_alg(istream& is, ostream& os) {
    size_t n = 0;
    is >> n;
    int *array = new int[n];
    for (size_t i = 0; i < n; ++i) {
        int elem = 0;
        is >> elem;
        array[i] = elem;
    }
    os << k_stat(array, n, (size_t)(n * 0.1), [](int a, int b){return a < b;}) << endl;
    os << k_stat(array, n, (size_t)(n * 0.5), [](int a, int b){return a < b;}) << endl;
    os << k_stat(array, n, (size_t)(n * 0.9), [](int a, int b){return a < b;}) << endl;
    delete[] array;
}

int main() {
    run_alg(cin, cout);
    
    return 0;
}
