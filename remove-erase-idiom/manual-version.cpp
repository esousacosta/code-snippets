#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> myIntVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto it = myIntVec.begin();

  // Remocao dos pares do vetor
  while (it != myIntVec.cend()) {
    if (*it % 2 == 0) {
      it = myIntVec.erase(it);
    } else
      ++it;
  }

  std::cout << "Conteudo do vetor apos a remocao: { ";
  for (auto num : myIntVec) {
    std::cout << num << " ";
  }
  std::cout << "}" << std::endl;
  return 0;
}