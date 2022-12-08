#include <iostream>
#include <cstddef>
#include <sstream>
#include <queue>
#include <vector>
#include <sstream>

template <typename KeyType>
struct DefaultComparator {
    bool operator()(const KeyType &lhs, const KeyType &rhs) {
        return lhs < rhs;
    }
};

template < typename KeyType, typename Comparator = DefaultComparator<KeyType> >
class BTree {
    struct Node {
        std::vector<KeyType> keys;
        std::vector<Node *> children;

        bool leaf;

        Node() : leaf(true) {}
 
        ~Node() {
            for (Node *child : children) {
                delete child;
            }
        }
    };

 public:
    BTree(size_t min_degree, Comparator comp = Comparator())
    : root(nullptr), t(min_degree), comp(comp) {}

    ~BTree() {
        if (root) {
            delete root;
        }
    }

    void insert(const KeyType &key) {
        if (!root) {
            root = new Node;
        }
        
        if (is_full(root)) {
            Node *new_root = new Node();
            new_root->children.push_back(root);
            new_root->leaf = false;
            root = new_root;
            split_child(root, 0);
        }

        insert_non_full(root, key);
    }

    void level_order() {
        std::queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            size_t i = q.size();
            for (; i > 0; --i) {
                Node *curr = q.front();
                for (size_t i = 0; i < curr->keys.size(); ++i) {
                    std::cout << curr->keys[i] << ' ';
                }
                for (Node *node : curr->children) {
                    q.push(node);
                }
                q.pop();
            }
            std::cout << std::endl;
        }
    }

 private:

    bool is_full(Node *node) {
        return node->keys.size() == 2 * t - 1;
    }

    void split_child(Node *node, size_t index_child) {
        Node *new_child = new Node;
        new_child->leaf = node->children[index_child]->leaf;
        new_child->keys.resize(t - 1);
        for (size_t i = 0; i < t - 1; ++i) {
            new_child->keys[i] = node->children[index_child]->keys[t + i];
        }

        for (size_t i = 0; i < t - 1; ++i) {
            node->children[index_child]->keys.pop_back();
        }

        if (!new_child->leaf) {
            for (size_t i = 0; i < t; ++i) {
                new_child->children.push_back(node->children[index_child]->children[t + i]);
            }

            for (size_t i = 0; i < t; ++i) {
                node->children[index_child]->children.pop_back();
            }
        }

        KeyType will_upwoard = node->children[index_child]->keys[t - 1];
        size_t pos = node->keys.size() - 1;
        node->keys.resize(node->keys.size() + 1);
        while (pos >= 0 && comp(will_upwoard, node->keys[pos])) {
            node->keys[pos + 1] = node->keys[pos];
            --pos;
        }
        node->keys[pos + 1] = will_upwoard;
        node->children[index_child]->keys.pop_back();

        size_t pos_child = node->keys.size() - 1;
        node->children.resize(node->keys.size() + 1);
        while (pos_child >= 0 && comp(will_upwoard, node->keys[pos_child])) {
            node->children[pos_child + 1] = node->children[pos_child];
            --pos_child;
        }
        node->children[pos_child + 1] = new_child;
    }

    void insert_non_full(Node *node, const KeyType &key) {
        size_t pos = node->keys.size() - 1;
        if (node->leaf) {
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && comp(key, node->keys[pos])) {
                node->keys[pos + 1] = node->keys[pos];
                --pos;
            }
            node->keys[pos + 1] = key;
        } else {
            while (pos >= 0 && comp(key, node->keys[pos])) {
                --pos;
            }

            if (is_full(node->children[pos + 1])) {
                split_child(node, pos + 1);
                
                if (comp(node->keys[pos + 1], key)) {
                    ++pos;
                }
            }

            insert_non_full(node->children[pos + 1], key);
        }
    }

    Node *root;
    size_t t;
    Comparator comp;
};

void run_case(std::istream &is = std::cin, std::ostream &os = std::cout) {
    size_t t;
    is >> t;
    BTree<int> btree(t);
    int elem;
    while (is >> elem) {
        btree.insert(elem);
    }
    btree.level_order();

}

int main() {
    run_case();
    return 0;
}
