#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

//bool myfunction (Process p1, Process p2) { return (p1<p2); }

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  //processes_.clear(); 
  vector<int> values = LinuxParser::Pids();
  for (const int  value: values){
    processes_.emplace_back(value);
  }
  std::sort (processes_.begin(), processes_.end(), [] (Process& a, Process& b) {return a<b;});
  return processes_; 


}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }  // PassThrough

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
  total_processes_ = LinuxParser::TotalProcesses();
  return total_processes_; 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
  uptime_ = LinuxParser::UpTime(); 
  return  uptime_; }