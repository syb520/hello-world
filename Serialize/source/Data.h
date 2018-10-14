/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Data.h
 *  作者: luwei
 *  日期: 2018/08/08
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_DATA_H_  
#define SERIALIZE_DATA_H_

#include <xstring>
#include <vector>
#include <map>
#include "../include/I_Data_Helper.h" 

namespace Fs_Utility
{
    class DataPropIterator;
    class DataPropRecursionIterator;

    class Basic : public IBasic
    {
    public:
        std::string m_ClsName;
        virtual const char* GetName() { return m_ClsName.c_str(); }
        virtual void SetName(const char* name) { m_ClsName = name; }

        // 工厂方法
        std::string m_FactoryMethod;
        virtual const char* GetFactoryMethod() { return m_FactoryMethod.c_str(); }
        virtual void SetFactoryMethod(const char* method) { m_FactoryMethod = method; }
    };

    class DataProp : public IDataProp
    {
        friend class Data;
        friend class DataPropRecursionIterator;

        //key[std::string], value[DataProp*]
        std::map<std::string, IDataProp*> m_Children;
        std::string m_Name;
        IDataPropIterator* m_Iterator{ nullptr };

    public:
        ~DataProp();
        void SetDataManager(IDataManager*);
        std::size_t Guid() { return std::size_t(this); }

        const char* GetName() { return m_Name.c_str(); }
        void SetName(const char* name) { m_Name = name; }

        void AddChild(const char*, IDataProp*);
        void AddChild(IDataProp*);
        IDataProp* FindChild(const char*);
        IDataProp* Parent();
        void SetParent(IDataProp*);

		bool Remove(const char*);
        IDataProp* Take(const char*);
        void Combine(IDataProp*, bool bCover = false);

		void Clear();
        size_t Size();
        bool Dirty();

        const std::map<std::string, IDataProp*>& _Children();
        IDataPropIterator* GetIterator();
    };

    class Data : public IData
    {
        friend class DataPropRecursionIterator;

    public:
        Data(IDataManager* dataMgr);
        ~Data();
        std::size_t Guid() { return std::size_t(this); }

        void AddChildProp(const char* name, IDataProp*);
        IDataProp* RootProp();
        IDataProp* FindChildProp(const char* name);
        IDataProp* NextSiblingProp(IDataProp*);
        void Combine(IData*, bool bCover = false);
    };

}

#endif  // SERIALIZE_DATA_H_