/* 
 * File:   Process.h
 * Author: User
 *
 * Created on October 22, 2015, 12:20 PM
 */
#include <list>
#include <utility>
#include "Description.h"
#include "Picture.h"

#ifndef PROCESS_H
#define	PROCESS_H

struct Process{
	void Clear();
	void AddStep(const Picture& picture, const Description& description);
	void Reverse();
	void Save(const std::string& folder);
private:
	typedef std::list<std::pair<Picture, Description> > Steps;
	Steps m_steps;
};

#endif	/* PROCESS_H */

