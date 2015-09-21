#ifndef DISPLAY_H
#define DISPLAY_H
/////////////////////////////////////////////////////////////////////////////
// Display.h - Provide Fuctions to Display to Console					   //
// ver 1.0                                                                 //
// Language:    Visual C++, Visual Studio 2013                             //
// Platform:    Dell XPS L520, Core i7, Windows 7 SP3                      //
// Application: CSE 687 Project 2                                          //
// Author:      Vijayendra Ghadge, Syracuse University	                   //
//              (315) 728 8953, vvgahdge@syr.edu	                       //
/////////////////////////////////////////////////////////////////////////////

/*

Module Purpose:
===============
This module is responsible for displaying query outputs ,write output to file or string,display strings and messages to console.

Public Interface:
=================
Display d;
sPtr root;
d.dispReq(3); //display requirement number string
std::string str = "<meter>Hello Vijayendra Ghadge!</meter>";
d.dispstr(str); //display string
d.dispstring(str); //display string
d.dispstring("Search ID ="); //display string
XmlDocument docum(str, XmlDocument::string);
root = docum.constructtree(str, false);
d.disp(root);  //display sPtr contents 
d.writeToString(root); //write elements pointed by sPtr to String
d.writeToFile(root); //write elements pointed by sPtr to File 

std::vector<sPtr> temp;
std::string temp_str = "Company";
temp = doc.findElembyId(root, temp_str);	//get vector of sPtr 
d.dispfindelembyid(temp);		//Display vector of Smart pointers with child
d.dispfindelembyval(temp);		//Display vector of Smart pointers with child
d.dispfindelembytag(temp);		//Display vector of Smart pointers with child


std::vector<std::pair<std::string, std::string>> att;
temp = doc.findElembyId(root, temp_str);
for (std::vector<sPtr>::iterator i = temp.begin(); i != temp.end(); ++i)
{
att = (*i)->getattrib(); //get attributes from pointed smart pointer 
d.dispattrib(att);  //display vector of attibute pairs 
}

Build Process:
==============
Required files
- XmlDocument.h, Display.h, Display.cpp;

Build commands:
==============
- devenv XmlDocument.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 3/24/2015

*/
#include "../XmlDocument/XmlDocument.h"
using namespace XmlProcessing;
class Display
{
	
	using sPtr = std::shared_ptr < AbstractXmlElement >;
public:
	void disp(sPtr);
	void dispstring(std::string);
	void dispReq(int n);
	void dispfromstr();
	void dispstr(std::string);
	void dispfromfile();
	void writeToFile();
	void writeToString(std::string);
	void dispfindelembyid(std::vector<sPtr> temp);
	void dispfindelembyval(std::vector<sPtr> temp);
	void dispfindelembytag(std::vector<sPtr> temp);
	void dispattrib(std::vector<std::pair<std::string, std::string>> att);
	void dispchildren(std::vector<sPtr> temp);
private:
};

#endif