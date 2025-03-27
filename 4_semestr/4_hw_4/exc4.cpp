
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <chrono>
#include <map>

using namespace std;

struct Book {
    int id;
    string author;
    string title;

    bool operator<(const Book& other) const {
        return id < other.id;
    }
};

class RedBlackTree {
private:
    struct Node {
        Book book;
        bool color; // true -> red, false -> black
        Node *left, *right, *parent;

        Node(Book book) : book(book), color(true), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node *root;
    Node *TNULL;

    void leftRotate(Node *&x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *&x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node *&k) {
        Node *u;
        while (k->parent->color == true) {
            if (k->parent == k->parent->parent->left) {
                u = k->parent->parent->right;
                if (u->color == true) {
                    k->parent->color = false;
                    u->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    rightRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->left;
                if (u->color == true) {
                    k->parent->color = false;
                    u->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    leftRotate(k->parent->parent);
                }
            }
            if (k == root) break;
        }
        root->color = false;
    }

    void fixDelete(Node *&x) {
        Node *s;
        while (x != root && x->color == false) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == true) {
                    s->color = false;
                    x->parent->color = true;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == false && s->right->color == false) {
                    s->color = true;
                    x = x->parent;
                } else {
                    if (s->right->color == false) {
                        s->left->color = false;
                        s->color = true;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = false;
                    s->right->color = false;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {

                s = x->parent->left;
                if (s->color == true) {
                    s->color = false;
                    x->parent->color = true;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->right->color == false && s->left->color == false) {
                    s->color = true;
                    x = x->parent;
                } else {
                    if (s->left->color == false) {
                        s->right->color = false;
                        s->color = true;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = false;
                    s->left->color = false;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = false;
    }

public:
    RedBlackTree() {
        TNULL = new Node({0, "", ""});
        TNULL->color = false;
        root = TNULL;
    }

    void insert(Book book) {
        Node *node = new Node(book);
        node->parent = nullptr;
        node->book = book;
        node->left = TNULL;
        node->right = TNULL;

        Node *y = nullptr;
        Node *x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->book.id < x->book.id) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->book.id < y->book.id) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = false;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);
    }

    void deleteNode(int bookId) {
        Node *node = TNULL;
        Node *x, *y;
        while (root != TNULL) {
            if (root->book.id == bookId) {
                node = root;
            }
            if (root->book.id <= bookId) {
                root = root->right;
            } else {
                root = root->left;
            }
        }

        if (node == TNULL) {
            cout << "Book not found\n";
            return;
        }

        y = node;
        bool yOriginalColor = y->color;
        if (node->left == TNULL) {
            x = node->right;
            transplant(node, node->right);
        } else if (node->right == TNULL) {
            x = node->left;
            transplant(node, node->left);
        } else {
            y = minimum(node->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == node) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }

            transplant(node, y);
            y->left = node->left;
            y->left->parent = y;
            y->color = node->color;
        }
        delete node;
        if (yOriginalColor == false) {
            fixDelete(x);
        }
    }

    Node* search(int key) {
        return searchHelper(this->root, key);
    }

    void printInOrder(Node *node, ofstream& file) {
        if (node != TNULL) {
            printInOrder(node->left, file);
            file << "ID: " << node->book.id << ", Author: " << node->book.author << ", Title: " << node->book.title << endl;
            printInOrder(node->right, file);
        }
    }

    void writeToFile(const string& filename) {
        ofstream file(filename);
        printInOrder(this->root, file);
        file.close();
    }

    Node* minimum(Node* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    Node* searchHelper(Node *node, int key) {
        if (node == TNULL || key == node->book.id) {

            return node;
        }

        if (key < node->book.id) {
            return searchHelper(node->left, key);
        }
        return searchHelper(node->right, key);
    }

    void transplant(Node *u, Node *v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    Node* getRoot() {
        return this->root;
    }
};

int main() {
    const int numberOfBooks = 10000;
    RedBlackTree rbt;
    map<int, Book> bookMap;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> idDis(1, 100000);
    uniform_int_distribution<> authorDis(1, 100);
    uniform_int_distribution<> titleDis(1, 1000);

    for (int i = 0; i < numberOfBooks; i++) {
        Book book = { idDis(gen), "Author " + to_string(authorDis(gen)), "Title " + to_string(titleDis(gen)) };

        auto start = chrono::high_resolution_clock::now();
        rbt.insert(book);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> rbtInsertTime = end - start;

        start = chrono::high_resolution_clock::now();
        bookMap[book.id] = book;
        end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> mapInsertTime = end - start;

        cout << "RB Tree insert time: " << rbtInsertTime.count() << " ms, Map insert time: " << mapInsertTime.count() << " ms" << endl;
    }

    for (int i = 0; i < 100; i++) {
        int bookId = idDis(gen);

        auto start = chrono::high_resolution_clock::now();
        rbt.search(bookId);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> rbtSearchTime = end - start;

        start = chrono::high_resolution_clock::now();
        bookMap.find(bookId);
        end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> mapSearchTime = end - start;

        cout << "RB Tree search time: " << rbtSearchTime.count() << " ms, Map search time: " << mapSearchTime.count() << " ms" << endl;
    }

    rbt.writeToFile("books.txt");

    return 0;
}
