//! @file
//! @brief Meta data module (vector) - Source file.
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
#include "meta-vector.hpp"
//============================================
namespace ict { namespace  reflect { namespace  meta { 
//============================================

//===========================================
} } }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"
#include <string>

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

REGISTER_TEST(meta_vector,tc1){
    int out=0;
    testowa_klasa test;
    ict::reflect::meta::getVector(test);
    if (ict::reflect::meta::getVector(test).size()!=3) return(-1);
    if (ict::reflect::meta::getVector(test).at(0).access!=ict::reflect::type::Private) return(-2);
    if (ict::reflect::meta::getVector(test).at(1).access!=ict::reflect::type::Protected) return(-3);
    if (ict::reflect::meta::getVector(test).at(2).access!=ict::reflect::type::Public) return(-4);
    if (std::string(ict::reflect::meta::getVector(test).at(0).propName)!="one") return(-5);
    if (std::string(ict::reflect::meta::getVector(test).at(1).propName)!="two") return(-6);
    if (std::string(ict::reflect::meta::getVector(test).at(2).propName)!="three") return(-7);
    if (std::string(ict::reflect::meta::getVector(test).at(0).givenName)!="one") return(-8);
    if (std::string(ict::reflect::meta::getVector(test).at(1).givenName)!="two") return(-9);
    if (std::string(ict::reflect::meta::getVector(test).at(2).givenName)!="trzy") return(-10);
    return(out);
}

#endif
//===========================================