#include "../../Include/Serialize_API.h"
#include "ObjectManager.h"
#include "../Utility.h"

//
#include "../../Reflect/include/reflection_helper.h"


IObjectManager* G_CreateObjectManager(IObjectFactory* fac, Fs_Serialize::ISerializerApi* api)
{
    return new Fs_ObjectManager(fac, api);
}


Fs_ObjectManager::Fs_ObjectManager(IObjectFactory* fac, Fs_Serialize::ISerializerApi* api)
{
    m_pFactory = dynamic_cast<Fs_ObjectFactory*>(fac);
    m_pGuidGenerator = api->GetGuidGenerator();
    m_Api = api;
}

void Fs_ObjectManager::Merge(IObjectManager* imgr)
{
    if (!imgr)
        return;

    Fs_ObjectManager* mgr = dynamic_cast<Fs_ObjectManager*>(imgr);
    if (!mgr)
        return;

    for (auto iter : mgr->m_Objects)
        m_Objects[iter.first] = iter.second;

    for (auto iter : mgr->m_Instances)
        m_Instances[iter.first] = iter.second;

    for (auto iter : mgr->m_ClassInfo)
        m_ClassInfo[iter.first] = iter.second;
}

Fs_ClsObject* Fs_ObjectManager::CreateObject(std::size_t ClsId, std::size_t ObjectId /*= 0*/)
{
    if (ObjectId == 0)
        ObjectId = m_pGuidGenerator->Hash(m_pGuidGenerator->Create(ClsId));

    Fs_ClsObject* pObject = FindObjectByObjectId(ObjectId);
    if (pObject)
        return pObject;

    pObject = m_pFactory->CreateByClassId(m_Api->UniqueId(), ClsId);
    if (!pObject)
        return nullptr;
    
    //
    pObject->m_Basic->m_ObjectId = ObjectId;
    RegistClassInfo(ClsId, pObject->m_Basic);

    //
    m_Objects.insert(std::make_pair(ObjectId, pObject));

    //
    m_Instances[pObject->ImplInstanceId()] = ObjectId;
    m_Instances[pObject->BaseInstanceId()] = ObjectId;

    return pObject;
}

Fs_ClsObject* Fs_ObjectManager::CreateObject(std::size_t ClsId, const char* ClsName, std::size_t ExternFactoryId, const char* Method, std::size_t ObjectId /*= 0*/)
{
    if (ObjectId == 0)
        ObjectId = m_pGuidGenerator->Hash(m_pGuidGenerator->Create(ClsId));

    Fs_ClsObject* pObject = FindObjectByObjectId(ObjectId);
    if (pObject)
        return pObject;

    // 创建工厂
    Fs_ClsObject* pFactoryObject = m_pFactory->CreateByClassId(m_Api->UniqueId(), ExternFactoryId);
    if (!pFactoryObject)
        return nullptr;

    void* pFactory = pFactoryObject->_MemoryInstance();
    if (!pFactory)
        return nullptr;

    Reflection::IReflection* iReflection = Reflection::GetReflection();
    if (!iReflection)
        return nullptr;

    Reflection::Args i_args, o_args;
    i_args.AddString(ClsName);
    iReflection->InvokeMethod(pFactory, pFactoryObject->ClassName(), Method, i_args, o_args);

    void* ObjPtr = o_args.PointerVal(0);
    if (!ObjPtr)
        return nullptr;

    // 是否要删除工厂
    if (false)
    {
        pFactoryObject->DestoryInstance();
        DeleteObject(pFactoryObject->ObjectId());
    }

    // 构造实例对象
    ISerializerMgr* serializerMgr = m_Api->GetSerializerMgr();
    Fs_Serialize::Serialize_Execr* pExecr = nullptr;
    if (pExecr = serializerMgr->GetSerializeExecr(ClsId))
        pObject = pExecr->CreateClsObj(m_Api->UniqueId(), ObjPtr);
    else
        pObject = new Fs_ClsObjectProxy<Fs_ClsObject::Fs_EmptyClsObj>((Fs_ClsObject::Fs_EmptyClsObj*)ObjPtr, (std::size_t)ObjPtr, (std::size_t)ObjPtr);

    pObject->m_Basic = m_pFactory->CreateBasic(ClsId, ClsName);

    //
    pObject->m_Basic->m_ObjectId = ObjectId;
    RegistClassInfo(ClsId, pObject->m_Basic);

    //
    m_Objects.insert(std::make_pair(ObjectId, pObject));

    //
    m_Instances[pObject->ImplInstanceId()] = ObjectId;
    m_Instances[pObject->BaseInstanceId()] = ObjectId;

    return pObject;
}



bool Fs_ObjectManager::ExistObject(std::size_t InstanceId)
{
    return (m_Instances.find(InstanceId) != m_Instances.end());
}

bool Fs_ObjectManager::DeleteObject(std::size_t ObjectId, bool AlsoAutoDeleteInstance /*= false*/)
{
    if (m_Objects.find(ObjectId) != m_Objects.end())
    {
        Fs_ClsObject* pObj = m_Objects[ObjectId];

        m_Instances.erase(pObj->ImplInstanceId());
        m_Instances.erase(pObj->BaseInstanceId());

        m_Objects.erase(ObjectId);
        delete pObj;

        return true;
    }

    return false;
}

Fs_ClsObject* Fs_ObjectManager::FindObjectByObjectId(std::size_t ObjectId)
{
    if (m_Objects.find(ObjectId) != m_Objects.end())
        return m_Objects[ObjectId];

    return nullptr;
}

Fs_ClsObject* Fs_ObjectManager::FindObjectByInstanceId(std::size_t InstanceId)
{
    if (m_Instances.find(InstanceId) != m_Instances.end())
        return FindObjectByObjectId(m_Instances[InstanceId]);

    return nullptr;
}

void Fs_ObjectManager::RegistClassInfo(std::size_t ClsId, Fs_Utility::IBasic* basic)
{
    m_ClassInfo[ClsId] = basic;
}

