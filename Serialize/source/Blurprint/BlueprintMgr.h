/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  �ļ�: BlurprintMgr.h
 *  ����: luwei
 *  ����: 2018/09/19
 *  �汾: 1.0 
 *  ˵��: 
 ******************************************************************/  
  
#ifndef SERIALIZE_BLURPRINTMGR_H_  
#define SERIALIZE_BLURPRINTMGR_H_

#include "../../include/Blueprint/I_Blueprint.h"
#include "../../Include/I_Serialize.h"


class BlueprintMgr : public IBlueprintApi
{
public:
    BlueprintMgr(Fs_Serialize::ISerializer*, IObjectManager*, Fs_Utility::IDataManager*);

    // ���ô�����API
    virtual TriggerAPI* _GetTriggerApi() override { return m_TriggerApi; }
    virtual void InitTriggerApi(TriggerAPI* api) override;

    virtual INodePropertyObject* CreateNodeProperty(int) override;
    virtual void DestroyObjectNodeProperty(INodePropertyObject*) override;
    
    virtual void AddVariable() override;
    virtual void ModifyVariable() override;
    virtual void DeleteVariable() override;

    // �ڲ�����
    virtual INodePropertyObject* DeSerialize(Fs_Utility::IDataPropIterator*, std::size_t t = 0);
    virtual void Modify(INodePropertyObject*&, Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType);

    // �ӿ�ʵ��
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