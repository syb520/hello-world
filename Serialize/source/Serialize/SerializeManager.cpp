#include "../../Include/Serialize_API.h"
#include "../ObjectFactory/ObjectManager.h"
#include "SerializeManager.h"


ISerializerMgr* G_CreateSerializerMgr(IObjectManager* objMgr, Fs_Utility::IDataManager* dataMgr)
{
    static Fs_SerializerMgr _(objMgr, dataMgr);
    return &_;
}

Fs_SerializerMgr::Fs_SerializerMgr(IObjectManager* objMgr, Fs_Utility::IDataManager* dataMgr)
{
    _objMgr = dynamic_cast<Fs_ObjectManager*>(objMgr);
    _dataMgr = dataMgr;
}

void Fs_SerializerMgr::Merge(ISerializerMgr* pIMgr)
{
    if (!pIMgr)
        return;

    Fs_SerializerMgr* pMgr = dynamic_cast<Fs_SerializerMgr*>(pIMgr);
    if (!pMgr)
        return;

    for (auto iter : pMgr->m_callback)
        RegistSerializeExecr(iter.second);
}


void Fs_SerializerMgr::RegistSerializeExecr(Fs_Serialize::Serialize_Execr* pCb)
{
    if (pCb && (m_callback.find(pCb->GetClassId()) == m_callback.end()))
        m_callback.insert(std::make_pair(pCb->GetClassId(), pCb));
}

Fs_Serialize::Serialize_Execr* Fs_SerializerMgr::GetSerializeExecr(size_t ClsId)
{
    if (m_callback.find(ClsId) != m_callback.end())
        return m_callback[ClsId];
    return nullptr;
}



void Fs_SerializerMgr::StartSerialize(std::size_t transId /*= 0*/)
{
    Fs_Serialize::Task* pTask = GetTransactionTask(transId);
    if (!pTask)
        return;

    for (auto iter : pTask->mapObject)
    {
        if (pTask->mapData.find(iter.first) != pTask->mapData.end() &&
            pTask->mapData[iter.first].second)
            continue;

        StartOneSerialize(iter.first, transId);
    }
}

Fs_Utility::IData* Fs_SerializerMgr::StartOneSerialize(std::size_t objId, std::size_t transId /*= 0*/)
{
    Fs_Utility::IData* pData = nullptr;

    // 判断序列化Data是否存在
    Fs_Serialize::Task* pTask = GetTransactionTask(transId);
    if (!pTask)
        return nullptr;

    // 获取实例
    Fs_ClsObject* pObject = _objMgr->FindObjectByObjectId(objId);
    if (!pObject)
        return nullptr;

    // 构造数据
    pData = _dataMgr->CreateData();
    pTask->mapData[objId] = std::make_pair(pData->Guid(), true);

    // 属性复制
    pData->m_basic->SetName(pObject->Basic()->GetName());
    pData->m_basic->SetFactoryMethod(pObject->Basic()->GetFactoryMethod());
    pData->m_basic->m_ClsId = pObject->Basic()->m_ClsId;
    pData->m_basic->m_ObjectId = pObject->Basic()->m_ObjectId;
    pData->m_basic->m_FactoryId = pObject->Basic()->m_FactoryId;
    pData->m_basic->m_Prefab = pObject->Basic()->m_Prefab;

    // 序列化
    pObject->Serialize(pData->RootProp(), transId);

    return pData;
}

void Fs_SerializerMgr::StartDeSerialize(std::size_t transId /*= 0*/)
{
    Fs_Serialize::Task* pTask = GetTransactionTask(transId);
    if (!pTask)
        return;

    for (auto iter : pTask->mapData)
    {
        if (pTask->mapObject.find(iter.first) != pTask->mapObject.end() &&
            pTask->mapObject[iter.first])
            continue;

        StartOneDeSerialize(iter.first, transId);
    }
}

Fs_ClsObject* Fs_SerializerMgr::StartOneDeSerialize(std::size_t objId, std::size_t transId /*= 0*/)
{
    Fs_ClsObject* pObject = nullptr;

    // 判断序列化Data是否存在
    Fs_Serialize::Task* pTask = GetTransactionTask(transId);
    if (!pTask)
        return nullptr;

    // 检验Data
    Fs_Utility::IData* pData = _dataMgr->FindData(pTask->mapData[objId].first);
    if (!pData)
        return nullptr;

    // 创建对象
    if (!pObject)
    {
        if (pData->m_basic->m_FactoryId == 0)
            pObject = _objMgr->CreateObject(pData->m_basic->m_ClsId, pData->m_basic->m_ObjectId);
        else
            pObject = _objMgr->CreateObject(pData->m_basic->m_ClsId, pData->m_basic->GetName(), pData->m_basic->m_FactoryId,
                pData->m_basic->GetFactoryMethod(), pData->m_basic->m_ObjectId);

        if (!pObject)
            return nullptr;

        pTask->mapObject.insert(std::make_pair(objId, true));
    }

    // 判断Prefab
    if (pData->m_basic->m_Prefab != 0 &&
        pTask->mapData.find(pData->m_basic->m_Prefab) != pTask->mapData.end())
    {
        // 合并Data和Prefab Data
        Fs_Utility::IData* pPrefabData = _dataMgr->FindData(pTask->mapData[pData->m_basic->m_Prefab].first);
        pData->Combine(pPrefabData);
    }

    // 反序列化            
    Fs_Utility::IDataPropIterator* pIter = _dataMgr->CreateDataPropRecursionIterator(pData->RootProp());
    pObject->DeSerialize(pIter, transId);
    _dataMgr->DestroyDataIterator(pIter);

    return pObject;
}


void Fs_SerializerMgr::ModifyAttibute(const Fs_Utility::IDataModifier& modifier)
{
    // 格式化数据
    Fs_Utility::IDataProp* pPropData = SerializeModifer(modifier);
    if (!pPropData)
        return;

    // 获取对象
    Fs_ClsObject* pObj = _objMgr->FindObjectByObjectId(modifier.m_ObjectId);
    if (!pObj)
        return;

    Fs_Utility::IDataPropIterator* pIter = _dataMgr->CreateDataPropRecursionIterator(pPropData);
    pObj->ModifyAttribute(pIter, modifier.m_Type);
    _dataMgr->DestroyDataIterator(pIter);
}

Fs_Utility::IDataProp* Fs_SerializerMgr::SerializeModifer(const Fs_Utility::IDataModifier& modifier)
{
    Fs_Utility::IDataProp* pPropData = modifier.m_NewValue->RootProp();
    return pPropData;
}


std::size_t Fs_SerializerMgr::CreateTransaction()
{
    Fs_Serialize::Task* task = new Fs_Serialize::Task;
    task->transId = (std::size_t)task;

    std::lock_guard<std::mutex> guard(m_mutex);
    m_tasks.insert(std::make_pair(task->transId, task));

    return task->transId;
}

void Fs_SerializerMgr::FinishTransaction(std::size_t transId /*= 0*/)
{
    std::lock_guard<std::mutex> guard(m_mutex);

    if (m_tasks.find(transId) != m_tasks.end())
    {
        Fs_Serialize::Task* pTask = m_tasks[transId];
        m_tasks.erase(transId);
        delete pTask;
    }
}

bool Fs_SerializerMgr::TransactionResult(std::vector<Fs_Utility::IData*>* pDataList, std::vector<Fs_ClsObject*>* pObjList, std::size_t transId /*= 0*/)
{
    Fs_Serialize::Task* pTask = GetTransactionTask(transId);
    if (!pTask)
        return false;

    if (pDataList)
    {
        for (auto iter : pTask->mapData)
            pDataList->push_back(_dataMgr->FindData(iter.second.first));
    }

    if (pObjList)
    {
        for (auto iter : pTask->mapObject)
            pObjList->push_back(_objMgr->FindObjectByObjectId(iter.first));
    }

    return true;
}

Fs_Serialize::Task* Fs_SerializerMgr::GetTransactionTask(std::size_t transId)
{
    std::lock_guard<std::mutex> guard(m_mutex);

    if (transId == 0 && (m_tasks.find(0) == m_tasks.end()))
    {
        Fs_Serialize::Task* task = new Fs_Serialize::Task;
        task->transId = 0;
        m_tasks.insert(std::make_pair(0, task));
        return task;
    }

    if (m_tasks.find(transId) == m_tasks.end())
        return nullptr;

    return m_tasks[transId];
}

