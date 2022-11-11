#include <iostream>
#include <cstddef>
#include <sstream>

using namespace std;

struct Shopper {
    Shopper() : _time_start(0), _time_end(0) {}
    Shopper(int time_start, int time_end) : _time_start(time_start), _time_end(time_end) {}
    Shopper(const Shopper& shopper) : _time_start(shopper.time_start()), _time_end(shopper.time_end()) {}
    Shopper& operator=(const Shopper& shopper) {
        _time_start = shopper.time_start();
        _time_end = shopper.time_end();
        return (*this);
    }
    Shopper(Shopper&& shopper) = default;
    Shopper& operator=(Shopper&& shopper) = default;

    int time_start() const {
        return _time_start;
    }
    int time_end() const {
        return _time_end;
    }
 private:
    int _time_start;
    int _time_end;
};

struct ShopperComparator {
    bool operator()(const Shopper& left_shopper, const Shopper& right_shopper) {
        if (left_shopper.time_end() == right_shopper.time_end()) {
            return left_shopper.time_start() < right_shopper.time_start();
        }
        return left_shopper.time_end() < right_shopper.time_end();
    }
};

struct Shoppers {
    Shoppers() : _size(0), _array(nullptr) {}
    Shoppers(int n) : _size(0), _array(new Shopper[n]) {}
    Shoppers(const Shoppers& shoppers) : _size(0), _array(new Shopper[shoppers.size()]) {
        for (int i = 0; i < shoppers.size(); ++i) {
            (*this)[i] = shoppers[i];
        }
    }
    Shoppers& operator=(const Shoppers& shoppers) {
        _size = 0;
        _array = new Shopper[shoppers.size()];
        for (int i = 0; i < shoppers.size(); ++i) {
            (*this)[i] = shoppers[i];
        }
        return *this;
    }
    Shoppers(Shoppers&& shoppers) = delete;
    Shoppers& operator=(Shoppers&& shoppers) = delete;

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    Shopper *array() const {
        return _array;
    }

    void push(const Shopper& shopper) {
        _array[_size++] = shopper;
    }

    const Shopper& top() const {
        return _array[0];
    }

    Shopper& operator[](int index) const {
        return _array[index];
    }
 private:
    int _size;
    Shopper *_array;
};

template <typename T, typename Comparator>
void merge(T *left_array, int left_n, T *right_array, int right_n) {
    Comparator comp;
    int left_actual_index = 0;
    int right_actual_index = 0;
    T *new_array = new T[left_n + right_n];
    int new_index = 0;
    while (left_actual_index < left_n && right_actual_index < right_n) {
        if (comp(left_array[left_actual_index], right_array[right_actual_index])) {
            new_array[new_index++] = left_array[left_actual_index];
            ++left_actual_index;
        } else {
            new_array[new_index++] = right_array[right_actual_index];
            ++right_actual_index;
        }
    }
    if (left_actual_index == left_n) {
        while (right_actual_index < right_n) {
            new_array[new_index++] = right_array[right_actual_index];
            ++right_actual_index;
        }
    } else {
        while (left_actual_index < left_n) {
            new_array[new_index++] = left_array[left_actual_index];
            ++left_actual_index;
        }
    }
    std::copy(new_array, new_array + left_n + right_n, left_array);
    delete[] new_array;
}

template <typename T, typename Comparator>
void merge_sort(T *array, int n) {
    if (n <= 1) {
        return;
    }
    int left_n = n / 2;
    int right_n = n - left_n;
    if (left_n > 1) {
        merge_sort<T, Comparator>(array, left_n);
    }
    if (right_n > 1) {
        merge_sort<T, Comparator>(array + left_n, right_n);
    }
    merge<T, Comparator>(array, left_n, array + left_n, right_n);
}

int min_view_count(Shoppers& shoppers) {
    int result_count = 0;
    int last_view = -1;
    int prev_last_view = -1;
    for (int i = 0; i < shoppers.size(); ++i) {
        if (shoppers[i].time_start() > last_view) {
            last_view = shoppers[i].time_end();
            prev_last_view = last_view - 1;
            result_count += 2;
        } else if (shoppers[i].time_start() == last_view) {
            prev_last_view = last_view;

            last_view = shoppers[i].time_end();
            ++result_count;
        } 
        else if (shoppers[i].time_start() > prev_last_view && shoppers[i].time_end() == last_view) {
            prev_last_view = shoppers[i].time_end() - 1;
            ++result_count;
        } 
        else if (shoppers[i].time_start() > prev_last_view && shoppers[i].time_end() > last_view) {
            prev_last_view = last_view;
            last_view = shoppers[i].time_end();
            ++result_count;
        }
    }
    return result_count;
}

void test_views(istream& is, ostream& os) {
    int n = 0;
    is >> n;
    Shoppers shoppers(n);
    for (int i = 0; i < n; ++i) {
        int time_start, time_end;
        is >> time_start >> time_end;
        shoppers.push(Shopper(time_start, time_end));
    }
    merge_sort<Shopper, ShopperComparator>(shoppers.array(), shoppers.size());

    int view_count = min_view_count(shoppers);
    os << view_count << endl;
}

int main() {
    // stringstream is1("4 8 9 1 3 3 5 7 8\n");
    // stringstream os1;
    // stringstream exp_os1("6\n");
    // test_views(is1, os1);
    // if (!(os1.str() == exp_os1.str())) {
    //     cout << "FAIL";
    //     return 0;
    // }

    // stringstream is2("4 1 3 3 5 1 7 7 8\n");
    // stringstream os2;
    // stringstream exp_os2("5\n");
    // test_views(is2, os2);
    // if (!(os2.str() == exp_os2.str())) {
    //     cout << "FAIL";
    //     return 0;
    // }
    // stringstream is3("100 41 44 94 96 209 211 198 200 82 84 185 188 1 4 121 124 115 117 27 29 231 233 62 65 52 54 141 143 38 41 167 169 131 133 189 191 227 230 235 237 143 146 122 125 153 155 21 24 173 175 107 109 22 25 117 120 83 86 169 171 76 79 110 112 48 50 160 162 64 66 86 89 50 53 130 132 126 129 153 155 189 192 84 86 36 38 166 168 11 13 144 147 146 149 17 19 38 40 129 132 33 36 79 81 144 146 57 59 233 235 221 224 44 46 30 33 137 140 57 59 226 228 41 43 35 38 135 137 191 193 230 232 141 143 46 48 147 150 7 10 97 100 153 156 65 68 49 51 221 223 182 184 146 148 93 95 180 183 42 45 130 133 24 27 188 191 235 238 2 4 211 213 14 16 36 39 228 231 228 230 121 123 53 56 18 20 180 182 127 130 128 131 168 171 47 50 150 153 13 15\n");
    // stringstream os3;
    // stringstream exp_os3("98\n");
    // test_views(is3, os3);
    // if (!(os3.str() == exp_os3.str())) {
    //     cout << "FAIL" << endl;
    //     cout << os3.str() << endl;
    //     return 0;
    // }

    test_views(cin, cout);
    

    return 0;
}