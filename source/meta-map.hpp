//! @file
//! @brief Meta data module (map) - header file.
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
#ifndef _REFLECT_META_MAP_HEADER
#define _REFLECT_META_MAP_HEADER
//============================================
#include "definition.hpp"
#include <map>
#include <mutex>
#include <string>
//============================================
namespace ict { namespace  reflect { namespace  meta { 
//===========================================

//! Mapa metadanych obiektu uporządkowana po indeksie.
typedef std::map<ict::reflect::type::index_t,ict::reflect::type::meta_t> mapByIndex;
//! Mapa metadanych obiektu uporządkowana po nazwie.
typedef std::map<std::string,ict::reflect::type::meta_t> mapByName;

//! 
//! @brief Daje mapę metadanych uporządkowana po indeksie dla podanego obiektu.
//! 
//! @param object Obiekt wejściowy.
//! @return Mapa metadanych uporządkowana po indeksie.
//! 
template<typename Object> const mapByIndex & getMapByIndex(const Object & object){
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    static class : public ict::reflect::meta::interface {
    public:
        mapByIndex meta;
        void exec(
            const ict::reflect::type::index_t & index,
            ict::reflect::type::access_t accessType,
            const char * propName,
            const char * givenName
        ){
            meta[index]={index,accessType,propName,givenName};
        }
    } mv;
    if (mv.meta.empty()){
        object.REFLECT_FUN_NAME(object,mv,mv);
    }
    return(mv.meta);
}

//! 
//! @brief Daje mapę metadanych uporządkowana po nazwie w kodzie dla podanego obiektu.
//! 
//! @param object Obiekt wejściowy.
//! @return Mapa metadanych uporządkowana po nazwie w kodzie.
//! 
template<typename Object> const mapByName & getMapByPropName(const Object & object){
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    static class : public ict::reflect::meta::interface {
    public:
        mapByName meta;
        void exec(
            const ict::reflect::type::index_t & index,
            ict::reflect::type::access_t accessType,
            const char * propName,
            const char * givenName
        ){
            meta[propName]={index,accessType,propName,givenName};
        }
    } mv;
    if (mv.meta.empty()){
        object.REFLECT_FUN_NAME(object,mv,mv);
    }
    return(mv.meta);
}

//! 
//! @brief Daje mapę metadanych uporządkowana po nazwie dla podanego obiektu.
//! 
//! @param object Obiekt wejściowy.
//! @return Mapa metadanych uporządkowana po nazwie.
//!
template<typename Object> const mapByName & getMapByGivenName(const Object & object){
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    static class : public ict::reflect::meta::interface {
    public:
        mapByName meta;
        void exec(
            const ict::reflect::type::index_t & index,
            ict::reflect::type::access_t accessType,
            const char * propName,
            const char * givenName
        ){
            meta[givenName]={index,accessType,propName,givenName};
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