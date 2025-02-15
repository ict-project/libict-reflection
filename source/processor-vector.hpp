//! @file
//! @brief Vector context module - header file.
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
#ifndef _REFLECT_PROCESSOR_VECTOR_HEADER
#define _REFLECT_PROCESSOR_VECTOR_HEADER
//============================================
#include "processor-array.hpp"
#include <vector>
#include <exception>
//============================================
namespace ict { namespace  reflect { namespace context {
//============================================
template <class T, class Allocator> class VectorTemplate;
class Vector: public Array {
private:
    //! 
    //! @brief Konstruktor.
    //! 
    //! @param o Opcje kontekstu.
    //! 
    Vector(const Options & o):
        Array(o){}
    //! Fabryka kontekstów.
    template <class _T, class _Allocator> class _Factory : public Factory {
    private:
        typedef std::vector<_T,_Allocator> vector_t;
        //! Referencja do obiektów.
        vector_t & vector;
    public:
        //! Konstruktor.
        _Factory(vector_t & v):vector(v){}
        //! Patrz: ict::reflect::context::Factory::get()
        Interface * get(const Options & options) const {
            return new VectorTemplate(vector,options);
        }
    };
public:
    //! 
    //! @brief Dostęp do fabryki kontekstów dla danego wektora.
    //! 
    //! @param vector Wektor, dla którego ma być stworzony kontekst.
    //! @return Referencja do fabryki.
    //! 
    template <class _T, class _Allocator> friend const Factory & factory(std::vector<_T,_Allocator> & vector){
        static const _Factory f(vector);
        return f;
    }
    ~Vector(){}
};
template <class T, class Allocator> class VectorTemplate: public Vector {
private:
    typedef std::vector<T,Allocator> vector_t;
    vector_t vector;
    VectorTemplate(vector_t & v,const Options & o):
        vector(v),
        Vector(o){
    }
    std::size_t size(){
        return vector.size();
    }
    void resize(const std::size_t & s){
        vector.resize(s);
    }
public:
    ~VectorTemplate(){}
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