#include <iostream>
#include <fstream>
#include <string>

#include <boost/date_time.hpp>

#ifndef LOGGER_HPP
#define	LOGGER_HPP

struct Logger {
private:
	static void LogToStream(std::ostream& os, const char* message) {
		try {
			os << boost::posix_time::to_iso_extended_string(boost::posix_time::microsec_clock::local_time()) << "\t" << message << std::endl;
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	static void LogToFile(const char* message) {
		try {
			std::ofstream log("general.log", std::ios::app | std::ios::out);
			if (!log.is_open()) {
				LogToStream(std::cout, "I can't open general.log...");
				return;
			}
			LogToStream(log, message);
			log.close();
		} catch (const std::exception& e) {
			LogToStream(std::cout, e.what());
		}
	}

	static void Log(const char* message) {
		LogToStream(std::cout, message);
		LogToFile(message);
	}
public:
	static void Write(const char* message) {
		Log(message);
	}

	static void Write(const std::string& message) {
		Log(message.c_str());
	}
};

#endif	/* LOGGER_HPP */

