// https://stackoverflow.com/q/45013903

struct Node
{
    constexpr Node(const int n, Node const* next = nullptr)
        : value(n), next(next) {}
    constexpr Node push(const int n) const { return Node(n, this); }

    int value;
    Node const* next;
};

constexpr auto getSum(Node n) {
    int sum = 0;
    Node const *current = &n;
    while(current != nullptr) {
        sum += current->value;
        current = current->next;
    }
    return sum;
}

int main() {
    constexpr Node a(0);
    constexpr auto result = getSum(a.push(1).push(22));
    return result;
}

