/////////////////////////////////////////////////////////////////////////////
// Executive.cpp -Handle command line arguments,						   //
//				  control all commanding operations of all packages.	   //
// ver 1.0                                                                 //
// Language:    Visual C++, Visual Studio 2013                             //
// Platform:    Dell XPS L520, Core i7, Windows 7 SP3                      //
// Application: CSE 687 Project 2                                          //
// Author:      Vijayendra Ghadge, Syracuse University	                   //
//              (315) 728 8953, vvgahdge@syr.edu	                       //
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include<stdlib.h>
#include "../XmlDocument/XmlDocument.h"
#include "../XmlElement/XmlElement.h"
#include "../Display/Display.h"
#include <vector>
using namespace::std;
using namespace XmlProcessing;
using sPtr = std::shared_ptr <AbstractXmlElement>;

XmlDocument testFunction()
{
	XmlDocument s("<author>Jeff Prosise <hello> <men>Men will be men!</men> </hello><note Company = 'Wintellect'>< / note>< / author>", XmlDocument::string);
	return s;
}

//----< display requirement >----------------------------------------
void req51(Display d, XmlDocument &doc)
{
	d.dispReq(5);
	std::vector<sPtr> temp;
	std::string str;
	std::string temp_str = "Company";					//ID string  " Change this to try different query"
	str=doc.documentToString();
	d.dispstr(str);
	d.dispstr("Search ID =");
	d.dispstr(temp_str);
	temp = doc.findElementById(temp_str);
	d.dispfindelembyid(temp);
	doc.clearvector();
	getchar();	system("cls");
}
//----< display requirement >----------------------------------------
void req52(Display d, XmlDocument &doc)
{
	d.dispReq(5);
	std::vector<sPtr> temp;
	std::string str;
	std::string temp_str = "1.0";					//value string  " Change this to try different query"
	str = doc.documentToString();
	d.dispstr(str);
	d.dispstr("Search Value =");
	d.dispstr(temp_str);
	temp = doc.findElementByVal(temp_str);
	d.dispfindelembyval(temp);
	doc.clearvector();
	getchar();	system("cls");
}
//----< display requirement >----------------------------------------
void req6(Display d, XmlDocument &doc)
{
	d.dispReq(6);
	std::vector<sPtr> temp;
	std::string str;
	std::string temp_str = "title";					//value string  " Change this to try different query"
	str = doc.documentToString();
	d.dispstr(str);
	d.dispstr("Search tag =");
	d.dispstr(temp_str);
	temp = doc.findElementByTag(temp_str);
	d.dispfindelembytag(temp);
	doc.clearvector();
	getchar();	system("cls");
}

//----< display requirement >----------------------------------------
void req71(Display d, XmlDocument &doc)
{
	std::vector<sPtr> temp;
	std::string str;
	d.dispReq(7);
	std::string temp_str = "date";					//value string " Change this to try different query"
	str = doc.documentToString();
	d.dispstr(str);
	d.dispstr("Search tag =");
	d.dispstr(temp_str);
	temp = doc.findElementByTag(temp_str);
	d.dispfindelembytag(temp);
	std::string addchilren = "<authorname>Vijayendra Ghadge <hello> <meter>Hello Vijayendra Ghadge!</meter> </hello><noted Companyname = 'Wintellectual'>< / noted>< / authorname>";
	d.dispstr("Add SubTree from String =");
	d.dispstr(addchilren);
	
	//doc.addnewchild(addchilren,)

	for (std::vector<sPtr>::iterator i = temp.begin(); i != temp.end(); ++i)
	{
		if (doc.addnewchild(addchilren, false, *i))							//in the vector of smart pointers addchild to all the pointers
		{
			str = doc.documentToString();
			d.dispstr(str);
		}
	}
	doc.clearvector();
	getchar();	system("cls");
}

//----< display requirement >----------------------------------------
void req72(Display d, XmlDocument &doc)
{
	std::vector<sPtr> temp;
	std::string str;
	d.dispReq(7);
	std::string temp_str = "Wintellect";					//value string " Change this to try different query"
	str = doc.documentToString();
	d.dispstr(str);
	d.dispstr("Search Val =");
	d.dispstr(temp_str);
	temp = doc.findElementByVal(temp_str);
	d.dispfindelembyval(temp);
	std::string addchilren = "<newtag> hey i am a new tag </newtag>";
	d.dispstr("Add child from String =");
	d.dispstr(addchilren);

	//doc.addnewchild(addchilren,)

	for (std::vector<sPtr>::iterator i = temp.begin(); i != temp.end(); ++i)
	{
		if (doc.addnewchild(addchilren, false, *i))							//in the vector of smart pointers addchild to all the pointers
		{
			str = doc.documentToString();
			d.dispstr(str);
		}
	}
	doc.clearvector();
	getchar();	system("cls");
}

//----< display requirement >----------------------------------------
void req73(Display d,  XmlDocument &doc)
{
	std::vector<sPtr> temp;
	std::string str;
	d.dispReq(7);
	std::string temp_str = "Company";					//value string " Change this to try different query"
	str = doc.documentToString();
	d.dispstr(str);
	d.dispstr("Search ID =");
	d.dispstr(temp_str);
	temp = doc.findElementById(temp_str);
	d.dispfindelembyval(temp);
	d.dispstr("Remove Children");
	
	for (std::vector<sPtr>::iterator i = temp.begin(); i != temp.end(); ++i)
	{
		if (doc.removechildren(*i))											//in the vector of smart pointers remove chilren from all the pointers to xml parse tree	
		{
			str = doc.documentToString();
			d.dispstr(str);
		}
	}
	doc.clearvector();
	getchar();	system("cls");
}
//----< display requirement >----------------------------------------
void req74(Display d, XmlDocument &doc)
{
	std::vector<sPtr> temp;
	std::string str;
	d.dispReq(7);
	std::string temp_str = "reference";					//value string " Change this to try different query"
	str = doc.documentToString();
	d.dispstr(str);
	d.dispstr("Search Tag =");
	d.dispstr(temp_str);
	temp = doc.findElementByTag(temp_str);
	d.dispfindelembytag(temp);
	d.dispstr("Remove Children");

	for (std::vector<sPtr>::iterator i = temp.begin(); i != temp.end(); ++i)
	{
		if (doc.removechildren(*i))											//in the vector of smart pointers remove chilren from all the pointers to xml parse tree	
		{
			str = doc.documentToString();
			d.dispstr(str);
		}
	}
	doc.clearvector();
	getchar();	system("cls");

}
//----< display requirement >----------------------------------------
void  req75(Display d, XmlDocument &doc)
{
	std::string str;
	d.dispReq(7);
	d.dispstr("Diplaying doc");
	str = doc.documentToString();
	d.dispstr(str);
	d.dispstr("Add Root Node");
	std::string s = "LectureNote.xml";
	doc.addroot(s, true); 
	str = doc.documentToString();
	d.dispstr(str);
	getchar();	system("cls");
}

//----< display requirement >----------------------------------------
void req81(Display d, XmlDocument &doc)
{
	std::string str;
	std::vector<sPtr> temp;
	std::vector<std::pair<std::string, std::string>> att;
	d.dispReq(8);
	std::string temp_str = "version";					//ID string " Change this to try different query"
	str = doc.documentToString();
	d.dispstr(str);
	d.dispstr("Search ID =");
	d.dispstr(temp_str);
	temp = doc.findElementById(temp_str);
	d.dispfindelembyid(temp);
	d.dispstr("Get Attributes");
	att=doc.getattributes(temp);
	d.dispattrib(att);
	doc.clearvector();
	getchar();	system("cls");

}

//----< display requirement >----------------------------------------
void req82(Display d, XmlDocument &doc)
{
std::string str;
std::vector<sPtr> temp,temporary;
d.dispReq(8);
std::string temp_str = "reference";					//ID string " Change this to try different query"
str = doc.documentToString();
d.dispstr(str);
d.dispstr("Search TAG =");
d.dispstr(temp_str);
temp = doc.findElementByTag(temp_str);
d.dispfindelembytag(temp);
d.dispstr("Get Children");
temporary=doc.GetChild(temp);
d.dispfindelembytag(temporary);
doc.clearvector();
getchar();	system("cls");
}

//----< display requirement >----------------------------------------
void req91(Display d, XmlDocument &doc)
{
	std::string str;
	std::vector<sPtr> temp, temporary;
	std::vector<std::pair<std::string, std::string>> att;
	d.dispReq(9);
	std::string	temp_str = "LectureNote";					//ID string " Change this to try different query"
	str = doc.documentToString();
	d.dispstr(str);
	d.dispstr("Search tag =");
	d.dispstr(temp_str);
	temp = doc.findElementByTag(temp_str);
	d.dispfindelembytag(temp);
	d.dispstr("Adding Attribute");
	std::string str1, str2;
	str1 = "attribute_name";
	str2 = "attribute_value";
	d.dispstr(str1);
	d.dispstr(str2);
	doc.addattributes(temp,str1,str2);
	str = doc.documentToString();
	d.dispstr(str);
	doc.clearvector();
	getchar();	system("cls");
}

//----< display requirement >----------------------------------------
void req92(Display d, XmlDocument &doc)
{


	std::string str;
	std::vector<sPtr> temp, temporary;
	std::vector<std::pair<std::string, std::string>> att;
	d.dispReq(9);
	std::string	temp_str = "LectureNote";					//ID string " Change this to try different query"
	str = doc.documentToString();
	d.dispstr(str);
	d.dispstr("Search tag =");
	d.dispstr(temp_str);
	temp = doc.findElementByTag(temp_str);
	d.dispfindelembytag(temp);
	d.dispstr("Removing Attribute");
	std::string str1 = "attribute_name";
	d.dispstr(str1);
	doc.removeattributes(temp, str1);
	str = doc.documentToString();
	d.dispstr(str);
	str1 = "course";
	d.dispstr(str1);
	doc.removeattributes(temp, str1);
	str = doc.documentToString();
	d.dispstr(str);
	doc.clearvector();
	getchar();	system("cls");
}


int main(int argc, char *argv[])
{
	title("XML Document Test Executive");
	Display d;
	std::string xml,myfile;
	std::vector<sPtr> temp, temp2;
	std::vector<std::pair<std::string, std::string>> att;
	d.dispReq(3);
	d.dispfromstr();
	std::string str = "<authorname>Vijayendra Ghadge <hello> <meter>Hello Vijayendra Ghadge!</meter> </hello><noted Companyname = 'Wintellectual'>< / noted>< / authorname>";
	d.dispstr(str);
	XmlDocument docum(str, XmlDocument::string);
	docum.constructtree(str,false);
	xml = docum.documentToString();
	d.dispstr(xml);
	getchar();	system("cls");
	d.dispReq(3);
	d.dispfromfile();
	myfile = argv[1];
	XmlDocument doc(myfile, XmlDocument::filename);
	doc.constructtree(myfile, true);
	xml = doc.documentToString();
	d.dispstr(xml);
	getchar();	system("cls");
	d.dispReq(4);
	docum= std::move(doc); //move assignemt operator will be called.
	xml = docum.documentToString();
	d.dispstr(xml);
	xml = doc.documentToString();
	d.dispstr(xml);
	getchar();	system("cls");
	d.dispReq(4);
	XmlDocument foo = testFunction(); //move constructor will be called.
	foo.constructtree(myfile, true);
	xml = foo.documentToString();
	d.dispstr(xml);
	getchar();	system("cls");
	d.dispReq(4); d.dispReq(10);
	doc.constructtree(myfile, true);
	xml = doc.documentToString();
	d.writeToString(xml);
	getchar();	system("cls");
	d.dispReq(4); d.dispReq(10);
	d.writeToFile();
	doc.documentToFile("out.xml");
	getchar();	system("cls");
	req51(d, doc); 	req52(d, doc);	req6(d, doc);	req71(d, doc);	req72(d, doc);	req73(d, doc);	req74(d, doc);	req75(d, doc);	req81(d, doc);	req82(d, doc);	req91(d, doc);	req92(d, doc); //diplaying requirements
	std::cout << "\n\n";
	return 0;
}

