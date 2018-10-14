/*******************************************************************
*  Copyright(c) 2000-2017 SnailGame
*  All rights reserved.
*
*  文件: Serialize_Pack.h
*  作者: luwei
*  日期: 2018/08/06
*  版本: 1.0
*  说明: 模块内部文件，不直接对外包含
******************************************************************/

#ifndef SERIALIZE_SERIALIZE_PACK_H_  
#define SERIALIZE_SERIALIZE_PACK_H_

#include "../Traits.h"          
#include "Serialize_Pack_Helper.h"

#include <vector>
#include <xstring> 
#include <type_traits> 
#include <utility>
#include <iostream>

namespace Fs_Serialize
{
    class SerializePack
    {
    public:

        inline void PackValue(Fs_Utility::IDataProp* prop, bool& val) {
            prop->m_Value = val;
        }

        template<typename T>
        inline std::enable_if_t<is_signed_intergral_like<T>::value> PackValue(Fs_Utility::IDataProp* prop, T& val) {
            prop->m_Value = val;
        }

        template<typename T>
        inline std::enable_if_t<is_unsigned_intergral_like<T>::value> PackValue(Fs_Utility::IDataProp* prop, T& val) {
            prop->m_Value = val;
        }

        template<typename T>
        inline std::enable_if_t<is_stdstring<T>::value> PackValue(Fs_Utility::IDataProp* prop, T& val) {
            prop->m_Value = val.c_str();
        }

        template<typename T>
        inline std::enable_if_t<std::is_enum<T>::value> PackValue(Fs_Utility::IDataProp* prop, T& val) {
            typedef typename std::underlying_type<T>::type RAW_TYPE;
            prop->m_Value = (RAW_TYPE)val;
        }

        template<typename T>
        inline std::enable_if_t<std::is_floating_point<T>::value> PackValue(Fs_Utility::IDataProp* prop, T& val) {
            prop->m_Value = val;
        }

        template<typename T>
        inline std::enable_if_t<is_sequence_container<T>::value> PackValue(Fs_Utility::IDataProp* prop, T& val) {

            prop->m_Value = val.size();
            prop->m_Category = Fs_Utility::IDataProp::VT_ARRAY;

            for (size_t i = 0; i < val.size(); ++i)
            {
                Fs_Utility::IDataProp* child = m_DataMgr->CreateDataProp();
                child->SetName(Fs_Utility::Variant(i).ToString());
                prop->AddChild(child);

                PackValue(child, val[i]);
            }
        }

        template<typename T>
        inline std::enable_if_t<is_associat_container<T>::value> PackValue(Fs_Utility::IDataProp* prop, T& val) {

            prop->m_Value = val.size();
            prop->m_Category = Fs_Utility::IDataProp::VT_MAP;

            using pair_type = typename std::pair<T::key_type, T::mapped_type>;

            int i = 0;
            for (pair_type pair : val)
            {
                Fs_Utility::IDataProp* child = m_DataMgr->CreateDataProp();
                child->SetName(Fs_Utility::Variant(i++).ToString());
                prop->AddChild(child);

                PackValue(child, pair);
            }
        }

        template<typename T>
        inline std::enable_if_t<is_stdpair<T>::value> PackValue(Fs_Utility::IDataProp* prop, T& val) {

            Fs_Utility::IDataProp* key = m_DataMgr->CreateDataProp();
            prop->m_KeyData = key;

            PackValue(key, val.first);
            PackValue(prop, val.second);
        }

        template<typename T>
        inline std::enable_if_t<std::is_pointer<T>::value> PackValue(Fs_Utility::IDataProp* prop, T& val) {

            // 空指针返回
            if (!val)
                return;

            using value_type = typename std::decay_t<std::remove_reference<std::remove_pointer<T>::type>::type>;

            if (!is_serialize<value_type>::value && !m_Api->GetObjectManager()->ExistObject(std::size_t(val)))
            {
                PackValue(prop, *val);
                return;
            }

            prop->m_Category = Fs_Utility::IDataProp::VT_MAP;
            SerializerT(m_Api, prop, val, m_TransId);
        }

        template<typename T>
        inline void PackArray(Fs_Utility::IDataProp* prop, T& val, size_t N) {

            prop->m_Value = N;
            prop->m_Category = Fs_Utility::IDataProp::VT_ARRAY;

            for (size_t i = 0; i < N; ++i)
            {
                Fs_Utility::IDataProp* child = m_DataMgr->CreateDataProp();
                child->SetName(Fs_Utility::Variant(i).ToString());
                prop->AddChild(child);

                PackValue(child, val[i]);
            }
        }

        template <typename T, size_t N>
        inline void PackValue(Fs_Utility::IDataProp* prop, T(&val)[N]) {
            PackArray(prop, val, N);
        }

        template <typename T, size_t N>
        inline void PackValue(Fs_Utility::IDataProp* prop, std::array<T, N>& val) {
            PackArray(prop, val, N);
        }

        template<typename T, typename = std::enable_if_t<is_serialize<T>::value>>
        inline void PackValue(Fs_Utility::IDataProp* prop, T& val) {

            using value_type = typename std::decay_t<std::remove_reference<std::remove_pointer<T>::type>::type>;
            using M = decltype(value_type::Fs_METAOBJECT(std::declval<value_type>()));
            auto execr = M::Execr();
            if (execr)
                prop->m_ClsId = execr->GetClassId();

            PackData(prop, &val);
        }

        //
        template<typename T, typename _Ty = std::enable_if_t<
            !is_serialize<T>::value &&
            !is_signed_intergral_like<std::decay_t<T>>::value &&
            !is_unsigned_intergral_like<std::decay_t<T>>::value &&
            !is_stdstring<std::decay_t<T>>::value &&
            !std::is_enum<std::decay_t<T>>::value &&
            !std::is_floating_point<std::decay_t<T>>::value &&
            !is_associat_container<std::decay_t<T>>::value &&
            !is_sequence_container<std::decay_t<T>>::value &&
            !is_stdpair<std::decay_t<T>>::value &&
            !std::is_same<std::decay_t<T>, bool>::value>>
        inline void PackValue(Fs_Utility::IDataProp*& prop, T&& t) {}
        template<typename T, typename _Ty = std::enable_if_t<!is_serialize<T>::value>>
        inline void PackData(Fs_Utility::IDataProp*& prop, T*& t) {}

        template<typename T, typename _Ty = std::enable_if_t<is_serialize<T>::value>>
        inline void PackData(Fs_Utility::IDataProp* prop, T* t) {

            prop->m_Category = Fs_Utility::IDataProp::VT_MAP;

            for_each(std::forward<T>(*t), [&](const auto &v, auto index)
            {
                constexpr auto Index = decltype(index)::value;
                auto name = GetName<decltype(*t), Index>();
                {
                    Fs_Utility::IDataProp* child = m_DataMgr->CreateDataProp();
                    child->SetName(name);
                    prop->AddChild(child);

                    PackValue(child, t->*v);
                }

                return true;
            });
        }


        SerializePack(std::size_t transId, ISerializerApi* api) : m_TransId(transId), m_Api(api){
            m_DataMgr = api->GetDataManager();
        }

    private:
        std::size_t m_TransId;
        ISerializerApi* m_Api;
        Fs_Utility::IDataManager* m_DataMgr;
    };
}

#endif 