/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: I_Blueprint.h
 *  作者: luwei
 *  日期: 2018/09/19
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_I_BLUEPRINT_H_  
#define SERIALIZE_I_BLUEPRINT_H_

#include "../I_Data.h"           
#include "../../../Blueprint/include/node_property_object.h"  
#include "../../../Blueprint/include/trigger_api.h" 

 //                 
class Fs_NodeVariable;
class FsBp_CustomVariable;

class IBlueprintApi 
{
public:
    // 设置触发器API
    virtual TriggerAPI* _GetTriggerApi() = 0;
    virtual void InitTriggerApi(TriggerAPI*) = 0;

    // 创建容器
    virtual INodePropertyObject* CreateNodeProperty(int) = 0;
    virtual void DestroyObjectNodeProperty(INodePropertyObject*) = 0;

    // 增删改成员变量
    virtual void AddVariable() = 0;
    virtual void ModifyVariable() = 0;
    virtual void DeleteVariable() = 0;

    // 序列化
    virtual Fs_Data* Serialize(INodePropertyObject*, std::size_t t = 0) = 0;
    virtual void DeSerialize(FsBp_CustomVariable*, Fs_Utility::IDataPropIterator*, std::size_t t = 0) = 0;
    virtual void DeSerialize(Fs_NodeVariable*, Fs_Utility::IDataPropIterator*, std::size_t t = 0) = 0;
    virtual void Modify(FsBp_CustomVariable*, Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType) = 0;
    virtual void Modify(Fs_NodeVariable*, Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType) = 0;
};

#endif  // SERIALIZE_I_BLUEPRINT_H_