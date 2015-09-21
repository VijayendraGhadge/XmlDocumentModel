#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H
///////////////////////////////////////////////////////////////////
// XmlDocument.h - a container of XmlElement nodes               //
// Ver 1.3                                                       //
// Application: CSE687 Pr#2, Spring 2015                         //
// Platform:    Dell XPS L520, Core i7, Windows 7 SP3            //
// Author:      Vijayendra Ghadge, Syracuse University	         //
//              (315) 728 8953, vvgahdge@syr.edu	             //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is used for CSE687 - Object Oriented Design
* Project #2 - XML Document Model.  It uses C++11 constructs,
* most noteably std::shared_ptr.  The XML Document Model is essentially
* a program-friendly wrapper around an Abstract Syntax Tree (AST) used to
* contain the results of parsing XML markup.
*
* Abstract Syntax Trees, defined in this package, are unordered trees with 
* two types of nodes:
*   Terminal nodes     - nodes with no children
*   Non-Terminal nodes - nodes which may have a finite number of children
* They are often used to contain the results of parsing some language.
*
* The elements defined in the companion package, XmlElement, will be used in
* the AST defined in this package.  They are:
*   AbstractXmlElement - base for all the XML Element types
*   DocElement         - XML element with children designed to hold prologue, Xml root, and epilogue
*   TaggedElement      - XML element with tag, attributes, child elements
*   TextElement        - XML element with only text, no markup
*   CommentElement     - XML element with comment markup and text
*   ProcInstrElement   - XML element with markup and attributes but no children
*   XmlDeclarElement   - XML declaration element with attributes
*
Public Interface:
=================
std::vector<sPtr> temp;  //vector of smart pointer
std::vector<std::pair<std::string, std::string>> att; //vector of attributes
XmlDocument doc(s,XmlDocument string );// OR filename); create object from string/filename where s=string or filename 
doc.constructtree(s, true);  //Contruct xml parse tree in doc object
std::string temp_str = "Company";
doc.addnewchild(addchilren, false, sPtr);   //Add child or subtree from unparsed string "addchildren" 
doc.removechildren(sPtr)					//Removes children of elements pointed by sPtr
doc.clearvector();							//Clears Query result vector found_
doc.addroot(s, true);  //Add root to texisting doc object
doc.addattributes(temp,"attribute_name","attribute_val");  //Add attributes to  pointed elements
bool removeattributes(std::vector<sPtr>, "course");  //Removes attributes of pointed elements
temp =findElementByTag(const std::string tag);    	//Find element by Tag
temp =findElementById(const std::string id);	//Find element by ID of attribute
temp =findElementByVal(const std::string val);   //Find element by Value of Attribute
att =getattributes(std::vector<sPtr>);				//fetch attributes of pointed element
temp=GetChild(std::vector<sPtr>);					//Get children of pointed element
doc.documentToString(); //Display XML Parse Tree	
bool documentToFile(std::string fileName);  //Write XML parse tree to file

void clearvector(); //clear query vector found_

* Required Files:
* ---------------
*   - XmlDocument.h, XmlDocument.cpp, 
*     XmlElement.h, XmlElement.cpp
*	  tokenizer.h,tokenizer.cpp
*     xmlElementParts.cpp ,xmlElementParts.h
*
* Build Process:
* --------------
*   devenv XmlDocument.sln /debug rebuild
*
* Maintenance History:
* --------------------
* ver 1.3 : 24 Mar 15
* - added functionality
    getchild,addnewchild,constructtree, parse element, 
	sPtr createDecElem(XmlParts), 
	sPtr createCommElem(XmlParts)
	sPtr createProcElem(XmlParts);
	sPtr createTagElem(XmlParts);
	sPtr createTextElem(XmlParts);
	sPtr createselfclosingtag(XmlParts);
	sPtr createElementType(XmlParts)
	std::vector<sPtr> findElembytag(sPtr,const std::string tag);
	std::vector<sPtr> findElembyId(sPtr, const std::string id);
	std::vector<sPtr> findElembyVal(sPtr, const std::string val);
	void stacktopaddchild(sPtr);
	sPtr stackpopoperation(sPtr);
* ver 1.2 : 21 Feb 15
* - modified these comments
* ver 1.1 : 14 Feb 15
* - minor changes to comments, method arguments
* Ver 1.0 : 11 Feb 15
* - first release
* simply roughed a design that is similar to that
* used in the .Net Framework XDocument class.
*/

#include <memory>
#include <string>
#include <stack>
#include "../XmlElement/XmlElement.h"
#include "../XmlElementParts/XmlElementParts/Tokenizer.h"
#include "../XmlElementParts/XmlElementParts/xmlElementParts.h"

namespace XmlProcessing
{
  class XmlDocument
  {
  public:
    using sPtr = std::shared_ptr < AbstractXmlElement > ;

    enum sourceType { string, filename };

    XmlDocument(const std::string& src, sourceType srcType=string); //Parameterzier Constructor
	XmlDocument(); //default constructor //void constructor
	XmlDocument(XmlDocument&& s); //move constructor
	XmlDocument& operator=(XmlDocument&& s); //move assignment operator
    
    // queries return XmlDocument references so they can be chained, e.g., doc.element("foobar").descendents();
    //XmlDocument& element(const std::string& tag);           // found_[0] contains first element (DFS order) with tag
    //XmlDocument& elements(const std::string& tag);          // found_ contains all elements with tag
    //XmlDocument& children(const std::string& tag = "");     // found_ contains sPtrs to children of prior found_[0] 
    //XmlDocument& descendents(const std::string& tag = "");  // found_ contains sPtrs to descendents of prior found_[0]
   // std::vector<sPtr>& select();                            // return reference to found_.  Use std::move(found_) to clear found_
	
	void constructtree(std::string, bool mode);
	bool addnewchild(std::string, bool mode,sPtr parent);
	bool removechildren(sPtr node);
	bool addroot(std::string, bool mode);
	bool addattributes(std::vector<sPtr>, std::string, std::string);
	bool removeattributes(std::vector<sPtr>, std::string);
	std::vector<sPtr> findElementByTag(const std::string tag);
	std::vector<sPtr> findElementById(const std::string id);
	std::vector<sPtr> findElementByVal(const std::string val);
	std::vector<std::pair<std::string, std::string>> getattributes(std::vector<sPtr>);
	std::vector<sPtr> GetChild(std::vector<sPtr>);
	std::string documentToString();
	bool documentToFile(std::string fileName);

	void clearvector();

  private:
    sPtr pDocElement_;         // AST that holds procInstr, comments, XML root, and more comments
    std::vector<sPtr> found_;  // query results
	std::stack <sPtr> node;

	void DFS_tag(sPtr, std::string);
	void DFS_val(sPtr, std::string);
	void DFS_id(sPtr, std::string);

	sPtr parseElem(std::string, bool mode, sPtr root);

	sPtr createDecElem(XmlParts);
	sPtr createCommElem(XmlParts);
	sPtr createProcElem(XmlParts);
	sPtr createTagElem(XmlParts);
	sPtr createTextElem(XmlParts);
	sPtr createselfclosingtag(XmlParts);
	sPtr createElementType(XmlParts);
	std::string getval(const std::string);
	void stacktopaddchild(sPtr);
	sPtr stackpopoperation(sPtr);

  };
}
#endif
