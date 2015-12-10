#include "Parser.h"

Parser::Parser(const std::string& config) 
{
	LoadConfig(config);
}

Parser::~Parser(){
}

void Parser::LoadConfig(const std::string& config) {
	try{
		if(!boost::filesystem::exists(config)){
			Logger::Write(config + " doesn't exists..");
			return;
		}
		boost::property_tree::ptree pt;
		boost::property_tree::read_ini(config, pt);
		m_root = pt.get_child("Parser").get<std::string>("root");
		m_destination = pt.get_child("Parser").get<std::string>("destination");
		m_start = pt.get_child("Parser").get<int>("start");
		m_end = pt.get_child("Parser").get<int>("end");
	}catch(const boost::property_tree::ptree_error& e){
		Logger::Write(e.what());
	}
}


void Parser::Parse(std::string& source) {
	try {
		typedef std::string::iterator _iterator;
		_iterator it = source.begin(), end = source.end();
		typedef UrlGrammar<_iterator> grammar;
		grammar g;
		Url u;
		boost::regex recipeUrl("^(http://www.edimdoma.ru/retsepty/)\\d+-[a-z-]*$");
		while (it != end) {
			size_t pos = source.find("<a href=\"http://www.edimdoma.ru/retsepty/");
			if (pos == std::string::npos)
				break;
			source = std::string(source.begin() + pos, source.end());
			it = source.begin();
			end = source.end();
			if (boost::spirit::qi::phrase_parse(it, end, g, boost::spirit::qi::ascii::space, u)) {
				if (boost::regex_match(u.url, recipeUrl))
					m_urls.insert(u.url);
				u.Clear();
				source = std::string(it, end);
			}
		}
		
	} catch (const std::exception& e) {
		Logger::Write(e.what());
	}
}

void Parser::Add() {
	try {
		std::ofstream file(m_destination, std::ios::out | std::ios::app);
		if (!file.is_open()) {
			Logger::Write("I can't open " + m_destination + "..");
			return;
		}
		auto it = m_urls.begin(), end = m_urls.end();
		for(; it != end; it++)
			file << *it << std::endl;
		file.close();
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}


void Parser::Load(const std::string& url) {
	try{
	CURL* curl = curl_easy_init();
	if(!curl){
		Logger::Write("I can't init curl");
		return;
	}
	CURLcode res;
	std::string data;
	auto done = [](CURLcode& res){ return res == CURLE_OK; };
	res = curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	if(!done) Logger::Write("I can't set url: " + url + "..");
	res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
	if(!done) Logger::Write("I can't set write function..");
	res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
	if(!done) Logger::Write("I can't set write data..");
	Logger::Write("Loading page...\t" + url);
	res = curl_easy_perform(curl);	
	if(!done) Logger::Write("I can't perform curl..");
	curl_easy_cleanup(curl);
	Parse(data);
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}

void Parser::Parse() {
	try{
		if(0 > m_start > m_end){
			Logger::Write("Interval isn't valid..");
			return;
		}
		m_urls.clear();
		for(int i = m_start; i <= m_end; i++)
			Load(m_root + boost::lexical_cast<std::string>(i));
		Add();
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}
