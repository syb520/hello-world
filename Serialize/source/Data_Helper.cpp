#include "Data_Helper.h"
#include "Data.h"

Fs_Utility::IDataManager* G_CreateDataManager() {
    return new Fs_Utility::DataManager;
}

namespace Fs_Utility
{

    void DataManager::Merge(IDataManager* pMgr)
    {
    }
    
    IData* DataManager::FindData(std::size_t guid)
    {
        if (m_data.find(guid) != m_data.end())
            return m_data[guid];
        return nullptr;
    }


    IData* DataManager::CreateData()
    {
        Data* data = new Data(this);
        m_data.insert(std::make_pair(data->Guid(), data));
        return data;
    }

    IDataProp* DataManager::CreateDataProp()
    {
        DataProp* prop = new DataProp;
        prop->SetDataManager(this);
        m_dataProp.insert(std::make_pair(prop->Guid(), prop));
        return prop;
    }

    IDataPropIterator* DataManager::CreateDataPropRecursionIterator(IDataProp* prop)
    {
        DataPropRecursionIterator* iter = new DataPropRecursionIterator(prop);
        m_dataIterator.insert(std::make_pair(iter->Guid(), iter));
        return iter;
    }

    IStringGuard* DataManager::CreateStringGuard(const char* pMemory)
    {
        IStringGuard* pString = new StringGuard(pMemory);
        m_memoryGuard.insert(pString);
        return pString;
    }

    IVectorGuard<IData*>* DataManager::CreateDataVectorGuard()
    {
        VectorGuard<IData*>* pDataVector = new VectorGuard<IData*>;
        m_memoryGuard.insert(pDataVector);
        return pDataVector;
    }

    IVectorGuard<Fs_ClsObject*>* DataManager::CreateObjectVectorGuard()
    {
        VectorGuard<Fs_ClsObject*>* pObjectVector = new VectorGuard<Fs_ClsObject*>;
        m_memoryGuard.insert(pObjectVector);
        return pObjectVector;
    }


    void DataManager::DestroyData(IData* pData)
    {
        if (pData)
        {
            std::size_t guid = pData->Guid();
            delete m_data[guid];
            m_data.erase(guid);
        }
    }

    void DataManager::DestroyDataProp(IDataProp* pProp)
    {
        if (pProp)
        {
            std::size_t guid = pProp->Guid();
            delete m_dataProp[guid];
            m_dataProp.erase(guid);
        }
    }

    void DataManager::DestroyDataIterator(IDataPropIterator* pIter)
    {
        if (pIter)
        {
            std::size_t guid = pIter->Guid();
            delete m_dataIterator[guid];
            m_dataIterator.erase(guid);
        }
    }

    void DataManager::DestroyMemoryGuard(IMemoryGuard* pMemory)
    {
        m_memoryGuard.erase(pMemory);
        delete pMemory;
    }
    
    
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////


    DataPropIterator::DataPropIterator(IDataProp* pDataProp)
    {
        m_Root = dynamic_cast<DataProp*>(pDataProp);

        Reset();
    }

    void DataPropIterator::Reset()
    {
        if (!m_Root)
            return;

        m_Iter = m_Root->_Children().begin();
        if (!AtEnd())
            m_CurProp = m_Iter->second;
    }

    bool DataPropIterator::AtEnd()
    {
        if (m_Root && (m_Iter != m_Root->_Children().end()))
            return false;
        return true;
    }

    bool DataPropIterator::Next()
    {
        m_Iter++;

        bool bAtEnd = AtEnd();
        if (!bAtEnd)
            m_CurProp = m_Iter->second;

        return bAtEnd;
    }

    IDataProp* DataPropIterator::GetDataProp()
    {
        return m_CurProp;
    }

    const char* DataPropIterator::GetName()
    {
        if (!m_CurProp)
            return nullptr;
        return m_CurProp->GetName();
    }

    std::size_t DataPropIterator::GetClsId()
    {
        if (!m_CurProp)
            return 0;
        return m_CurProp->m_ClsId;
    }

    std::size_t DataPropIterator::GetObjectId()
    {
        if (!m_CurProp)
            return 0;
        return m_CurProp->m_ObjId;
    }

    Variant DataPropIterator::GetValue()
    {
        if (!m_CurProp)
            return Variant();
        return m_CurProp->m_Value;
    }


    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////


    DataPropRecursionIterator::DataPropRecursionIterator(IDataProp* rootProp)
        : DataPropIterator(rootProp)
    {
        Reset();
    }

    DataPropRecursionIterator::~DataPropRecursionIterator()
    {
        for (_MyIter* pIter : stackedProp)
            if (pIter) delete pIter;
    }

    void DataPropRecursionIterator::Reset()
    {
        m_CurProp = m_Root;

        for (_MyIter* pIter : stackedProp)
            if (pIter) delete pIter;

        stackedProp.clear();
        stackedProp.push_back(nullptr);
        into.clear();
    }

    bool DataPropRecursionIterator::AtEnd()
    {
        return stackedProp.empty();
    }
    
    bool DataPropRecursionIterator::Next()
    {
        if (AtEnd())
            return true;

        auto Back = [&]()
        {
            auto pIter = stackedProp.rbegin();

            if (!*pIter)
            {
                m_CurProp = nullptr;
                stackedProp.pop_back();
                return;
            }

            _MyIter& iter = **pIter;

            DataProp* d_curParent = nullptr;
            if (m_CurProp->Parent())
                d_curParent = dynamic_cast<DataProp*>(m_CurProp->Parent());

            if (d_curParent &&
                d_curParent->_Children().end() != iter &&
                d_curParent->_Children().end() != ++iter)
            {
                m_CurProp = iter->second;
                return;
            }
            else
            {
                m_CurProp = m_CurProp->Parent();
            }

            stackedProp.pop_back();
            delete &iter;

            Next();
        };

        DataProp* d_curProp = dynamic_cast<DataProp*>(m_CurProp);
        if (d_curProp->_Children().empty())
        {
            Back();
        }
        else
        {
            if (into.find(m_CurProp) == into.end())
            {
                into.insert(std::make_pair(m_CurProp, true));

                _MyIter iter = d_curProp->_Children().begin();
                _MyIter* pIter = new _MyIter(iter);
                stackedProp.push_back(pIter);

                m_CurProp = iter->second;
            }
            else
            {
                Back();
            }
        }

        return AtEnd();
    }
    
    bool DataPropRecursionIterator::NextSlibing()
    {
        if (AtEnd() || stackedProp.empty())
            return true;

        auto Back = [&]()
        {
            auto pIter = stackedProp.rbegin();

            if (!*pIter)
            {
                m_CurProp = nullptr;
                stackedProp.pop_back();
                return;
            }

            _MyIter& iter = **pIter;

            DataProp* d_curParent = nullptr;
            if (m_CurProp->Parent())
                d_curParent = dynamic_cast<DataProp*>(m_CurProp->Parent());

            if (d_curParent &&
                d_curParent->_Children().end() != iter &&
                d_curParent->_Children().end() != ++iter)
            {
                m_CurProp = iter->second;
                return;
            }
            else
            {
                m_CurProp = m_CurProp->Parent();
            }

            stackedProp.pop_back();
            delete &iter;

            NextSlibing();
        };

        Back();

        return AtEnd();
    }

}

