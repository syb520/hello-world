/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: I_NodeObjectProperty.h
 *  作者: luwei
 *  日期: 2018/09/17
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_I_NODEOBJECTPROPERTY_H_  
#define SERIALIZE_I_NODEOBJECTPROPERTY_H_

#include "I_Blueprint.h"
#include "../Serialize/ObjectFactory/Fs_ClsObject.h"
#include "../Serialize_API.h"

 //
#define Fs_ArrayNodeProperty_Type  10083
#define Fs_SetNodeProperty_Type    10084   
#define Fs_MapNodeProperty_Type    10085
#define Fs_ObjectNodeProperty_Type 10086


class Fs_NodeProperty : public INodePropertyObject
{
public:

    template<class T>
    auto SetReference(const T& obj) {
        //
        AttachClsObject((size_t)&obj);
        //
        _GetTriggerApi()->UploadPropertyUpdata(this);
    }

    template<class T>
    auto SetInstance(const T& obj) {
        //
        CloneClsObject((size_t)&obj);
        //
        _GetTriggerApi()->UploadPropertyUpdata(this);
    }

    template<class T>
    std::decay_t<T>& GetReference() {
        return *(GetClsObject()->GetInstance<std::decay_t<T>>());
    }

    template<class T>
    auto GetInstance() {
        return GetClsObject()->GetInstance<std::decay_t<T>>();
    }

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    virtual TriggerAPI* _GetTriggerApi() = 0;
    virtual void SetTriggerApi(TriggerAPI*) = 0;
    virtual Fs_ClsObject* GetClsObject() = 0;
private:
    virtual void AttachClsObject(std::size_t) = 0;
    virtual void CloneClsObject(std::size_t) = 0;
};


class Fs_ArrayNodeProperty : public Fs_NodeProperty
{
};

class Fs_SetNodeProperty : public Fs_NodeProperty
{
};

class Fs_MapNodeProperty : public Fs_NodeProperty
{
};

class Fs_ObjectNodeProperty : public Fs_NodeProperty
{
};


#define DECLEAR_NodeProperty_FACTORY(CLSDESC, TYPE)                                 \
class Fs_##CLSDESC##Fac : public INodePropertyFactory                               \
{                                                                                   \
public:                                                                             \
    virtual INodePropertyObject* CreateNewProperty()                                \
    {                                                                               \
        Fs_Serialize::ISerializerApi* api = Fs_Serialize::GlobalSerializerApi();    \
        IBlueprintApi* bpApi = api->GetBlurprintApi();                              \
        return bpApi->CreateNodeProperty(TYPE);                                     \
    }                                                                               \
    virtual void FreePropertyInst(INodePropertyObject* inst)                        \
    {                                                                               \
        inst->instLog = NULL;                                                       \
        delete inst;                                                                \
    }                                                                               \
    virtual int GetPropertyType()                                                   \
    {                                                                               \
        return TYPE;                                                                \
    }                                                                               \
};

DECLEAR_NodeProperty_FACTORY(ArrayNodeProperty, Fs_ArrayNodeProperty_Type)
DECLEAR_NodeProperty_FACTORY(SetNodeProperty, Fs_SetNodeProperty_Type)
DECLEAR_NodeProperty_FACTORY(MapNodeProperty, Fs_MapNodeProperty_Type)
DECLEAR_NodeProperty_FACTORY(ObjectNodeProperty, Fs_ObjectNodeProperty_Type)


#endif  // SERIALIZE_I_NODEOBJECTPROPERTY_H_