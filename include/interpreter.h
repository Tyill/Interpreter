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

#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <cstdint>

class InterpreterImpl;
class Interpreter {

public:
  using UserFunction = std::function<std::string(const std::vector<std::string>& args)>;
  using UserOperator = std::function<std::string(std::string& ioLeftOperand, std::string& ioRightOperand)>;

  explicit 
  Interpreter();
  ~Interpreter();

  Interpreter(const Interpreter&);
  Interpreter(Interpreter&&);
  Interpreter& operator=(const Interpreter&);  
  Interpreter& operator=(Interpreter&&);

  /// Add function
  /// @param name
  /// @param ufunc function
  /// return true - ok
  bool addFunction(const std::string& name, UserFunction ufunc);

  /// Add operator
  /// @param name
  /// @param uopr operator
  /// @param priority
  /// return true - ok
  bool addOperator(const std::string& name, UserOperator uopr, uint32_t priority);
   
  /// Execute script
  /// @param script
  /// @return result or error
  std::string cmd(std::string script);

  /// All variables
  /// @return vname, value
  std::map<std::string, std::string> allVariables() const;

  /// Value of variable
  /// @param vname
  /// @return value
  std::string variable(const std::string& vname) const;

  /// Set value of variable
  /// @param vname
  /// @param value
  /// @return true - ok
  bool setVariable(const std::string& vname, const std::string& value);

  /// Set macro
  /// @param mname
  /// @param script
  /// @return true - ok
  bool setMacro(const std::string& mname, const std::string& script);

  /// Go-to on label
  /// @param lname label name
  /// @return true - ok
  bool gotoOnLabel(const std::string& lname);

  /// Exit from script
  void exitFromScript();
  
private:
  InterpreterImpl* m_d = nullptr;
};