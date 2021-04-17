#ifndef _XMLFILE2_H
#define _XMLFILE2_H

#include "XMLDef.h"

#pragma warning(disable : 4290)     // disable 'C++ Exception Specification ignored'

class PugiXMLFile2
{
    public:
        PugiXMLFile2();
        ~PugiXMLFile2();

        void open(const _bstr_t& name,
                  const _bstr_t& schemaNamespace = L"",
                  const _bstr_t& schemaFilename = L"") throw(_com_error);
        void close();

        void create() throw(_com_error);
        void save(const _bstr_t& name) throw(_com_error);

        __declspec(property (get=getDocument)) 
        XMLDOMDocumentPtr document;

        XMLNodePtr getElement(const _bstr_t& name) const throw(_com_error);
        XMLNodeListPtr getElements(const _bstr_t& pattern) const throw(_com_error);

       // XMLDOMParseErrorPtr getParseError() const throw (_com_error) { return _document->parseError; }

//        _bstr_t filename() const throw (_com_error) { return _document->url; }

        XMLDOMDocumentPtr getDocument();

    private:
        XMLDOMDocument2Ptr _document;
};



#endif