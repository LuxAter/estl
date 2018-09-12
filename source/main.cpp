#include <iostream>

#include "fuzz.hpp"

#include <vector>
#include <fstream>

std::vector<std::string> LoadWords(){
  // std::ifstream file("words_alpha.txt");
  std::ifstream file("words_small.txt");
  std::vector<std::string> words;
  if(file.is_open()){
    std::string line;
    while(getline(file, line)){
      words.push_back(line);
    }
    file.close();
  }
  return words;
}

int main(int argc, char const* argv[]) {
  auto words = LoadWords();
  std::string input = "";
  while(input != "quit"){
    std::cout << ">>";
    std::cin >> input;
    auto rec = estl::fuzz::Fuzz<5>(input, words, estl::fuzz::Manhattin);
    for(auto& it : rec){
      std::cout << it << '\n';
    }
    std::cout << '\n';
  }
  return 0;
}
