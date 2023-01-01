#ifndef ABCC_COMPILER_H
#define ABCC_COMPILER_H

#include <string>

class Compiler {
public:
  void readFromFile(const std::string);
  void run(const std::string);
};


#endif //ABCC_COMPILER_H

