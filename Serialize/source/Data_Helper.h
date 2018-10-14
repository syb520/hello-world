/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Data_Helper.h
 *  作者: luwei
 *  日期: 2018/08/08
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_DATA_HELPER_H_  
#define SERIALIZE_DATA_HELPER_H_

#include <xstring>
#include <vector>
#include <map>
#include <set>
#include "../include/I_Data_Helper.h"

namespace Fs_Utility
{
    class DataProp;

    class DataManager : public IDataManager
    {
    public:
        virtual void Merge(IDataManager* pMgr) override;
        virtual IData* FindData(std::size_t) override;

        virtual IData* CreateData() override;
        virtual IDataProp* CreateDataProp() override;
        virtual IDataPropIterator* CreateDataPropRecursionIterator(IDataProp*) override;
        virtual IStringGuard* CreateStringGuard(const char* pChar) override;
        virtual IVectorGuard<IData*>* CreateDataVectorGuard() override;
        virtual IVectorGuard<Fs_ClsObject*>* CreateObjectVectorGuard() override;

        virtual void DestroyData(IData*) override;
        virtual void DestroyDataProp(IDataProp*) override;
        virtual void DestroyDataIterator(IDataPropIterator*) override;
        virtual void DestroyMemoryGuard(IMemoryGuard*) override;

        std::map<std::size_t, IData*> m_data;
        std::map<std::size_t, IDataProp*> m_dataProp;
        std::map<std::size_t, IDataPropIterator*> m_dataIterator;
        std::set<IMemoryGuard*> m_memoryGuard;
    };
    
    
    class StringGuard : public IStringGuard
    {
        char* m_pMemory{ nullptr };

        ~StringGuard() {
            if (m_pMemory)
                delete m_pMemory;
            m_pMemory = nullptr;
        }

    public:
        StringGuard(const char* pMemory) {

            if (pMemory == nullptr)
                return;

            std::size_t length = strlen(pMemory);
            m_pMemory = new char[length + 1];
            memcpy(m_pMemory, pMemory, length);
            m_pMemory[length] = '\0';
        }

        // 获取内存大小
        virtual std::size_t _Size() {
            return m_pMemory ? strlen(m_pMemory) : 0;
        }

        // 获取内存
        virtual const char* _Memory() const {
            return m_pMemory;
        }
    };

    template<typename Ty>
    class VectorGuard : public IVectorGuard<Ty>
    {
        std::vector<Ty> m_vecMemory;

    public:
        inline std::size_t _Size() { return m_vecMemory.size(); }
        inline virtual Ty _Memory(std::size_t index) { return (index >= 0 && index < _Size()) ? m_vecMemory[index] : nullptr; }
        inline virtual void _Push_Back(const Ty& pData) { m_vecMemory.push_back(pData); }
        inline virtual void Clear() { m_vecMemory.clear(); }
    };


    //////////////////////////////////////////////////////////////////////////


    class DataPropIterator : public IDataPropIterator
    {
    protected:

        typedef std::map<std::string, IDataProp*>::const_iterator _MyIter;
        _MyIter m_Iter;
        DataProp* m_Root{ nullptr };
        IDataProp* m_CurProp;

    public:
        DataPropIterator(IDataProp*);
        ~DataPropIterator() {}
        std::size_t Guid() { return std::size_t(this); }
        bool IsRecursive() { return false; }

        void Reset();
        bool AtEnd();
        bool Next();
        bool NextSlibing() { return Next(); }

        IDataProp* GetDataProp();
        const char* GetName();
        std::size_t GetClsId();
        std::size_t GetObjectId();
        Variant GetValue();
    };

    class DataPropRecursionIterator : public DataPropIterator
    {
    protected:
        std::vector<_MyIter*> stackedProp;
        std::map<IDataProp*, bool> into;

    public:
        DataPropRecursionIterator(IDataProp*);
        ~DataPropRecursionIterator();
        bool IsRecursive() { return true; }

        void Reset();
        bool AtEnd();
        bool Next();
        bool NextSlibing();
    };
}

#endif  // SERIALIZE_DATA_HELPER_H_