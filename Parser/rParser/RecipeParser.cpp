#include "RecipeParser.h"

Parser::Parser(const std::string& outDir) 
: m_dest(outDir + "\\")
{
	Create(outDir);
}

void Parser::Parse(const std::string& inDir) {
	try{
		if(!boost::filesystem::exists(inDir)){
			Write(inDir + " doesn't exists..");
			return;
		}
		boost::filesystem::directory_iterator dir(inDir), end;
		for(; dir != end; dir++){
			if(boost::filesystem::is_regular_file(dir->path()))
				LoadSource(dir->path());
		}
	}catch(const boost::filesystem::filesystem_error& e){
		Write(e.what());
	}
}

void Parser::ParseSource(const std::string& source) {
	try{
		boost::shared_ptr<Recipe> recipe = boost::make_shared<Recipe>();
		recipe->SetRoot(m_recipeRoot);
		recipe->Parse(source);
		recipe->Save(m_dest);
	}catch(const std::exception& e){
		Write(e.what());
	}
}


void Parser::LoadSource(const boost::filesystem::path& path) {
	try{
		const std::string pth(path.string());
		m_recipeRoot = std::string(pth.begin() + pth.find("-") + 1, pth.begin() + pth.find("."));
		if(!boost::filesystem::exists(path)){
			Write(pth + " doesn't exists..");
			return;
		}
		std::ifstream src(pth, std::ios::in);
		if(!src.is_open()){
			Write("I can't open " + pth + "..");
			return;
		}
		std::string source((std::istreambuf_iterator<char>(src)), std::istreambuf_iterator<char>());
		ParseSource(source);
	}catch(const std::exception& e){
		Write(e.what());
	}
}



