#include "stdafx.h"
#include "PugiXMLFile2.h"

#ifdef _DEBUG
//#include "DebugNew.h"
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////

PugiXMLFile2::PugiXMLFile2():_document(0)
{
}

/////////////////////////////////////////////////////////////////////

PugiXMLFile2::~PugiXMLFile2()
{
}

/////////////////////////////////////////////////////////////////////

void PugiXMLFile2::open(const _bstr_t& name,
                    const _bstr_t& schemaNamespace,
                    const _bstr_t& schemaFilename)
{
#ifdef _PUGIXML
	//_document.
#else
    _document.CreateInstance(MSXML2::CLSID_DOMDocument);

    if(schemaNamespace.length() > 0)
    {
        MSXML2::IXMLDOMSchemaCollectionPtr schemas;
        schemas.CreateInstance(MSXML2::CLSID_XMLSchemaCache);

        schemas->add(schemaNamespace, schemaFilename);

        _document->schemas = _variant_t((IDispatch*)schemas);
    }
    
    _document->async = VARIANT_FALSE;
    _document->validateOnParse = VARIANT_FALSE;

    _variant_t varName(name);

    if(VARIANT_FALSE == _document->load(varName))
    {
        _bstr_t text(L"Loading XML file '");
        text += varName.bstrVal;
        text += _bstr_t(L"' failed");

        IErrorInfo* pErrorInfo = 0;
        ICreateErrorInfoPtr pCreateErrorInfo;
        if(SUCCEEDED(CreateErrorInfo(&pCreateErrorInfo)))
        {
            pCreateErrorInfo->SetDescription(text);

            pCreateErrorInfo->QueryInterface(&pErrorInfo);
        }

        MSXML2::IXMLDOMParseErrorPtr parseError = _document->parseError;
        _bstr_t reason = parseError->reason;

        _com_raise_error(E_INVALIDARG, pErrorInfo);
    }
#endif
}

/////////////////////////////////////////////////////////////////////

void PugiXMLFile2::close()
{
#ifdef _PUGIXML
	if(_document)
	{
		delete _document;
		_document = 0;
	}
#else
    _document.Release();
    _document = 0;
#endif
}

/////////////////////////////////////////////////////////////////////

void PugiXMLFile2::create()
{
#ifdef _PUGIXML
	/*if(!_document)
	{
		_document = new pugi::xml_document();
	}*/
#else
	_document.CreateInstance(L"Msxml2.DOMDocument");
#endif
}

/////////////////////////////////////////////////////////////////////

void PugiXMLFile2::save(const _bstr_t& name)
{
#ifdef _PUGIXML

#else
    _variant_t destination(name);
    _document->save(destination);
#endif
}

/////////////////////////////////////////////////////////////////////

XMLNodePtr PugiXMLFile2::getElement(const _bstr_t& name) const
{
#ifdef _PUGIXML
	return _document->selectSingleNode(name);
#else
    return _document->selectSingleNode(name);
#endif
}

/////////////////////////////////////////////////////////////////////

XMLNodeListPtr PugiXMLFile2::getElements(const _bstr_t& pattern) const
{
#ifdef _PUGIXML
	return NULL;
#else
    return _document->getElementsByTagName(pattern);
#endif
}

/////////////////////////////////////////////////////////////////////

XMLDOMDocumentPtr PugiXMLFile2::getDocument()
{
    return _document;
}

/////////////////////////////////////////////////////////////////////
