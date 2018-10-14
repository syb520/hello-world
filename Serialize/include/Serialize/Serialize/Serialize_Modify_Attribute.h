/*******************************************************************
 *  Copyright(c) 2000-2017 SnailGame
 *  All rights reserved.
 *
 *  文件: Serialize_Modify_Attribute.h
 *  作者: luwei
 *  日期: 2018/08/06
 *  版本: 1.0
 *  说明: 模块内部文件，不直接对外包含
 ******************************************************************/

#ifndef SERIALIZE_SERIALIZE_MODIFY_ATTRIBUTE_H_  
#define SERIALIZE_SERIALIZE_MODIFY_ATTRIBUTE_H_

#include "../Traits.h"          

#include <vector>
#include <xstring> 
#include <type_traits> 
#include <utility>
#include <sstream>

namespace Fs_Serialize
{
    class SerializeUnpackAttribute
    {
    public:

        inline void UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType, bool& val) {
            val = pIter->GetValue().ToBool();
        }

        inline void UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt, FsBp_CustomVariable& val) {
            m_Api->GetBlurprintApi()->Modify(&val, pIter, mt);
        }

        inline void UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt, Fs_NodeVariable& val) {
            m_Api->GetBlurprintApi()->Modify(&val, pIter, mt);
        }

        template<typename T>
        inline std::enable_if_t<is_signed_intergral_like<T>::value> UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType, T& val) {
            val = pIter->GetValue().ToInt();
        }

        template<typename T>
        inline std::enable_if_t<is_unsigned_intergral_like<T>::value> UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType, T& val) {
            val = pIter->GetValue().ToUnSignedInt();
        }

        template<typename T>
        inline std::enable_if_t<is_stdstring<T>::value> UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType, T& val) {
            val = pIter->GetValue().ToString();
        }

        template<typename T>
        inline std::enable_if_t<std::is_enum<T>::value> UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt, T& val) {
            typedef typename std::underlying_type<T>::type RAW_TYPE;
            UnpackMemberAttribute(pIter, mt, (RAW_TYPE&)val);
        }

        template<typename T>
        inline std::enable_if_t<std::is_floating_point<T>::value> UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType, T& val) {
            val = pIter->GetValue().ToFloat();
        }

        //////////////////////////////////////////////////////////////////////////

        template<typename T>
        inline std::enable_if_t<is_sequence_container<T>::value> UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt, T& val) {

            // 获取值类型
            using value_type = typename T::value_type;

            // 名字转化为索引
            auto Name2Index = [](const std::string& strName)
            {
                int index = 0;
                if ((std::stringstream(strName) >> index))
                    return index;
                return -1;
            };

            switch (mt)
            {
                case Fs_Utility::E_ADD:
                {
                    value_type v;
                    UnpackMemberAttribute(pIter, mt, v);
                    val.push_back(v);

                    break;
                }
                case Fs_Utility::E_REMOVE:
                {
                    T::size_type index = Name2Index(pIter->GetName());
                    if (index >= 0 && index < val.size())
                        val.erase(val.begin() + index);

                    break;
                }
                case Fs_Utility::E_MODIFY:
                {
                    pIter->Next();

                    T::size_type index = Name2Index(pIter->GetName());
                    if (index >= 0 && index < val.size())
                        UnpackMemberAttribute(pIter, mt, val[index]);
                        
                    break;
                }
                case Fs_Utility::E_REPLACE:
                {
                    // 清空
                    val.clear();

                    std::size_t size = pIter->GetDataProp()->Size();
                    for (std::size_t index = 0; index < size; index++)
                    {
                        pIter->Next();

                        value_type v;
                        UnpackMemberAttribute(pIter, mt, v);
                        val.push_back(v);
                    }

                    break;
                }
                default:
                    break;
            }
        }

        template<typename T>
        inline std::enable_if_t<is_associat_container<T>::value> UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt, T& val) {

            using pair_type = typename std::pair<T::key_type, T::mapped_type>;

            if (mt = Fs_Utility::E_REPLACE)
                val.clear();// 清空

            std::size_t size = pIter->GetDataProp()->Size();
            for (std::size_t index = 0; index < size; index++)
            {
                pIter->Next();

                pair_type pair;
                UnpackMemberAttribute(pIter, mt, pair);

                switch (mt)
                {
                case Fs_Utility::E_ADD:
                case Fs_Utility::E_REPLACE:
                    val.insert(pair);
                    break;
                case Fs_Utility::E_REMOVE:
                    val.erase(pair.first);
                    break;
                case Fs_Utility::E_MODIFY:
                    val[pair.first] = pair.second;
                    break;
                default:
                    break;
                }
            }
        }

        template<typename T>
        inline std::enable_if_t<is_stdpair<T>::value> UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt, T& val) {

            if (pIter->GetDataProp()->m_KeyData)
            {
                Fs_Utility::IDataPropIterator* _iter = m_DataMgr->CreateDataPropRecursionIterator(pIter->GetDataProp()->m_KeyData);
                UnpackMemberAttribute(_iter, mt, val.first);
                m_DataMgr->DestroyDataIterator(_iter);
            }

            UnpackMemberAttribute(pIter, mt, val.second);
        }

        template<typename T>
        inline std::enable_if_t<std::is_pointer<T>::value> UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt, T& val) {

            // 移除
            if (mt == Fs_Utility::E_REMOVE && (val))
            {
                delete val;
                val = nullptr;
                return;
            }

            using value_type = typename std::decay_t<std::remove_pointer_t<T>>;
            size_t objId = pIter->GetObjectId();

            if (!is_serialize<value_type>::value && objId == 0)
            {
                // 修改值
                if (mt == Fs_Utility::E_MODIFY && (val))
                {
                    UnpackMemberAttribute(pIter, mt, *val);
                    return;
                }

                // 替换指针
                if (mt == Fs_Utility::E_REPLACE)
                {
                    if (val)
                        delete val;
                    val = nullptr;

                    val = new value_type;
                    UnpackMemberAttribute(pIter, mt, *val);
                    return;
                }
            }

            if (mt == Fs_Utility::E_ADD ||
                mt == Fs_Utility::E_MODIFY ||
                mt == Fs_Utility::E_REPLACE)
            {
                if (val)
                    delete val;
                val = nullptr;

                Fs_ClsObject* clsObj = m_Api->GetObjectManager()->FindObjectByObjectId(objId);
                if (clsObj)
                    val = clsObj->GetInstance<value_type>();
            }
        }

        template<typename T>
        inline void UnpackArrayAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt, T& val, size_t N) {
            
            for (size_t i = 0; i < N; ++i)
            {
                pIter->Next();
                UnpackMemberAttribute(pIter, mt, val[i]);
            }
        }

        template <typename T, size_t N>
        inline void UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt, T(&val)[N]) {
            UnpackArrayAttribute(pIter, mt, val, N);
        }

        template <typename T, size_t N>
        inline void UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt, std::array<T, N>& val) {
            UnpackArrayAttribute(pIter, mt, val, N);
        }

        //
        template<typename T, typename = std::enable_if_t<is_serialize<T>::value>>
        inline void UnpackMemberAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt, T& val) {
            UnpackObjectAttribute(pIter, mt, &val);
        }

        //
        template<typename T, typename _Ty = std::enable_if_t<!is_serialize<T>::value>>
        inline void UnpackMemberAttribute(Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType, T&&) {}
        template<typename T, typename _Ty = std::enable_if_t<!is_serialize<T>::value && !is_serialize_T<T>::value>>
        inline void UnpackObjectAttribute(Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType, T*&&) {}
        template<typename T, typename _Ty = std::enable_if_t<!is_serialize<T>::value && is_serialize_T<T>::value>>
        inline void UnpackObjectAttribute(Fs_Utility::IDataPropIterator*&, Fs_Utility::ModifyType, T*) {}

        //
        template<typename T, typename _Ty = std::enable_if_t<is_serialize<T>::value>>
        inline void UnpackObjectAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt, T* t)
        {
            // 获取元对象类型
            using M = decltype(T::Fs_METAOBJECT(std::forward<T>(*t)));
            
            // 获取元数据成员个数
            constexpr auto Size = M::value();

            // 遍历
            pIter->Next();

            // 判断名字
            if (!pIter->GetName())
                return;

            // 获取索引
            auto index = GetIndex<T>(pIter->GetName());
            if (index < 0 || index >= Size)
                return;

            // 获取元数据
            auto valTuple = M::staticMetaObject();
            TupleAt(index, valTuple, [&](auto& v) { UnpackMemberAttribute(pIter, mt, t->*v); }, std::make_index_sequence<Size>{});
        }

        SerializeUnpackAttribute(std::size_t transId, ISerializerApi* api) : m_TransId(transId), m_Api(api) {
            m_DataMgr = api->GetDataManager();
        }

    private:
        std::size_t m_TransId;
        ISerializerApi* m_Api;
        Fs_Utility::IDataManager* m_DataMgr;
    };
}

#endif  // SERIALIZE_SERIALIZE_MODIFY_ATTRIBUTE_H_