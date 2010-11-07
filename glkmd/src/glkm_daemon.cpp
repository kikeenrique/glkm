/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Enrique Garcia 2010 <enrgar+glkm@eldemonionegro.com>
	 * 
 * glkm-daemon is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
	 * 
 * glkm-daemon is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include "LinuxKernelMonitor_i.hpp"

static CORBA::Boolean bindObjectToName(CORBA::ORB_ptr, CORBA::Object_ptr);

int main(int argc, char** argv)
{
	try
	{
		// Initialise the ORB.
		CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

		// Obtain a reference to the root POA.
		CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
		PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

		// We allocate the objects on the heap.  Since these are reference
		// counted objects, they will be deleted by the POA when they are no
		// longer needed.
		LinuxKernelMonitor_i* myLinuxKernelMonitor_i = new LinuxKernelMonitor_i();


		// Activate the objects.  This tells the POA that the objects are
		// ready to accept requests.
		PortableServer::ObjectId_var myLinuxKernelMonitor_iid = poa->activate_object(myLinuxKernelMonitor_i);


		// Obtain a reference to each object and output the stringified
		// IOR to stdout
		// IDL interface: LinuxKernelMonitor
		CORBA::Object_var ref = myLinuxKernelMonitor_i->_this();
		CORBA::String_var sior(orb->object_to_string(ref));
		std::cout << "IDL object LinuxKernelMonitor IOR = ' " << (char*)sior << " '" << std::endl;
		
		/* 
		 The object reference is registered with the COS naming service. 
		 The client uses the naming service to locate this object.
		 */
//		if( !bindObjectToName(orb, obj) )
		if( !bindObjectToName(orb, ref) )
		{
			return 1;
		}

		// Obtain a POAManager, and tell the POA to start accepting
		// requests on its objects.
		PortableServer::POAManager_var pman = poa->the_POAManager();
		pman->activate();

		orb->run();

		//End IMPL
		if (myLinuxKernelMonitor_i)
		{
			myLinuxKernelMonitor_i->_remove_ref();
		}

		// End CORBA
		if (!CORBA::is_nil(orb))
		{
			try
			{
				orb->destroy();
				std::cout << "Ending CORBA..." << std::endl;
			} catch (const CORBA::Exception& e)
			{
				std::cout << "orb->destroy() failed:" << e._name() << std::endl;
				return 1;
			}
		}

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
	return 0;
}


static CORBA::Boolean bindObjectToName(CORBA::ORB_ptr orb,
                                       CORBA::Object_ptr objref)
{
	std::cout << "main::bindObjectToName [BEGIN]" << std::endl;
	CosNaming::NamingContext_var rootContext;

	std::cout << "main::bindObjectToName Get reference to root context" << std::endl;

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
			return 0;
		}
	}
	catch (CORBA::NO_RESOURCES&)
	{
		std::cerr << "Caught NO_RESOURCES exception. You must configure omniORB "
       		      << "with the location" << std::endl
                  << "of the naming service." << std::endl;
		return 0;
	}
	catch (CORBA::ORB::InvalidName&)
	{
		// This should not happen!
		std::cerr << "Service required is invalid [does not exist]." << std::endl;
		return 0;
	}

	try
	{
		std::cout << "main::bindObjectToName Bind Context" << std::endl;
		// Bind a context called "test" to the root context:

		CosNaming::Name contextName;
		contextName.length(1);
		contextName[0].id   = (const char*) "test";       // string copied
		contextName[0].kind = (const char*) "my_context"; // string copied
		// Note on kind: The kind field is used to indicate the type
		// of the object. This is to avoid conventions such as that used
		// by files (name.type -- e.g. test.ps = postscript etc.)

		CosNaming::NamingContext_var testContext;
		try
		{
			// Bind the context to root.
			testContext = rootContext->bind_new_context(contextName);
		}
		catch(CosNaming::NamingContext::AlreadyBound& ex)
		{
			// If the context already exists, this exception will be raised.
			// In this case, just resolve the name and assign testContext
			// to the object returned:
			CORBA::Object_var obj;
			obj = rootContext->resolve(contextName);
			testContext = CosNaming::NamingContext::_narrow(obj);
			if( CORBA::is_nil(testContext) )
			{
				std::cerr << "Failed to narrow naming context." << std::endl;
				return 0;
			}
		}

		std::cout << "main::bindObjectToName Bind objref" << std::endl;

		// Bind objref with name Echo to the testContext:
		CosNaming::Name objectName;
		objectName.length(1);
		objectName[0].id   = (const char*) "GetAllProcess";   // string copied
		objectName[0].kind = (const char*) "Object"; // string copied

		try
		{
			testContext->bind(objectName, objref);
		}
		catch(CosNaming::NamingContext::AlreadyBound& ex)
		{
			testContext->rebind(objectName, objref);
		}
		// Note: Using rebind() will overwrite any Object previously bound
		//       to /test/GetAllProcess with obj.
		//       Alternatively, bind() can be used, which will raise a
		//       CosNaming::NamingContext::AlreadyBound exception if the name
		//       supplied is already bound to an object.

		// Amendment: When using OrbixNames, it is necessary to first try bind
		// and then rebind, as rebind on it's own will throw a NotFoundexception if
		// the Name has not already been bound. [This is incorrect behaviour -
		// it should just bind].
	}
	catch(CORBA::TRANSIENT& ex)
	{
		std::cerr << "Caught system exception TRANSIENT -- unable to contact the "
                  << "naming service." << std::endl
                  << "Make sure the naming server is running and that omniORB is "
                  << "configured correctly." << std::endl;

		return 0;
	}
	catch(CORBA::SystemException& ex)
	{
		std::cerr << "Caught a CORBA::" << ex._name()
                  << " while using the naming service." << std::endl;
		return 0;
	}

	std::cout << "main::bindObjectToName [END]" << std::endl;
	return 1;
}