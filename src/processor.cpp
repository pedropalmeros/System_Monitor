#include "processor.h"
#include "linux_parser.h"
#include <vector> 
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::stoi;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 

  if(first_loop){
  	prevVals = {0,0,0,0,0,0,0,0,0,0};
  	first_loop = false;
  }

  actuVals = LinuxParser::CpuUtilization();

  long PrevIdle = prevVals[LinuxParser::kIdle_] + prevVals[LinuxParser::kIOwait_];
  long Idle     = actuVals[LinuxParser::kIdle_] + actuVals[LinuxParser::kIOwait_];

  long PrevNonIdle = prevVals[LinuxParser::kUser_] + prevVals[LinuxParser::kNice_] + 
                      prevVals[LinuxParser::kSystem_] + prevVals[LinuxParser::kIRQ_] +  
                      prevVals[LinuxParser::kSoftIRQ_] + prevVals[LinuxParser::kSteal_];
  long     NonIdel = actuVals[LinuxParser::kUser_] + actuVals[LinuxParser::kNice_] + 
                      actuVals[LinuxParser::kSystem_] + actuVals[LinuxParser::kIRQ_] +  
                      actuVals[LinuxParser::kSoftIRQ_] + actuVals[LinuxParser::kSteal_];


  long PrevTotal = prevVals[LinuxParser::kIdle_] + PrevNonIdle;
  long     Total = actuVals[LinuxParser::kIdle_] + NonIdel;

  long totald = Total - PrevTotal;
  long idled = Idle - PrevIdle;


  prevVals = actuVals;
  float CPU_Percentage = (float)(totald - idled)/totald;

  return CPU_Percentage;
}
  					