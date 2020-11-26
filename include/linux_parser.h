#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};


/***********************************************  
            System Analysis
************************************************/            
std::string OperatingSystem();    // DONE
std::string Kernel();             // DONE
std::vector<int> Pids();          // DONE
float MemoryUtilization();        // DONE
long UpTime();                    // DONE 
int TotalProcesses();             // DONE
int RunningProcesses();           // DONE



/***********************************************  
            Processor Analysis - CPU
************************************************/ 
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};


std::vector<long> CpuUtilization();


/***********************************************  
            Processes Analysis
************************************************/ 

// Processes
enum pidStat {
  utime_ = 13,
  stime_,
  cutime_,
  cstime_,
  starttime_ = 21
};


std::string Command(int pid);   // DONE
std::string Ram(int pid);       // DONE
std::string Uid(int pid);       // DONE
std::string User(int pid);      // DONE
long int UpTime(int pid);       // DONE
float ProcessorUtilization(int pid); 
};  // namespace LinuxParser
  
#endif