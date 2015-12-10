/* 
 * File:   Picture.h
 * Author: User
 *
 * Created on October 20, 2015, 2:26 PM
 */
#include "curl/curl.h"
#include "Logger.hpp"

#ifndef PICTURE_H
#define	PICTURE_H

struct Picture{
	Picture();
	Picture(const std::string& addr);
	void Save(const std::string& path);
private:
	std::string m_url;
};

#endif	/* PICTURE_H */

