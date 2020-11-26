#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid):pid_(pid){}

// TODO: Return this process's ID
int Process::Pid() { 
	return pid_; 
	//return 0;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
	return LinuxParser::ProcessorUtilization(this->pid_); 
	//return 0.0;
}

// TODO: Return the command that generated this process
string Process::Command() { 
	return LinuxParser::Command(this->pid_);
	//return string(); 
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
	return LinuxParser::Ram(this->pid_); 
	//return string();
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
	return LinuxParser::User(this->pid_);
	//return string(); 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
	return LinuxParser::UpTime(this->pid_); 
	//return 0;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& processB) const { 
	int pidA = this->pid_;
	int pidB = processB.pid_;
	return LinuxParser::ProcessorUtilization(pidA)<LinuxParser::ProcessorUtilization(pidB);
}