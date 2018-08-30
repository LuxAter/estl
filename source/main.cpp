#include <iostream>
#include <sstream>
#include <fstream>

#include "json.hpp"

using namespace estl::json;

int main(int argc, char const* argv[]) {
  estl::json::Json a;
  std::ifstream load("latin_dictionary.json");
  if(load.is_open()){
    a = estl::json::ParseStream(load);
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
  std::cout << a << "\n";
  // std::cout << a[3]["Users"][0]["Name"] << "<<\n";
  return 0;
}
