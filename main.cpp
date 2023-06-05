#include <iostream>
#include <stack>
#include <string_view>

int main(int, char **) {
  std::string source = "int a = 1;";
  std::string_view input = source;
  std::string_view alphabetTable[] = {"int", "a", "=", "1", ";"};
  std::string_view stackTable[] = {"ε", "stmt", "var", "expr", "assignment", "intLiteral", "$"};
  std::string_view status[] = {"q0", "q1", "q2"};

  // init
  std::string_view currentStatus = status[0];
  std::stack<std::string_view> stackView;
  stackView.push("$"); //  push $
  // q0 int $ -> q1 stmt$
  if (input.find("int") == 0 && currentStatus == "q0" && stackView.top() == "$") {
    input = input.substr(3, source.size() - 3);
    currentStatus = "q1";
    stackView.push("stmt");
  }

  // q1 a stmt -> q2 var
  if (input.find(" a") == 0 && currentStatus == "q1" && stackView.top() == "stmt") {
    input = input.substr(2, source.size() - 5);
    currentStatus = "q2";
    stackView.push("var");
  }

  // q2 = var -> q3 assignment
  if (input.find(" =") == 0 && currentStatus == "q2" && stackView.top() == "var") {
    input = input.substr(2, source.size() - 7);
    currentStatus = "q3";
    stackView.push("assignment");
  }

  // q3 1 assignment -> q4 intLiteral
  if (input.find(" 1") == 0 && currentStatus == "q3" && stackView.top() == "assignment") {
    input = input.substr(2, source.size() - 9);
    currentStatus = "q4";
    stackView.push("intLiteral");
  }

  // q4 ; intLiteral -> q0 ε
  if (input.find(";") == 0 && currentStatus == "q4" && stackView.top() == "intLiteral") {
    input = input.substr(1, source.size() - 10);
    currentStatus = "q0";
    stackView.push("ε");
  }

  while (!stackView.empty()) {
    std::cout << stackView.top() << std::endl;
    stackView.pop();
  }
}
