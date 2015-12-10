#include "Process.h"

void Process::Clear() {
	m_steps.clear();
}

void Process::AddStep(const Picture& picture, const Description& description) {
	m_steps.push_back(std::make_pair(picture, description));
}

void Process::Reverse() {
	m_steps.reverse();
}

void Process::Save(const std::string& folder) {
	try{
		Steps::iterator it = m_steps.begin(), end = m_steps.end();
		int counter = 1;
		for(; it != end; it++){
			const std::string& fileName("step_" + boost::lexical_cast<std::string>(counter));
			it->first.Save(folder + fileName + ".jpg");
			it->second.Save(folder + fileName + ".txt");
			counter++;
		}
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}
