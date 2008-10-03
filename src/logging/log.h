#ifndef __LOG_H__
#define __LOG_H__

#include "ref/ref.h"

namespace logging
{
	enum severity
	{
		debug,
		info,
		warning,
		error
	};

	class log : public refs::referenceable<log>
	{
	public:
		virtual void message(severity svrty, const char* msg) = 0;
	};

	void message(log& lg, severity svrty, const char* fmt, ...);
}

#endif //__LOG_H__
