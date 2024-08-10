#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> myIntVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // Remocao dos pares do vetor com a tecnica do remove-erase
  myIntVec.erase(std::remove_if(myIntVec.begin(), myIntVec.end(),
                                [](int num) { return (num % 2 == 0); }),
                 myIntVec.end());

  std::cout << "Conteudo do vetor apos a remocao: { ";
  for (auto num : myIntVec) {
    std::cout << num << " ";
  }
  std::cout << "}" << std::endl;
  return 0;
}