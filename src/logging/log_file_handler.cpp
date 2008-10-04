#include "log_file_handler.h"

logging::log_file_handler::log_file_handler(const std::string& path)
:	out(path.c_str())
{
}

void logging::log_file_handler::message(severity svrty, const char* msg)
{
	const char* prefix;
	switch (svrty)
	{
	case debug:   prefix = "D:"; break;
	case info:    prefix = "  "; break;
	case warning: prefix = "W:"; break;
	case error:   prefix = "E:"; break;
	default:      prefix = "**"; break;
	}

	this->out << prefix << " " << msg;
	this->out.flush();
}

void logging::add_log_file_handler(log_handler& handler, const std::string& file_path)
{
	boost::intrusive_ptr<log_file_handler> file_hndlr(new log_file_handler(file_path));
	handler.add_handler(file_hndlr);
}
