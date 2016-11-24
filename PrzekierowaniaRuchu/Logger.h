#pragma once

#include <string>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

using namespace logging::trivial;
using namespace std;

class Logger
{
public:
	enum logLevels {
		TRACE = 0,
		DEBUG = 1,
		INFO = 2,
		WARNING = 3,
		ERROR = 4,
		FATAL = 5
	};

	static Logger &getLogger() {
		static Logger singleton;
		return singleton;
	}

	void setLogLevel(logLevels logLvl);

	void Log(int logLvl, string message);
private:
	bool logLevelSetted = false;
	Logger();
	Logger(const Logger &);
};


