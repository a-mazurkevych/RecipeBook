#include "Logger.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/regex.hpp>

#ifndef UTILS_HPP
#define	UTILS_HPP

using namespace boost::spirit;

struct Url {
	std::string url;
	void Clear(){
		url.clear();
	}
};

BOOST_FUSION_ADAPT_STRUCT(
	Url,
	(std::string, url)
	)

template <typename Iterator>
struct UrlGrammar : qi::grammar<Iterator, Url(), qi::ascii::space_type> {

	UrlGrammar() : UrlGrammar::base_type {
		value
	}
	{
		value %= lit("<a href=") >> '\"' >> +(qi::char_ - '\"') >> '\"';
	}

	qi::rule<Iterator, Url(), qi::ascii::space_type> value;
};

static std::size_t WriteData(void *ptr, size_t size, size_t nmemb, void *data) {
	((std::string*)data)->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

static std::string GetData(const std::string& first, const std::string& second, const std::string& source){
	try{
		std::string data, src(source);
		std::size_t pos = src.find(first);
		if(pos != std::string::npos){
			pos += first.length();
			src = std::string(src.begin() + pos, src.end());
			data = std::string(src.begin(), src.begin() + src.find(second));
		}
		return data;
	}catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}
}

static void SkipSmile(std::string& result) {
	try{
		const std::string& start("<img alt="), end("/>");
		bool found = true;
		while(found){
			std::size_t pos = result.find(start);
			if(pos != std::string::npos){
				result = std::string(result.begin(), result.begin() + pos) + " " + std::string(result.begin() + result.find(end) + end.length(), result.end());
			}else
				found = false;
		}
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}

static void Filter(std::string& result) {
	boost::replace_all(result, "<br />", "\n");
	boost::replace_all(result, "&nbsp;", " ");
	boost::replace_all(result, "&quot;", "\"");
	boost::replace_all(result, "<p>", "");
	boost::replace_all(result, "</p>", "");
	SkipSmile(result);
}

#endif	/* UTILS_HPP */

