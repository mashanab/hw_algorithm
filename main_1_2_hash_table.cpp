#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <vector>

size_t str_hash(const std::string &str) {
    size_t hash = 0;
    for (const char &i : str) {
        hash = hash * 13 + i;
    }
    return hash;
}

template <class KeyType>
struct Hash {
    size_t operator()(const KeyType &key, const size_t &i) {
        return key;
    }
};

template <>
struct Hash<std::string> {
    size_t operator()(const std::string &key, const size_t &i) {
        size_t h = str_hash(key);
        return h + i * (h + (((h % 2) == 1) ? 0 : 1));
    }
};


template < class KeyType, class HashType = Hash<KeyType> >
class HashTable {
    struct HashTableNode {

        KeyType key;
        
        HashTableNode() : state(State::EMPTY) {}

        bool is_empty() {
            return (state == State::EMPTY) ? true : false;
        }

        bool is_used() {
            return (state == State::USED) ? true : false;
        }

        bool is_deleted() {
            return (state == State::DELETED) ? true : false;
        }

        void make_empty() {
            state = State::EMPTY;
        }

        void make_used() {
            state = State::USED;
        }

        void make_deleted() {
            state = State::DELETED;
        }

     private:
        enum State {
            EMPTY,
            USED,
            DELETED
        };

        State state;
    };
 public:
    HashTable() : table(8), items_count(8), used_items_count(0), deleted_items_count(0) {}

    HashTable(const HashTable &)=delete;
    HashTable(HashTable &&)=delete;

    HashTable &operator=(const HashTable &)=delete;
    HashTable &operator=(HashTable &&)=delete;

    ~HashTable() {}

    bool find(const KeyType &key) {
        for (size_t i = 0; i < items_count; ++i) {
            size_t idx = hasher(key, i) % items_count;
            if (table[idx].is_empty()) {
                return false;
            }
            if (table[idx].is_used() && table[idx].key == key) {
                return true;
            }
        }
        return false;
    }

    void insert(const KeyType &key) {
        if (used_items_count >= items_count * 0.75) {
            grow();
        } else if (deleted_items_count * 2 >= items_count) {
            clean();
        }
        bool met_first_deleted = false;
        size_t idx_first_deleted = 0;
        for (size_t i = 0; i < items_count; ++i) {
            size_t idx = hasher(key, i) % items_count;
            if (table[idx].is_empty()) {
                if (met_first_deleted) {
                    table[idx_first_deleted].key = key;
                    table[idx_first_deleted].make_used();
                    --deleted_items_count;
                } else {
                    table[idx].key = key;
                    table[idx].make_used();
                }
                ++used_items_count;
                return;
            } else if (!met_first_deleted && table[idx].is_deleted()) {
                met_first_deleted = true;
                idx_first_deleted = idx;
            } else if (table[idx].key == key) {
                return;
            }
        }
    }

    void erase(const KeyType &key) {
        if (used_items_count >= items_count * 0.75) {
            grow();
        } else if (deleted_items_count * 2 >= items_count) {
            clean();
        }
        for (size_t i = 0; i < items_count; ++i) {
            size_t idx = hasher(key, i) % items_count;
            if (table[idx].is_empty()) {
                return;
            }
            if (table[idx].is_used() && table[idx].key == key) {
                table[idx].make_deleted();
                --used_items_count;
                ++deleted_items_count;
                return;
            }
        }
    }

 private:
    void grow() {
        size_t new_items_count = items_count * 2;
        size_t new_used_items_count = 0;
        std::vector<HashTableNode> new_table(new_items_count);
        for (size_t i = 0; i < items_count; ++i) {
            if (table[i].is_used()) {
                for (size_t j = 0; j < new_items_count; ++j) {
                    size_t idx = hasher(table[i].key, j) % new_items_count;
                    if (new_table[idx].is_empty()) {
                        new_table[idx].key = table[i].key;
                        new_table[idx].make_used();
                        ++new_used_items_count;
                        break;
                    }
                }
            }
        }
        table = std::move(new_table);
        items_count = new_items_count;
        used_items_count = new_used_items_count;
        deleted_items_count = 0;
    }

    void clean() {
        size_t new_items_count = items_count;
        size_t new_used_items_count = 0;
        std::vector<HashTableNode> new_table(new_items_count);
        for (size_t i = 0; i < items_count; ++i) {
            if (table[i].is_used()) {
                for (size_t j = 0; j < new_items_count; ++j) {
                    size_t idx = hasher(table[i].key, j) % new_items_count;
                    if (new_table[idx].is_empty()) {
                        new_table[idx].key = table[i].key;
                        new_table[idx].make_used();
                        ++new_used_items_count;
                        break;
                    }
                }
            }
        }
        table = std::move(new_table);
        items_count = new_items_count;
        used_items_count = new_used_items_count;
        deleted_items_count = 0;
    }

    std::vector<HashTableNode> table;
    size_t items_count;
    size_t used_items_count;
    size_t deleted_items_count;

    Hash<KeyType> hasher;
};

void run_case(std::istream &in, std::ostream &os) {
    char symbol;
    std::string key;
    HashTable<std::string> hash_table;
    while (in >> symbol && in >> key) {
        bool res = false;
        switch (symbol) {
            case '+':
                if (!hash_table.find(key)) {
                    res = true;
                }
                hash_table.insert(key);
                break;
            case '?':
                if (hash_table.find(key)) {
                    res = true;
                }
                break;
            case '-':
                if (hash_table.find(key)) {
                    res = true;
                }
                hash_table.erase(key);
                break;
            default:
                break;
        }

        if (res) {
            os << "OK" << std::endl;
        } else {
            os << "FAIL" << std::endl;
        }
    }
}

int main() {
    run_case(std::cin, std::cout);
    return 0;
}
