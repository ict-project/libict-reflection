//! @file
//! @brief Array context module - header file.
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
#ifndef _REFLECT_PROCESSOR_ARRAY_HEADER
#define _REFLECT_PROCESSOR_ARRAY_HEADER
//============================================
#include "processor-context.hpp"
#include <exception>
//============================================
namespace ict { namespace  reflect { namespace context {
//============================================
class Array: public Interface {
private:
    //! Aktualny indeks.
    ict::reflect::type::index_t index=0;
    //! Aktualna nazwa.
    std::string name="0";
    //! 
    //! @brief Zamienia indeks na nazwę.
    //! 
    //! @param index Indeks do zmiany.
    //! @param name Nazwa na podstawie indeksu.
    //! @return true Sukces.
    //! @return false Porażka.
    //! 
    static bool index2name(const ict::reflect::type::index_t & index, std::string & name);
    //! 
    //! @brief Zamienia nazwę na indeks.
    //! 
    //! @param name Nazwa do zmiany.
    //! @param index Indeks na podstawie nazwy.
    //! @return true Sukces.
    //! @return false Porażka.
    //! 
    static bool name2index(const std::string & name, ict::reflect::type::index_t & index);
protected:
    //! 
    //! @brief Zwraca rozmiar.
    //! 
    //! @return Rozmiar.
    //! 
    virtual std::size_t size()=0;
    //! 
    //! @brief Zmienia rozmiar.
    //! 
    //! @param s Nowy rozmiar.
    //! 
    virtual void resize(const std::size_t & s)=0;
public:
    //! 
    //! @brief Konstruktor.
    //! 
    //! @param o Opcje kontekstu.
    //! 
    Array(const Options & o):
        Interface(o){
        setFirstElement();
    }
    //! Opcja ustawiająca sortowanie w kierunku malejącym (w przeciwnym wypadku jest w kierunku rosnącym).
    const static Options optionDescending=0x1<<2;
    //! Destruktor.
    virtual ~Array(){}
    //! Patrz: ict::reflect::context::Interface::setIndex()
    bool setIndex(const ict::reflect::type::index_t & i);
    //! Patrz: ict::reflect::context::Interface::getIndex()
    bool getIndex(ict::reflect::type::index_t & i) const;
    //! Patrz: ict::reflect::context::Interface::setName()
    bool setName(const std::string & n);
    //! Patrz: ict::reflect::context::Interface::getName()
    bool getName(std::string & n) const;
    //! Patrz: ict::reflect::context::Interface::setFirstElement()
    bool setFirstElement();
    //! Patrz: ict::reflect::context::Interface::setNextElement()
    bool setNextElement();
    //! Patrz: ict::reflect::context::Interface::isArray()
    bool isArray(){
        return true;
    }
};
//===========================================
} } }
//============================================
#endif