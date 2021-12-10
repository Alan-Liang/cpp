#include <bits/stdc++.h>

class LinkList {
 private:
  struct ListNode {
    int value;
    std::shared_ptr<ListNode> next;
    ListNode () = default;
    explicit ListNode (int value) : value(value) {}
    ListNode (int value, std::shared_ptr<ListNode> next) : value(value), next(next) {}
  };
  std::shared_ptr<ListNode> head;
  int pop_ () {
    int res = head->next->value;
    head->next = head->next->next;
    return res;
  }
 public:
  LinkList () : head(new ListNode()) {}
  void push (int x) {
    std::shared_ptr<ListNode> current = head;
    for (; current->next; current = current->next) {
      if (current->next->value >= x) {
        current->next = std::make_shared<ListNode>(x, current->next);
        return;
      }
    }
    current->next = std::make_shared<ListNode>(x);
  }
  int getKth (int k) {
    std::shared_ptr<ListNode> current = head;
    while (k--) {
      if (!current->next) return -1;
      current = current->next;
    }
    if (!current->next) return -1;
    return current->next->value;
  }
  void merge (LinkList *other) {
    if (this == other) throw "bad";
    std::shared_ptr<ListNode> newHead = std::make_shared<ListNode>();
    std::shared_ptr<ListNode> newTail = newHead;
    while (true) {
      if (!head->next && !other->head->next) break;
      if (head->next && !other->head->next) {
        newTail = newTail->next = std::make_shared<ListNode>(pop_());
        continue;
      }
      if (!head->next && other->head->next) {
        newTail = newTail->next = std::make_shared<ListNode>(other->pop_());
        continue;
      }
      int lhs = head->next->value, rhs = other->head->next->value;
      if (lhs < rhs) {
        newTail = newTail->next = std::make_shared<ListNode>(pop_());
      } else {
        newTail = newTail->next = std::make_shared<ListNode>(other->pop_());
      }
    }
    head = newHead;
  }
};

class LinkListArray {
private:
    int len;
    LinkList **lists;

public:
    LinkListArray(int n): len(n) {
        lists = new LinkList*[n];
        for (int i = 0; i < n; ++i) lists[i] = new LinkList;
    }
    ~LinkListArray() {
        for (int i = 0; i < len; ++i) {
            delete lists[i];
        }
        delete []lists;
    }

    void insertNumber(int n, int x) {
        lists[n]->push(x);
    }
    int queryNumber(int n, int k) {
        return lists[n]->getKth(k);
    }
    void mergeLists(int p, int q) {
        lists[p]->merge(lists[q]);
    }
};

#ifndef ONLINE_JUDGE
int main() {
    int len, m;
    scanf("%d%d", &len, &m);
    LinkListArray a = LinkListArray(len);
    for (int i = 0, op, s1, s2; i < m; ++i) {
        scanf("%d%d%d", &op, &s1, &s2);
        if (op == 0) {
            a.insertNumber(s1, s2);
        }
        if (op == 1) {
            printf("%d\n", a.queryNumber(s1, s2));
        }
        if (op == 2) {
            a.mergeLists(s1, s2);
        }
    }
    return 0;
}
#endif
