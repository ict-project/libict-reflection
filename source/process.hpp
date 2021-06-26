//! @file
//! @brief Object processing module - header file.
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
#ifndef _REFLECT_PROCESS_HEADER
#define _REFLECT_PROCESS_HEADER
//============================================
#include "definition.hpp"
//============================================
namespace ict { namespace  reflect { 
//===========================================

//! 
//! @brief Funkcja uruchamiająca przetwarzanie dla danego kontekstu (context) na wskazanej indeksem (index) składowej obiektu - wersja z modyfikacją obiektu.
//! 
//! @param object Obiekt, którego składowa jest przetwarzana.
//! @param context Kontekst przetwarzania.
//! @param index Indeks składowej, która jest przetwarzana.
//! @return Rezultat przetwarzania.
//! 
template<typename Object,class Context> int process(Object & object,Context & context,const ict::reflect::type::index_t & index){
    if (index) return(object.REFLECT_FUN_NAME(object,context,ict::reflect::meta::empty(),index));
    return(-2);
}

//! 
//! @brief Funkcja uruchamiająca przetwarzanie dla danego kontekstu (context) na wskazanej indeksem (index) składowej obiektu - wersja bez modyfikacji obiektu.
//! 
//! @param object Obiekt, którego składowa jest przetwarzana.
//! @param context Kontekst przetwarzania.
//! @param index Indeks składowej, która jest przetwarzana.
//! @return Rezultat przetwarzania.
//! 
template<typename Object,class Context> int process(const Object & object,Context & context,const ict::reflect::type::index_t & index){
    if (index) return(object.REFLECT_FUN_NAME(object,context,ict::reflect::meta::empty(),index));
    return(-2);
}

//===========================================
} }
//============================================
#endif