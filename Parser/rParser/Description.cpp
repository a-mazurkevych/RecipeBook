#include "Description.h"

Description::Description() {
}

Description::Description(const std::string& description) 
: m_desc(description)
{}

void Description::Save(const std::string& path) {
	try{
		std::ofstream desription(path, std::ios::out | std::ios::binary);
		if(!desription.is_open()){
			Logger::Write("I can't open " + path + "..");
			return;
		}
		desription << m_desc;
		desription.close();
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}
