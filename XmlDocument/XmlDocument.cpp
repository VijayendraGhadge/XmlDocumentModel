///////////////////////////////////////////////////////////////////
// XmlDocument.cpp - a container of XmlElement nodes             //
// Ver 1.3                                                       //
// Application: CSE687 Pr#2, Spring 2015                         //
// Platform:    Dell XPS L520, Core i7, Windows 7 SP3            //
// Author:      Vijayendra Ghadge, Syracuse University	         //
//              (315) 728 8953, vvgahdge@syr.edu	             //
///////////////////////////////////////////////////////////////////

#include <iostream>
#include "XmlDocument.h"
#include <fstream>
#include <vector>
using namespace XmlProcessing;
using sPtr = std::shared_ptr <AbstractXmlElement>;

//>>>>>>void constructor-------------------------------- -
XmlProcessing::XmlDocument::XmlDocument() : found_(std::vector<sPtr>())
{
	sPtr pDoc = makeDocElement(nullptr);
	pDocElement_ = pDoc;
	//node.push(pDoc);
}
//..............parameterzised constructor...................
XmlProcessing::XmlDocument::XmlDocument(const std::string& src, sourceType srcType)
{
	sPtr pDoc = makeDocElement(nullptr);
	pDocElement_ = pDoc;
	//node.push(pDoc);
}

//----<move constructor >--------------------------------------
XmlProcessing::XmlDocument::XmlDocument(XmlDocument&& s) : pDocElement_(s.pDocElement_), node(s.node), found_(s.found_)
{
	s.pDocElement_ = nullptr;  // must do this to avoid delete in s dtor
	while (!s.node.empty())				// std::stack<sPtr>node //pop entire stack...
		s.node.pop();
	for (unsigned int i = 0; i < found_.size(); ++i)
		s.found_[i] = nullptr;
	s.found_.clear();
	std::cout << "\n...........................Move constructor called..............................\n";
}

////----< move assignment operator >-----------------------------

XmlDocument& XmlProcessing::XmlDocument::operator=(XmlDocument&& s) {

	if (this == &s) return *this;
	for (unsigned int i = 0; i < found_.size(); i++)
	{
		found_[i] = nullptr;
	}	
	while (!node.empty())
		node.pop();
	found_.clear();
	pDocElement_ = nullptr;
	found_ = s.found_;
	node = s.node;
	pDocElement_ = s.pDocElement_;
	s.pDocElement_ = nullptr;  // must do this to avoid delete in s dtor
	while (!s.node.empty())
		s.node.pop();
	for (unsigned int i = 0; i < found_.size(); i++)
		s.found_[i] = nullptr;
	s.found_.clear();
	std::cout << "\n........................Move assignment operator called.........................\n";
	return *this;
}

//----< construct new xml parse tree>----------------------------------------
void XmlDocument::constructtree(std::string s, bool mode)
{
	sPtr pDoc = makeDocElement(nullptr);
	pDocElement_ = parseElem(s, mode, pDoc);
	//pDocElement_ = parseElem(s, mode, pDocElement_);
	node.push(pDocElement_);
}
//.............. Xml Parse tree to String..................
std::string XmlDocument::documentToString()
{
	std::string temp=".................................Empty Tree....................................";
	if (pDocElement_!=nullptr)
	temp=pDocElement_->toString();
	return temp;
}

//..............Xml Parse  tree to XML file..................
bool  XmlDocument::documentToFile(std::string filename)
{
	if (pDocElement_ != nullptr)
	{
		std::ofstream myfile;
		myfile.open(filename);
		myfile << pDocElement_->toString();
		myfile.close();
		return true;
	}
	return false;
}

//----< function to add new child/children to existing xml parse tree >----------------------------------------
bool XmlDocument::addnewchild(std::string s, bool mode,sPtr parent)
{
	if (!node.empty())
		node.pop();
	sPtr temp=parseElem(s, mode, nullptr);
	parent->addChild(temp);
	node.push(pDocElement_);

	return true;
}

//----< function to add root to existing doc element >----------------------------------------
bool XmlDocument::addroot(std::string s, bool mode)
{

	sPtr pDoc = makeDocElement(nullptr);
	if (node.empty())
	{
		pDocElement_ = parseElem(s, mode, pDoc);
		node.push(pDocElement_);
	}
	else
	{
		pDocElement_ = parseElem(s, mode, pDoc);
	}

	return true;
}
//----< function to remove child/children from existing xml parse tree >----------------------------------------
bool XmlDocument::removechildren(sPtr node)
{
	for (auto a : node->getchild())
	node->removeChild(a);
	return true;
}
//----< parse tokens,stack to construct subtree for xml parse tree >----------------------------------------
sPtr  XmlDocument::parseElem(std::string text,bool mode,sPtr pt)
{
	sPtr ptr;
	if (pt != nullptr)								//if no xml parse tree exists 
	{
		node.push(pt);								//push it to stack
	}
	
	Toker toker;
	toker.setMode(Toker::xml);
	toker.attach(text, mode);
	XmlParts parts(&toker);		//parse tokens on basis of file or string 
	/*//parts.verbose();               	// uncomment to show token details*/
	while (parts.get())										//while end of tokens
	{
		ptr = createElementType(parts);
	}
	ptr = stackpopoperation(ptr);
	return ptr; //return document pointer.
}

sPtr XmlDocument::createElementType(XmlParts parts)
{
	sPtr ptr;
	int size = -1;

	size = parts.length() - 1; 			//std::cout << parts.show().c_str() << std::endl; 
	if (parts[0] == "<" && parts[1] == "?" && parts[2] == "xml" && parts[3] != "-" && parts[size - 1] == "?" && parts[size] == ">") //declaration element
	{
		ptr = createDecElem(parts);		//create declaration element and add it as child to parent on stack
		stacktopaddchild(ptr);
	}
	else if (parts[0] == "<" && parts[1] == "!" && parts[2] == "--" && parts[size - 1] == "--" && parts[size] == ">")
	{
		ptr = createCommElem(parts);	//create comment element and add it as child to parent on stack
		stacktopaddchild(ptr);
	}
	else if (parts[0] == "<" && parts[1] == "?" && parts[size - 1] == "?" && parts[size] == ">")
	{
		ptr = createProcElem(parts);//create processing instruction element and add it as child to parent on stack
		stacktopaddchild(ptr);
	}
	else if (parts[0] == "<" && parts[size - 1] == "/" && parts[size] == ">")
	{
		ptr = createselfclosingtag(parts);					//create tagged element 
		stacktopaddchild(ptr); //else add it as child to parent on stack
	}	
	else if (parts[0] == "<" && parts[size] == ">")
	{
		if (parts[1] != "/")					// tagged element or closing tag
		{
			ptr = createTagElem(parts);					//create tagged element 
			//if (node.empty())			//{ 			//	node.push(ptr);  			//} 			//else { stacktopaddchild(ptr);	node.push(ptr); }	
			stacktopaddchild(ptr);  
			node.push(ptr); 
		}
		else if (parts[2] == (node.top())->value() && !node.empty())	{ node.pop(); } //if closing tag pop element on stack
		else{ std::cout << "\n..............................Malformed XML.....................................\n"; exit(0); } 	//detected malformed xml exit program			//std::cout << temp->toString();
	}
	else if (parts[0] != "<" && parts[size] != ">")	
	{
		ptr = createTextElem(parts);	// create text element add it as child to parent on stack
		stacktopaddchild(ptr);
	} 

	return ptr;
}
//..................add child to element pointed by item on stack top...........
void XmlDocument::stacktopaddchild(sPtr p)
{
	sPtr temp;
	if (!node.empty())
	{
		temp = node.top();
		temp->addChild(p);
	}
	else
	{
		node.push(p);
	}
}
//............pop stack top element and return .......... only if stack is not empty
sPtr XmlDocument::stackpopoperation(sPtr p)
{
	if (!node.empty())
	{
		p = node.top(); 
		node.pop();	//get document pointer on stack
	}
	return p;
}

//----< create declaration element >----------------------------------------
std::shared_ptr < AbstractXmlElement > XmlDocument::createDecElem(XmlParts p)
{
	sPtr ptr = makeXmlDeclarElement();
	for (int i = 1; i < p.length()-1; ++i)	
	{		
		if (p[i] == "=")		
		{
		ptr->addAttrib(p[i - 1], getval(p[i + 1]));	
		}
	}	//std::cout << ptr->toString();	
	return ptr;
}
//----< create comment element >----------------------------------------
std::shared_ptr < AbstractXmlElement > XmlDocument::createCommElem(XmlParts p)
{
	sPtr ptr;
	std::string temp;
	for (int i = 3; i < p.length() - 2; ++i)
	{
		temp = temp + p[i]+" ";
	}
	temp.erase(temp.end() - 1);
	ptr = makeCommentElement(temp);
	//std::cout << ptr->toString();
	return ptr;
}
//----< create processing instruction element >----------------------------------------
std::shared_ptr < AbstractXmlElement > XmlDocument::createProcElem(XmlParts p)
{
	sPtr ptr;
	std::string temp;
	int flag = 0;
	for (int i = 2; i < p.length() - 1; ++i)
	{
		if (p[i + 1] != "=")
			temp = temp + p[i];
		else
		{
			break;
		}
	}
	ptr = makeProcInstrElement(temp);
	for (int i = 2; i < p.length()-1; ++i)
	{
		if (p[i] == "=")
		{
			ptr->addAttrib(p[i - 1], getval(p[i + 1]));
			flag = 1;
		}
	}
	if (flag == 0)
	{
		for (int i = 2; i < p.length() - 3; ++i)
		{
			ptr->addAttrib(p[i], p[i + 1]);
		}
	}	//std::cout << ptr->toString();
	return ptr;
}
//----< create tagged element >----------------------------------------
std::shared_ptr < AbstractXmlElement > XmlDocument::createTagElem(XmlParts p)
{
	sPtr ptr;
	std::string temp;
	ptr = makeTaggedElement(p[1]);
	for (int i = 2; i < p.length() - 1; ++i)
	{
		if (p[i] == "=")
		{
			ptr->addAttrib(p[i - 1], getval(p[i + 1]));
		}
	}
	//std::cout << ptr->toString();
	return ptr;
	
}
//----< create self closing tagged element >----------------------------------------
std::shared_ptr < AbstractXmlElement > XmlDocument::createselfclosingtag(XmlParts p)
{
	sPtr ptr;
	std::string temp=p[1];
	ptr = makeTaggedElement(temp);
	for (int i = 2; i < p.length() - 1; ++i)
	{
		if (p[i] == "=")
		{
			ptr->addAttrib(p[i - 1], getval(p[i + 1]));
		}
	}
	//std::cout << ptr->toString();
	return ptr;

}
//----< create text element >----------------------------------------
std::shared_ptr < AbstractXmlElement > XmlDocument::createTextElem(XmlParts p)
{
	sPtr ptr;
	std::string temp;
	for (int i = 0; i < p.length(); ++i)
	{
		temp = temp + " " + p[i];
	}
	ptr = makeTextElement(temp);
	//std::cout << ptr->toString();
	return ptr;
}
//----< extract token from xxx -> "xxx" or 'xxx' >----------------------------------------
std::string XmlDocument::getval(std::string x)
{
	x.erase(x.begin());
	x.erase(x.end() - 1);
	//std::cout << x;
	return x;
}

//-----------------------------//find element by tag 
std::vector<sPtr> XmlDocument::findElementByTag(const std::string tag)
{
	DFS_tag(pDocElement_, tag);
	return found_;
}

//...........DFS to find tag..................
void XmlDocument::DFS_tag(sPtr Pnode , std::string tag)
{
	for (auto pChild : Pnode->getchild())					//get children pointers
	{
		if (pChild->value() == tag)								//if tag == tags of child pointers push result to vector
		{
			found_.push_back(pChild);
		}
		DFS_tag(pChild, tag);								//recurse
	}
}

//-----------------------------//find element by attribute name
std::vector<sPtr> XmlDocument::findElementById(const std::string id)
{
	DFS_id(pDocElement_, id);
	return found_;
}

//...........DFS to find id..................
void XmlDocument::DFS_id(sPtr Pnode, std::string id)
{
	std::vector<std::pair<std::string, std::string>> att;
	for (auto pChild : Pnode->getchild())						//get children pointers
	{
		att = pChild->getattrib();								//get attributes of pointed element

		for (auto a : att)
		{
			if (a.first == id)								//if ID = attritube id query successful , add result to vectory 
				found_.push_back(pChild);
		}
		DFS_id(pChild, id);								//recurse
	}
}
//----< recursive left-to-right Depth First Search >-------------------------//find element by attribute value
std::vector<sPtr> XmlDocument::findElementByVal(const std::string val)
{
	DFS_val(pDocElement_, val);
	return found_;
}
//...........DFS to find id..................
void XmlDocument::DFS_val(sPtr Pnode, std::string val)
{
	std::vector<std::pair<std::string, std::string>> att;
	for (auto pChild : Pnode->getchild())						//get children pointers
	{
		att = pChild->getattrib();								//get attributes of pointed element

		for (auto a : att)
		{
			if (a.second == val)								//if val = attritube value query successful , add result to vectory 
				found_.push_back(pChild);
		}
		DFS_val(pChild, val);								//recurse
	}
}
//..............Get attributes of pointed element .....................
std::vector<std::pair<std::string, std::string>> XmlDocument::getattributes(std::vector<sPtr> vec)
{
	std::vector<std::pair<std::string, std::string>> att,result;
	for (auto a : vec)
	{
		result = a->getattrib();
		for (auto x : result)
		{
			att.push_back(x);
		}
	}
	return att;
}
//..............Get childeren of pointed element .....................
std::vector<sPtr> XmlDocument::GetChild(std::vector<sPtr> vec)
{
	std::vector<sPtr> result;
	for (auto a : vec)
	{
		result=a->getchild();
		for (auto x : result)
		{
			found_.push_back(x);
		}
		
	}
	return found_;
}

//..............Add Attritbutes to pointed element .....................
bool XmlDocument::addattributes(std::vector<sPtr> vec, std::string name, std::string val)
{
	for (auto a : vec)
	{
		a->addAttrib(name,val);
	}
	return true;
}

//..............Remove Attritbutes from pointed element .....................
bool XmlDocument::removeattributes(std::vector<sPtr> vec,std::string str)
{
	for (auto a : vec)
	{
		a->removeAttrib(str);
	}
	return true;
}


//................clear found_ vector..........used for storing query results.
void XmlDocument::clearvector()
{
	found_.clear();
}
/*
XmlDocument testFunction()
{
	XmlDocument s("<author>Jeff Prosise <hello> <men>Men will be men!</men> </hello><note Company = 'Wintellect'>< / note>< / author>", XmlDocument::string);
	return s;
}*/

#ifdef TEST_XMLDOCUMENT
int main()
{
  title("Testing XmlDocument class");

  std::vector<sPtr> temp,temp2;
  std::vector<std::pair<std::string, std::string>> att;
 /* std::string s = "<author>Jeff Prosise <hello> <men>Men will be men!</men> </hello><note Company = 'Wintellect'>< / note>< / author>";
  XmlDocument docum(s, XmlDocument::string);
  docum.constructtree(s,false);
  std::string x = docum.documentToString();
  std::cout << "\n" << x;*/
  std::string s = "LectureNote.xml";
  XmlDocument doc(s, XmlDocument::filename);
  doc.constructtree(s, true);
 // std::string addchilren = "<author>Jeff Prosise <hello> <men>Men will be men!</men> </hello><note Company = 'Wintellect'>< / note>< / author>";
  std::string x2=doc.documentToString();
  //std::cout <<"\n"<< x2;
 // doc.documentToFile("out.xml");
  //docum = std::move(doc);  //move assignment operator 
  //x = docum.documentToString();
  //std::cout << "\n" << x;
  //x2 = doc.documentToString();
  //std::cout << "\n" << x2;
  //XmlDocument docm=testFunction(); //Move constructor 
  ////doc = docum; //copy Constructor
  //x2 = docm.documentToString();
  //std::cout << "\n" << x2;

 /* std::string addchilren = "<author>Jeff Prosise <hello> <men>Men will be men!</men> </hello><note Company = 'Wintellect'>< / note>< / author>";  root = doc.addnewchild(addchilren, false,root);  std::cout << root->toString();*/ 
 //temp=doc.findElementByTag("title"); for (std::vector<sPtr>::iterator i = temp.begin(); i != temp.end(); ++i)  {	std::cout <<(*i)->toString();  }
  /*temp = doc.findElementById("Company");  for (std::vector<sPtr>::iterator i = temp.begin(); i != temp.end(); ++i)  { std::cout << (*i)->toString(); }*/
 /* temp = doc.findElementByVal("1.0");  for (std::vector<sPtr>::iterator i = temp.begin(); i != temp.end(); ++i) { std::cout << (*i)->toString(); }*/
  /*temp = doc.findElementByTag("date"); 
  for (std::vector<sPtr>::iterator i = temp.begin(); i != temp.end(); ++i)   
  {
	// std::cout << (*i)->toString(); 
	  std::string addchilren = "<author>Jeff Prosise <hello> <men>Men will be men!</men> </hello><note Company = 'Wintellect'>< / note>< / author>";
	  if (doc.addnewchild(addchilren, false, *i)) 
	  {
		  std::string str1 = doc.documentToString();
		  std::cout <<"\n"<< str1;
	  }
  }*/
 /* temp = doc.findElementByTag("reference");  for (std::vector<sPtr>::iterator i = temp.begin(); i != temp.end(); ++i)    {	  	  if (doc.removechildren(*i))	  {		  std::string str1 = doc.documentToString();		  std::cout << "\n" << str1;	  }  }*/
  //doc.addroot(addchilren, false);     /*    temp = doc.findElementByTag("note");  		 doc.clearvector();		 doc.addattributes(temp, "hi", "hello");		  x2 = doc.documentToString();		  std::cout << "\n" << x2;		  doc.removeattributes(temp,"hi");		  x2 = doc.documentToString();		  std::cout << "\n" << x2;		temp2= doc.GetChild(temp);		 for (std::vector<sPtr>::iterator i = temp2.begin(); i != temp2.end(); ++i)   { std::cout << (*i)->toString(); }*/
    std::cout << "\n\n";
  return 0;
}
#endif