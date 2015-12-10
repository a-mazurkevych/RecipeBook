#include "Logger.h"
#include "Recipe.h"
#include "WorkSpace.hpp"
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>

#ifndef RECIPEPARSER_H
#define	RECIPEPARSER_H

class Parser : public Logger, public WorkSpace
{
public:
	Parser(const std::string& outDir);
	void Parse(const std::string& inDir);
private:
	void LoadSource(const boost::filesystem::path& path);
	void ParseSource(const std::string& source);
private:
	std::string m_dest;
	std::string m_recipeRoot;
};

#endif	/* RECIPEPARSER_H */

