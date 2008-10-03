#ifndef __LOG_FILE_HANDER_H__
#define __LOG_FILE_HANDER_H__

#include "log.h"
#include "log_handler.h"
#include <string>
#include <fstream>

namespace logging
{
	class log_file_handler : public refs::reference_target<log_file_handler, log>
	{
	public:
		log_file_handler(const std::string& path);

		// log
		virtual void message(severity svrty, const char* msg);

	private:
		std::ofstream out;
	};

	void add_log_file_handler(log_handler& handler, const std::string& file_path);
}

#endif //__LOG_FILE_HANDER_H__
