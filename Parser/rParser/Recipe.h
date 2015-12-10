#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include "Ingredients.h"
#include "Process.h"

#ifndef RECIPE_H
#define	RECIPE_H

struct RecipeWorkspace {
public:
	RecipeWorkspace();
	void SetRoot(const std::string & folder);
	void Init();
public:
	std::string root;
	std::string rcpSteps;
	std::string rcpName;
	std::string rcpPic;
	std::string rcpDescrip;
	std::string rcpIngredients;
};

class Recipe : public RecipeWorkspace
{
public:
	Recipe();
	void Parse(const std::string& sourse);
	void Save(const std::string& folder);
private:
	void ParseName(const std::string& sourse);
	void SaveName(const std::string& path);
	void ParsePicture(const std::string& sourse);
	void ParseDescription(const std::string& sourse);
	void ParseIngredients(const std::string& sourse);
	void ParseProcess(const std::string& sourse);
//	void Filter(std::string& result);
//	void SkipSmile(std::string& result);
private:
	std::string m_name;
	Picture m_picture;
	Description m_description;
	Ingredients m_ingredients;
	Process m_process;
};

#endif	/* RECIPE_H */

