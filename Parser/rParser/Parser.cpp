#include "Parser.h"
#include "WorkSpace.hpp"

Parser::Parser(const std::string& config) 
{
	LoadConfig(config);
}

void Parser::LoadConfig(const std::string& config) {
	try{
		if(!boost::filesystem::exists(config)){
			Logger::Write(config + " doesn't exists..");
			return;
		}
		boost::property_tree::ptree pt;
		boost::property_tree::read_ini(config, pt);
		m_destination = pt.get_child("Parser").get<std::string>("destination") + "\\";
		WorkSpace::Create(m_destination);
		m_sourceUrls = pt.get_child("Parser").get<std::string>("source");
	}catch(const boost::property_tree::ptree_error& e){
		Logger::Write(e.what());
	}
}


void Parser::Parse() {
	try{
		if(!boost::filesystem::exists(m_sourceUrls)){
			Logger::Write(m_sourceUrls + " doesn't exists..");
			return;
		}
		std::ifstream data(m_sourceUrls, std::ios::in);
		if(!data.is_open()){
			Logger::Write("I can't open " + m_sourceUrls + "..");
			return;
		}
		while (!data.eof()) {
			std::string rcpUrl;
			data >> rcpUrl;
			Load(rcpUrl);
		}
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
	m_rcpFolder = std::string(url.begin() + url.find("-") + 1, url.end());
	ParseSource(data);
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}

void Parser::ParseSource(const std::string& source) {
	try{
		boost::shared_ptr<Recipe> recipe = boost::make_shared<Recipe>();
		recipe->SetRoot(m_rcpFolder);
		recipe->Parse(source);
		recipe->Save(m_destination);
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}

