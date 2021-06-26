//! @file
//! @brief Meta data module - header file.
//! @author Mariusz Ornowski (mariusz.ornowski@ict-project.pl)
//! @version 1.0
//! @date 2012-2021
//! @copyright ICT-Project Mariusz Ornowski (ict-project.pl)
/* **************************************************************
Copyright (c) 2012-2021, ICT-Project Mariusz Ornowski (ict-project.pl)
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
#ifndef _REFLECT_META_HEADER
#define _REFLECT_META_HEADER
//============================================
#include "types.hpp"
//============================================
namespace ict { namespace  reflect { namespace  meta { 
//===========================================

class interface{
    public:
    //! 
    //! @brief Destruktor
    //! 
    virtual ~interface(){}
    //! 
    //! @brief Dodaje metadaną do listy - funkcja do nadpisania.
    //! 
    //! @param index Indeks składowej klasy.
    //! @param accessType Typ dostępu do składowej klasy.
    //! @param propName Nazwa składowej klasy w kodzie.
    //! @param givenName Nazwa składowej, która ma być efektywnie używana.
    //! 
    virtual void exec(
        const ict::reflect::type::index_t & index,
        ict::reflect::type::access_t accessType,
        const char * propName,
        const char * givenName
    ){}
    //! 
    //! @brief Dodaje metadaną do listy.
    //! 
    //! @param index Indeks składowej klasy.
    //! @param accessType Typ dostępu do składowej klasy.
    //! @param propName Nazwa składowej klasy w kodzie, która ma być efektywnie używana.
    //! @param givenName Nazwa składowej, która ma być efektywnie używana.
    //!
    void add(
        const ict::reflect::type::index_t & index,
        ict::reflect::type::access_t accessType,
        const char * propName,
        const char * givenName=nullptr
    ){
        exec(index,accessType,propName,givenName?givenName:propName);
    }
};

inline interface & empty(){
    static interface i;
    return(i);
};

//===========================================
} } }
//============================================
#endif