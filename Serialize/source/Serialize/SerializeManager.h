/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: SerializeManager.h
 *  作者: luwei
 *  日期: 2018/08/06
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_SERIALIZEMANAGER_H_  
#define SERIALIZE_SERIALIZEMANAGER_H_

#include "../../include/I_Serialize.h"
#include <mutex>
#include <set>
#include <stack>

class Fs_ClsObject;
class Fs_ObjectManager;
class Fs_SerializerMgr;

namespace Fs_Serialize {
    class Serialize_Execr;
    class Task {
        friend class Serializer;
        friend class Fs_SerializerMgr;
        std::size_t transId;
        
        std::map<std::size_t, std::pair<std::size_t, bool>> mapData; //ObjId,<DataGuid, bool>
        std::map<std::size_t, bool> mapObject; //ObjId

        // bool值: 表示该数据/实例对象 是否是序列化/反序列化过程中生成
    };
}

class Fs_SerializerMgr : public ISerializerMgr
{
public:
    Fs_SerializerMgr(IObjectManager*, Fs_Utility::IDataManager*);
    void Merge(ISerializerMgr* pMgr);

    void RegistSerializeExecr(Fs_Serialize::Serialize_Execr*);
    Fs_Serialize::Serialize_Execr* GetSerializeExecr(size_t ClsId);

    void StartSerialize(std::size_t transId = 0);
    Fs_Utility::IData* StartOneSerialize(std::size_t objId, std::size_t transId = 0);
    void StartDeSerialize(std::size_t transId = 0);
    Fs_ClsObject* StartOneDeSerialize(std::size_t objId, std::size_t transId = 0);

    void ModifyAttibute(const Fs_Utility::IDataModifier&);
    Fs_Utility::IDataProp* SerializeModifer(const Fs_Utility::IDataModifier&);

    std::size_t CreateTransaction();
    void FinishTransaction(std::size_t transId = 0);
    bool TransactionResult(std::vector<Fs_Utility::IData*>*, std::vector<Fs_ClsObject*>*, std::size_t transId = 0);
    Fs_Serialize::Task* GetTransactionTask(std::size_t transId = 0);

protected:
    std::map<std::size_t, Fs_Serialize::Serialize_Execr*> m_callback;
    std::map<std::size_t, Fs_Serialize::Task*> m_tasks;
    std::mutex m_mutex;
    Fs_ObjectManager* _objMgr;
    Fs_Utility::IDataManager* _dataMgr;

    std::stack<std::size_t> _Undo;
    std::stack<std::size_t> _Redo;
};



#endif  // SERIALIZE_SERIALIZEMANAGER_H_