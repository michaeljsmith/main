#include "log.h"
#include <cstdarg>
#include <cstdio>

void logging::message(log& lg, severity svrty, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char buf[1024];
	vsprintf_s(buf, fmt, args);
	lg.message(svrty, buf);
	va_end(args);
}
