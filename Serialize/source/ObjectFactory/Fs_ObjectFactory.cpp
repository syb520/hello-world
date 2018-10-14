#include "../../Include/Serialize_API.h"
#include "Fs_ObjectFactory.h"
#include "../Data.h"



IObjectFactory* G_GetObjectFactory()
{
    static Fs_ObjectFactory _;
    return &_;
}

void Fs_ObjectFactory::Merge(IObjectFactory* pIFactory)
{
    if (!pIFactory)
        return;

    Fs_ObjectFactory* pFactory = dynamic_cast<Fs_ObjectFactory*>(pIFactory);
    if (!pFactory)
        return;

    for (auto iter : pFactory->_creator)
        Regist(iter.first, iter.second, true);
}

Fs_Utility::IBasic* Fs_ObjectFactory::CreateBasic(std::size_t classId, const char* name)
{
    Fs_Utility::Basic* _basic = new Fs_Utility::Basic;
    _basic->m_ClsId = classId;
    _basic->m_ClsName = name;
    return _basic;
}

void Fs_ObjectFactory::Regist(std::size_t classId, Fs_ObjectCreator* pCreator, bool bReplaced /*= true*/)
{
    if (!pCreator)
        return;

    bool exist = _creator.find(classId) != _creator.end();
    if (exist && bReplaced)
        _creator[classId] = pCreator;
    else if (!exist)
        _creator.insert(std::make_pair(classId, pCreator));
}
