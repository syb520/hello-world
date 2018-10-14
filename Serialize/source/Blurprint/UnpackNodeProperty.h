/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: UnpackNodeProperty.h
 *  作者: luwei
 *  日期: 2018/09/20
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_UNPACKNODEPROPERTY_H_  
#define SERIALIZE_UNPACKNODEPROPERTY_H_

#include "../../Include/I_Data.h" 
#include "../../Include/I_Data_Helper.h" 
#include "../../../Blueprint/include/trigger_system_type.h"

#include <type_traits>

namespace Fs_Blueprint {

    class BlueprintUnpackValue
    {
    public:

        template<typename T>
        inline std::enable_if_t<std::is_same<T, TriggerBoolean>::value> UnpackValue(Fs_Utility::IDataPropIterator* pIter, T*& val) {

        }

        template<typename T>
        inline std::enable_if_t<std::is_same<T, TriggerInt>::value> UnpackValue(Fs_Utility::IDataPropIterator* pIter, T*& val) {
            val->SetInt(pIter->GetValue().ToInt());
        }

        template<typename T>
        inline std::enable_if_t<std::is_same<T, TriggerInt64>::value> UnpackValue(Fs_Utility::IDataPropIterator* pIter, T*& val) {

        }

        template<typename T>
        inline std::enable_if_t<std::is_same<T, TriggerFloat>::value> UnpackValue(Fs_Utility::IDataPropIterator* pIter, T*& val) {

        }

        template<typename T>
        inline std::enable_if_t<std::is_same<T, TriggerDouble>::value> UnpackValue(Fs_Utility::IDataPropIterator* pIter, T*& val) {

        }

        template<typename T>
        inline std::enable_if_t<std::is_same<T, TriggerString>::value> UnpackValue(Fs_Utility::IDataPropIterator* pIter, T*& val) {

        }

        template<typename T>
        inline std::enable_if_t<std::is_same<T, TriggerWString>::value> UnpackValue(Fs_Utility::IDataPropIterator* pIter, T*& val) {

        }

        template<typename T>
        inline std::enable_if_t<std::is_same<T, Fs_ArrayNodeProperty>::value> UnpackValue(Fs_Utility::IDataPropIterator* pIter, T*& val) {

        }

        template<typename T>
        inline std::enable_if_t<std::is_same<T, Fs_SetNodeProperty>::value> UnpackValue(Fs_Utility::IDataPropIterator* pIter, T*& val) {

        }

        template<typename T>
        inline std::enable_if_t<std::is_same<T, Fs_MapNodeProperty>::value> UnpackValue(Fs_Utility::IDataPropIterator* pIter, T*& val) {

        }

        template<typename T>
        inline std::enable_if_t<std::is_same<T, Fs_ObjectNodeProperty>::value> UnpackValue(Fs_Utility::IDataPropIterator* pIter, T*& val) {

            if (!pIter || !pIter->GetDataProp())
                return;

            Fs_ClsObject* clsObj = m_Serializer->StartOneDeSerialize(pIter->GetObjectId(), m_TransId);
            Fs_ClsObjectNodeProperty* clsObjNode = 
                (Fs_ClsObjectNodeProperty*)m_BlueprintApi->CreateNodeProperty(Fs_ObjectNodeProperty_Type);
            clsObjNode->AttachClsObject(clsObj);
            val = clsObjNode;
        }

        BlueprintUnpackValue(Fs_Serialize::ISerializer* pSerializer, IBlueprintApi* pBlueprintApi, std::size_t t)
            : m_Serializer(pSerializer), m_BlueprintApi(pBlueprintApi), m_TransId(t) {
        }

    private:
        std::size_t m_TransId;
        Fs_Serialize::ISerializer* m_Serializer;
        IBlueprintApi* m_BlueprintApi;
    };
}


#endif  // SERIALIZE_UNPACKNODEPROPERTY_H_