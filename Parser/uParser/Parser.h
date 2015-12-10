#include "Utils.hpp"
#include "WorkSpace.hpp"
#include <utility>
#include <set>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "curl/curl.h"

#ifndef PARSER_H
#define	PARSER_H

class Parser{
public:
	Parser(const std::string& config);
	~Parser();
	void Parse();
private:
	void LoadConfig(const std::string& config);
	void Parse(std::string& source);
	void Load(const std::string& url);
	void Add();
private:
	std::string m_root;
	std::string m_destination;
	int m_start;
	int m_end;
	std::set<std::string> m_urls;
};

#endif	/* PARSER_H */

