#include "NodeObjectProperty.h"
#include "trigger_system_type.h"
#include "trigger_api.h"  
#include "../../include/Serialize_API.h"


Fs_ClsObject* Fs_ClsObjectNodeProperty::GetClsObject()
{
    return m_pClsObj;
}

void Fs_ClsObjectNodeProperty::AttachClsObject(std::size_t instId)
{
    AttachClsObject(m_pClsObj = m_pObjMgr->FindObjectByInstanceId(instId));
}

void Fs_ClsObjectNodeProperty::AttachClsObject(Fs_ClsObject* clsObj)
{
    if (clsObj)
    {
        m_ClsId = clsObj->ClassId();
        m_ObjId = clsObj->ObjectId();
        m_pClsObj = clsObj;
    }
}

void Fs_ClsObjectNodeProperty::CloneClsObject(std::size_t instId)
{
    Fs_ClsObject* clsObj = m_pObjMgr->FindObjectByInstanceId(instId);
    if (clsObj)
    {
        m_pClsObj = m_pObjMgr->CreateObject(clsObj->ClassId());
        if (m_pClsObj && m_pClsObj->CloneInstance(clsObj))
        {
            m_ClsId = m_pClsObj->ClassId();
            m_ObjId = m_pClsObj->ObjectId();
        }
    }
}

TriggerAPI* Fs_ClsObjectNodeProperty::_GetTriggerApi()
{
    return m_TriggerApi;
}

void Fs_ClsObjectNodeProperty::SetTriggerApi(TriggerAPI* api)
{
    m_TriggerApi = api;
}

bool Fs_ClsObjectNodeProperty::SetValue(INodePropertyObject* val)
{
    Fs_ClsObjectNodeProperty* _property = dynamic_cast<Fs_ClsObjectNodeProperty*>(val);
    if (!_property || _property == this || !m_TriggerApi)
        return false;

    // ÒÆ¶¯
    *this = std::move(*_property);

    return m_TriggerApi->UploadPropertyUpdata(this);
}

bool Fs_ClsObjectNodeProperty::SetValueWithConfig(const char*)
{
    return false;
}

bool Fs_ClsObjectNodeProperty::Equal(INodePropertyObject* val)
{
    Fs_ClsObjectNodeProperty* _property = dynamic_cast<Fs_ClsObjectNodeProperty*>(val);
    return _property && *this == *_property;
}

std::string Fs_ClsObjectNodeProperty::getValueSerialize()
{
    return "";
}

int Fs_ClsObjectNodeProperty::GetType()
{
    return Fs_ObjectNodeProperty_Type;
}

int Fs_ClsObjectNodeProperty::Compare(INodePropertyObject* other)
{
    Fs_ClsObjectNodeProperty* _property = dynamic_cast<Fs_ClsObjectNodeProperty*>(other);
    return (_property && _property->m_ClsId == _property->m_ClsId) 
        ? (this->m_ObjId == _property->m_ObjId 
            ? CMP_RES_EQU 
            : (this->m_ObjId < _property->m_ObjId 
                ? CMP_RES_LESS 
                : CMP_RES_GREAT))
        : CMP_RES_OP_NOT_SUPPORT;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


Fs_ClsObjectNodeProperty::Fs_ClsObjectNodeProperty() noexcept
    : m_ClsId(0), m_ObjId(0)
{
}

Fs_ClsObjectNodeProperty::Fs_ClsObjectNodeProperty(Fs_ClsObjectNodeProperty&& rhs) noexcept 
    : m_ClsId(rhs.m_ClsId), m_ObjId(rhs.m_ObjId), m_TriggerApi(rhs.m_TriggerApi), m_pClsObj(rhs.m_pClsObj), m_pObjMgr(rhs.m_pObjMgr)
{
}

Fs_ClsObjectNodeProperty::Fs_ClsObjectNodeProperty(const Fs_ClsObjectNodeProperty& rhs) 
    : m_ClsId(rhs.m_ClsId), m_ObjId(rhs.m_ObjId), m_TriggerApi(rhs.m_TriggerApi), m_pClsObj(rhs.m_pClsObj), m_pObjMgr(rhs.m_pObjMgr)
{

}

Fs_ClsObjectNodeProperty& Fs_ClsObjectNodeProperty::operator=(Fs_ClsObjectNodeProperty&& rhs) noexcept
{
    this->Copy(std::move(rhs));
    return *this;
}

Fs_ClsObjectNodeProperty& Fs_ClsObjectNodeProperty::operator=(const Fs_ClsObjectNodeProperty& rhs)
{
    this->Copy(rhs);
    return *this;
}

Fs_ClsObjectNodeProperty& Fs_ClsObjectNodeProperty::Copy(const Fs_ClsObjectNodeProperty& rhs) noexcept
{
    if (&rhs != this)
    {
        m_ClsId = rhs.m_ClsId;
        m_ObjId = rhs.m_ObjId;
        m_pClsObj = rhs.m_pClsObj;
        m_pObjMgr = rhs.m_pObjMgr;
        m_TriggerApi = rhs.m_TriggerApi;
    }

    return *this;
}

bool Fs_ClsObjectNodeProperty::operator!=(const Fs_ClsObjectNodeProperty& rhs) const
{
    return (m_ClsId != rhs.m_ClsId || m_ObjId != rhs.m_ObjId);
}

bool Fs_ClsObjectNodeProperty::operator==(const Fs_ClsObjectNodeProperty& rhs) const
{
    return (m_ClsId == rhs.m_ClsId && m_ObjId == rhs.m_ObjId);
}
