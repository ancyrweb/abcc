#include "Compiler.h"
#include "Lexer.h"

#include <iostream>
#include <fstream>

void Compiler::readFromFile(const std::string filePath) {
  std::ifstream file;
  file.open(filePath);

  if(!file.is_open()) {
    // TODO : proper error handling
    exit(0);
  }

  file.seekg(0, std::ios::end);
  size_t size = file.tellg();
  std::string buffer(size, 0);
  file.seekg(0);
  file.read(&buffer[0], size);

  this->run(buffer);
}

void Compiler::run(const std::string source) {
  Lexer lexer;
  lexer.scan(source);
}