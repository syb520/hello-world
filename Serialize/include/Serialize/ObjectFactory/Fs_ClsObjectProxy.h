/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Fs_ClsObjectProxy.h
 *  作者: luwei
 *  日期: 2018/08/03
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_CLSOBJECT_PROXY_H_  
#define SERIALIZE_CLSOBJECT_PROXY_H_

#include "Fs_ClsObject.h"  
#include "../Serialize/Serialize_Micro.h" 
#include "../Serialize/Serialize_Execr_T.h"

template<typename Ty, typename Base>
class Fs_ClsObjectSerializeProxy : public Fs_ClsObjectProxy<Ty>
{
    unsigned int m_ApiId;

public:
    Fs_ClsObjectSerializeProxy(Ty* ptr, unsigned int apiId, std::size_t implInstId, std::size_t baseInstId)
        : Fs_ClsObjectProxy<Ty>(ptr, implInstId, baseInstId), m_ApiId(apiId) {
    }

    unsigned int ApiId() { return m_ApiId; }

    template<class CHECK_CLASS>
    inline std::enable_if_t<Fs_Serialize::is_serialize<CHECK_CLASS>::value> Execr(Fs_Serialize::Serialize_Execr** ppExecr) {
        CHECK_CLASS* pBase = dynamic_cast<CHECK_CLASS*>(m_Ptr);
        using EXECR = decltype(CHECK_CLASS::Fs_METAOBJECT(std::forward<CHECK_CLASS>(*pBase)));
        auto _excer = EXECR::Execr();
        *ppExecr = _excer;
    }
    template<class CHECK_CLASS>
    inline std::enable_if_t<!Fs_Serialize::is_serialize<CHECK_CLASS>::value> Execr(Fs_Serialize::Serialize_Execr**&& ppExecr) {
        *ppExecr = nullptr;
    }

    void Serialize(Fs_Utility::IDataProp* pData, std::size_t TransId = 0) {

        if (!pData)
            return;

        Fs_Serialize::Serialize_Execr* _excer = nullptr;
        Fs_ClsObjectSerializeProxy<Ty, Base> _clsObj(m_Ptr, m_ApiId, (std::size_t)m_Ptr, (std::size_t)m_Ptr);
        Fs_ClsObjectSerializeProxy<Base, Base> __clsObj(m_Ptr, m_ApiId, (std::size_t)m_Ptr, (std::size_t)m_Ptr);

        Execr<Ty>(&_excer);
        if (_excer)
            _excer->Serialze(&_clsObj, pData, TransId);

        Execr<Base>(&_excer);
        if (_excer && !std::is_same<Ty, Base>::value)
            _excer->Serialze(&__clsObj, pData, TransId);
    }

    void DeSerialize(Fs_Utility::IDataPropIterator* pIter, std::size_t TransId = 0) {

        if (!pIter)
            return;

        Fs_Serialize::Serialize_Execr* _excer = nullptr;
        Fs_ClsObjectSerializeProxy<Ty, Base> _clsObj(m_Ptr, m_ApiId, (std::size_t)m_Ptr, (std::size_t)m_Ptr);
        Fs_ClsObjectSerializeProxy<Base, Base> __clsObj(m_Ptr, m_ApiId, (std::size_t)m_Ptr, (std::size_t)m_Ptr);

        Execr<Ty>(&_excer);
        if (_excer)
            _excer->DeSerialze(&_clsObj, pIter, TransId);

        pIter->Reset();

        Execr<Base>(&_excer);
        if (_excer && !std::is_same<Ty, Base>::value)
            _excer->DeSerialze(&__clsObj, pIter, TransId);
    }

    void ModifyAttribute(Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt) {

        if (!pIter)
            return;

        Fs_Serialize::Serialize_Execr* _excer = nullptr;
        Fs_ClsObjectSerializeProxy<Ty, Base> _clsObj(m_Ptr, m_ApiId, (std::size_t)m_Ptr, (std::size_t)m_Ptr);
        Fs_ClsObjectSerializeProxy<Base, Base> __clsObj(m_Ptr, m_ApiId, (std::size_t)m_Ptr, (std::size_t)m_Ptr);

        Execr<Ty>(&_excer);
        if (_excer)
            _excer->ModifyAttribute(&_clsObj, pIter, mt);

        pIter->Reset();

        Execr<Base>(&_excer);
        if (_excer && !std::is_same<Ty, Base>::value)
            _excer->ModifyAttribute(&__clsObj, pIter, mt);
    }
};


#endif  // SERIALIZE_CLSOBJECT_PROXY_H_