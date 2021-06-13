//
// Interpreter Project
// Copyright (C) 2020 by Contributors <https://github.com/Tyill/interpreter>
//
// This code is licensed under the MIT License.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../include/interpreter.h"
#include "../include/base_library/arithmetic_operations.h"
#include "../include/base_library/comparison_operations.h"
#include "../include/base_library/base_container.h"
#include <cctype>

using namespace std;

bool isNumber(const string& s) {
  for (auto c : s) {
    if (!std::isdigit(c)) {
      return false;
    }
  }
  return !s.empty();
}

int main(int argc, char* argv[])
{  
  Interpreter ir;

  InterpreterBaseLib::ArithmeticOperations ao(ir);
  InterpreterBaseLib::ComparisonOperations co(ir);
  InterpreterBaseLib::BaseContainer bc(ir);

  ir.addFunction("summ", [](const vector<string>& args) ->string {
    int res = 0;
    for (auto& v : args) {
      if (isNumber(v)) res += stoi(v);
    }
    return to_string(res);
  });

  ir.addFunction("print", [](const vector<string>& args) ->string {
    for (auto& v : args) {
      printf("%s\n", v.c_str());
    }
    return "";
  });

  string scenar = "$a = 5; $b = 2; while ($a > 1){ $a = $a - 1; $b = summ($b, $a); if ($a < 4){ break;} } $b;";
  string res = ir.cmd(scenar); // 9
  
  scenar = "$a = 5; $b = 2; $c = summ($a, ($a + ($a * ($b + $a))), summ(5)); $c;";
  res = ir.cmd(scenar); // 50

  scenar = "a = Vector; a.push_back(1); a.push_back(2); a.push_back(3); a.size()";
  res = ir.cmd(scenar); // 3

  scenar = "b = Map; b.insert(myKeyOne, myValueOne); b.insert(myKeyTwo, myValueTwo); b.at(myKeyTwo)";
  res = ir.cmd(scenar); // myValueTwo

  scenar = "a = Vector; a.push_back(1); a.push_back(2); a.push_back(3); while($v : a) print($v);";
  res = ir.cmd(scenar); // 1 2 3

  return 0;
}

