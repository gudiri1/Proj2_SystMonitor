#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include <curses.h>

#include "process.h"
#include "system.h"


namespace NCursesDisplay {
void Display(System& system, int n = 30);
void DisplaySystem(System& system, WINDOW* window);
void DisplayProcesses(std::vector<Process>& processes, WINDOW* window, int n);
std::string ProgressBar(float percent);

const std::string filterProcesses("processes");
const std::string filterRunningProcesses("procs_running");
const std::string filterMemTotalString("MemTotal:");
const std::string filterMemFreeString("MemFree:");
const std::string filterCpu("cpu");
const std::string filterUID("Uid:");
const std::string filterProcMem("VmData:"); // Instead of VmSize
const std::string filterUName("/etc/passwd");

};  // namespace NCursesDisplay

#endif