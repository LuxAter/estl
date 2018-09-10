#include <iostream>
#include <sstream>
#include <fstream>

#include <ctime>

#include "json.hpp"

using namespace estl::json;

int main(int argc, char const* argv[]) {
  std::clock_t start;
  estl::json::Json a;
  std::ifstream load("laboris.json");
  if(load.is_open()){
    start = std::clock();
    a = estl::json::ParseStream(load);
    std::cout << "TIME: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << "ms\n";
    load.close();
  }
  std::ifstream string_load("latin_dictionary.json");
  if (string_load.is_open()){
    start = std::clock();
    std::pair<estl::json::Json::JsonToken, std::string> token;
    token = estl::json::GetNextToken(string_load);
    while(token.first != estl::json::Json::T_NILL){
      token = estl::json::GetNextToken(string_load);
    }
    // a = estl::json::ParseString(static_cast<std::stringstream const&>(std::stringstream() << string_load.rdbuf()).str());
    std::cout << "TIME: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << "ms\n";
    load.close();
  }

  // std::queue<std::pair<Json::JsonToken, std::string>> tokens;
  // tokens.push({Json::T_OPEN_LIST, ""});
  // tokens.push({Json::T_INT, "2018"});
  // tokens.push({Json::T_INT, "1998"});
  // tokens.push({Json::T_OPEN_DICT, ""});
  // tokens.push({Json::T_STRING, "Name"});
  // tokens.push({Json::T_COLLON, ":"});
  // tokens.push({Json::T_STRING, "Arden"});
  // tokens.push({Json::T_STRING, "Age"});
  // tokens.push({Json::T_COLLON, ":"});
  // tokens.push({Json::T_INT, "20"});
  // tokens.push({Json::T_CLOSE_DICT, ""});
  // tokens.push({Json::T_CLOSE_LIST, ""});
  // estl::json::Json a = estl::json::ParseTokenQueue(tokens);
  // std::cout << a << "\n";
  // std::cout << a[3]["Users"][0]["Name"] << "<<\n";
  return 0;
}
