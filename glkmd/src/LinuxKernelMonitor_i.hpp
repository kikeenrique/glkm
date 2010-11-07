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
#include "LinuxKernelMonitor.hpp"
#include "GlkmNetlinkClient.hpp"

//
// Example class implementing IDL interface LinuxKernelMonitor
//
class LinuxKernelMonitor_i:
  public POA_LinuxKernelMonitor
{
    private:
        // Make sure all instances are built on the heap by making the
        // destructor non-public
        virtual ~LinuxKernelMonitor_i();
        GlkmNetlinkClient m_glkmNetClient;

    public:
        // standard constructor
        LinuxKernelMonitor_i();
        //virtual ~LinuxKernelMonitor_i();

        // methods corresponding to defined IDL attributes and operations
        LinuxKernelMonitor::StringList* GetAllProcesses();

};
