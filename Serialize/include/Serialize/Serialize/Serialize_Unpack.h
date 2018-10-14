/*******************************************************************
 *  Copyright(c) 2000-2017 SnailGame
 *  All rights reserved.
 *
 *  文件: Serialize_Unpack.h
 *  作者: luwei
 *  日期: 2018/08/06
 *  版本: 1.0
 *  说明: 模块内部文件，不直接对外包含
 ******************************************************************/

#ifndef SERIALIZE_SERIALIZE_UNPACK_H_  
#define SERIALIZE_SERIALIZE_UNPACK_H_

#include "../Traits.h"    
#include "Serialize_Unpack_Helper.h"

#include <vector>
#include <xstring> 
#include <type_traits> 
#include <utility>

namespace Fs_Serialize
{
    class SerializeUnpack
    {
    public:

        inline void UnpackValue(Fs_Utility::IDataPropIterator* iter, bool& val) {
            val = iter->GetValue().ToBool();
        }

        inline void UnpackValue(Fs_Utility::IDataPropIterator* iter, FsBp_CustomVariable& val) {
            m_Api->GetBlurprintApi()->DeSerialize(&val, iter, m_TransId);
        }

        inline void UnpackValue(Fs_Utility::IDataPropIterator* iter, Fs_NodeVariable& val) {
            m_Api->GetBlurprintApi()->DeSerialize(&val, iter, m_TransId);
        }

        template<typename T>
        inline std::enable_if_t<is_signed_intergral_like<T>::value> UnpackValue(Fs_Utility::IDataPropIterator* iter, T& val) {
            val = iter->GetValue().ToInt();
        }

        template<typename T>
        inline std::enable_if_t<is_unsigned_intergral_like<T>::value> UnpackValue(Fs_Utility::IDataPropIterator* iter, T& val) {
            val = iter->GetValue().ToUnSignedInt();
        }

        template<typename T>
        inline std::enable_if_t<is_stdstring<T>::value> UnpackValue(Fs_Utility::IDataPropIterator* iter, T& val) {
            val = iter->GetValue().ToString();
        }

        template<typename T>
        inline std::enable_if_t<std::is_enum<T>::value> UnpackValue(Fs_Utility::IDataPropIterator* iter, T& val) {
            typedef typename std::underlying_type<T>::type RAW_TYPE;
            UnpackValue(iter, (RAW_TYPE&)val);
        }

        template<typename T>
        inline std::enable_if_t<std::is_floating_point<T>::value> UnpackValue(Fs_Utility::IDataPropIterator* iter, T& val) {
            val = iter->GetValue().ToFloat();
        }

        template<typename T>
        inline std::enable_if_t<is_sequence_container<T>::value> UnpackValue(Fs_Utility::IDataPropIterator* iter, T& val) {

            size_t size;
            UnpackValue(iter, size);

            using value_type = typename T::value_type;

            for (size_t i = 0; i < size; i++)
            {
                iter->Next();

                value_type v;
                UnpackValue(iter, v);
                val.push_back(v);
            }
        }

        template<typename T>
        inline std::enable_if_t<is_associat_container<T>::value> UnpackValue(Fs_Utility::IDataPropIterator* iter, T& val) {

            size_t size;
            UnpackValue(iter, size);

            using pair_type = typename std::pair<T::key_type, T::mapped_type>;

            for (size_t i = 0; i < size; i++)
            {
                iter->Next();

                pair_type pair;
                UnpackValue(iter, pair);
                val.insert(pair);
            }
        }

        template<typename T>
        inline std::enable_if_t<is_stdpair<T>::value> UnpackValue(Fs_Utility::IDataPropIterator* iter, T& val) {

            // 解析First
            if (iter->GetDataProp()->m_KeyData)
            {
                Fs_Utility::IDataPropIterator* _iter = m_DataMgr->CreateDataPropRecursionIterator(iter->GetDataProp()->m_KeyData);
                UnpackValue(_iter, val.first);
                m_DataMgr->DestroyDataIterator(_iter);
            }

            // 解析Second
            UnpackValue(iter, val.second);
        }

        template<typename T>
        inline std::enable_if_t<std::is_pointer<T>::value> UnpackValue(Fs_Utility::IDataPropIterator* iter, T& val) {

            //
            using value_type = typename std::decay_t<std::remove_pointer_t<T>>;
            size_t objId = iter->GetObjectId();

            if (!is_serialize<value_type>::value && objId == 0)
            {
                val = new value_type;
                UnpackValue(iter, *val);
                return;
            }

            val = DeSerializerT<value_type>(m_Api->GetSerializer(), m_TransId, iter);
        }

        template<typename T>
        inline void UnpackArray(Fs_Utility::IDataPropIterator* iter, T& val, size_t N) {
            for (size_t i = 0; i < N; ++i)
            {
                iter->Next();
                UnpackValue(iter, val[i]);
            }
        }

        template <typename T, size_t N>
        inline void UnpackValue(Fs_Utility::IDataPropIterator* iter, T(&val)[N]) {
            UnpackArray(iter, val, N);
        }

        template <typename T, size_t N>
        inline void UnpackValue(Fs_Utility::IDataPropIterator* iter, std::array<T, N>& val) {
            UnpackArray(iter, val, N);
        }

        //
        template<typename T, typename = std::enable_if_t<is_serialize<T>::value>>
        inline void UnpackValue(Fs_Utility::IDataPropIterator* iter, T& val) {
            UnpackData(iter, &val);
        }

        //
        template<typename T, typename _Ty = std::enable_if_t<!is_serialize<T>::value>>
        inline void UnpackValue(Fs_Utility::IDataPropIterator* iter, T&& t) {}
        template<typename T, typename _Ty = std::enable_if_t<!is_serialize<T>::value>>
        inline void UnpackData(Fs_Utility::IDataPropIterator*& iter, T*& t) {}

        //
        template<typename T, typename _Ty = std::enable_if_t<is_serialize<T>::value>>
        inline void UnpackData(Fs_Utility::IDataPropIterator* iter, T* t)
        {
            using M = decltype(T::Fs_METAOBJECT(std::forward<T>(*t)));
            auto valTuple = M::staticMetaObject();

            constexpr auto Size = M::value();
            size_t Count = iter->GetDataProp()->Size();

            iter->Next();

            for (size_t i = 0; i < Count; iter->NextSlibing(), ++i)
            {
                auto index = GetIndex<T>(iter->GetName());
                if (index == Size)
                    continue;

                TupleAt(
                    index,
                    valTuple,
                    [&](auto& v) { UnpackValue(iter, t->*v); },
                    std::make_index_sequence<Size>{}
                );
            }
        }

        SerializeUnpack(std::size_t transId, ISerializerApi* api) : m_TransId(transId), m_Api(api) {
            m_DataMgr = api->GetDataManager();
        }

    private:
        std::size_t m_TransId;
        ISerializerApi* m_Api;
        Fs_Utility::IDataManager* m_DataMgr;
    };
}

#endif  // SERIALIZE_SERIALIZE_UNPACK_H_