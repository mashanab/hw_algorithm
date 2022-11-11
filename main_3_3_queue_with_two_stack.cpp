#include <iostream>
#include <sstream>

enum class QUEUE_COMMAND {
    POP_FRONT = 2,
    PUSH_BACK = 3
};

using namespace std;

template <typename T>
class Stack {
 public:
    Stack(): data(nullptr), _capacity(0), _size(0) {}

    Stack(const Stack& s)=delete;
    Stack& operator=(const Stack& s)=delete;

    Stack(Stack&& s)=delete;
    Stack& operator=(Stack&& s)=delete;

    void push_back(const T& value) {
        if (size() == capacity()) {
            _capacity = std::max(_capacity * 2, size_t(1));

            T* new_data = new T[_capacity];
            copy(data, data + _size, new_data);

            delete[] data;
            data = new_data;
        }
        data[_size++] = value;
    }

    T top() const {
        return data[_size - 1];
    }

    void pop_back() {
        if (_size * 4 <= _capacity) {
            _capacity = _size * 2;

            T* new_data = new T[_capacity];
            copy(data, data + _size, new_data);

            delete[] data;
            data = new_data;
        }
        --_size;
    }

    bool empty() const {
        return size() == 0;
    }

    size_t size() const {
        return _size;
    }

    size_t capacity() const {
        return _capacity;
    }

    ~Stack() {
        delete[] data;
    }
 private:
    T *data;
    size_t _capacity;
    size_t _size;
};

template <typename T>
class Queue {
 public:
    Queue() {}

    Queue(const Queue& s)=delete;
    Queue& operator=(const Queue& s)=delete;

    Queue(Queue&& s)=delete;
    Queue& operator=(Queue&& s)=delete;

    void pop_front() {
        if (pop_stack.empty()) {
            while (!push_stack.empty()) {
                pop_stack.push_back(push_stack.top());
                push_stack.pop_back();
            }
        }
        pop_stack.pop_back();
    }

    bool empty() {
        return push_stack.empty() && pop_stack.empty();
    }

    T front() {
        if (pop_stack.empty()) {
            while (!push_stack.empty()) {
                pop_stack.push_back(push_stack.top());
                push_stack.pop_back();
            }
        }
        return pop_stack.top();
    }

    void push_back(const T& value) {
        push_stack.push_back(value);
    }
 private:
    Stack<T> push_stack;
    Stack<T> pop_stack;
};

int main() {
    size_t n;
    cin >> n;
    Queue<int> q;
    for (size_t i = 0; i < n; ++i) {
        int command;
        int value;
        cin >> command >> value;
        switch (QUEUE_COMMAND(command))
        {
        case QUEUE_COMMAND::POP_FRONT:
            if (q.empty() && value != -1) {
                cout << "NO" << endl;
                return 0;
            }
            if (!q.empty()) {
                if (value != q.front()) {
                    cout << "NO" << endl;
                    return 0;
                }
                q.pop_front();
            }
            break;
        case QUEUE_COMMAND::PUSH_BACK:
            q.push_back(value);
            break;
        default:
            break;
        }
    }
    cout << "YES" << endl;
    return 0;
}