class ObjectAdaptor::Private
!!!128957.cpp!!!	unregister_function_stub(inout conn : DBusConnection, inout data : void) : void
 	//TODO: what do we have to do here ?
!!!129085.cpp!!!	message_function_stub(inout  : DBusConnection, inout dmsg : DBusMessage, inout data : void) : DBusHandlerResult
	ObjectAdaptor* o = static_cast<ObjectAdaptor*>(data);

	if( o )
	{
		Message msg(new Message::Private(dmsg));	

		debug_log("in object %s", o->path().c_str());
		debug_log(" got message #%d from %s to %s",
			msg.serial(),
			msg.sender(),
			msg.destination()
		);

		return o->handle_message(msg)
			? DBUS_HANDLER_RESULT_HANDLED
			: DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}
	else
	{
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}
