#include "Ingredients.h"

TypedIngredients::TypedIngredients(const std::string& source)
: m_source(source) {
	Parse();
}

void TypedIngredients::Parse() {
	try {
		SetType();
		std::string src(m_source);
		bool found(true);
		do {
			std::size_t pos = src.rfind("<tr class=\"hs_recipe_ingridient clearfix utk-sku");
			if (pos != std::string::npos) {
				const std::string ingreds(src.begin() + pos, src.end());
				const std::string & name(GetData("data-utk-sku-text=\"", "\"", ingreds));
				const std::string & count(GetData("data-utk-sku-count=\"", "\"", ingreds) + " " + GetData("data-utk-sku-unit=\"", "\"", ingreds));
				Add(name, count);
				src = std::string(src.begin(), src.begin() + pos);
			} else
				found = false;
		} while (found);
		m_data.reverse();
	} catch (const std::exception& e) {
		Logger::Write(e.what());
	}
}

void TypedIngredients::SetType() {
	std::string src(m_source);
	m_type = GetData("rec-ing-subtitle\">", "</div>", src);
}

void TypedIngredients::Add(const std::string& name, const std::string& count) {
	m_data.push_back(std::make_pair(name, count));
}

void TypedIngredients::Save(std::ostream& stream) {
	try {
		stream << m_type << std::endl;
		Data::iterator it = m_data.begin(), end = m_data.end();

		for (; it != end; it++) {
			stream << it->first << "\t\t\t" << it->second << std::endl;
		}
		stream << "\n";
	} catch (const std::exception& e) {
		Logger::Write(e.what());
	}
}

void Ingredients::AddIngredients(const TypedIngredients& subIngred) {
	m_data.push_back(subIngred);
}

void Ingredients::Reverse() {
	m_data.reverse();
}

bool Ingredients::Empty() {
	return !(bool)m_data.size();
}

void Ingredients::Parse(const std::string& source) {
	try {
		std::string src(source.begin() + source.find("Ингредиенты"), source.end());
		m_recipe = GetData("b-page_block__outside\"><p>", "</p>", src);
		Filter(m_recipe);
	} catch (const std::exception& e) {
		Logger::Write(e.what());
	}
}

void Ingredients::Save(const std::string& path) {
	try {
		std::ofstream ingredients(path, std::ios::out | std::ios::binary);
		if (!ingredients.is_open()) {
			Logger::Write("I can't open " + path + "..");
			return;
		}
		if (!Empty()) {
			Data::iterator it = m_data.begin(), end = m_data.end();
			for (; it != end; it++)
				it->Save(ingredients);
		} else
			ingredients << m_recipe;
		ingredients.close();
	} catch (const std::exception& e) {
		Logger::Write(e.what());
	}
}
