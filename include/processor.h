#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>


class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp


  // TODO: Declare any necessary private members
  std::vector<long> actuVals{};
  std::vector<long> prevVals = {0,0,0,0,0,0,0,0,0,0};

 private:
  bool first_loop = true;
};

#endif