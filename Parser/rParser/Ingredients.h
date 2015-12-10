/* 
 * File:   Ingredients.h
 * Author: User
 *
 * Created on October 22, 2015, 12:06 PM
 */
#include "Utils.hpp"

#ifndef INGREDIENTS_H
#define	INGREDIENTS_H

struct TypedIngredients
{
	TypedIngredients(const std::string& source);
	void Save(std::ostream& stream);
private:
	void Parse();
	void SetType();
	void Add(const std::string& name, const std::string& count);
	typedef std::list<std::pair<std::string, std::string> > Data;
	std::string m_type;
	std::string m_source;
	Data m_data;
};

struct Ingredients
{
	void Save(const std::string& path);
	void AddIngredients(const TypedIngredients& subIngred);
	void Reverse();
	bool Empty();
	void Parse(const std::string& source);
private:
	typedef std::list<TypedIngredients> Data;
	Data m_data;
	std::string m_recipe;
};

#endif	/* INGREDIENTS_H */

