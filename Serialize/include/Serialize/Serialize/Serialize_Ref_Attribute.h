/*******************************************************************
 *  Copyright(c) 2000-2017 SnailGame
 *  All rights reserved.
 *
 *  文件: Serialize_Ref_Attribute.h
 *  作者: luwei
 *  日期: 2018/08/06
 *  版本: 1.0
 *  说明: 模块内部文件，不直接对外包含
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

            // 获取元对象类型
            using M = decltype(T::Fs_METAOBJECT(std::forward<T>(*t)));
            
            // 获取元数据成员个数
            constexpr auto Size = M::value();

            // 获取索引
            auto index = GetIndex<T>(pName);
            if (index < 0 || index >= Size)
                return pRetPtr;

            // 获取元数据
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