#include "Recipe.h"
#include "WorkSpace.hpp"

RecipeWorkspace::RecipeWorkspace()
{}

void RecipeWorkspace::Init(){
	try{
		rcpName =  root + "name.txt";
		rcpPic = root + "picture.jpg";
		rcpDescrip = root + "description.txt";
		rcpIngredients = root + "ingredients.txt";
		rcpSteps = root + "Steps\\";
	}catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}
}

void RecipeWorkspace::SetRoot(const std::string& folder){
	root = folder + "\\";
	Init();
}

Recipe::Recipe() {
}

void Recipe::Parse(const std::string& sourse) {
	ParseName(sourse);
	ParsePicture(sourse);
	ParseDescription(sourse);
	ParseIngredients(sourse);
	ParseProcess(sourse);
}

void Recipe::Save(const std::string& folder) {
	WorkSpace::Create(folder + root);
	WorkSpace::Create(folder + rcpSteps);
	SaveName(folder + rcpName);
	m_picture.Save(folder + rcpPic);
	m_description.Save(folder + rcpDescrip);
	m_ingredients.Save(folder + rcpIngredients);
	m_process.Save(folder + rcpSteps);
}

void Recipe::SaveName(const std::string& path) {
	try{
		std::ofstream name(path, std::ios::out | std::ios::binary);
		if(!name.is_open()){
			Logger::Write("I can't open " + path + "..");
			return;
		}
		Filter(m_name);
		name << m_name;
		name.close();
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}

void Recipe::ParseName(const std::string& sourse) {
	try{
		std::string src(sourse);
		m_name.assign(GetData("data-utk-recipe-name=\"", "\"", src));
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}

void Recipe::ParsePicture(const std::string& sourse) {
	try{
		std::string src(sourse.begin() + sourse.find("<a href=\"/photos/recipes/"), sourse.end());
		m_picture = Picture(GetData("src=\"", "\"", src));
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}


void Recipe::ParseDescription(const std::string& sourse) {
	try{
		std::string src(sourse.begin() + sourse.find("Описание"), sourse.end());
		std::string res(GetData("description\">", "</div>", src));
		Filter(res);
		m_description = Description(res);
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}

void Recipe::ParseIngredients(const std::string& sourse) {
	try{
		std::string src(sourse.begin() + sourse.find("Ингредиенты"), sourse.begin() + sourse.find("Способ приготовления"));
		bool found(true);
		const std::string& subIng("b-page_block__title rec-ing-subtitle");
		do{
			std::size_t pos = src.rfind(subIng);
			if(pos != std::string::npos){
				m_ingredients.AddIngredients(TypedIngredients(std::string(src.begin() + pos, src.end())));
				src = std::string(src.begin(), src.begin() + pos);
			}else
				found = false;
		}while(found);
		if(m_ingredients.Empty())
			m_ingredients.Parse(sourse);
		else
			m_ingredients.Reverse();
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}

void Recipe::ParseProcess(const std::string& sourse) {
	try{
		std::string src(sourse.begin() + sourse.find("Способ приготовления"), sourse.end());
		bool found(true);
		do{
			std::size_t pos = src.rfind("rec-sposob-inst__with_image");
			if(pos != std::string::npos){
				const std::string step(src.begin() + pos, src.end());
				const std::string& pic(GetData("src=\"", "\"", step));
				const std::string& desc(GetData("b-list__clause__text\"><p>", "</p>", step));
				m_process.AddStep(Picture(pic), Description(desc));
				src = std::string(src.begin(), src.begin() + pos);
			}else
				found = false;
		}while(found);
		m_process.Reverse();
	}catch(const std::exception& e){
		Logger::Write(e.what());
	}
}