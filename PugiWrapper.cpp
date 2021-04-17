#include "stdafx.h"
#include "PugiWrapper.h"
#include <sstream>

PugiXMLNode::PugiXMLNode():_childrens(NULL), _attributes(NULL)
{
}

//PugiXMLNode::PugiXMLNode(const PugiXMLNode* node):_node(*node)
//{
//}

PugiXMLNode::PugiXMLNode( pugi::xml_node& node):
		_node(node), _childrens(NULL), _attributes(NULL)
{
}

//PugiXMLNode::PugiXMLNode(const PugiXMLNode& node):
//		_node(NULL), _childrens(NULL), _attributes(NULL)
//{
//
//}

//pugi::xml_node* PugiXMLNode::getNode()
//{
//	return _node;
//}

PugiXMLNode::~PugiXMLNode()
{
	if(_childrens)
	{
		delete _childrens;
		_childrens = 0;
	}
	if(_attributes)
	{
		delete _attributes;
		_attributes = 0;
	}
}

const PugiXMLNode PugiXMLNode::getFirstChild()
{
	return _node.first_child();
}

pugi::xml_node_type PugiXMLNode::getNodeType()
{
	return _node.type();
}

_bstr_t PugiXMLNode::getName()
{
	return _node.name();
}
	
_bstr_t PugiXMLNode::getText()
{
	return _node.text().get();
}

_bstr_t PugiXMLNode::getValue()
{
	return _node.value();
}

_variant_t PugiXMLNode::GetnodeTypedValue()
{
	return _node.value();
}

//PugiXMLNodeList* PugiXMLNode::getChildNodes()
//{
//	if(!_childrens)
//	{
//		_childrens = new PugiXMLNodeList();
//		_childrens->getChildrens(_node);
//	}
//	return _childrens;
//}
//
//PugiXMLNamedNodeMap* PugiXMLNode::getAttributes()
//{
//	if(!_attributes)
//	{
//		_attributes = new PugiXMLNamedNodeMap();
//		_attributes->getAttributeList(_node);
//	}
//	return _attributes;
//}

void PugiXMLNode::setName(const _bstr_t& name)
{
	_node.set_name(name);
}

void PugiXMLNode::setValue(const _bstr_t& val)
{
	_node.append_child(pugi::node_pcdata).set_value(val);
	_node.set_value(val);
}

void PugiXMLNode::setText(const _bstr_t& txt)
{
	_node.set_value(txt);
}

//CString PugiXMLNode::trace()
//{
//	std::stringstream stream;
//	stream << _node.name() << " << " << _node.value();
//	return CString(stream.str().c_str());
//}
//
//CString PugiXMLNodeList::trace()
//{
//	std::stringstream stream;
//	stream << "size = " << getLength();
//	std::vector<PugiXMLNode*>::const_iterator it = _childrens.begin();
//	std::vector<PugiXMLNode*>::const_iterator itEnd = _childrens.end();
//	for(; it != itEnd; ++it)
//	{
//		//PugiXMLNode no(*it)->;
//		stream << "Name=" << (*it)->getName() << " Value=" << (*it)->getText() << " Text=" << (*it)->getValue() << "\n";
//	}
//
//	return CString(stream.str().c_str());
//}

//PugiXMLNodeList::PugiXMLNodeList()
//{
//}
//
//PugiXMLNodeList::~PugiXMLNodeList()
//{
//	//_childrens.clear();
//}
pugi::xml_object_range<pugi::xml_node_iterator> PugiXMLNodeList::getChildrens(const pugi::xml_node& node)
{
	/*for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling())
	{
		//PugiXMLNode no(child);
		_childrens.push_back(PugiXMLNode(child));
	}
	return _childrens;
	*/
	return node.children();
}

//std::vector<PugiXMLNode>& PugiXMLNodeList::getChildNodes()
//{
//	return _childrens;
//}
//
//unsigned int PugiXMLNodeList::getLength()
//{
//	return _childrens.size();
//}

const PugiXMLNode PugiXMLDocument::selectSingleNode(const _bstr_t& path)
{
	return _doc.child(path);
}
int PugiXMLDocument::open(const _bstr_t & path)
{
	if (!_doc.load_file((const wchar_t*)path)) 
		return -1;
}

const PugiXMLNode PugiXMLDocument::getElement(const _bstr_t & elem)
{
	return _doc.child(elem);
}

//PugiXMLNode* PugiXMLDOMAttribute::getNamedItem(const _bstr_t& path)
//{
//	return NULL;
//}

PugiXMLNamedNodeMap::~PugiXMLNamedNodeMap()
{
	_attributes.clear();
}

//CString PugiXMLNamedNodeMap::trace()
//{
//	std::stringstream stream;
//	std::map<_bstr_t, _bstr_t>::const_iterator it = _attributes.begin();
//	std::map<_bstr_t, _bstr_t>::const_iterator itEnd = _attributes.end();
//	for(; it != itEnd; ++it)
//	{
//		stream << "Key=" << (*it).first << " keyvalue=" << (*it).second << "\n";
//	}
//
//	return CString(stream.str().c_str());
//}

void PugiXMLNamedNodeMap::getAttributeList(const pugi::xml_node& node)
{
	pugi::xml_attribute attr;
    for (attr = node.first_attribute(); attr; attr = attr.next_attribute())
    {
		if (!attr.empty())
		{
			_attributes[attr.name()] = attr;
		}
    }
}

pugi::xml_attribute PugiXMLNamedNodeMap::getNamedItem(const _bstr_t& name)
{
	pugi::xml_attribute attr;
	std::map<_bstr_t, pugi::xml_attribute>::const_iterator find = _attributes.find(name);
	return find!= _attributes.end() ? find->second : attr;
}
