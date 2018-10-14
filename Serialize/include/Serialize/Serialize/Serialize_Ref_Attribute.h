/*******************************************************************
 *  Copyright(c) 2000-2017 SnailGame
 *  All rights reserved.
 *
 *  �ļ�: Serialize_Ref_Attribute.h
 *  ����: luwei
 *  ����: 2018/08/06
 *  �汾: 1.0
 *  ˵��: ģ���ڲ��ļ�����ֱ�Ӷ������
 ******************************************************************/

#ifndef SERIALIZE_SERIALIZE_REF_ATTRIBUTE_H_  
#define SERIALIZE_SERIALIZE_REF_ATTRIBUTE_H_

#include "../Traits.h"          
#include "../../I_Serialize.h"
#include "Serialize_Micro.h"

#include <vector>
#include <xstring> 
#include <type_traits> 
#include <utility>
#include <sstream>

namespace Fs_Serialize
{
    class SerializeRefAttribute
    {
    public:
        template<typename _Ret, typename T, typename _Ty = std::enable_if_t<!is_serialize<T>::value && !is_serialize_T<T>::value>>
        inline _Ret* Pointer2ObjectAttribute(const char*, T*&&) { return (_Ret*)nullptr; }
        template<typename _Ret, typename T, typename _Ty = std::enable_if_t<!is_serialize<T>::value && is_serialize_T<T>::value>>
        inline _Ret* Pointer2ObjectAttribute(const char*&, T*) { return (_Ret*)nullptr; }

        //
        template<typename _Ret, typename T, typename _Ty = std::enable_if_t<is_serialize<T>::value>>
        inline _Ret* Pointer2ObjectAttribute(const char* pName, T* t)
        {
            //
            _Ret* pRetPtr = nullptr;

            // ��ȡԪ��������
            using M = decltype(T::Fs_METAOBJECT(std::forward<T>(*t)));
            
            // ��ȡԪ���ݳ�Ա����
            constexpr auto Size = M::value();

            // ��ȡ����
            auto index = GetIndex<T>(pName);
            if (index < 0 || index >= Size)
                return pRetPtr;

            // ��ȡԪ����
            auto valTuple = M::staticMetaObject();

            //
            TupleAt(index, valTuple, [&](auto& v) { pRetPtr = &(t->*v); }, std::make_index_sequence<Size>{});

            return pRetPtr;
        }

        SerializeRefAttribute() {
        }
    };
}

#endif  // SERIALIZE_SERIALIZE_REF_ATTRIBUTE_H_