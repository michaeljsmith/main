#include "log_handler.h"
#include <boost/foreach.hpp>

void logging::log_handler::message(severity svrty, const char* msg)
{
	BOOST_FOREACH(boost::intrusive_ptr<log> log, this->handlers)
	{
		log->message(svrty, msg);
	}
}

void logging::log_handler::add_handler(boost::intrusive_ptr<log> lg)
{
	this->handlers.push_back(lg);
}
