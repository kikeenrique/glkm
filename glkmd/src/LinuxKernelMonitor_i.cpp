// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA

#include <iostream>
#include <sstream>
#include <string>

#include "LinuxKernelMonitor_i.hpp"

LinuxKernelMonitor_i::LinuxKernelMonitor_i()
 : m_glkmNetClient()
{
    // add extra constructor code here
    std::cout << "LinuxKernelMonitor_i::CONSTRUCTOR [BEGIN]" << std::endl;
    std::cout << "LinuxKernelMonitor_i::CONSTRUCTOR [ENG]" << std::endl;

}

LinuxKernelMonitor_i::~LinuxKernelMonitor_i()
{
    // add extra destructor code here
    std::cout << "LinuxKernelMonitor_i::DESTRUCTOR [BEGIN]" << std::endl;
    std::cout << "LinuxKernelMonitor_i::DESTRUCTOR [END]" << std::endl;
}


LinuxKernelMonitor::StringList* LinuxKernelMonitor_i::GetAllProcesses_TEST()
{
//    TEST CODE
    std::cout << "LinuxKernelMonitor_i::GetAllProcesses [BEGIN]" << std::endl;

    LinuxKernelMonitor::StringList* process_list_rt = new LinuxKernelMonitor::StringList;
    std::string test;
    for (CORBA::ULong i=0; i<10; i++)
    {
        process_list_rt->length(i+1);
        test.clear();
        test = "test_";
        std::stringstream formater;
        formater << i;
        test+=formater.str();
        (*process_list_rt)[i] = CORBA::string_dup(test.c_str());
        std::cout << "LinuxKernelMonitor_i::GetAllProcesses " << test << (*process_list_rt)[i] << std::endl;
    }

    std::cout << "LinuxKernelMonitor_i::GetAllProcesses [END]" << std::endl;
    return process_list_rt;
}


LinuxKernelMonitor::StringList* LinuxKernelMonitor_i::GetAllProcesses()
{
    std::cout << "LinuxKernelMonitor_i::GetAllProcesses [BEGIN]" << std::endl;

    LinuxKernelMonitor::StringList* process_list_rt = new LinuxKernelMonitor::StringList;
    std::vector<std::string> processes;

    m_glkmNetClient.GetAllProcesses(processes);

    std::vector<std::string>::iterator processes_it = processes.begin();
    for (CORBA::ULong i=0; processes_it < processes.end(); processes_it++,i++)
    {
        process_list_rt->length(i+1);
        (*process_list_rt)[i] = CORBA::string_dup((*processes_it).c_str());
        std::cout << "LinuxKernelMonitor_i::GetAllProcesses "  << i << " " << *processes_it << std::endl;
    }

    std::cout << "LinuxKernelMonitor_i::GetAllProcesses [END] " << std::endl;
    return process_list_rt;
}

