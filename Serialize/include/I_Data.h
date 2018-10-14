/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  �ļ�: I_Data.h
 *  ����: luwei
 *  ����: 2018/08/08
 *  �汾: 1.0 
 *  ˵��: 
 ******************************************************************/  
  
#ifndef SERIALIZE_I_DATA_H_  
#define SERIALIZE_I_DATA_H_

#include <xstring>
#include <vector>
#include <map>
#include <type_traits>
#include <utility>
#include <deque>
#include <list>

#include "Serialize/Variant.h"

namespace Fs_Utility
{
    
    // ������
    class IBasic;
    class IDataProp;
    class IData;
    class IDataModifier;
    class IDataPropIterator;
    class IDataManager;


    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////


    class IBasic
    {
    public:
        // ��GUID
        size_t m_ClsId{ 0 };
        
        // ����
        virtual const char* GetName() = 0;
        virtual void SetName(const char*) = 0;
        
        // �����ID
        size_t m_ObjectId{ 0 };

        // ����ID
        size_t m_FactoryId{ 0 };

        // ��������
        virtual const char* GetFactoryMethod() = 0;
        virtual void SetFactoryMethod(const char*) = 0;
        
        // PrefabId
        size_t m_Prefab{ 0 };

        // �û��Զ�������
        // std::map<std::string, Variant> m_UserData;
    };

    class IDataProp
    {

    protected:
        IDataProp* m_Parent{ nullptr };
        IData* m_DataPtr{ nullptr };
        IDataManager* m_DataMgr;
        bool m_IsDirty{ false };

    public:
        enum Category {
            VT_VALUE = 0,
            VT_ARRAY,
            VT_MAP
        };

        virtual ~IDataProp() {}
        virtual std::size_t Guid() = 0;
        inline IData* DataPtr() { return m_DataPtr; }
        
        // Key
        virtual const char* GetName() = 0;
        virtual void SetName(const char*) = 0;
        // ��Key��Ϊֵ����ʱ����ʶKey�����ԡ�����Ϊ��
        IDataProp* m_KeyData{ nullptr };

        // ���л�����ClsId��ObjId
        size_t m_ClsId{ 0 };
        size_t m_ObjId{ 0 };

        // Value
        Category m_Category{ VT_VALUE };
        Variant m_Value;

        virtual void AddChild(const char*, IDataProp*) = 0;
        virtual void AddChild(IDataProp*) = 0;
        virtual IDataProp* FindChild(const char*) = 0;
        virtual IDataProp* Parent() = 0;
        virtual void SetParent(IDataProp*) = 0;

        virtual bool Remove(const char*) = 0;
        virtual IDataProp* Take(const char*) = 0;
        virtual void Combine(IDataProp*, bool bCover = false) = 0;

        virtual void Clear() = 0;
        virtual std::size_t Size() = 0;
        virtual bool Dirty() = 0;

        // ��ȡ������
        virtual IDataPropIterator* GetIterator() = 0;
    };

    class IData
    {
    protected:

        IDataManager* m_DataMgr;
        IDataProp* m_dp;

    public:
        IBasic* m_basic;

        virtual ~IData() {}
        virtual std::size_t Guid() = 0;
        
        virtual void AddChildProp(const char* name, IDataProp*) = 0;
        virtual IDataProp* RootProp() = 0;
        virtual IDataProp* FindChildProp(const char* name) = 0;
        virtual IDataProp* NextSiblingProp(IDataProp*) = 0;
        virtual void Combine(IData*, bool bCover = false) = 0;
    };


    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////

    class IDataPropIterator
    {
    public:
        virtual ~IDataPropIterator() {}
        virtual std::size_t Guid() = 0;
        virtual bool IsRecursive() = 0;

        virtual void Reset() = 0;
        virtual bool AtEnd() = 0;
        virtual bool Next() = 0;
        virtual bool NextSlibing() = 0;

        virtual IDataProp* GetDataProp() = 0;
        virtual const char* GetName() = 0;
        virtual std::size_t GetClsId() = 0;
        virtual std::size_t GetObjectId() = 0;
        virtual Variant GetValue() = 0;
    };


    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////

    enum ModifyType {
        E_DESERIALIZE,
        E_MODIFY,
        E_REPLACE,
        E_ADD,
        E_REMOVE
    };

    class IDataModifier
    {
    public:
        
        ModifyType m_Type{ E_MODIFY };

        // ����Id
        std::size_t m_ObjectId;

        IData* m_NewValue;
        IData* m_OldValue;
    };

}


typedef Fs_Utility::IData Fs_Data;
typedef Fs_Utility::IBasic Fs_Basic;
typedef Fs_Utility::IDataModifier Fs_DataModifier;

#endif  // SERIALIZE_I_DATA_H_