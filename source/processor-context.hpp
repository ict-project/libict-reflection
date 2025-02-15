//! @file
//! @brief Generic contex module - header file.
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
#ifndef _REFLECT_PROCESSOR_CONTEX_HEADER
#define _REFLECT_PROCESSOR_CONTEX_HEADER
//============================================
#include "types.hpp"
#include <string>
#include <vector>
#include <memory>
//============================================
namespace ict { namespace  reflect { namespace context {
//============================================
typedef uint16_t Options;
enum Control{
    s_beforeStruct=0x1<<0,
    s_beforeTag=0x1<<1,
    s_processTag=0x1<<2,
    s_afterTag=0x1<<3,
    s_betweenTagAndValue=0x1<<4,
    s_beforeValue=0x1<<5,
    s_processValue=0x1<<6,
    s_afterValue=0x1<<7,
    s_betweenElements=0x1<<8,
    s_afterStruct=0x1<<9,
    s_theEnd=0x1<<10,
    a_beforeArray=0x1<<11,
    a_beforeValue=0x1<<12,
    a_processValue=0x1<<13,
    a_afterValue=0x1<<14,
    a_betweenElements=0x1<<15,
    a_afterArray=0x1<<16,
    a_theEnd=0x1<<17
};
//! Interfejs kontekstu obiektu.
class Interface{
protected:
    const Options & options;
    ict::reflect::type::index_t currentIndex=0;
public:
    //! 
    //! @brief Konstruktor.
    //! 
    //! @param o Opcje kontekstu.
    //! 
    Interface(const Options & o):options(o){}
    //! Desutruktor.
    virtual ~Interface(){}
    //! Aktualna faza w kontekście.
    Control currentControl=s_beforeStruct;
    //! 
    //! @brief Ustawia indeks elementu obiektu o podanej nazwie.
    //! 
    //! @param index Indeks elementu obiektu.
    //! @return true Sukces.
    //! @return false Porażka.
    //! 
    virtual bool setIndex(const ict::reflect::type::index_t & index)=0;
    //! 
    //! @brief Pobiera indeks aktualnego (w danym kontekście) elementu obiektu.
    //! 
    //! @param index Indeks aktualnego (w danym kontekście) elementu obiektu. 
    //! @return true Sukces.
    //! @return false Porażka.
    //! 
    virtual bool getIndex(ict::reflect::type::index_t & index) const =0;
    //! 
    //! @brief Ustawia kontekst elementu obiektu o podanej nazwie.
    //! 
    //! @param name Nazwa elementu obiektu. 
    //! @return true Sukces.
    //! @return false Porażka.
    //!
    virtual bool setName(const std::string & name)=0;
    //! 
    //! @brief Pobiera nazwę aktualnego (w danym kontekście) elementu obiektu.
    //! 
    //! @param name Nazwa aktualnego (w danym kontekście) elementu obiektu. 
    //! @return true Sukces.
    //! @return false Porażka.
    //! 
    virtual bool getName(std::string & name) const=0;
    //! 
    //! @brief Ustawia kontekst na pierwszy element obiektu.
    //! 
    //! @return true Sukces.
    //! @return false Porażka.
    //! 
    virtual bool setFirstElement()=0;
    //! 
    //! @brief Ustawia kontekst na następny element obiektu.
    //! 
    //! @return true Sukces.
    //! @return false Porażka.
    //! 
    virtual bool setNextElement()=0;
    //! 
    //! @brief Zwraca informację, czy aktualny kontekst dotyczy obiektu typu Array.
    //! 
    //! @return true Dotyczy obiektu typu Array.
    //! @return false Dotyczy obiektu typy Structure.
    //! 
    virtual bool isArray()=0;
};
//! Fabryka kontekstów.
class Factory{
public:
    //! Destruktor.
    virtual ~Factory(){}
    //! Tworzy nowy kontekst dla elementu, który jest aktualnie przetwarzany.
    virtual Interface * get(const Options & o) const=0;
};
//! Stos kontekstów (dla zagnieżdżonych obiektów).
class Stack{
private:
    //! Typ stosu kontekstów.
    typedef std::vector<std::unique_ptr<Interface>> stack_t;
    //! Stos kontekstów.
    stack_t stack;
    //! Opcje z jakimi tworzone są konteksty na stosie.
    const Options options;
    //! Aktualny poziom stosu kontekstów.
    std::size_t level=0;
    //! 
    //! @brief Dostęp do kontekstu na aktualnym poziomie.
    //! 
    //! @return Interface& Interfejs kontekstu.
    //! 
    Interface & accessElement() const {
        return *stack.at(level-1);
    }
    //! 
    //! @brief Dostęp do kontekstu na aktualnym poziomie.
    //! 
    //! @return Interface& Interfejs kontekstu.
    //! 
    Interface & accessElement() {
        return *stack[level-1];
    }
public:
    //! 
    //! @brief Konstruktor.
    //! 
    //! @param o Opcje z jakimi mają być tworzone konteksty
    //! 
    Stack(const Options & o):options(o){}
    //! 
    //! @brief Przejście na wyższy poziom stosu kontekstów.
    //! 
    //! @param factory Frabryka, która jest używana do tworzenia nowego kontekstu, jeśli nie ma wyższego poziomu stosu.
    //! 
    void enterElement(const Factory & factory);
    //! 
    //! @brief Przejście na niższy poziom stosu kontekstów.
    //! 
    void leaveElement();
    //! Patrz: ict::reflect::context::Interface::setIndex()
    bool setIndex(const ict::reflect::type::index_t & index){
        return accessElement().setIndex(index);
    }
    //! Patrz: ict::reflect::context::Interface::getIndex()
    bool getIndex(ict::reflect::type::index_t & index) const{
        return accessElement().getIndex(index);
    }
    //! Patrz: ict::reflect::context::Interface::setName()
    bool setName(const std::string & name){
        return accessElement().setName(name);
    }
    //! Patrz: ict::reflect::context::Interface::getName()
    bool getName(std::string & name) const {
        return accessElement().getName(name);
    }
    //! Patrz: ict::reflect::context::Interface::setFirstElement()
    bool setFirstElement(){
        return accessElement().setFirstElement();
    }
    //! Patrz: ict::reflect::context::Interface::setNextElement()
    bool setNextElement(){
        return accessElement().setNextElement();
    }
    //! Patrz: ict::reflect::context::Interface::isArray()
    bool isArray(){
        return accessElement().isArray();
    }
    //! 
    //! @brief Dostęp do fazy aktualnego kontekstu w stosie.
    //! 
    //! @return Control& Faza aktualnego kontekstu w stosie.
    //! 
    Control & accessControl(){
        return accessElement().currentControl;
    }
};
//============================================
} } }
//============================================
#endif