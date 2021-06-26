//! @file
//! @brief Struct/class definition module - Source file.
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
//============================================
#include "definition.hpp"
//============================================
namespace ict { namespace  reflect {  
//============================================

//===========================================
} }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"

class testowa_klasa {
private:
    int one;
protected:
    float two;
public:
    double three;

REFLECT_BEGIN
    PRIVATE_PROP(one)
    PROTECTED_PROP(two)
    PUBLIC_PROP(three,"trzy")
REFLECT_END
};

class testowa_meta: public ict::reflect::meta::interface{
public:
    void exec(
        const ict::reflect::type::index_t & index,
        ict::reflect::type::access_t accessType,
        const char * propName,
        const char * givenName
    ){
        std::cout<<"index="<<index<<","<<"accessType="<<(int)accessType<<","<<"propName="<<propName<<","<<"givenName="<<givenName<<std::endl;
    }
};

REGISTER_TEST(definition,tc1){
    int out=0;
    testowa_klasa test;
    testowa_meta meta;
    test.REFLECT_FUN_NAME(test,meta,meta);
    return(out);
}

#endif
//===========================================