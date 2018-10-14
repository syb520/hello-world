/*******************************************************************
 *  Copyright(c) 2000-2017 SnailGame
 *  All rights reserved.
 *
 *  文件: ObjectFactory.h
 *  作者: luwei
 *  日期: 2018/07/24
 *  版本: 1.0
 *  说明:
 ******************************************************************/

#ifndef SERIALIZE_OBJECTFACTORY_H
#define SERIALIZE_OBJECTFACTORY_H

#include <map>                                         
#include "../../include/I_Serialize.h"
#include "../../include/Serialize/ObjectFactory/Fs_ObjectCreator.h" 
#include "../../include/Serialize/ObjectFactory/Fs_ClsObject.h" 


class Fs_ObjectFactory : public IObjectFactory
{
public:
    virtual void Merge(IObjectFactory* pFactory);
    virtual Fs_Utility::IBasic* CreateBasic(std::size_t classId, const char* name);

    template<class... Args>
    Fs_ClsObject* CreateByClassId(unsigned int apiId, std::size_t classId, Args... args) {
        
        Fs_ObjectCreator* pCreator = nullptr;
        
        if (_creator.find(classId) == _creator.end())
            return nullptr;

        pCreator = _creator[classId];
        if (!pCreator)
            return nullptr;

        Fs_ObjectCreatorProxy<Fs_ClsObject, Args...>* pCreatorProxy =
            dynamic_cast<Fs_ObjectCreatorProxy<Fs_ClsObject, Args...>*>(pCreator);
        if (!pCreatorProxy)
            return nullptr;

        Fs_ClsObject* pObject = pCreatorProxy->Create(apiId, std::forward<Args>(args)...);
        pObject->m_Basic = CreateBasic(classId, pCreatorProxy->CreatorName());
        return pObject;
    }

    virtual void Regist(std::size_t classId, Fs_ObjectCreator* pCreator, bool bReplaced = true);
    virtual void UnRegistCreator(std::size_t classId, Fs_ObjectCreator* pCreator, bool bReplaced = true){}

    std::map<std::size_t, Fs_ObjectCreator*> _creator;
};

#endif // SERIALIZE_OBJECTFACTORY_H
