#include <map>
#include <string>
#include <iostream>

int main() {
  std::map<std::string, int> str_to_number;
  str_to_number["one"] = 1;
  std::cout << str_to_number["one"] << "\n";
  str_to_number["two"] = 2;
  std::cout << str_to_number["two"] << "\n";
  std::cout << (str_to_number.find("aba") != str_to_number.end()) << "\n";
  std::cout << str_to_number.contains("one") << "\n";
}
// РАБОТАЕМ, РЕБЯТА
