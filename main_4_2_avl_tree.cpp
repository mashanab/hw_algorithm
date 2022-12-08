#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stack>
#include <sstream>

template < typename T >
struct DefaultComparator {
    bool operator()(const T& l, const T& r) const;
};

template < typename T, typename Comparator = DefaultComparator<T> >
class AvlTree {
    struct Node {
        Node *left;
        Node *right;
        T key;

        uint8_t height;

        Node(const T& k);
    };

 public:
    AvlTree(Comparator comp = Comparator());

    AvlTree(const AvlTree &other)=delete;
    AvlTree &operator=(const AvlTree &other)=delete;
    AvlTree(AvlTree &&other)=delete;
    AvlTree &operator=(AvlTree &&other)=delete;

    ~AvlTree();

    bool contains(const T& key) const;

    Node *lower_bound(const T& key) const;

    Node *upper_bound(const T& key) const;

    void insert(const T& key);

    void erase(const T& key);

    T k_stat(const size_t &k);

    size_t size() const;
    bool empty() const;
    void clear();

 private:
    Node *insert_aux(const T& key, Node *node);

    Node *erase_aux(const T& key, Node *node);

    Node *find_max(Node *node);
    Node *find_min(Node *node);

    Node *remove_max(Node *node);
    Node *remove_min(Node *node);

    Node *find_and_remove_max(Node *node);
    Node *find_and_remove_min(Node *node);

    Node *balance(Node *node);
    int bfactor(Node *node) const;
    void fix_height(Node *node) const;
    int height(Node *node) const;

    Node *rotate_left(Node *node);
    Node *rotate_right(Node *node);

    size_t items_count;
    Node *root;
    Comparator comp;
};

void run_case(std::istream &is = std::cin, std::ostream &os = std::cout) {
    AvlTree< long int > avl_tree;

    size_t n = 0;
    is >> n;

    for (size_t i = 0; i < n; ++i) {
        int command;
        int k;
        is >> command >> k;
        if (command > 0) {
            avl_tree.insert(command);
        } else if (command < 0) {
            avl_tree.erase(command * (-1));
        }
        os << avl_tree.k_stat(k) << std::endl;
    }
}

int main() {
    // std::stringstream s("3 1 0 2 0 -1 0\n");
   run_case();
    return 0;
}

template < typename T >
bool DefaultComparator< T >::operator()(const T& l, const T& r) const {
    if (l < r) {
        return true;
    }
    return false;
}

template< class T, class Comparator >
T AvlTree< T, Comparator >::k_stat(const size_t &k) {
    std::stack<Node *> nodes;
    size_t i = 0;
    Node *curr = root;
    while (curr || !nodes.empty()) {
        while (curr) {
            nodes.push(curr);
            curr = curr->left;
        }
        curr = nodes.top();
        nodes.pop();
        
        if (i == k) {
            return curr->key;
        }

        curr = curr->right;
        ++i;
    }
    return -1;
}

template < typename T, typename Comparator >
AvlTree< T, Comparator >::Node::Node(const T& k)
: left(nullptr), right(nullptr), key(k), height(1) {}

template < typename T, typename Comparator >
AvlTree< T, Comparator >::~AvlTree() {
    clear();
}

template < typename T, typename Comparator >
AvlTree< T, Comparator >::AvlTree(Comparator comp)
: items_count(0), root(nullptr), comp(comp) {}

template< class T, class Comparator >
bool AvlTree< T, Comparator >::contains(const T& key) const {
    Node *tmp = root;
    while (tmp) {
        if (!(tmp->key < key) && !(key < tmp->key)) {
            return true;
        } else if (tmp->key < key) {
            tmp = tmp->right;
        } else {
            tmp = tmp->left;
        }
    }
    return false;
}

template< typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *
AvlTree< T, Comparator >::lower_bound(const T& key) const { // in_order
    std::stack< Node * > nodes;
    Node *curr = root;

    while (curr || !nodes.empty()) {
        while (curr) {
            nodes.push(curr);
            curr = curr->left;
        }
        curr = nodes.top();
        nodes.pop();
        if (comp(key, curr->key)) {
            return curr;
        }
        curr = curr->right;
    }
    return nullptr;
}

template< typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *
AvlTree< T, Comparator >::upper_bound(const T& key) const { // in-order
    std::stack< Node * > nodes;
    Node *curr = root;

    while (curr || !nodes.empty()) {
        while (curr) {
            nodes.push(curr);
            curr = curr->right;
        }
        curr = nodes.top();
        nodes.pop();
        if (comp(curr->key, key)) {
            return curr;
        }
        curr = curr->left;
    }
    return nullptr;
}

template < typename T, typename Comparator >
void AvlTree< T, Comparator >::insert(const T& key) {
    root = insert_aux(key, root);
}

template < typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *AvlTree< T, Comparator >::insert_aux
                                (const T& key, Node *node) {
    if (!node) {
        ++items_count;
        Node *new_key = new Node(key);
        return new_key;
    }

    if (comp(key, node->key)) {
        node->left = insert_aux(key, node->left);
    } else if (comp(node->key, key)) {
        node->right = insert_aux(key, node->right);
    }
    return balance(node);
}

template < typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *AvlTree< T, Comparator >::balance(Node *node) {
    fix_height(node);

    int bf = bfactor(node);
    if (bf == 2) {
        if (bfactor(node->right) < 0) {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    } else if (bf == -2) {
        if (bfactor(node->left) > 0) {
            node->left = rotate_left(node->left);
        }
        return rotate_right(node);
    }
    return node;
}

template < typename T, typename Comparator >
void AvlTree< T, Comparator >::fix_height(Node *node) const {
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

template < typename T, typename Comparator >
int AvlTree< T, Comparator >::height(Node *node) const {
    if (!node) {
        return 0;
    }
    return node->height;
}

template < typename T, typename Comparator >
int AvlTree< T, Comparator >::bfactor(Node *node) const {
    return height(node->right) - height(node->left);
}

template < typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *
AvlTree< T, Comparator >::rotate_left(Node *node) {
    Node *tmp = node->right;
    node->right = tmp->left;

    tmp->left = node;
    fix_height(node);
    fix_height(tmp);
    return tmp;
}

template < typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *
AvlTree< T, Comparator >::rotate_right(Node *node) {
    Node *tmp = node->left;
    node->left = tmp->right;

    tmp->right = node;

    fix_height(node);
    fix_height(tmp);
    return tmp;
}

template < typename T, typename Comparator >
void AvlTree< T, Comparator >::erase(const T& key) {
    root = erase_aux(key, root);
}

template < typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *
AvlTree< T, Comparator >::erase_aux(const T& key, Node *node) {
    if (!node) {
        return nullptr;
    }
    if (comp(node->key, key)) {
        node->right = erase_aux(key, node->right);
    } else if (comp(key, node->key)) {
        node->left = erase_aux(key, node->left);
    } else {
        Node *left = node->left;
        Node *right = node->right;

        --items_count;

        if (!right) {
            delete node;
            return left;
        }
        Node *erased_node;
        if (height(left) > height(right)) {
            erased_node = find_and_remove_max(left);
            erased_node->right = right;
        } else {
            erased_node = find_and_remove_min(right);
            erased_node->left = left;
        }
        delete node;

        return balance(erased_node);
    }
    return balance(node);
}

template < typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *AvlTree< T, Comparator >::find_min(Node *node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

template < typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *AvlTree< T, Comparator >::remove_min(Node *node) {
    if (!node->left) {
        return node->right;
    }
    node->left = remove_min(node->left);

    return balance(node);
}

template < typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *AvlTree< T, Comparator >::find_max(Node *node) {
    while (node->right) {
        node = node->right;
    }
    return node;
}

template < typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *AvlTree< T, Comparator >::remove_max(Node *node) {
    if (!node->right) {
        return node->left;
    }
    node->right = remove_max(node->right);

    return balance(node);
}

template < typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *
AvlTree< T, Comparator >::find_and_remove_max(Node *node) {
    Node *max_node = find_max(node);
    max_node->left = remove_max(node);

    return max_node;
}

template < typename T, typename Comparator >
typename AvlTree< T, Comparator >::Node *
AvlTree< T, Comparator >::find_and_remove_min(Node *node) {
    Node *min_node = find_min(node);
    min_node->right = remove_min(node);

    return min_node;
}

template < typename T, typename Comparator >
size_t  AvlTree< T, Comparator >::size() const {
    return items_count;
}

template < typename T, typename Comparator >
bool  AvlTree< T, Comparator >::empty() const {
    return items_count == 0;
}

template< typename T, typename Comparator >
void AvlTree< T, Comparator >::clear() { // pre_order
    std::stack< Node * > nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        Node *curr = nodes.top();
        nodes.pop();
        if (curr->right) {
            nodes.push(will_be_deleted->right);
        }
        if (curr->left) {
            nodes.push(will_be_deleted->left);
        }
        delete curr;
        curr = nullptr;
    }
}
