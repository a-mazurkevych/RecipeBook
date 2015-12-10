/* 
 * File:   Parser.h
 * Author: User
 *
 * Created on October 22, 2015, 2:22 PM
 */
#include "Recipe.h"
#include <boost/make_shared.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#ifndef PARSER_H
#define	PARSER_H

class Parser
{
public:
	Parser(const std::string& config);
	void Parse();
private:
	void LoadConfig(const std::string& config);
	void Load(const std::string& url);
	void ParseSource(const std::string& source);
private:
	std::string m_destination;
	std::string m_rcpFolder;
	std::string m_sourceUrls;
};

#endif	/* PARSER_H */

