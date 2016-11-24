#include "Logger.h"

Logger::Logger()
{
	logging::add_file_log
	(
		keywords::file_name ="LOG_przekierowaniaRuchu_%N.log",  /*< file name pattern >*/
		keywords::rotation_size = 10 * 1024 * 1024,             /*< rotate files every 10 MiB... >*/
		keywords::format = "[%TimeStamp%]: %Message%"           /*< log record format >*/
	);

	logging::add_common_attributes();
}

void Logger::setLogLevel(logLevels logLvl) {
	if (!logLevelSetted) {
		logging::core::get()->set_filter
		(
			logging::trivial::severity >= logLvl
		);
		logLevelSetted = true;
		return;
	}

	getLogger().Log(ERROR, "Log level is already set");
}

void Logger::Log(int logLvl, string message) {

	if (!logLevelSetted) {
		getLogger().setLogLevel(WARNING);
	}

	src::severity_logger< severity_level > lg;

	if (logLvl < 1) {
		cout << message << "\n";
	}

	switch (logLvl) {
	case 0:
		BOOST_LOG_SEV(lg, trace) << message;
		break;
	case 1:
		BOOST_LOG_SEV(lg, debug) << message;
		break;
	case 2:
		BOOST_LOG_SEV(lg, info) << message;
		break;
	case 3:
		BOOST_LOG_SEV(lg, warning) << message;
		break;
	case 4:
		BOOST_LOG_SEV(lg, error) << message;
		break;
	case 5:
		BOOST_LOG_SEV(lg, fatal) << message;
		break;
	}
	
}
