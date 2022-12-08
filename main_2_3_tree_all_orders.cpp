#include <iostream>
#include <stack>
#include <cstddef>
#include <sstream>
#include <queue>

template <typename T>
struct DefaultComparator {
    bool operator()(const T &lhs, const T &rhs) const {
        return lhs < rhs;
    }
};

template < typename Key, typename Comparator = DefaultComparator<Key> >
class Tree {
 public:
    struct Node {
        Node *left;
        Node *right;
        Key key;

        Node(const Key &key) : left(nullptr), right(nullptr), key(key) {}
    };

    Tree(Comparator comp = Comparator()) : root(nullptr), items_count(0), comp(comp) {}

    ~Tree() { // pre_order
        std::stack<Node *> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            Node *curr = nodes.top();
            nodes.pop();
            if (curr->right) {
                nodes.push(curr->right);
            }
            if (curr->left) {
                nodes.push(curr->left);
            }
            delete curr;
        }
    }

    void insert(const Key &key) {
        root = insert_aux(root, key);
    }

    bool contains(const Key &key) {
        return contains_aux(root, key);
    }

    void erase(const Key &key) {
        root = erase_aux(root, key);
    }

    std::queue<Node *> pre_order() { // pre_order
        std::stack<Node *> s;
        std::queue<Node *> q;
        s.push(root);
        while (!s.empty()) {
            Node *curr = s.top();
            q.push(curr);
            s.pop();
            if (curr->right) {
                s.push(curr->right);
            }
            if (curr->left) {
                s.push(curr->left);
            }
        }
        return q;
    }

    std::queue<Node *> in_order() { // in_order
        std::stack<Node *> s;
        std::queue<Node *> q;
        Node *curr = root;
        while (!s.empty() || curr) {
            while (curr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            q.push(curr);
            s.pop();

            curr = curr->right;
        }
        return q;
    }

    std::stack<Node *> post_order() { // post_order
        std::stack<Node *> s1;
        std::stack<Node *> s2;
        Node *curr = root;
        s2.push(curr);
        while (true) {
            if (curr->right) {
                s2.push(curr->right);
                if (curr->left) {
                    s1.push(curr->left);
                }
                curr = curr->right;
            } else if (curr->left) {
                s2.push(curr->left);
                curr = curr->left;
            } else {
                if (!s1.empty()) {
                    curr = s1.top();
                    s1.pop();
                    s2.push(curr);
                } else {
                    break;
                }
            }
        }
        return s2;
    }

    std::queue<Node *> level_order() { // level_order
        std::queue<Node *> q;
        std::queue<Node *> q_res;
        q.push(root);
        while (!q.empty()) {
            Node *curr = q.front();
            q_res.push(curr);
            q.pop();

            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
        }
        return q_res;
    }

 private:
    Node *insert_aux(Node *node, const Key &key) {
        if (!node) {
            return new Node(key);
        }
        if (comp(key, node->key)) {
            node->left = insert_aux(node->left, key);
        } else {
            node->right = insert_aux(node->right, key);
        }
        return node;
    }

    bool contains_aux(Node *node, const Key &key) {
        if (!node) {
            return false;
        }
        if (comp(key, node->key)) {
            return contains_aux(node->left, key);
        } else if (comp(node->key, key)) {
            return contains_aux(node->right, key);
        } else {
            return true;
        }
    }

    Node *erase_aux(Node *node, const Key &key) {
        if (!node) {
            return nullptr;
        }
        if (comp(key, node->key)) {
            node->left = erase_aux(node->left, key);
        } else if (comp(node->key, key)) {
            node->right = erase_aux(node->right, key);
        } else {
            Node *left = node->left;
            Node *right = node->right;
            if (!right) {
                delete node;
                return left;
            }
            if (!left) {
                delete node;
                return right;
            }

            if (!right->left) {
                delete node;
                right->left = left;
                return right;
            }

            Node *parent_min = node;
            Node *min = right;
            while (min->left) {
                parent_min = min;
                min = min->left;
            }
            
            if (parent_min == node) {
                parent_min->right = min->right;
            } else {
                parent_min->left = min->right;
            }
            node->key = min->key;
            delete min;
        }
        return node;
    }

    Node *root;
    size_t items_count;
    Comparator comp;

};

void run_case(std::istream &is = std::cin, std::ostream &os = std::cout) {
    size_t N = 0;
    is >> N;
    Tree<int> tree;
    for (size_t i = 0; i < N; ++i) {
        int key = 0;
        is >> key;
        tree.insert(key);
    }
    std::queue<Tree<int>::Node *> queue_level_order = tree.level_order();
    while (!queue_level_order.empty()) {
        os << queue_level_order.front()->key << ((queue_level_order.size() == 1) ? '\n' : ' ');
        queue_level_order.pop();
    }
}

int main() {
    run_case();
    return 0;
}
