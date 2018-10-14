/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: BlurprintMgr.h
 *  作者: luwei
 *  日期: 2018/09/19
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_BLURPRINTMGR_H_  
#define SERIALIZE_BLURPRINTMGR_H_

#include "../../include/Blueprint/I_Blueprint.h"
#include "../../Include/I_Serialize.h"


class BlueprintMgr : public IBlueprintApi
{
public:
    BlueprintMgr(Fs_Serialize::ISerializer*, IObjectManager*, Fs_Utility::IDataManager*);

    // 设置触发器API
    virtual TriggerAPI* _GetTriggerApi() override { return m_TriggerApi; }
    virtual void InitTriggerApi(TriggerAPI* api) override;

    virtual INodePropertyObject* CreateNodeProperty(int) override;
    virtual void DestroyObjectNodeProperty(INodePropertyObject*) override;
    
    virtual void AddVariable() override;
    virtual void ModifyVariable() override;
    virtual void DeleteVariable() override;

    // 内部方法
    virtual INodePropertyObject* DeSerialize(Fs_Utility::IDataPropIterator*, std::size_t t = 0);
    virtual void Modify(INodePropertyObject*&, Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType);

    // 接口实现
    virtual Fs_Data* Serialize(INodePropertyObject*, std::size_t t = 0) override;
    virtual void DeSerialize(FsBp_CustomVariable*, Fs_Utility::IDataPropIterator*, std::size_t t = 0);
    virtual void DeSerialize(Fs_NodeVariable*, Fs_Utility::IDataPropIterator*, std::size_t t = 0);
    virtual void Modify(FsBp_CustomVariable*, Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType);
    virtual void Modify(Fs_NodeVariable*, Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType);


    std::map<std::size_t, INodePropertyObject*> m_NodePropertys;
    Fs_Serialize::ISerializer* m_Serializer;
    IObjectManager* m_ObjectMgr;
    Fs_Utility::IDataManager*  m_DataMgr;
    TriggerAPI* m_TriggerApi{ nullptr };

};

#endif  // SERIALIZE_BLURPRINTMGR_H_