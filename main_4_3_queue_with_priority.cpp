#include <iostream>

using namespace std;

template<typename PriorityType = size_t, typename TimeType = size_t>
class Process;

template<typename PriorityType = size_t, typename TimeType = size_t>
class ProcessComparator {
 public:
    bool operator()(const Process<PriorityType, TimeType>& lp, const Process<PriorityType, TimeType>& rp) const {
        return lp._priority * (lp._time + 1) < rp._priority * (rp._time + 1);
    }
};

template <typename PriorityType, typename TimeType>
class Process {
 public:
    Process() : _priority(0), _time(0), _worked_time(0) {}

    Process(PriorityType priority, TimeType worked_time) : _priority(priority), _time(0), _worked_time(worked_time) {}

    void do_work() {
        _time += _priority;
    }

    bool is_finished() const {
        return _time >= _worked_time;
    }

    friend bool ProcessComparator<PriorityType, TimeType>::operator()(const Process<PriorityType, TimeType>& lp, const Process<PriorityType, TimeType>& rp) const;

 private:
    PriorityType _priority;
    TimeType _time;
    TimeType _worked_time;
};

template <typename T = Process<size_t, size_t>, typename Comparator = ProcessComparator<size_t, size_t> >
class Heap {
 public:
    Heap(size_t size): _size(0), _capacity(size) {
        _buf = new T[size];
    }

    Heap(const Heap& h)=delete;
    Heap& operator=(const Heap& h)=delete;
    Heap(Heap&& h)=delete;
    Heap& operator=(Heap&& h)=delete;

    ~Heap() {
        delete[] _buf;
    }

    T top() const {
        // assert(!empty());
        return _buf[0];
    }

    void pop() {
        // assert(!empty());
        if (_size * 4 <= _capacity) {
            _capacity = _size * 2;

            T* new_data = new T[_capacity];
            copy(_buf, _buf + _size, new_data);

            delete[] _buf;
            _buf = new_data;
        }

        _buf[0] = _buf[_size - 1];
        --_size;
        if (!empty()) {
            sift_down(0);
        }
    }

    void push(const T& process) {
        if (_size == _capacity) {
            _capacity = std::max(_capacity * 2, size_t(1));

            T* new_data = new T[_capacity];
            copy(_buf, _buf + _size, new_data);

            delete[] _buf;
            _buf = new_data;
        }

        _buf[_size++] = process;
        sift_up(_size - 1);
    }

    size_t size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    // void build_heap() {
    //     for(size_t i = _size() / 2 - 1; i >= 0; --i) {
    //         sift_down(i);
    //     }
    // }

 private:
    void sift_up(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (!_comparator(_buf[index], _buf[parent])) { // _buf[index] >= _buf[parent] -> !(_buf[index] < _buf[parent]) 
                return;
            }
            std::swap(_buf[index], _buf[parent]);
            index = parent;
        }
    }

    void sift_down(size_t index) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t largest = index;
        if  (left < _size && _comparator(_buf[left], _buf[index]))
            largest = left;
        if  (right < _size && _comparator(_buf[right], _buf[largest]))
            largest = right;

        if (largest != index) {
            swap(_buf[index], _buf[largest]);
            sift_down(largest);
        }
    }

    T* _buf;
    size_t _size;
    size_t _capacity;
    Comparator _comparator;
};

size_t finish_processes(Heap<Process<size_t, size_t> >& heap) {
    size_t count = 0;
    while (!heap.empty()) {
        Process<size_t, size_t> process = heap.top();
        heap.pop();
        if (process.is_finished()) {
            continue;
        }
        process.do_work();
        ++count;
        if (!process.is_finished()) {
            heap.push(process);
        }
    }
    return count;
}

int main() {
    size_t n = 0;
    cin >> n;
    Heap<Process<size_t, size_t> > heap(n);
    for (size_t i = 0; i < n; ++i) {
        size_t priority = 0; 
        size_t worked_time = 0;
        cin >> priority >> worked_time;
        heap.push(Process<size_t, size_t>(priority, worked_time));
    }
    size_t result_count = finish_processes(heap);
    cout << result_count << endl;
    return 0;
}