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

#include "LinuxKernelMonitor_i.hpp"

LinuxKernelMonitor_i::LinuxKernelMonitor_i()
 : m_glkmNetClient()
{
    // add extra constructor code here
    std::cout << "LinuxKernelMonitor_i::CONSTRUCTOR [BEGIN]" << std::endl;
}

LinuxKernelMonitor_i::~LinuxKernelMonitor_i()
{
    // add extra destructor code here
        std::cout << "LinuxKernelMonitor_i::DESTRUCTOR [BEGIN]" << std::endl;
}


LinuxKernelMonitor::StringList* LinuxKernelMonitor_i::GetAllProcesses()
{
    std::cout << "LinuxKernelMonitor_i::GetAllProcesses [BEGIN]" << std::endl;

    LinuxKernelMonitor::StringList* process_list_rt = new LinuxKernelMonitor::StringList;
    std::vector<std::string> processes = m_glkmNetClient.GetAllProcesses();
    std::vector<std::string>::iterator &processes_it = processes.begin();
    
    for (CORBA::ULong i=0,
         processes_it=processes.begin(); processes_it; processes_it++)
    {
        process_list_rt->length(i+1);
        (*process_list_rt)[i] = CORBA::string_dup(*processes_it.c_str()); 
    }
//    process_list_rt->length(i);
    std::cout << "LinuxKernelMonitor_i::GetAllProcesses [END]" << std::endl;

    return process_list_rt;

/*
    std::cout << "LinuxKernelMonitor_i::GetAllProcesses [BEGIN]" << std::endl;
    TEST CODE
    LinuxKernelMonitor::StringList* process_list_rt = new LinuxKernelMonitor::StringList;
    std::string test;

    for (CORBA::ULong i=0; i<10; i++)
    {
        process_list_rt->length(i+1);
        test.clear();
        test = "test_" + i;
        (*process_list_rt)[i] = CORBA::string_dup(test.c_str()); 
    }
//    process_list_rt->length(i);
    std::cout << "LinuxKernelMonitor_i::GetAllProcesses [END]" << std::endl;

    return process_list_rt;
*/
}

