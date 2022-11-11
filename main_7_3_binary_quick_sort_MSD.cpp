#include <iostream>
#include <sstream>

using namespace std;

// Возращает индекс начала элементов, у которых разряд, равный старшему разряду пивота, равен ему (то есть единице)
template <typename Comparator>
size_t partition(unsigned long long *array, size_t begin, size_t end, size_t max_bit_number_of_pivot, Comparator comparator);

struct BitComparator;

void run_case(istream& is, ostream& os);

template <typename Comparator>
void quick_sort(unsigned long long *array, size_t begin, size_t end, size_t curr_max_bits_count, Comparator comparator);

int main() {
    run_case(cin, cout);
    return 0;
}

template <typename Comparator>
size_t partition(unsigned long long *array, size_t begin, size_t end, size_t max_bit_number_of_pivot, Comparator comparator) {
    if (begin + 1 == end) {
        return begin;
    }
    unsigned long long pivot = ((unsigned long long)1 << max_bit_number_of_pivot);

    size_t i = begin;
    for (size_t j = begin; j < end; ++j) {
        if (comparator(array[j], pivot, max_bit_number_of_pivot)) {
            swap(array[i], array[j]);
            ++i;
        }
    }
    return i;
}

template <typename Comparator>
void quick_sort(unsigned long long *array, size_t begin, size_t end, size_t curr_max_bits_count, Comparator comparator) { 
    if (begin + 1 == end || curr_max_bits_count == -1) {
        return;
    }

    size_t index_pivot = partition(array, begin, end, curr_max_bits_count, comparator);

    while (index_pivot == end && curr_max_bits_count > 0) {
        --curr_max_bits_count;
        index_pivot = partition(array, begin, end, curr_max_bits_count, comparator);
    }
    if (index_pivot > begin && curr_max_bits_count > 0) {
        quick_sort(array, begin, index_pivot, curr_max_bits_count - 1, comparator);
    }
    if (index_pivot < end && curr_max_bits_count > 0) {
        quick_sort(array, index_pivot, end, curr_max_bits_count - 1, comparator);
    }
}

struct BitComparator {
    bool operator()(unsigned long long left, unsigned long long right, size_t bit_number) {
        if ((left & ((unsigned long long)1 << bit_number)) < (right & ((unsigned long long)1 << bit_number))) {
            return true;
        }
        return false;
    }
};

void run_case(istream& is, ostream& os) {
    size_t n = 0;
    is >> n;
    unsigned long long *array = new unsigned long long[n];
    for (size_t i = 0; i < n; ++i) {
        is >> array[i];
    }
    BitComparator comparator;
    quick_sort(array, 0, n, 63, comparator);
    for (size_t i = 0; i < n; ++i) {
        os << array[i] << ' ';
    }
    os << endl;
    delete[] array;
}
