#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

#include "process.h"
#include "linux_parser.h"
#include "system.h"
#include "ncurses_display.h"

using std::string;
using std::to_string;
using std::vector;
using std::stoi;

// TODO: Return this process's ID
int Process::Pid() { 
    
    return pid_; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
  string line, token;
  long ut, st, cut, cst, startt, total; // utime stime cutime cstime starttime
  long seconds; // process uptime

  float usage;
  std::stringstream ss;
  ss << LinuxParser::kProcDirectory << pid_ << LinuxParser::kStatFilename;
  string locat = ss.str();
  std::ifstream stream(locat);
  if (stream.is_open()) {
    std::getline(stream, line); 
    std::istringstream lstream(line);
    string token;
    for (int i=0; i<14; i++){ lstream >> token; }
    ut = stol(token);
    lstream >> token; st = stol(token);
    lstream >> token; cut = stol(token);
    lstream >> token; cst = stol(token);
    lstream >> token; lstream >> token; lstream >> token; lstream >> token;
    lstream >> token; startt = stol(token);
    
    total = ut + st + cut + cst;
    seconds = LinuxParser::UpTime() - (startt/sysconf(_SC_CLK_TCK));

    usage =  ( (float)total/(float)sysconf(_SC_CLK_TCK) ) / (float)seconds ;
    //100 * ((total/sysconf(_SC_CLK_TCK))/seconds);
    return usage; //usage;  
  }
  return 0;
}

// TODO: Return the command that generated this process  /proc/[pid]/cmdline
string Process::Command() { 
  string pcommand = LinuxParser::Command(this->pid_);

  if (pcommand.size() > 40){
    return pcommand.substr(0, 40) + "...";
  }

  return pcommand;
}


// TODO: Return this process's memory utilization
string Process::Ram() { 
  float size;
  string vmsize = LinuxParser::Ram(this->pid_);
  if (vmsize != ""){
  size = std::stof(vmsize);
        std::ostringstream ss;
        ss << size/1000.0;
        return ss.str();
  }
  return string();
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
  string line, desc, uid;
  std::stringstream ss;
  ss << LinuxParser::kProcDirectory << pid_ << LinuxParser::kStatusFilename;
  string locat = ss.str();
  std::ifstream stream(locat);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
      std::istringstream linestream(line);
      linestream >> desc >> uid;
      if (desc == NCursesDisplay::filterUID) {
        std::ifstream stream(NCursesDisplay::filterUName);
        if (stream.is_open()) {
          while(std::getline(stream, line)){
            std::istringstream lstream(line);
            string user;
            string token;
            for (int i=0; i<3; i++){
              std::getline(lstream, token, ':');
              if (i==0) user = token;
            }
            if (token == uid) return user;
          }
        }
      }  
    }
  }
  return string(); 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  string line, token;
  std::stringstream ss;
  long startt;
  ss << LinuxParser::kProcDirectory << pid_ << LinuxParser::kStatFilename;
  string locat = ss.str();
  std::ifstream stream(locat);
  if (stream.is_open()) {
    std::getline(stream, line); 
    std::istringstream lstream(line);
    string token;
    for (int i=0; i<22; i++){
      lstream >> token;
    }
    startt = std::stol(token); 
    return LinuxParser::UpTime() - (startt/sysconf(_SC_CLK_TCK));
  }
  return 0;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return this->CpuUtilization() > a.CpuUtilization();
}