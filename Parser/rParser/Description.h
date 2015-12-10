/* 
 * File:   Description.h
 * Author: User
 *
 * Created on October 20, 2015, 2:34 PM
 */
#include "Logger.hpp"

#ifndef DESCRIPTION_H
#define	DESCRIPTION_H

struct Description{
	Description();
	Description(const std::string& description);
	void Save(const std::string& path);
private:
	std::string m_desc;
};

#endif	/* DESCRIPTION_H */

