//! @file
//! @brief Structure context module - Source file.
//! @author Mariusz Ornowski (mariusz.ornowski@ict-project.pl)
//! @version 1.0
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
#include "processor-structure.hpp"
//============================================
namespace ict { namespace  reflect {  namespace context { 
//============================================
bool Structure::setIndex(const ict::reflect::type::index_t & index){
    if (byIndex.count(index)) {
        currentIndex=index;
        return true;
    }
    return false;
}
bool Structure::getIndex(ict::reflect::type::index_t & index) const {
    index=currentIndex;
    return true;
}
bool Structure::setName(const std::string & name){
    if (byName.count(name)) {
        currentIndex=byName.at(name).index;
        return true;
    }
    return false;
}
bool Structure::getName(std::string & name) const {
    if (byIndex.count(currentIndex)) {
        name=byIndex.at(currentIndex).givenName;
        return true;
    }
    return false;
}
bool Structure::setFirstElement(){
    switch(options&(optionByIndex||optionDescending)){
        case optionByIndex:{
            iterator.itAscByIndex=byIndex.cbegin();
            if (iterator.itAscByIndex!=byIndex.cend()){
                currentIndex=iterator.itAscByIndex->second.index;
                return true;
            }
        } break;
        case optionByIndex&optionDescending:{
            iterator.itDescByIndex=byIndex.crbegin();
            if (iterator.itDescByIndex!=byIndex.crend()){
                currentIndex=iterator.itDescByIndex->second.index;
                return true;
            }
        } break;
        case optionDescending:{
            iterator.itDescByName=byName.crbegin();
            if (iterator.itDescByName!=byName.crend()){
                currentIndex=iterator.itDescByName->second.index;
                return true;
            }
        } break;
        default:{
            iterator.itAscByName=byName.cbegin();
            if (iterator.itAscByName!=byName.cend()){
                currentIndex=iterator.itAscByName->second.index;
                return true;
            }
        } break;
    }
    return false;
}
bool Structure::setNextElement(){
    switch(options&(optionByIndex||optionDescending)){
        case optionByIndex:{
            if (iterator.itAscByIndex!=byIndex.cend()) iterator.itAscByIndex++;
            if (iterator.itAscByIndex!=byIndex.cend()){
                currentIndex=iterator.itAscByIndex->second.index;
                return true;
            }
        } break;
        case optionByIndex&optionDescending:{
            if (iterator.itDescByIndex!=byIndex.crend()) iterator.itDescByIndex++;
            if (iterator.itDescByIndex!=byIndex.crend()){
                currentIndex=iterator.itDescByIndex->second.index;
                return true;
            }
        } break;
        case optionDescending:{
            if (iterator.itDescByName!=byName.crend()) iterator.itDescByName++;
            if (iterator.itDescByName!=byName.crend()){
                currentIndex=iterator.itDescByName->second.index;
                return true;
            }
        } break;
        default:{
            if (iterator.itAscByName!=byName.cend()) iterator.itAscByName++;
            if (iterator.itAscByName!=byName.cend()){
                currentIndex=iterator.itAscByName->second.index;
                return true;
            }
        } break;
    }
    return false;
}
//===========================================
} } }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"
#include "definition.hpp"
#include <sstream>
/*
struct TestContext234: public ict::reflect::context::structure::Context<> {
    int processControl(const ict::reflect::context::structure::Control & control){
        switch (control){
            case ict::reflect::context::structure::c_beforeStruct:
                s<<"c_beforeStruct";
                break;
            case ict::reflect::context::structure::c_beforeTag:
                s<<"c_beforeTag";
                break;
            case ict::reflect::context::structure::c_processTag:
                s<<"c_processTag";
                break;
            case ict::reflect::context::structure::c_afterTag:
                s<<"c_afterTag";
                break;
            case ict::reflect::context::structure::c_betweenTagAndValue:
                s<<"c_betweenTagAndValue";
                break;
            case ict::reflect::context::structure::c_beforeValue:
                s<<"c_beforeValue";
                break;
            case ict::reflect::context::structure::c_processValue:
                s<<"c_processValue";
                break;
            case ict::reflect::context::structure::c_afterValue:
                s<<"c_afterValue";
                break;
            case ict::reflect::context::structure::c_betweenElements:
                s<<"c_betweenElements";
                break;
            case ict::reflect::context::structure::c_afterStruct:
                s<<"c_afterStruct";
                break;
            default:return -1;
        }
        s<<" ";
        return 0;
    }
    int processControl(ict::reflect::context::structure::Control & control){
        return 0;
    }
    std::stringstream s;
};

namespace ict { namespace  reflect {  
int processor(int & object,TestContext234 & context){
    return 0;
}
int processor(const int & object,TestContext234 & context){
    return 0;
}
int processor(float & object,TestContext234 & context){
    return 0;
}
int processor(const float & object,TestContext234 & context){
    return 0;
}
int processor(std::string & object,TestContext234 & context){
    return 0;    
}
int processor(const std::string & object,TestContext234 & context){
    return 0;
}
}}

struct TestStruct038433{
    int jeden;
    float dwa;
    std::string trzy;
    REFLECT_BEGIN
        PUBLIC_PROP(jeden)
        PUBLIC_PROP(dwa)
        PUBLIC_PROP(trzy)
    REFLECT_END
};

REGISTER_TEST(processor_struct,tc1){
    int out=0;
    TestContext234 testContext234;
    //TestStruct038433 test82726={1,2.3,"4"};
    const TestStruct038433 test53683={1,2.3,"4"};
    ict::reflect::processor(test53683,testContext234);
    return(out);
}
*/
#endif
//===========================================