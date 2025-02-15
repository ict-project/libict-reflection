//! @file
//! @brief Array context module - Source file.
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
//============================================
#include "processor-array.hpp"
#include <sstream>
//============================================
namespace ict { namespace  reflect {  namespace context { 
//============================================
bool Array::index2name(const ict::reflect::type::index_t & index, std::string & name){
    try {
        std::ostringstream stream;
        stream<<std::dec<<index;
        name=stream.str();
        return true;
    } catch(...){}
    return false;
}
bool Array::name2index(const std::string & name, ict::reflect::type::index_t & index){
    try {
        std::istringstream stream(name);
        stream>>std::dec>>index;
        return true;
    } catch(...){}
    return false;
}
bool Array::setIndex(const ict::reflect::type::index_t & i){
    if (size()<=i) {
        resize(i+1);
        if (size()<=i) {
            return false;
        }
    }
    index=i;
    if (!index2name(index,name)){
        return false;
    }
    return true;
}
bool Array::getIndex(ict::reflect::type::index_t & i) const{
    i=index;
    return true;
}
bool Array::setName(const std::string & n){
    if (!name2index(n,index)){
        return false;
    }
    if (!index2name(index,name)){
        return false;
    }
    return true;
}
bool Array::getName(std::string & n) const{
    n=name;
    return false;
}
bool Array::setFirstElement(){
    if (size()==0) return false;
    if (options&optionDescending){
        index=size()-1;
    } else {
        index=0;
    }
    if (!index2name(index,name)){
        return false;
    }
    return true;
}
bool Array::setNextElement(){
    if (size()==0) return false;
    if (options&optionDescending){
        if (0<index){
            index--;
            if (!index2name(index,name)){
                return false;
            }
            return true;
        }
    } else {
        if ((index+1)<size()) {
            index++;
            if (!index2name(index,name)){
                return false;
            }
            return true;
        }
    }
    return false;
}
//===========================================
} } }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"

#endif
//===========================================