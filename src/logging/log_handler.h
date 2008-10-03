#ifndef __LOG_HANDLER_H__
#define __LOG_HANDLER_H__

#include "log.h"
#include <boost/intrusive_ptr.hpp>
#include <vector>

namespace logging
{
	class log_handler : public refs::reference_target<log_handler, log>
	{
	public:
		// log
		virtual void message(severity svrty, const char* msg);

		void add_handler(boost::intrusive_ptr<log> lg);

	private:
		std::vector<boost::intrusive_ptr<log> > handlers;
	};
}

#endif //__LOG_HANDLER_H__
