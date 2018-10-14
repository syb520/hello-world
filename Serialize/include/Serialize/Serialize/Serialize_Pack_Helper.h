/*******************************************************************
*  Copyright(c) 2000-2017 SnailGame
*  All rights reserved.
*
*  文件: Serialize_Pack_Helper.h
*  作者: luwei
*  日期: 2018/08/06
*  版本: 1.0
*  说明: 模块内部文件，不直接对外包含
******************************************************************/

#ifndef SERIALIZE_SERIALIZE_PACK_HELPER_H_  
#define SERIALIZE_SERIALIZE_PACK_HELPER_H_

#include "../Traits.h"           
#include "../../Serialize_API.h"
#include "../ObjectFactory/Fs_ClsObject.h" 

#include <vector>
#include <xstring> 
#include <type_traits> 
#include <utility>

class Fs_ClsObject;

namespace Fs_Serialize
{

    template<typename T, typename _Ty = std::enable_if_t<!is_serialize<T>::value && !is_serialize_T<T>::value>>
    void SerializerT(ISerializerApi* pApi, Fs_Utility::IDataProp*& prop, T*& val, std::size_t transId) {

        Fs_ClsObject* clsObj = pApi->GetObjectManager()->FindObjectByInstanceId(size_t(val));
        if (!clsObj)
            return;

        prop->m_ClsId = clsObj->ClassId();
        prop->m_ObjId = clsObj->ObjectId();

        pApi->GetSerializer()->StartOneSerialize(clsObj->ObjectId(), transId);
    }

    template<typename T, typename _Ty = std::enable_if_t<!is_serialize<T>::value && is_serialize_T<T>::value >>
    void SerializerT(ISerializerApi* pApi, Fs_Utility::IDataProp*& prop, T* val, std::size_t transId) {

        using M = decltype(Fs_METAOBJECT_T(std::declval<T>())); 
        auto execr = M::Execr();
        if (!execr)
            return;

        Fs_ClsObject* clsObj = execr->InitObject(pApi, val);
        if (!clsObj)
            return;

        prop->m_ClsId = clsObj->ClassId();
        prop->m_ObjId = clsObj->ObjectId();

        pApi->GetSerializer()->StartOneSerialize(clsObj->ObjectId(), transId);
    }

    template<typename T, typename _Ty = std::enable_if_t<is_serialize<T>::value>>
    void SerializerT(ISerializerApi* pApi, Fs_Utility::IDataProp* prop, T* val, std::size_t transId) {

        using M = decltype(std::declval<T>().Fs_METAOBJECT(std::declval<T>()));
        auto execr = M::Execr();
        if (!execr)
            return;

        Fs_ClsObject* clsObj = execr->InitObject(pApi, val);
        if (!clsObj)
            return;

        prop->m_ClsId = clsObj->ClassId();
        prop->m_ObjId = clsObj->ObjectId();

        pApi->GetSerializer()->StartOneSerialize(clsObj->ObjectId(), transId);
    }

}

#endif // SERIALIZE_SERIALIZE_PACK_HELPER_H_