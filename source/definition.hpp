//! @file
//! @brief Struct/class module - header file.
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
#ifndef _REFLECT_DEFINITION_HEADER
#define _REFLECT_DEFINITION_HEADER
//============================================
#include "meta.hpp"
//============================================
namespace ict { namespace  reflect { 
//===========================================

//! 
//! @brief Procesor, który przetwarza dane w obiekcie (object) używając podanego kontekstu typu ict::reflect::meta::interface (context) - wersja z modyfikacją obiektu.
//! 
//! @param object Obiekt, którego dane są przetwarzane.
//! @param context Kontekst przetwarzania.
//! @return int Zawsze zero.
//! 
template<typename Object> int processor(Object & object,ict::reflect::meta::interface & context){
    // Nic nie robi.
    return(0);
}
//! 
//! @brief Procesor, który przetwarza dane w obiekcie (object) używając podanego kontekstu typu ict::reflect::meta::interface (context) - wersja bez modyfikacji obiektu.
//! 
//! @param object Obiekt, którego dane są przetwarzane.
//! @param context Kontekst przetwarzania.
//! @return int Zawsze zero.
//! 
template<typename Object> int processor(const Object & object,ict::reflect::meta::interface & context){
    // Nic nie robi.
    return(0);
}

//! Nazwa funkcji do tworzenia metadanych w strukturze/klasie.
#define REFLECT_FUN_NAME _ict_reflect_definition_

//! Początek sekcji definiującej metadane w strukturze/klasie.
#define REFLECT_BEGIN \
    template<typename Object,class Context> static int REFLECT_FUN_NAME(\
        Object & object,\
        Context & context,\
        ict::reflect::meta::interface & meta,\
        ict::reflect::type::index_t index=0\
    ){\
        switch(index){\
            default:return(-1);\
            case 0:


//! Definicja metadanej składowej w strukturze/klasie.
#define REFLECT_PROP(access,prop,...)\
    case __LINE__: \
        if (index) \
            {return(ict::reflect::processor(object.prop,context));} \
        else \
            {meta.add(__LINE__,access,#prop,##__VA_ARGS__);};

//! Definicja metadanej składowej w strukturze/klasie - prywatna.
#define PRIVATE_PROP(...) REFLECT_PROP(ict::reflect::type::Private,__VA_ARGS__)

//! Definicja metadanej składowej w strukturze/klasie - chroniona.
#define PROTECTED_PROP(...) REFLECT_PROP(ict::reflect::type::Protected,__VA_ARGS__)

//! Definicja metadanej składowej w strukturze/klasie - publiczna.
#define PUBLIC_PROP(...) REFLECT_PROP(ict::reflect::type::Public,__VA_ARGS__)


//! Koniec sekcji definiującej metadane w strukturze/klasie.
#define REFLECT_END \
        }\
        return(0);\
    }

//===========================================
} }
//============================================
#endif