#ifndef _PUGIWRAPPER_H
#define _PUGIWRAPPER_H

#ifdef _PUGIXML
#include "pugixml.hpp"

#include <map>
#include <vector>
#include <comdef.h>

#pragma warning(disable : 4290)     // disable 'C++ Exception Specification ignored'

class PugiXMLNodeList;
class PugiXMLDocument;
class PugiXMLDOMAttribute;
class PugiXMLNamedNodeMap;
class PugiXMLDOMElement;

class PugiXMLNode
{
	
	//PugiXMLNodeList* _childrens;
	//PugiXMLNamedNodeMap* _attributes;
public:
	pugi::xml_node _node;
	PugiXMLNode();
	PugiXMLNode( pugi::xml_node& node);
	//PugiXMLNode(const PugiXMLNode* node);
	~PugiXMLNode();

	//__declspec(property (get=getChildNodes)) 
 //       PugiXMLNodeList* childNodes;

	//__declspec(property (get=getAttributes)) 
 //       PugiXMLNamedNodeMap* attributes;

	__declspec(property (get=getText)) 
        _bstr_t text;

	__declspec(property (get=getName)) 
        _bstr_t name;

	__declspec(property (get=getName)) 
        _bstr_t nodeName;

	__declspec(property (get=getValue)) 
        _bstr_t value;

	__declspec(property (get=getFirstChild)) 
        const PugiXMLNode firstChild;

	__declspec(property (get=getNodeType)) 
		pugi::xml_node_type nodeType;

	_bstr_t getName();
	
	_bstr_t getText();

	_bstr_t getValue();

	//PugiXMLNodeList* getChildNodes();
	//
	//PugiXMLNamedNodeMap* getAttributes();
	_variant_t GetnodeTypedValue();

	void setName(const _bstr_t& name);
	void setValue(const _bstr_t& val);
	void setText(const _bstr_t& txt);
	pugi::xml_node_type getNodeType();
	const PugiXMLNode getFirstChild();

	//CString trace();
};

class PugiXMLNamedNodeMap
{
	std::map<_bstr_t, pugi::xml_attribute> _attributes;
public:
	~PugiXMLNamedNodeMap();
	void getAttributeList(const pugi::xml_node& node);
	pugi::xml_attribute getNamedItem(const _bstr_t& name);

	//CString trace();
};


class PugiXMLNodeList
{
	//std::vector<PugiXMLNode> _childrens;
public:
	pugi::xml_object_range<pugi::xml_node_iterator> getChildrens(const pugi::xml_node& node);

	//pugi::xml_object_range<pugi::xml_node_iterator> children = att_values.children();
	/*__declspec(property (get=getChildNodes)) 
        pugi::xml_object_range<pugi::xml_node_iterator> item;
	pugi::xml_object_range<pugi::xml_node_iterator> getChildNodes();*/

	/*__declspec(property (get=getLength)) 
        unsigned int length;
	unsigned int getLength();*/

	//CString trace();
};

class PugiXMLDocument
{
	pugi::xml_document _doc;
public:
	int open(const _bstr_t& path);
	const PugiXMLNode getElement(const _bstr_t & elem);
	const PugiXMLNode selectSingleNode(const _bstr_t& path);
};

class PugiXMLDOMAttribute
{
public:
	PugiXMLNode& getNamedItem(const _bstr_t& path);
};

class PugiXMLDOMElement
{

};


#endif //_PUGIXML
#endif //_PUGIWRAPPER_H