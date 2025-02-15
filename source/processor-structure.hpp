//! @file
//! @brief Structure context module - header file.
//! @author Mariusz Ornowski (mariusz.ornowski@ict-project.pl)
//! @date 2012-2022
//! @copyright ICT-Project Mariusz Ornowski (ict-project.pl)
/* **************************************************************
Copyright (c) 2012-2022, ICT-Project Mariusz Ornowski (ict-project.pl)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. Neither the name of the ICT-Project Mariusz Ornowski nor the names
of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**************************************************************/
#ifndef _REFLECT_PROCESSOR_STRUCT_HEADER
#define _REFLECT_PROCESSOR_STRUCT_HEADER
//============================================
#include "process.hpp"
#include "meta-map.hpp"
#include "processor-context.hpp"
#include <exception>
//============================================
namespace ict { namespace  reflect { namespace context {
//============================================
class Structure: public Interface {
private:
    //! Typ iteratora.
    union Iterator{
        meta::mapByName::const_iterator itAscByName;
        meta::mapByIndex::const_iterator itAscByIndex;
        meta::mapByName::const_reverse_iterator itDescByName;
        meta::mapByIndex::const_reverse_iterator itDescByIndex;
    };
    //! Metadane obiektu (po nazwie).
    const meta::mapByName & byName;
    //! Metadane obiektu (po indeksie).
    const meta::mapByIndex & byIndex;
    //! Iterator
    Iterator iterator;
    //! 
    //! @brief Konstruktor kontekstu.
    //! 
    //! @param object Referencja do obiektu.
    //! @param opt Opcje kontekstu.
    //! 
    template <class O> Structure(const O & object,const Options & opt):
        Interface(opt),
        byName(meta::getMapByGivenName(object)),
        byIndex(meta::getMapByIndex(object)){
        setFirstElement();
    }
    //! Fabryka kontekstów.
    template <class O> class _Factory : public Factory {
    private:
        //! Referencja do obiektu.
        O & object;
    public:
        //! Konstruktor.
        _Factory(const O & o):object(o){}
        //! Patrz: ict::reflect::context::Factory::get()
        Interface * get(const Options & options) const{
            return new Structure(object,options);
        }
    };
public:
    //! 
    //! @brief Dostęp do fabryki kontekstów dla danego obiektu.
    //! 
    //! @param object Obiekt, dla którego ma być stworzony kontekst.
    //! @return Referencja do fabryki.
    //! 
    template <class O> friend const Factory & factory(const O & object){
        static const _Factory f(object);
        return f;
    }
    //! Opcja ustawiająca sortowanie w kierunku malejącym (w przeciwnym wypadku jest w kierunku rosnącym).
    const static Options optionDescending=0x1<<0;
    //! Opcja ustawiająca sortowanie po indeksie (w przeciwnym razie sortowanie jest po nazwie).
    const static Options optionByIndex=0x1<<1;
    //! Destruktor.
    ~Structure(){}
    //! Patrz: ict::reflect::context::Interface::setIndex()
    bool setIndex(const ict::reflect::type::index_t & index);
    //! Patrz: ict::reflect::context::Interface::getIndex()
    bool getIndex(ict::reflect::type::index_t & index) const;
    //! Patrz: ict::reflect::context::Interface::setName()
    bool setName(const std::string & name);
    //! Patrz: ict::reflect::context::Interface::getName()
    bool getName(std::string & name) const;
    //! Patrz: ict::reflect::context::Interface::setFirstElement()
    bool setFirstElement();
    //! Patrz: ict::reflect::context::Interface::setNextElement()
    bool setNextElement();
    //! Patrz: ict::reflect::context::Interface::isArray()
    bool isArray(){
        return false;
    }
};

/*

class Tag{
public:
    ~Tag(){}
    virtual bool setName(const std::string & n)=0;
    virtual bool getName(std::string & n) const=0;
};
class TagString: public std::string,public Tag {
public:
    bool setName(const std::string & n){
        assign(n);
        return true;
    }
    bool getName(std::string & n) const {
        n=*this;
        return true;
    }
};
template<typename T=TagString,class S=Stack<Element>> class Context {
public:
    typedef T tag_t;
    typedef S stack_t;
    typedef typename S::element_t element_t;
    tag_t currentTag;
    stack_t stack;
    virtual ~Context(){}
    virtual int processControl(const Control & control)=0;
    virtual int processControl(Control & control)=0;
    bool setTag(const tag_t & t){
        std::string n;
        if (t.getName(n)){
            return stack.accessElement().setName(n);
        }
        return false;
    }
    bool getTag(tag_t & t){
        std::string n;
        if (stack.accessElement().getName(n)){
            return t.setName(n);
        }
        return false;
    }
};
*/
//===========================================
//} }
//============================================
/*
//! 
//! @brief Procesor, który przetwarza dane w obiekcie (object) używając podanego kontekstu (context) - wersja z modyfikacją obiektu.
//! 
//! @param object Obiekt, którego dane są przetwarzane.
//! @param context Kontekst przetwarzania (musi zai).
//! @return int Wartości:
//!     * Mniejsze od zera - wystąpił błąd przy przetwarzaniu;
//!     * Zero - Przetwarzanie zakończone sukcesem;
//!     * Większe od zera - Przetwarzanie nie zakończyło się, bo dane są niekompletne lub brakuje miejsca.
//! 
template<typename O,typename T=context::structure::TagString,class S=context::structure::Stack<context::structure::Element>> 
int processor(O & object,context::structure::Context<T,S> & context){
    int out=0;
    context.stack.enterElement(object);
    try {
        auto & element(context.stack.accessElement());
        auto & tag (context.currentTag);
        auto & control (element.currentControl);
        while (!out){
            switch (element.currentControl){
                case context::structure::c_beforeStruct:{
                    out=context.processControl(control);
                    if (!out){
                        element.currentControl=context::structure::c_beforeTag;
                    }
                } break;
                case context::structure::c_beforeTag:{
                    out=context.processControl(control);
                    if (!out) {
                        element.currentControl=context::structure::c_processTag;
                    } else if (out<0){
                        element.currentControl=context::structure::c_afterStruct;
                        out=0;
                    }
                } break;
                case context::structure::c_processTag:{
                    out=processor(tag,context);
                    if (!out){
                        context.setTag(tag);
                        element.currentControl=context::structure::c_afterTag;
                    }
                } break;
                case context::structure::c_afterTag:{
                    out=context.processControl(control);
                    if (!out) {
                        element.currentControl=context::structure::c_betweenTagAndValue;
                    }
                } break;
                case context::structure::c_betweenTagAndValue:{
                    out=context.processControl(control);
                    if (!out) {
                        element.currentControl=context::structure::c_beforeValue;
                    }
                } break;
                case context::structure::c_beforeValue:{
                    out=context.processControl(control);
                    if (!out) {
                        element.currentControl=context::structure::c_processValue;
                    }
                } break;
                case context::structure::c_processValue:{
                    ict::reflect::type::index_t i;
                    if (element.getIndex(i)) {
                        out=process(object,context,i);
                        if (!out) {
                            element.currentControl=context::structure::c_afterValue;
                        }
                    } else {
                        out=-1;
                    }
                } break;
                case context::structure::c_afterValue:{
                    out=context.processControl(control);
                    if (!out) {
                        element.currentControl=context::structure::c_betweenElements;
                    }
                } break;
                case context::structure::c_betweenElements:{
                    out=context.processControl(control);
                    if (!out) {
                        element.currentControl=context::structure::c_beforeTag;
                    } else if (out<0) {
                        element.currentControl=context::structure::c_afterStruct;
                        out=0;
                    }
                } break;
                case context::structure::c_afterStruct:{
                    out=context.processControl(control);
                    if (!out) {
                        element.currentControl=context::structure::c_theEnd;
                    }
                } break;
                case context::structure::c_theEnd:{
                    context.stack.leaveElement();
                    return 0;
                } break;
                default:{
                    out=-2;
                } break;
            }
        }
    } catch (const std::exception & e){
        out=-3;
    }
    context.stack.leaveElement();
    return(out);
}
//! 
//! @brief Procesor, który przetwarza dane w obiekcie (object) używając podanego kontekstu (context) - wersja bez modyfikacji obiektu.
//! 
//! @param object Obiekt, którego dane są przetwarzane.
//! @param context Kontekst przetwarzania.
//! @return int Wartości:
//!     * Mniejsze od zera - wystąpił błąd przy przetwarzaniu;
//!     * Zero - Przetwarzanie zakończone sukcesem;
//!     * Większe od zera - Przetwarzanie nie zakończyło się, bo dane są niekompletne lub brakuje miejsca.
//! 
template<typename O,typename T=context::structure::TagString,class S=context::structure::Stack<context::structure::Element>> 
int processor(const O & object,context::structure::Context<T,S> & context){
    int out=0;
    context.stack.enterElement(object);
    try {
        auto & element(context.stack.accessElement());
        const auto & tag (context.currentTag);
        const auto & control (element.currentControl);
        while (!out){
            switch (element.currentControl){
                case context::structure::c_beforeStruct:{
                    out=context.processControl(control);
                    if (!out){
                        if (element.setFirstElement()){
                            element.currentControl=context::structure::c_beforeTag;
                        } else {
                            element.currentControl=context::structure::c_afterStruct;
                        }
                    }
                } break;
                case context::structure::c_beforeTag:{
                    out=context.processControl(control);
                    if (!out) {
                        context.setTag(tag);
                        element.currentControl=context::structure::c_processTag;
                    }
                } break;
                case context::structure::c_processTag:{
                    out=processor(tag,context);
                    if (!out){
                        element.currentControl=context::structure::c_afterTag;
                    }
                } break;
                case context::structure::c_afterTag:{
                    out=context.processControl(control);
                    if (!out) {
                        element.currentControl=context::structure::c_betweenTagAndValue;
                    }
                } break;
                case context::structure::c_betweenTagAndValue:{
                    out=context.processControl(control);
                    if (!out) {
                        element.currentControl=context::structure::c_beforeValue;
                    }
                } break;
                case context::structure::c_beforeValue:{
                    out=context.processControl(control);
                    if (!out) {
                        element.currentControl=context::structure::c_processValue;
                    }
                } break;
                case context::structure::c_processValue:{
                    ict::reflect::type::index_t i;
                    if (element.getIndex(i)) {
                        out=process(object,context,i);
                        if (!out) {
                            element.currentControl=context::structure::c_afterValue;
                        }
                    } else {
                        out=-1;
                    }
                } break;
                case context::structure::c_afterValue:{
                    out=context.processControl(control);
                    if (!out) {
                        if (element.setNextElement()){
                            element.currentControl=context::structure::c_betweenElements;
                        } else {
                            element.currentControl=context::structure::c_afterStruct;
                        }
                    }
                } break;
                case context::structure::c_betweenElements:{
                    out=context.processControl(control);
                    if (!out) {
                        element.currentControl=context::structure::c_beforeTag;
                    }
                } break;
                case context::structure::c_afterStruct:{
                    out=context.processControl(control);
                    if (!out) {
                        element.currentControl=context::structure::c_theEnd;
                    }
                } break;
                case context::structure::c_theEnd:{
                    context.stack.leaveElement();
                    return 0;
                } break;
                default:{
                    out=-2;
                } break;
            }
        }
    } catch (const std::exception & e){
        out=-3;
    }
    context.stack.leaveElement();
    return(out);
}
*/
//===========================================
} } }
//============================================
#endif