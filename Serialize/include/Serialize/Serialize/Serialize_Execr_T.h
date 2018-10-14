/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Serialize_Execr_T.h
 *  作者: luwei
 *  日期: 2018/08/06
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_SERIALIZE_EXECR_T_H_  
#define SERIALIZE_SERIALIZE_EXECR_T_H_

#include "Serialize_Execr.h" 
#include "Serialize_Pack.h" 
#include "Serialize_Unpack.h"
#include "Serialize_Modify_Attribute.h"  
#include "Serialize_Ref_Attribute.h"

namespace Fs_Serialize
{
    template<typename T, typename B>
    class Serialize_ExecrT : public Serialize_Execr
    {
        friend class SerializePack;
        friend class SerializeUnpack;

        std::size_t m_ClsId;
        const char* m_Name;

    public:

        // 静态
        static Serialize_ExecrT<T, B>* _self;

        Serialize_ExecrT(std::size_t clsId, const char* name)
            : m_ClsId(clsId), m_Name(name)
        {
            _self = this;
            Fs_Serialize::GlobalSerializerApi()->GetSerializerMgr()->RegistSerializeExecr(this);
        }

        virtual ~Serialize_ExecrT() { }
        virtual std::size_t GetClassId() { return m_ClsId; }

        virtual Fs_ClsObject* CreateClsObj(unsigned int apiId, void* ptr) {
            T* tptr = (T*)ptr;
            B* bptr = (B*)tptr;
            return new Fs_ClsObjectSerializeProxy<T, B>(tptr, apiId, (std::size_t)tptr, (std::size_t)bptr);
        }

        virtual T* InitObject(Fs_ClsObject* pObj) {

            T* pInstance = nullptr;

            if (pObj)
            {
                pInstance = pObj->GetInstance<T>();
                if (!pInstance)
                    pInstance = dynamic_cast<T*>(pObj->GetInstance<B>());
            }

            return pInstance;
        }

        template<class C>
        inline Fs_ClsObject* InitObject(ISerializerApi* pApi, C* c) {

            Fs_ClsObject* pClsObj = nullptr;

            if (std::is_base_of<C, T>::value)
            {
                std::size_t _instId = (std::size_t)((std::size_t*)dynamic_cast<T*>(c));
                if (_instId)
                {
                    IObjectManager* pMgr = pApi->GetObjectManager();
                    pClsObj = pMgr->FindObjectByInstanceId(_instId);
                }
            }

            return pClsObj;
        }

        virtual void Serialze(Fs_ClsObject* pObj, Fs_Utility::IDataProp* pProp, std::size_t TransId) { 

            if (pObj)
            {
                T* tObj = InitObject(pObj);

                if (tObj)
                    SerializePack(TransId, Fs_Serialize::CreateSerializerApi(pObj->ApiId())).PackData(pProp, tObj);
            }
        }

        virtual void DeSerialze(Fs_ClsObject* pObj, Fs_Utility::IDataPropIterator* pIter, std::size_t TransId) {

            if (pObj)
            {
                T* tObj = InitObject(pObj);

                if (tObj)
                    SerializeUnpack(TransId, Fs_Serialize::CreateSerializerApi(pObj->ApiId())).UnpackData(pIter, tObj);
            }
        }

        virtual void ModifyAttribute(Fs_ClsObject* pObj, Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt) {

            if (pObj && pIter && pIter->GetName())
            {
                T* tObj = InitObject(pObj);

                if (tObj)
                    SerializeUnpackAttribute(0, Fs_Serialize::CreateSerializerApi(pObj->ApiId())).UnpackObjectAttribute(pIter, mt, tObj);
            }
        }
    
        template<class _Ret>
        inline _Ret* RefAttribute(Fs_ClsObject* pObj, const char* pName) {

            if (pObj && pName)
            {
                T* tObj = InitObject(pObj);

                if (tObj)
                    return SerializeRefAttribute().Pointer2ObjectAttribute(pName, tObj);
            }

            return (_Ret*)nullptr;
        }
    };

    //__declspec(selectany) 
    template<typename T, typename B> Serialize_ExecrT<T, B>* Serialize_ExecrT<T, B>::_self = nullptr;
}


#endif  // SERIALIZE_SERIALIZE_EXECR_T_H_