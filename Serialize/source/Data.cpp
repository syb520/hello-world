#include "Data.h"
#include "Data_Helper.h"


namespace Fs_Utility
{

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

	DataProp::~DataProp()
	{
		for (auto it : m_Children) {
			delete it.second;
		}
		m_Children.clear();

        if (m_Iterator)
            delete m_Iterator;
	}

    void DataProp::SetDataManager(IDataManager* dataMgr)
    {
        m_DataMgr = dataMgr;
    }

    void DataProp::AddChild(const char* name, IDataProp* prop)
    {
        if (!name || !prop)
            return;

        if (m_Children.find(name) == m_Children.end())
        {
            m_Children.insert(std::make_pair(name, prop));
            prop->SetParent(this);
        }
    }

    void DataProp::AddChild(IDataProp* prop)
    {
        if (prop)
            AddChild(prop->GetName(), prop);
    }

    IDataProp* DataProp::FindChild(const char* name)
    {
        if (name && m_Children.find(name) != m_Children.end())
            return m_Children[name];
        return nullptr;
    }

	bool DataProp::Remove(const char* name)
	{
		if (name && m_Children.find(name) != m_Children.end())
        {
            delete m_Children[name];
            m_Children.erase(name);
            return true;
        }
		return false;
	}

    IDataProp* DataProp::Take(const char* name)
    {
        if (name && m_Children.find(name) != m_Children.end())
        {
            IDataProp* prop = m_Children[name];
            m_Children.erase(name);
            return prop;
        }

        return nullptr;
    }

    void DataProp::Combine(IDataProp* i_prop, bool bCover /*= false*/)
    {
        if (!i_prop)
            return;
        
        // »ù±¾ÊôÐÔ
        if (bCover)
        {
            this->m_Value = i_prop->m_Value;
            this->m_Category = i_prop->m_Category;
            this->m_ClsId = i_prop->m_ClsId;
            this->m_ObjId = i_prop->m_ObjId;
        }

        // Key
        if (this->m_KeyData)
            this->m_KeyData->Combine(i_prop->m_KeyData, bCover);

        // Child
        DataProp* d_prop = dynamic_cast<DataProp*>(i_prop);
        for (auto iter : d_prop->_Children())
        {
            IDataProp* prop = nullptr;

            if (this->m_Children.find(iter.first) == this->m_Children.end())
            {
                prop = m_DataMgr->CreateDataProp();
                prop->SetName(iter.second->GetName());
                this->AddChild(prop);
            }
            else if (bCover)
            {
                prop = this->m_Children[iter.first];
            }

            if (prop)
                prop->Combine(iter.second, true);
        }
    }

    void DataProp::Clear()
	{
		m_Children.clear();
	}

    IDataProp* DataProp::Parent()
    {
        return m_Parent;
    }

    void DataProp::SetParent(IDataProp* prop)
    {
        m_Parent = prop;
    }

    size_t DataProp::Size()
    {
        return m_Children.size();
    }

    bool DataProp::Dirty()
    {
        return m_IsDirty;
    }


    const std::map<std::string, IDataProp*>& DataProp::_Children()
    {
        return m_Children;
    }

    IDataPropIterator* DataProp::GetIterator()
    {
        if (m_Iterator)
            m_Iterator->Reset();
        else
            m_Iterator = new DataPropIterator(this);

        return m_Iterator;
    }


    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////


    Data::Data(IDataManager* dataMgr)
    {
        m_DataMgr = dataMgr;
        m_dp = m_DataMgr->CreateDataProp();
        m_dp->m_Category = DataProp::VT_MAP;
        m_basic = new Basic;
    }

    Data::~Data()
    {
        delete m_basic;
    }

    void Data::AddChildProp(const char* name, IDataProp* prop)
    {
        if (!name || !prop)
            return;

        prop->SetParent(m_dp);
        m_dp->AddChild(name, prop);
    }

    IDataProp* Data::RootProp()
    {
        return m_dp;
    }

    IDataProp* Data::FindChildProp(const char* name)
    {
        return m_dp->FindChild(name);
    }

    IDataProp* Data::NextSiblingProp(IDataProp* prop)
    {
        if (!prop || prop == m_dp || !prop->Parent())
            return nullptr;

        DataProp* d_parent = dynamic_cast<DataProp*>(prop->Parent());
        auto iter = d_parent->_Children().find(prop->GetName());
        if (iter == d_parent->_Children().end() ||
            ++iter == d_parent->_Children().end())
            return nullptr;

        return iter->second;
    }

    void Data::Combine(IData* i_data, bool bCover /*= false*/)
    {
        if (!i_data)
            return;

        this->m_dp->Combine(i_data->RootProp(), bCover);
    }

    
}

