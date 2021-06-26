//! @file
//! @brief Meta data module (vector) - header file.
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
#ifndef _REFLECT_META_VECTOR_HEADER
#define _REFLECT_META_VECTOR_HEADER
//============================================
#include "definition.hpp"
#include <vector>
#include <mutex>
//============================================
namespace ict { namespace  reflect { namespace  meta { 
//===========================================

//! Lista metadanych obiektu.
typedef std::vector<ict::reflect::type::meta_t> vector;

//! 
//! @brief Daje listę metadanych dla podanego obiektu.
//! 
//! @param object Obiekt wejściowy.
//! @return Lista metadanych dla obiektu.
//! 
template<typename Object> const vector & getVector(const Object & object){
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    static class : public ict::reflect::meta::interface {
    public:
        vector meta;
        void exec(
            const ict::reflect::type::index_t & index,
            ict::reflect::type::access_t accessType,
            const char * propName,
            const char * givenName
        ){
            meta.emplace_back(index,accessType,propName,givenName);
        }
    } mv;
    if (mv.meta.empty()){
        object.REFLECT_FUN_NAME(object,mv,mv);
    }
    return(mv.meta);
}

//===========================================
} } }
//============================================
#endif