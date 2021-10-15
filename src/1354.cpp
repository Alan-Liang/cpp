#include<iostream>

#define MAXN 400002

int lowerBound, upperBound, numOps;
int array[MAXN];

inline int realIndexFromInputIndex (int inputIndex) {
  return inputIndex - lowerBound;
}

inline bool isInputIndexOutOfBound (int inputIndex) {
  return inputIndex < lowerBound || inputIndex > upperBound;
}

int main () {
  std::cin >> lowerBound >> upperBound >> numOps;
  for (int i = 0; i < upperBound - lowerBound + 1; i++) std::cin >> array[i];
  for (int i = 0; i < numOps; i++) {
    int op, inputIndex;
    std::cin >> op >> inputIndex;
    if (isInputIndexOutOfBound(inputIndex)) {
      if (op == 1) std::cin >> op;
      std::cout << "RE\n";
      continue;
    }
    int realIndex = realIndexFromInputIndex(inputIndex);
    if (op == 1) {
      int value;
      std::cin >> value;
      array[realIndex] = value;
    } else {
      std::cout << array[realIndex] << '\n';
    }
  }
}
