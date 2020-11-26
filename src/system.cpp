#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
	this->processes_.clear();

	vector<int> ProcsId = LinuxParser::Pids();

	for (int pid : ProcsId){
		this->processes_.push_back(Process(pid));
	}

	std::sort(this->processes_.begin(), this->processes_.end(),
            [](Process a, Process b) {
              return a.CpuUtilization() > b.CpuUtilization();
            });




	return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
	return LinuxParser::MemoryUtilization();
	//return 0.0; 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }  // DONE

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }		// DONE

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }		 // DONE

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }