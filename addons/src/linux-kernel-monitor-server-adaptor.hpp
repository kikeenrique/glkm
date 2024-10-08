
/*
 *	This file was automatically generated by dbusmm-xml2cpp; DO NOT EDIT!
 */

#ifndef __dbusmm__linux_kernel_monitor_server_adaptor_hpp__ADAPTOR_MARSHAL_H
#define __dbusmm__linux_kernel_monitor_server_adaptor_hpp__ADAPTOR_MARSHAL_H

#include <dbusmm/dbus.h>

namespace org {
namespace freedesktop {
namespace Hal {
namespace Device {

class LinuxKernelMonitor
: public ::DBus::InterfaceAdaptor
{
public:

    LinuxKernelMonitor()
    : ::DBus::InterfaceAdaptor("org.freedesktop.Hal.Device.LinuxKernelMonitor")
    {
        register_method(LinuxKernelMonitor, GetAllProcesses, _GetAllProcesses_stub);
        register_method(LinuxKernelMonitor, Hello, _Hello_stub);
    }

    ::DBus::IntrospectedInterface* const introspect() const 
    {
        static ::DBus::IntrospectedArgument GetAllProcesses_args[] = 
        {
            { "return_code", "as", false },
            { 0, 0, 0 }
        };
        static ::DBus::IntrospectedArgument Hello_args[] = 
        {
            { "name", "s", true },
            { "greeting", "s", false },
            { 0, 0, 0 }
        };
        static ::DBus::IntrospectedMethod LinuxKernelMonitor_methods[] = 
        {
            { "GetAllProcesses", GetAllProcesses_args },
            { "Hello", Hello_args },
            { 0, 0 }
        };
        static ::DBus::IntrospectedMethod LinuxKernelMonitor_signals[] = 
        {
            { 0, 0 }
        };
        static ::DBus::IntrospectedProperty LinuxKernelMonitor_properties[] = 
        {
            { 0, 0, 0, 0 }
        };
        static ::DBus::IntrospectedInterface LinuxKernelMonitor_interface = 
        {
            "org.freedesktop.Hal.Device.LinuxKernelMonitor",
            LinuxKernelMonitor_methods,
            LinuxKernelMonitor_signals,
            LinuxKernelMonitor_properties
        };
        return &LinuxKernelMonitor_interface;
    }

public:

    /* properties exposed by this interface, use
     * property() and property(value) to get and set a particular property
     */

public:

    /* methods exported by this interface,
     * you will have to implement them in your ObjectAdaptor
     */
    virtual std::vector< ::DBus::String > GetAllProcesses(  ) = 0;
    virtual ::DBus::String Hello( const ::DBus::String& name ) = 0;

public:

    /* signal emitters for this interface
     */

private:

    /* unmarshalers (to unpack the DBus message before calling the actual interface method)
     */
    ::DBus::Message _GetAllProcesses_stub( const ::DBus::CallMessage& call )
    {
        ::DBus::MessageIter ri = call.reader();

        std::vector< ::DBus::String > argout1 = GetAllProcesses();
        ::DBus::ReturnMessage reply(call);
        ::DBus::MessageIter wi = reply.writer();
        wi << argout1;
        return reply;
    }
    ::DBus::Message _Hello_stub( const ::DBus::CallMessage& call )
    {
        ::DBus::MessageIter ri = call.reader();

        ::DBus::String argin1; ri >> argin1;
        ::DBus::String argout1 = Hello(argin1);
        ::DBus::ReturnMessage reply(call);
        ::DBus::MessageIter wi = reply.writer();
        wi << argout1;
        return reply;
    }
};

} } } } 
#endif//__dbusmm__linux_kernel_monitor_server_adaptor_hpp__ADAPTOR_MARSHAL_H
