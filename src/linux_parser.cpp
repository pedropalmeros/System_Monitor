#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>


#include "linux_parser.h"

using std::stof;
using std::stol;
using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;

/*************************************************************
          FUNCTIONS FOR SYSTEM ANALYSIS
****************************************************************/



// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string word2find;
  string value;
  long MemTotal{0};
  long MemFree{0};
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if(filestream.is_open()){
    while (std::getline(filestream,line)){
      std::istringstream linestream(line);
      while(linestream >> word2find >> value){
        if (word2find=="MemTotal:"){
          MemTotal = stoi(value);
          }
          else if(word2find == "MemFree:"){
            MemFree = stoi(value);
          }
        }
      }
    }
  return float( (MemFree)/MemTotal);
}


// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 

  string uptime;
  string line;
  std::ifstream stream(kProcDirectory+kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
    return stol(uptime);
  }
  return -1;

  

  //return 20155;
 }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string word2find;
  string value;
  //long processes{0};
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open()){
    while (std::getline(filestream,line)){
      std::istringstream linestream(line);
      while (linestream >> word2find >> value){
        if (word2find=="processes"){
          return stoi(value);
        }
      }
    }
  }
  return -1;
}


// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {   
  string line;
  string word2find;
  string value;
  //long procs_running{0};
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open()){
    while (std::getline(filestream,line)){
      std::istringstream linestream(line);
      while (linestream >> word2find >> value){
        if (word2find=="procs_running"){
          return stoi(value);
        }
      }
    }
  }
  return -1;
}


/************************************************************************
        Functions for CPU ANALYSIS
*************************************************************************/



// TODO: Read and return CPU utilization
vector<long> LinuxParser::CpuUtilization() { 
  std::string line;
  std::string cpu;
  std::vector<long> Vec{};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu;
    while(linestream >> cpu){
      Vec.push_back(stol(cpu));
    }
  }
  return Vec;
  }









/**********************************************************************
/           FUNCTIONS FOR PROCCESS ANALYSIS
***********************************************************************/

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::string line{};

  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) 
    std::getline(filestream, line);

 return line; }
  

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
// Memory Utilization
string LinuxParser::Ram(int pid) { 
  string word2find;
  string value;
  string line;
  string result;
  std::ifstream filestream(kProcDirectory + to_string(pid) +  kStatusFilename);
  if(filestream.is_open()){
    while (std::getline(filestream,line)){
      std::istringstream linestream(line);
      while (linestream >> word2find >> value){
        if (word2find=="VmSize:")
          return to_string(stof(value)/1000);
      }
    }
  }
  return string("error");
}


// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string word2find;
  string value;
  string line;
  std::ifstream filestream(kProcDirectory+to_string(pid) + kStatusFilename);
  if(filestream.is_open()){
    while (std::getline(filestream,line)){
      std::istringstream linestream(line);
      while (linestream >> word2find >> value){
        if (word2find=="Uid:"){
          return value;
        }
      }
    }
  }
  return string("Error");
}




  

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 

  string line;
  string uid = LinuxParser::Uid(pid);
  string uid_comp;
  string x;
  string username;

  std::ifstream filestream("/etc/passwd");
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> username >> x >> uid_comp ) {
        if (uid_comp == uid) {
          return username;
        }
      }
    }
  }
  return string("Error");
}


// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  
  std::string line;
  std::string myString;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for(int i = 0; i <= 21; i++){
      linestream >> myString;
    }
  }
  return LinuxParser::UpTime() - (stol(myString)/sysconf(_SC_CLK_TCK));
  
}


float LinuxParser::ProcessorUtilization(int pid){
  std::string line;
  std::string myString;
  std::vector<std::string> values{};
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while(linestream >> myString){
      values.push_back(myString);
    }
  }
  else{
    return 0.0;
  }
  float utime = (stof(values[utime_]))/sysconf(_SC_CLK_TCK);
  float stime = (stof(values[stime_]))/sysconf(_SC_CLK_TCK);
  float cutime = (stof(values[cutime_]))/sysconf(_SC_CLK_TCK);
  float cstime = (stof(values[cstime_]))/sysconf(_SC_CLK_TCK);
  float starttime = (stof(values[starttime_]))/sysconf(_SC_CLK_TCK);

  float total_time = utime + stime + cutime +  cstime;

  float seconds = LinuxParser::UpTime() - starttime;

  return total_time/seconds; 
}
