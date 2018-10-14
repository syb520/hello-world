#include "BlueprintMgr.h" 
#include "NodeObjectProperty.h"
#include "UnpackNodeProperty.h"
#include "../../Include/Blueprint/I_CustomVariable.h" 
#include "../../Include/Blueprint/I_NodeObjectProperty.h"

// 注册
MAKE_REGIST_OBJECT_WITH_GUID(FsBp_CustomVariable, FsBp_CustomVariable, 20202020, true)


extern IBlueprintApi* G_CreateBlueprintApi(Fs_Serialize::ISerializer* pSerializer, IObjectManager* pObjMgr, Fs_Utility::IDataManager* pDataMgr) {
    return new BlueprintMgr(pSerializer, pObjMgr, pDataMgr);
}


BlueprintMgr::BlueprintMgr(Fs_Serialize::ISerializer* pSerializer, IObjectManager* pObjMgr, Fs_Utility::IDataManager* pDataMgr)
{
    m_Serializer = pSerializer;
    m_ObjectMgr = pObjMgr;
    m_DataMgr = pDataMgr;
}

void BlueprintMgr::InitTriggerApi(TriggerAPI* api)
{
    m_TriggerApi = api;

    static Fs_ArrayNodePropertyFac _1;
    static Fs_SetNodePropertyFac _2;
    static Fs_MapNodePropertyFac _3;
    static Fs_ObjectNodePropertyFac _4;
    m_TriggerApi->RegPropertyType(&_1);
    m_TriggerApi->RegPropertyType(&_2);
    m_TriggerApi->RegPropertyType(&_3);
    m_TriggerApi->RegPropertyType(&_4);
}


INodePropertyObject* BlueprintMgr::CreateNodeProperty(int type)
{
    INodePropertyObject* _ = nullptr;

    switch (type)
    {
    case TRIGGER_TYPE_BOOL:
        _ = m_TriggerApi->CreateInsByType(TRIGGER_TYPE_BOOL);
        break;
    case TRIGGER_TYPE_INT:
        _ = m_TriggerApi->CreateInsByType(TRIGGER_TYPE_INT);
        break;
    case TRIGGER_TYPE_INT64:
        _ = m_TriggerApi->CreateInsByType(TRIGGER_TYPE_INT64);
        break;
    case TRIGGER_TYPE_FLOAT:
        _ = m_TriggerApi->CreateInsByType(TRIGGER_TYPE_FLOAT);
        break;
    case TRIGGER_TYPE_DOUBLE:
        _ = m_TriggerApi->CreateInsByType(TRIGGER_TYPE_DOUBLE);
        break;
    case TRIGGER_TYPE_STRING:
        _ = m_TriggerApi->CreateInsByType(TRIGGER_TYPE_STRING);
        break;
    case TRIGGER_TYPE_WIDESTR:
        _ = m_TriggerApi->CreateInsByType(TRIGGER_TYPE_WIDESTR);
        break;
    case Fs_ArrayNodeProperty_Type:
        _ = m_TriggerApi->CreateInsByType(Fs_ArrayNodeProperty_Type);
        break;
    case Fs_SetNodeProperty_Type:
        _ = m_TriggerApi->CreateInsByType(Fs_SetNodeProperty_Type);
        break;
    case Fs_MapNodeProperty_Type:
        _ = m_TriggerApi->CreateInsByType(Fs_MapNodeProperty_Type);
        break;
    case Fs_ObjectNodeProperty_Type:
        {
            Fs_ClsObjectNodeProperty* pNode = new Fs_ClsObjectNodeProperty;
            pNode->m_pObjMgr = m_ObjectMgr;
            pNode->m_TriggerApi = m_TriggerApi;
            _ = pNode;
        }
        break;
    default:
        break;
    }

    if (_)
        m_NodePropertys.insert(std::make_pair((std::size_t)_, _));

    return _;
}

void BlueprintMgr::DestroyObjectNodeProperty(INodePropertyObject* _)
{
    std::size_t _id = (std::size_t)_;
    if (m_NodePropertys.find(_id) != m_NodePropertys.end())
    {
        m_NodePropertys.erase(_id);
        delete _;
    }
}


void BlueprintMgr::AddVariable()
{
    throw std::logic_error("The method or operation is not implemented.");
}

void BlueprintMgr::ModifyVariable()
{
    throw std::logic_error("The method or operation is not implemented.");
}

void BlueprintMgr::DeleteVariable()
{
    throw std::logic_error("The method or operation is not implemented.");
}


Fs_Data* BlueprintMgr::Serialize(INodePropertyObject* node, std::size_t t /*= 0*/)
{
    if (!node || !m_Serializer)
        return nullptr;

    //Fs_ClsObject* clsObj = clsObjNode->GetClsObject();
    //return m_Serializer->StartOneSerialize(clsObj->ObjectId(), t);
}

INodePropertyObject* BlueprintMgr::DeSerialize(Fs_Utility::IDataPropIterator* pIter, std::size_t t /*= 0*/)
{
    if (!pIter || !pIter->GetDataProp() || !m_Serializer)
        return nullptr;

    Fs_Utility::IDataProp* propType = pIter->GetDataProp()->FindChild("Type");
    Fs_Utility::IDataProp* propProp = pIter->GetDataProp()->FindChild("Property");
    if (!propType || !propProp)
        return nullptr;

    // 获取类型
    int type = propType->m_Value.ToInt();
    Fs_Blueprint::BlueprintUnpackValue unpacker(m_Serializer, this, t);
    Fs_Utility::IDataPropIterator* _pIter = m_DataMgr->CreateDataPropRecursionIterator(propProp);

    switch (type)
    {
    case TRIGGER_TYPE_BOOL:
    {
        TriggerBoolean* pNode = ((TriggerBoolean*)m_TriggerApi->CreateInsByType(TRIGGER_TYPE_BOOL));
        unpacker.UnpackValue(_pIter, pNode);
        return pNode;
    }
    case TRIGGER_TYPE_INT:
    {
        TriggerInt* pNode = ((TriggerInt*)m_TriggerApi->CreateInsByType(TRIGGER_TYPE_INT));
        unpacker.UnpackValue(_pIter, pNode);
        return pNode;
    }
    case TRIGGER_TYPE_INT64:
    {
        TriggerInt64* pNode = ((TriggerInt64*)m_TriggerApi->CreateInsByType(TRIGGER_TYPE_INT64));
        unpacker.UnpackValue(_pIter, pNode);
        return pNode;
    }
    case TRIGGER_TYPE_FLOAT:
    {
        TriggerFloat* pNode = ((TriggerFloat*)m_TriggerApi->CreateInsByType(TRIGGER_TYPE_FLOAT));
        unpacker.UnpackValue(_pIter, pNode);
        return pNode;
    }
    case TRIGGER_TYPE_DOUBLE:
    {
        TriggerDouble* pNode = ((TriggerDouble*)m_TriggerApi->CreateInsByType(TRIGGER_TYPE_DOUBLE));
        unpacker.UnpackValue(_pIter, pNode);
        return pNode;
    }
    case TRIGGER_TYPE_STRING:
    {
        TriggerString* pNode = ((TriggerString*)m_TriggerApi->CreateInsByType(TRIGGER_TYPE_STRING));
        unpacker.UnpackValue(_pIter, pNode);
        return pNode;
    }
    case TRIGGER_TYPE_WIDESTR:
    {
        TriggerWString* pNode = ((TriggerWString*)m_TriggerApi->CreateInsByType(TRIGGER_TYPE_WIDESTR));
        unpacker.UnpackValue(_pIter, pNode);
        return pNode;
    }
    case Fs_ArrayNodeProperty_Type:
    {
        Fs_ArrayNodeProperty* pNode = ((Fs_ArrayNodeProperty*)m_TriggerApi->CreateInsByType(Fs_ArrayNodeProperty_Type));
        unpacker.UnpackValue(_pIter, pNode);
        return pNode;
    }
    case Fs_SetNodeProperty_Type:
    {
        Fs_SetNodeProperty* pNode = ((Fs_SetNodeProperty*)m_TriggerApi->CreateInsByType(Fs_SetNodeProperty_Type));
        unpacker.UnpackValue(_pIter, pNode);
        return pNode;
    }
    case Fs_MapNodeProperty_Type:
    {
        Fs_MapNodeProperty* pNode = ((Fs_MapNodeProperty*)m_TriggerApi->CreateInsByType(Fs_MapNodeProperty_Type));
        unpacker.UnpackValue(_pIter, pNode);
        return pNode;
    }
    case Fs_ObjectNodeProperty_Type:
    {
        Fs_ObjectNodeProperty* pNode = ((Fs_ObjectNodeProperty*)m_TriggerApi->CreateInsByType(Fs_ObjectNodeProperty_Type));
        unpacker.UnpackValue(_pIter, pNode);
        return pNode;
    }
    default:
        break;
    }

    return nullptr;
}

void BlueprintMgr::Modify(INodePropertyObject*&, Fs_Utility::IDataPropIterator* pIter, Fs_Utility::ModifyType mt)
{
    if (!pIter || !pIter->GetDataProp())
        return;

    // 构造Data
    Fs_Data* pData = m_DataMgr->CreateData();
    pData->m_basic->m_ClsId = pIter->GetClsId();
    pData->m_basic->m_ObjectId = pIter->GetObjectId();
    pData->AddChildProp(pIter->GetName(), pIter->GetDataProp());

    Fs_DataModifier dm;
    dm.m_ObjectId = pIter->GetObjectId();
    dm.m_NewValue = pData;
    dm.m_Type = mt;

    m_Serializer->ModifyAttibute(dm);
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


void BlueprintMgr::DeSerialize(FsBp_CustomVariable* pVar, Fs_Utility::IDataPropIterator* pIter, std::size_t t /*= 0*/)
{
    if (!pVar || !pIter || !pIter->GetDataProp())
        return;

    Fs_ClsObject* pClsObj =
        m_Serializer->StartOneDeSerialize(pIter->GetDataProp()->m_Value.ToUnSignedInt(), t);

    if (pClsObj)
        *pVar = *pClsObj->GetInstance<FsBp_CustomVariable>();
}

void BlueprintMgr::DeSerialize(Fs_NodeVariable* pNodeVar, Fs_Utility::IDataPropIterator* pIter, std::size_t t /*= 0*/)
{
    if (!pNodeVar || !pIter || !pIter->GetDataProp())
        return;

    Fs_Utility::IDataProp* propAccess = pIter->GetDataProp()->FindChild("Access");
    if (propAccess)
        pNodeVar->Access = (AccessLevel)propAccess->m_Value.ToInt();

    pNodeVar->NodeProperty = DeSerialize(pIter, t);

    pIter->Next();
    pIter->Next();
    pIter->Next();
}



void BlueprintMgr::Modify(FsBp_CustomVariable*, Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType)
{

}

void BlueprintMgr::Modify(Fs_NodeVariable*, Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType)
{

}

