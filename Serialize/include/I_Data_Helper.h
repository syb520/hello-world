/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  �ļ�: I_Data_Helper.h
 *  ����: luwei
 *  ����: 2018/08/08
 *  �汾: 1.0 
 *  ˵��: 
 ******************************************************************/  
  
#ifndef SERIALIZE_I_DATA_HELPER_H_  
#define SERIALIZE_I_DATA_HELPER_H_

#include "I_Data.h"

// ����
class Fs_ClsObject;


namespace Fs_Utility
{
    // ������
    class IMemoryGuard;
    class IStringGuard;
    template<typename Ty>
    class IVectorGuard;
    class IDataPropIterator;

    // ���ݹ���    
    class IDataManager
    {
    public:
        virtual void Merge(IDataManager* pMgr) = 0;

        // ����
        virtual IData* FindData(std::size_t) = 0;

        // ����
        virtual IData* CreateData() = 0;
        virtual IDataProp* CreateDataProp() = 0;
        virtual IDataPropIterator* CreateDataPropRecursionIterator(IDataProp*) = 0;
        virtual IStringGuard* CreateStringGuard(const char* pChar) = 0;
        virtual IVectorGuard<IData*>* CreateDataVectorGuard() = 0;
        virtual IVectorGuard<Fs_ClsObject*>* CreateObjectVectorGuard() = 0;
        
        // ����
        virtual void DestroyData(IData*) = 0;
        virtual void DestroyDataProp(IDataProp*) = 0;
        virtual void DestroyDataIterator(IDataPropIterator*) = 0;
        virtual void DestroyMemoryGuard(IMemoryGuard*) = 0;
    };


    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    class IMemoryGuard {
    public:
        virtual ~IMemoryGuard() {}
        virtual std::size_t _Size() = 0;  // ��ȡ�ڴ��С
    };

    class IStringGuard : public IMemoryGuard {
    public:
        // ��ȡ�ڴ�
        virtual const char* _Memory() const = 0;
    };

    template<typename Ty>
    class IVectorGuard : public IMemoryGuard
    {
    public:                              
        // �ڴ����
        virtual Ty _Memory(std::size_t) = 0;
        virtual void _Push_Back(const Ty&) = 0;
        virtual void Clear() = 0;
        IVectorGuard& operator<<(const Ty& ele) {
            _Push_Back(ele);
            return *this;
        }
    };


    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////


    class IGuidGenerator {
    public:
        virtual std::string Create() = 0;
        virtual std::string Create(std::size_t clsId) = 0;
        virtual std::string Create(std::size_t szID[4]) = 0;
        virtual std::string Create(std::size_t, std::size_t, std::size_t, std::size_t) = 0;
        virtual std::size_t Hash(const std::string&) = 0;
    };

    template<class T>
    inline std::size_t ClassIdGenerator() {
        return std::hash(typeid(T).hash_code(), sizeof(T));
    }

#define MAKE_GUID(CLSNAME) (Fs_Utility::ClassIdGenerator<CLSNAME>())


    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
}

typedef Fs_Utility::IStringGuard Fs_StringGuard;
typedef Fs_Utility::IVectorGuard<Fs_Data*> Fs_DataVector;
typedef Fs_Utility::IVectorGuard<Fs_ClsObject*> Fs_ClsObjectVector;


#endif  // SERIALIZE_I_DATA_HELPER_H_