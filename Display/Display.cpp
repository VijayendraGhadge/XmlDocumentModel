/////////////////////////////////////////////////////////////////////////////
// Display.cpp - Provide Fuctions to Display on Console					   //
// ver 1.0                                                                 //
// Language:    Visual C++, Visual Studio 2013                             //
// Platform:    Dell XPS L520, Core i7, Windows 7 SP3                      //
// Application: CSE 687 Project 2                                          //
// Author:      Vijayendra Ghadge, Syracuse University	                   //
//              (315) 728 8953, vvgahdge@syr.edu	                       //
/////////////////////////////////////////////////////////////////////////////
#include "Display.h"
#include <iostream>

//using namespace::std;
using namespace XmlProcessing;
using sPtr = std::shared_ptr <AbstractXmlElement>;

//----< display tree elements >----------------------------------------
void Display::disp(sPtr ptr)
{
	std::cout << "................................................................................";
	std::cout<<ptr->toString();
	std::cout << "\n................................................................................\n";
}

//----< display requirements >----------------------------------------
void Display::dispReq(int n)
{
	std::cout << "\n********************* Demostarting Requirement # "<< n<<" ****************************\n";	
}
//----< display passed string >----------------------------------------
void Display::dispstring(std::string s)
{
	std::cout << "\n...........................Imput XML Strings...................................\n";
	std::cout << "\n" << s << "\n";
}
//----< display string >----------------------------------------
void Display::dispfromstr()
{
	std::cout << "\n...........................Read XML Strings.....................................\n";
}
//----< display passed string >----------------------------------------
void Display::dispstr(std::string s)
{
	std::cout << "\n................................................................................\n";
	std::cout << "\n" << s << "\n";

}
//----< display string >----------------------------------------
void Display::dispfromfile()
{
	std::cout << "\n.............................Read XML Files..................................... \n";
}
//----< write xml tree to file >----------------------------------------
void Display::writeToFile()
{
	std::cout << "\n\n.............................Write XML Files....................................\n";
	std::cout << "\n...............................Check out.xml....................................\n";
	std::cout << "\n\n*******************************************************************************\n";
}
//----< write xml to string and display string >----------------------------------------
void Display::writeToString(std::string s)
{
	std::cout << "\n...........................Write XML Strings...................................\n";
	std::cout << "\n" << s << "\n";
	std::cout << "\n*******************************************************************************\n";
}
//----< display passed vector >----------------------------------------
void Display::dispfindelembyid(std::vector<sPtr> vec)
{
	std::cout << "\n......................Find Element By Attribute ID..............................\n";
	
	for (std::vector<sPtr>::iterator i = vec.begin(); i != vec.end(); ++i)
	{
		disp(*i);
	}
}
//----< display passed vector >----------------------------------------
void Display::dispfindelembyval(std::vector<sPtr> vec)
{
	std::cout << "\n.....................Find Element By Attribute Value...........................\n";
	for (std::vector<sPtr>::iterator i = vec.begin(); i != vec.end(); ++i)
	{
		disp(*i);
	}
}
//----< display passed vector >----------------------------------------
void Display::dispfindelembytag(std::vector<sPtr> vec)
{
	std::cout << "\n..........................Find Element By Tag...................................\n";
	for (std::vector<sPtr>::iterator i = vec.begin(); i != vec.end(); ++i)
	{
		disp(*i);
	}
}
//----< display passed vector >----------------------------------------
void Display::dispattrib(std::vector<std::pair<std::string, std::string>> att)
{
	for (auto a : att)
	{
		std::cout <<"\n\t Attribute Name="<<a.first<<"\t";
		std::cout << "Attribute Value=" << a.second << "\n";
	}
		
}
//----< display passed vector >----------------------------------------
void Display::dispchildren(std::vector<sPtr> vec)
{
	std::cout << "\n..........................Diplaying Children...................................\n";
	for (std::vector<sPtr>::iterator i = vec.begin(); i != vec.end(); ++i)
	{
		disp(*i);
	}
}

#ifdef TEST_DISPLAY
int main()
{
	std::cout << "\nTesting Display";
	Display d;
	d.dispstring("hey");
	d.dispReq(100);
	d.dispfromstr();
	d.dispfromfile();
	return 0;
}
#endif