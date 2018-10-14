/*******************************************************************
 *  Copyright(c) 2000-2017 SnailGame
 *  All rights reserved.
 *
 *  文件: ObjectManager.h
 *  作者: luwei
 *  日期: 2018/07/24
 *  版本: 1.0
 *  说明:
 ******************************************************************/

#ifndef SERIALIZE_OBJECTMANAGER_H
#define SERIALIZE_OBJECTMANAGER_H

#include "Fs_ObjectFactory.h" 
#include "../../include/I_Serialize.h"

class Fs_ObjectManager : public IObjectManager
{
    friend class Fs_ObjectFactory;

public:
    Fs_ObjectManager(IObjectFactory*, Fs_Serialize::ISerializerApi*);

    virtual void Merge(IObjectManager*);
    virtual Fs_ClsObject* CreateObject(std::size_t ClsId, std::size_t ObjectId = 0);
    virtual Fs_ClsObject* CreateObject(std::size_t ClsId, const char* ClsName, std::size_t ExternFactoryId, const char* Method, std::size_t ObjectId = 0/**/);
    virtual Fs_ClsObject* FindObjectByObjectId(std::size_t ObjectId);
    virtual Fs_ClsObject* FindObjectByInstanceId(std::size_t InstanceId);
    virtual bool ExistObject(std::size_t InstanceId);
    virtual bool DeleteObject(std::size_t, bool AlsoAutoDeleteInstance = false);
    virtual void RegistClassInfo(std::size_t ClsId, Fs_Utility::IBasic*);
 
protected:
    // key=ObjectId
    std::map<std::size_t, Fs_ClsObject*> m_Objects;
    // key=InstId, value=ObjectId
    std::map<std::size_t, std::size_t> m_Instances;
    // key=ClsId, value=Basic
    std::map<std::size_t, Fs_Utility::IBasic*> m_ClassInfo;
    //
    Fs_ObjectFactory* m_pFactory{ nullptr };
    Fs_Utility::IGuidGenerator* m_pGuidGenerator{ nullptr };
    Fs_Serialize::ISerializerApi* m_Api{ nullptr };
};

#endif // SERIALIZE_OBJECTMANAGER_H
