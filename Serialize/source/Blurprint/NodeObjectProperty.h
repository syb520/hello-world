/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: NodeObjectProperty.h
 *  作者: luwei
 *  日期: 2018/09/17
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_NODEOBJECTPROPERTY_H_  
#define SERIALIZE_NODEOBJECTPROPERTY_H_

//
#include "../../include/Blueprint/I_NodeObjectProperty.h"


class IObjectManager;

// 蓝图节点实现
class Fs_ClsObjectNodeProperty : public Fs_ObjectNodeProperty
{
    friend class BlueprintMgr;

public:
    virtual Fs_ClsObject* GetClsObject() override;
    virtual void AttachClsObject(Fs_ClsObject*);
    virtual void AttachClsObject(std::size_t) override;
    virtual void CloneClsObject(std::size_t) override;

    virtual TriggerAPI* _GetTriggerApi() override;
    virtual void SetTriggerApi(TriggerAPI*) override;

    virtual bool SetValue(INodePropertyObject* val) override;
    virtual bool SetValueWithConfig(const char* strValue) override;
    virtual bool Equal(INodePropertyObject* val) override;
    virtual std::string getValueSerialize() override;
    virtual int GetType() override;
    virtual int Compare(INodePropertyObject* other) override;

public:
    /*
    * @brief 构造函数
    */
    Fs_ClsObjectNodeProperty() noexcept;

    /*
    * @brief 复制构造函数
    */
    Fs_ClsObjectNodeProperty(const Fs_ClsObjectNodeProperty& rhs);

    /*
    * @brief 移动构造函数
    */
    Fs_ClsObjectNodeProperty(Fs_ClsObjectNodeProperty&& rhs) noexcept;

    /*
    * @brief 赋值操作
    */
    Fs_ClsObjectNodeProperty& operator =(const Fs_ClsObjectNodeProperty& rhs);

    /*
    * @brief 移动赋值
    */
    Fs_ClsObjectNodeProperty& operator =(Fs_ClsObjectNodeProperty&& rhs) noexcept;

    /*
    * @brief 拷贝
    */
    Fs_ClsObjectNodeProperty& Copy(const Fs_ClsObjectNodeProperty& rhs) noexcept;

    /*
    * @brief 判等
    */
    bool operator ==(const Fs_ClsObjectNodeProperty& rhs) const;

    /*
    * @brief 判不等
    */
    bool operator !=(const Fs_ClsObjectNodeProperty& rhs) const;

private:
    std::size_t m_ClsId;
    std::size_t m_ObjId;
    TriggerAPI* m_TriggerApi{ nullptr };
    Fs_ClsObject* m_pClsObj{ nullptr };
    IObjectManager* m_pObjMgr{ nullptr };
};


#endif  // SERIALIZE_I_NODEOBJECTPROPERTY_H_