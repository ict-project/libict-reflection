//! @file
//! @brief Object processing module - Source file.
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
#include "process.hpp"
//============================================
namespace ict { namespace  reflect {
//============================================

//===========================================
} }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"
#include "meta-vector.hpp"

class testowy_kontekst {
    int cos;
};

namespace ict { namespace  reflect {

int processor(const int & object,testowy_kontekst & context){
    std::cout<<"To jest int = "<<object<<std::endl;
    return(0);
}

int processor(const float & object,testowy_kontekst & context){
    std::cout<<"To jest float = "<<object<<std::endl;
    return(0);
}

int processor(const double & object,testowy_kontekst & context){
    std::cout<<"To jest double = "<<object<<std::endl;
    return(0);
}

template<typename Object> int processor(const Object & object,testowy_kontekst & context){
    std::cout<<"To jest object"<<std::endl;
    for (const auto m : ict::reflect::meta::getVector(object)){
        std::cout<<"index="<<m.index<<","<<"access="<<(int)m.access<<","<<"propName="<<m.propName<<","<<"givenName="<<m.givenName<<std::endl;
        int out=ict::reflect::process(object,context,m.index);
        if (out) return(out);
    }
    return(0);
}

}}

class testowa_klasa1 {
private:
    int one=1;
protected:
    float two=2;
public:
    double three=3;

REFLECT_BEGIN
    PRIVATE_PROP(one)
    PROTECTED_PROP(two)
    PUBLIC_PROP(three,"trzy")
REFLECT_END
};

class testowa_klasa2 {
private:
    int one=4;
protected:
    float two=5;
public:
    testowa_klasa1 three;

REFLECT_BEGIN
    PRIVATE_PROP(one)
    PROTECTED_PROP(two)
    PUBLIC_PROP(three,"obiekt")
REFLECT_END
};

REGISTER_TEST(process,tc1){
    int out=0;
    testowa_klasa2 test;
    testowy_kontekst kontekst;
    return(ict::reflect::processor(test,kontekst));
}

#endif
//===========================================