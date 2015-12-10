#include "Logger.hpp"
#include <boost/filesystem.hpp>

#ifndef WORKSPACE_HPP
#define	WORKSPACE_HPP

struct WorkSpace {
public:
	static void Create(const std::string& folder) {
		try {
			if (!boost::filesystem::exists(folder) && folder.length())
				if(!boost::filesystem::create_directory(folder))
					Logger::Write("I can't create derectory " + folder + "..");
		} catch (const boost::filesystem::filesystem_error& e) {
			Logger::Write(e.what());
		}
	}

	static void Clean(const std::string& folder) {
		try {
			if (boost::filesystem::exists(folder)) {
				boost::filesystem::directory_iterator it(folder), end;
				for (; it != end; it++) {
					boost::filesystem::remove_all(it->path());
				}
			}
		} catch (const boost::filesystem::filesystem_error& e) {
			Logger::Write(e.what());
		}
	}
};

#endif	/* WORKSPACE_HPP */

