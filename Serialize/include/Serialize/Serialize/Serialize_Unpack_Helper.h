/*******************************************************************
*  Copyright(c) 2000-2017 SnailGame
*  All rights reserved.
*
*  文件: Serialize_Unpack_Helper.h
*  作者: luwei
*  日期: 2018/08/06
*  版本: 1.0
*  说明: 模块内部文件，不直接对外包含
******************************************************************/

#ifndef SERIALIZE_SERIALIZE_UNPACK_HELPER_H_  
#define SERIALIZE_SERIALIZE_UNPACK_HELPER_H_

#include "../../Serialize_API.h"
#include "../../Blueprint/I_Blueprint.h" 
#include "../../Blueprint/I_NodeObjectProperty.h"
#include "../ObjectFactory/Fs_ClsObject.h" 

#include <vector>
#include <xstring> 
#include <map>
#include <type_traits>

class Fs_ClsObject;

namespace Fs_Serialize
{
    template<typename T, typename _Ty = std::enable_if_t<!is_serialize<T>::value && !is_serialize_T<T>::value>>
    inline T* DeSerializerT(ISerializer* pSerialize, size_t& transId, Fs_Utility::IDataPropIterator* iter) {

        Fs_ClsObject* clsObj = pSerialize->StartOneDeSerialize(iter->GetObjectId(), transId);
        return clsObj->GetInstance<T>();
    }

    template<typename T, typename _Ty = std::enable_if_t<!is_serialize<T>::value && is_serialize_T<T>::value >>
    inline T* DeSerializerT(ISerializer* pSerialize, size_t& transId, Fs_Utility::IDataPropIterator*& iter) {

        using M = decltype(Fs_METAOBJECT_T(std::declval<T>()));
        auto creator = M::Register();
        if (!creator)
            return (T*)nullptr;

        Fs_ClsObject* clsObj = pSerialize->StartOneDeSerialize(iter->GetObjectId(), transId);
        return clsObj->GetInstance<T>();
    }

    template<typename T, typename _Ty = std::enable_if_t<is_serialize<T>::value>>
    inline T* DeSerializerT(ISerializer* pSerialize, size_t transId, Fs_Utility::IDataPropIterator* iter) {

        using M = decltype(std::declval<T>().Fs_METAOBJECT(std::declval<T>()));
        auto execr = M::Execr();
        auto creator = M::Register();
        if (!execr || !creator)
            return nullptr;

        Fs_ClsObject* clsObj = pSerialize->StartOneDeSerialize(iter->GetObjectId(), transId);
        return clsObj->GetInstance<T>();
    }
}

#endif  // SERIALIZE_SERIALIZE_UNPACK_HELPER_H_