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


static CORBA::Object_ptr getObjectReference(CORBA::ORB_ptr orb);

static void test_op_GetAllProcesses(LinuxKernelMonitor_ptr e)
{
    LinuxKernelMonitor::StringList_var dest = e->GetAllProcesses();
    for (CORBA::ULong i=0; i<dest->length(); i++)
    {
        //        (*process_list_rt)[i] = CORBA::string_dup(test.c_str()); 
        std::cout << "The object replied, [" << i << "] \"" << (char*)dest[i]
            << "\"." << std::endl;
    }

}

int main(int argc, char** argv)
{
    CORBA::ORB_var orb;
    try
    {
        orb = CORBA::ORB_init(argc, argv);
/*
         
        if( argc != 2 )
        {
            std::cerr << "usage:  eg2_clt <object reference>" << std::endl;
            return 1;
        }
        else
        {
            std::cout << "Using... " << argv[1] << std::endl;
        }

        CORBA::Object_var obj = orb->string_to_object(argv[1]);
*/
        CORBA::Object_var obj = getObjectReference(orb);

        LinuxKernelMonitor_var object_ref = LinuxKernelMonitor::_narrow(obj);
        if( CORBA::is_nil(object_ref) )
        {
            std::cerr << "Can't narrow reference to type Echo (or it was nil)." << std::endl;
            return 1;
        }
        else
        {
            std::cout << "Calling GetAllProcesses... " << std::endl;
            test_op_GetAllProcesses(object_ref);
        }
//        sleep(3);
    }
    catch(CORBA::TRANSIENT&)
    {
        std::cerr << "Caught system exception TRANSIENT -- unable to contact the "
            << "server." << std::endl;
    }
    catch(CORBA::SystemException& ex)
    {
        std::cerr << "Caught a CORBA::" << ex._name() << std::endl;
    }
    catch(CORBA::Exception& ex)
    {
        std::cerr << "Caught CORBA::Exception: " << ex._name() << std::endl;
    }
    catch(omniORB::fatalException& fe)
    {
        std::cerr << "Caught omniORB::fatalException:" << std::endl;
        std::cerr << "  file: " << fe.file() << std::endl;
        std::cerr << "  line: " << fe.line() << std::endl;
        std::cerr << "  mesg: " << fe.errmsg() << std::endl;
    }

    // End CORBA
	if (!CORBA::is_nil(orb))
    {
		try
        {
            orb->shutdown(false);
			orb->destroy();
			std::cout << "Ending CORBA..." << std::endl;
		}
        catch (const CORBA::Exception& e)
		{
			std::cout << "ORB destroy failed:" << e._name() << std::endl;
			return 1;
		}
   }

    return 0;
}


static CORBA::Object_ptr getObjectReference(CORBA::ORB_ptr orb)
{
    CosNaming::NamingContext_var rootContext;

    try
    {
        // Obtain a reference to the root context of the Name service:
        CORBA::Object_var obj;
        obj = orb->resolve_initial_references("NameService");

        // Narrow the reference returned.
        rootContext = CosNaming::NamingContext::_narrow(obj);
        if( CORBA::is_nil(rootContext) )
        {
            std::cerr << "Failed to narrow the root naming context." << std::endl;
            return CORBA::Object::_nil();
        }
    }
    catch (CORBA::NO_RESOURCES&)
    {
        std::cerr << "Caught NO_RESOURCES exception. You must configure omniORB "
            << "with the location" << std::endl
            << "of the naming service." << std::endl;
        return 0;
    }
    catch(CORBA::ORB::InvalidName& ex)
    {
        // This should not happen!
        std::cerr << "Service required is invalid [does not exist]." << std::endl;
        return CORBA::Object::_nil();
    }

    // Create a name object, containing the name test/context:
    CosNaming::Name name;
    name.length(2);

    name[0].id   = (const char*) "test";       // string copied
    name[0].kind = (const char*) "my_context"; // string copied
    name[1].id   = (const char*) "GetAllProcess";
    name[1].kind = (const char*) "Object";
    // Note on kind: The kind field is used to indicate the type
    // of the object. This is to avoid conventions such as that used
    // by files (name.type -- e.g. test.ps = postscript etc.)

    try 
    {
        // Resolve the name to an object reference.
        return rootContext->resolve(name);
    }
    catch(CosNaming::NamingContext::NotFound& ex)
    {
        // This exception is thrown if any of the components of the
        // path [contexts or the object] aren't found:
        std::cerr << "Context not found." << std::endl;
    }
    catch(CORBA::TRANSIENT& ex)
    {
        std::cerr << "Caught system exception TRANSIENT -- unable to contact the "
            << "naming service." << std::endl
            << "Make sure the naming server is running and that omniORB is "
            << "configured correctly." << std::endl;

    }
    catch(CORBA::SystemException& ex)
    {
        std::cerr << "Caught a CORBA::" << ex._name()
            << " while using the naming service." << std::endl;
        return 0;
    }

    return CORBA::Object::_nil();
}
