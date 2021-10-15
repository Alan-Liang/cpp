#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct Node {
  int number;
  Node *next;
} Node;

typedef struct LinkedList {
  int length;
  Node *head;

  Node *_newNode () {
    return (Node *) malloc(sizeof(Node));
  }

  void initialize () {
    cin >> length;
    if (length == 0) {
      length = 0;
      return;
    }
    head = _newNode();
    Node *last = head;
    cin >> last->number;
    for (int i = 1; i < length; i++) {
      last->next = _newNode();
      last = last->next;
      cin >> last->number;
    }
    last->next = NULL;
  }

  Node *_nth (int n) {
    Node *node = head;
    while (n--) node = node->next;
    return node;
  }

  void insert (int i, int x) {
    Node *node = _nth(i - 1);
    Node *new_ = _newNode();
    new_->number = x;
    new_->next = node->next;
    node->next = new_;
    length++;
  }

  void erase (int i) {
    if (i == 1) {
      Node *newHead = head->next;
      free(head);
      head = newHead;
      length--;
      return;
    }
    Node *node = _nth(i - 2);
    Node *newNext = node->next->next;
    free(node->next);
    node->next = newNext;
    length--;
  }

  void swap () {
    Node *node = head;
    while (true) {
      Node *next = node->next;
      if (next == NULL) return;
      int tmp = node->number;
      node->number = next->number;
      next->number = tmp;
      node = next->next;
      if (node == NULL) return;
    }
  }

  void cut (int i) {
    Node *node = _nth(i - 1);
    Node *firstToDispose = node->next;
    if (firstToDispose == NULL) return;
    node->next = NULL;
    length = i;
    node = firstToDispose;
    while (node->next != NULL) {
      Node *current = node;
      node = node->next;
      free(current);
    }
    free(node);
  }

  int query (int i) {
    return _nth(i - 1)->number;
  }

  int size () {
    return length;
  }

  void print () {
    Node *node = head;
    while (node->next != NULL) {
      cout << node->number << ' ';
      node = node->next;
    }
    cout << node->number << '\n';
  }

  void freeMemory () {
    Node *node = head;
    while (node->next != NULL) {
      Node *current = node;
      node = node->next;
      free(current);
    }
    free(node);
  }
} LinkedList;

int main () {
  LinkedList l;
  int n, op, i, x;
  l.initialize();
  cin >> n;
  while (n--) {
    cin >> op;
    // cout << op << "!!\n";
    if (op == 0) {
      cin >> i >> x;
      l.insert(i, x);
    }
    else if (op == 1) {
      cin >> i;
      l.erase(i);
    }
    else if (op == 2) {
      l.swap();
    }
    else if (op == 3) {
      cin >> i;
      l.cut(i);
    }
    else if (op == 4) {
      cin >> i;
      cout << l.query(i) << endl;
    }
    else if (op == 5) {
      cout << l.size() << endl;
    }
    else {
      l.print();
    }
  }
  l.freeMemory();
  return 0;
}
