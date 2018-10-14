/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Fs_ClsObject.h
 *  作者: luwei
 *  日期: 2018/08/03
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_CLSOBJECT_H_  
#define SERIALIZE_CLSOBJECT_H_

#include "../../I_Data.h"

class Fs_ClsObject
{
public:
    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

    inline Fs_Utility::IBasic* Basic() { return m_Basic; }
    inline std::size_t ClassId() { return m_Basic->m_ClsId; }
    inline const char* ClassName() { return m_Basic->GetName(); }
    inline std::size_t ObjectId() { return m_Basic->m_ObjectId; }

    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

    virtual std::size_t ImplInstanceId() = 0;
    virtual std::size_t BaseInstanceId() = 0;

    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

    virtual unsigned int ApiId() = 0;

    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

public:
    template<class T> inline T* GetInstance() {
        Fs_ClsObjectProxy<T>* pProxy = dynamic_cast<Fs_ClsObjectProxy<T>*>(this);
        if (pProxy) return pProxy->m_Ptr;
        return (T*)nullptr;
    }

    virtual bool CloneInstance(Fs_ClsObject*) = 0;
    virtual void DestoryInstance() = 0;
    virtual void* _MemoryInstance() = 0;

    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

protected:
    Fs_Utility::IBasic* m_Basic{ nullptr };

    virtual void Serialize(Fs_Utility::IDataProp*, std::size_t TransId = 0) = 0;
    virtual void DeSerialize(Fs_Utility::IDataPropIterator*, std::size_t TransId = 0) = 0;
    virtual void ModifyAttribute(Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType) = 0;

    Fs_ClsObject() { }
    virtual ~Fs_ClsObject() { delete m_Basic;}

    friend class Fs_ObjectManager;
    friend class Fs_ObjectFactory;
    friend class Fs_SerializerMgr;

    class Fs_EmptyClsObj {
    public:
    };
};

template<class T>
class Fs_ClsObjectProxy : public Fs_ClsObject
{
public:
    Fs_ClsObjectProxy(T* ptr, std::size_t implInstId, std::size_t baseInstId)
        : m_Ptr(ptr), m_ImplInstId(implInstId), m_BaseInstId(baseInstId){
    }
    virtual ~Fs_ClsObjectProxy() {}

    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

    virtual std::size_t ImplInstanceId() { return m_ImplInstId; }
    virtual std::size_t BaseInstanceId() { return m_BaseInstId; }

    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

    virtual unsigned int ApiId() { return 0; }
    virtual void Serialize(Fs_Utility::IDataProp*, std::size_t TransId = 0) {}
    virtual void DeSerialize(Fs_Utility::IDataPropIterator*, std::size_t TransId = 0) {}
    virtual void ModifyAttribute(Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType) {}

    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

    virtual bool CloneInstance(Fs_ClsObject* pClsObj) {
        Fs_ClsObjectProxy<T>* pProxy = dynamic_cast<Fs_ClsObjectProxy<T>*>(pClsObj);
        if (pProxy) {
            *m_Ptr = *(pProxy->m_Ptr); 
            return true;
        }
        return false;
    }
    virtual void DestoryInstance() { if (!m_Ptr) return; m_Ptr; m_Ptr = nullptr; }
    virtual void* _MemoryInstance() { return m_Ptr; }

    T* m_Ptr;
    std::size_t m_ImplInstId;
    std::size_t m_BaseInstId;
};

#endif  // SERIALIZE_CLSOBJECT_H_