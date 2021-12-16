//! @file
//! @brief Types module - header file.
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
#ifndef _REFLECT_TYPES_HEADER
#define _REFLECT_TYPES_HEADER
//============================================
#include <cstdint>
#include <cstddef>
//============================================
namespace ict { namespace  reflect { namespace  type { 
//===========================================

//! Typ indeksu składowej klasy.
typedef std::size_t index_t;
//! Typ dostępu składowej klasy.
typedef std::uint8_t access_t;

struct meta_t {
    index_t index;
    access_t access;
    const char * propName;
    const char * givenName;
    meta_t(const index_t & i,access_t a,const char * pN,const char * gN):
        index(i),access(a),propName(pN),givenName(gN){}
    meta_t():
        index(0),access(0),propName(nullptr),givenName(nullptr){}
};

//! Dostęp prywatny.
const access_t Private(0x1<<0);
//! Dostęp ograniczony (chroniony).
const access_t Protected(0x1<<1);
//! Dostęp publiczny.
const access_t Public(0x1<<2);

//! Dostępy ograniczony (chroniony) i publiczny.
const access_t notPrivate(Protected|Public);
//! Dostępy prywatny i publiczny.
const access_t notProtected(Private|Public);
//! Dostępy prywatny i ograniczony (chroniony).
const access_t notPublic(Private|Protected);

//! Dostępy prywatny, ograniczony (chroniony) i publiczny.
const access_t All(Private|Protected|Public);
//! Dostęp żaden.
const access_t None(0);

//===========================================
} } }
//============================================
#endif