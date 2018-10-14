#include "../../Include/Serialize_API.h"
#include "SerializeManager.h" 
#include "../Data.h" 
#include "../Data_Helper.h"
#include "../../SerializeConvert/include/i_serialize_convert.h"

// ÒýÈëconvert
extern SerializeConvert::ISerializeConvert* G_CreateSerializeConvert(Fs_Utility::IDataManager*);

namespace Fs_Serialize {

    class Serializer : public ISerializer
    {
    public:
        Serializer(ISerializerMgr* mgr, Fs_Utility::IDataManager* dataMgr) {
            _mgr = dynamic_cast<Fs_SerializerMgr*>(mgr);
            _dataMgr = dataMgr;
            _convert = G_CreateSerializeConvert(dataMgr);
        }

        virtual std::size_t CreateSerializeTransaction();
        virtual void FinishSerializeTransaction(std::size_t);

        virtual void SerializeTransactionResult(Fs_DataVector* pVecData, std::size_t);
        virtual void DeSerializeTransactionResult(Fs_ClsObjectVector* pVecObject, std::size_t);

        virtual bool AppendDataToTransaction(Fs_Utility::IData*, std::size_t transId = 0);
        virtual bool AppendDataToTransaction(Fs_DataVector*, std::size_t transId = 0);
        virtual void StartDeSerialize(std::size_t transId = 0);
        virtual Fs_ClsObject* StartOneDeSerialize(std::size_t objId, std::size_t transId = 0);

        virtual bool AppendObjectToTransaction(Fs_ClsObject*, std::size_t transId = 0);
        virtual bool AppendObjectToTransaction(Fs_ClsObjectVector*, std::size_t transId = 0);
        virtual void StartSerialize(std::size_t transId = 0);
        virtual Fs_Utility::IData* StartOneSerialize(std::size_t objId, std::size_t transId = 0);

        virtual void ModifyAttibute(const Fs_Utility::IDataModifier&);

        virtual bool ConvertToByte(Fs_Utility::IData*, Fs_Utility::IStringGuard** pString, SerializeFileFormat);
        virtual bool ConvertToByte(Fs_DataVector*, Fs_Utility::IStringGuard** pString, SerializeFileFormat);
        virtual bool ConvertFromByte(Fs_Utility::IData*, const char* strData, SerializeFileFormat);
        virtual bool ConvertFromByte(Fs_DataVector*, const char* strData, SerializeFileFormat);
        virtual bool ConvertFromFile(Fs_Utility::IData*, const char* strFileName, SerializeFileFormat);
        virtual bool ConvertFromFile(Fs_DataVector*, const char* strFileName, SerializeFileFormat);

    protected:
        Fs_SerializerMgr* _mgr; 
        Fs_Utility::IDataManager* _dataMgr;
        SerializeConvert::ISerializeConvert* _convert;
    };


    //---------------------------------------------------------------------------------------------------------

    std::size_t Serializer::CreateSerializeTransaction()
    {
        return _mgr->CreateTransaction();
    }

    void Serializer::FinishSerializeTransaction(std::size_t transId)
    {
        _mgr->FinishTransaction(transId);
    }
    
    
    //---------------------------------------------------------------------------------------------------------

    void Serializer::SerializeTransactionResult(Fs_DataVector* pVecData, std::size_t transId)
    {
        if (!pVecData)
            return;

        std::vector<Fs_Utility::IData*> vecData;
        _mgr->TransactionResult(&vecData, nullptr, transId);

        for (auto data : vecData)
            pVecData->_Push_Back(data);
    }

    void Serializer::DeSerializeTransactionResult(Fs_ClsObjectVector* pVecObject, std::size_t transId)
    {
        if (!pVecObject)
            return;

        std::vector<Fs_ClsObject*> vecObject;
        _mgr->TransactionResult(nullptr, &vecObject, transId);

        for (auto obj : vecObject)
            pVecObject->_Push_Back(obj);
    }


    //---------------------------------------------------------------------------------------------------------

    bool Serializer::AppendDataToTransaction(Fs_Utility::IData* data, std::size_t transId /*= 0*/)
    {
        if (!data || data->m_basic->m_ObjectId == 0)
            return false;

        Task* pTask = _mgr->GetTransactionTask(transId);
        if (!pTask)
            return false;

        pTask->mapData.insert(std::make_pair(data->m_basic->m_ObjectId, std::make_pair(data->Guid(), false)));

        return true;
    }

    bool Serializer::AppendDataToTransaction(Fs_DataVector* pVecData, std::size_t transId /*= 0*/)
    {
        if (!pVecData)
            return false;

        for (std::size_t index = 0; index < pVecData->_Size(); index++)
            AppendDataToTransaction(pVecData->_Memory(index), transId);

        return true;
    }

    void Serializer::StartSerialize(std::size_t transId /*= 0*/)
    {
        _mgr->StartSerialize(transId);
    }

    Fs_Utility::IData* Serializer::StartOneSerialize(std::size_t objId, std::size_t transId /*= 0*/)
    {
        return _mgr->StartOneSerialize(objId, transId);
    }


    //---------------------------------------------------------------------------------------------------------

    bool Serializer::AppendObjectToTransaction(Fs_ClsObject* pObj, std::size_t transId /*= 0*/)
    {
        if (!pObj || pObj->ObjectId() == 0)
            return false;

        Task* pTask = _mgr->GetTransactionTask(transId);
        if (!pTask)
            return false;

        pTask->mapObject.insert(std::make_pair(pObj->ObjectId(), false));

        return true;
    }

    bool Serializer::AppendObjectToTransaction(Fs_ClsObjectVector* pVecObject, std::size_t transId /*= 0*/)
    {
        if (!pVecObject)
            return false;

        for (std::size_t index = 0; index < pVecObject->_Size(); index++)
            AppendObjectToTransaction(pVecObject->_Memory(index), transId);

        return true;
    }
    
    void Serializer::StartDeSerialize(std::size_t transId /*= 0*/)
    {
        _mgr->StartDeSerialize(transId);
    }

    Fs_ClsObject* Serializer::StartOneDeSerialize(std::size_t objId, std::size_t transId /*= 0*/)
    {
        return _mgr->StartOneDeSerialize(objId, transId);
    }

    
    //---------------------------------------------------------------------------------------------------------

    void Serializer::ModifyAttibute(const Fs_Utility::IDataModifier& modifer)
    {
        _mgr->ModifyAttibute(modifer);
    }


    //---------------------------------------------------------------------------------------------------------

    bool Serializer::ConvertToByte(Fs_Utility::IData* pData, Fs_Utility::IStringGuard** pString, SerializeFileFormat fmt)
    {
        if (!pData || (
            fmt != SerializeFileFormat::YAML &&
            fmt != SerializeFileFormat::XML &&
            fmt != SerializeFileFormat::JSON))
            return false;

        Fs_Utility::DataManager* _ImplDataMgr = dynamic_cast<Fs_Utility::DataManager*>(_dataMgr);
        if (!_ImplDataMgr)
            return false;

        std::string strData;
        _convert->Convert(pData, strData, SerializeConvert::ConvertFormat(int(fmt) * 2 - 1));

        Fs_Utility::IStringGuard* pStringGuard = _ImplDataMgr->CreateStringGuard(strData.c_str());
        *pString = pStringGuard;

        return !strData.empty();
    }

    bool Serializer::ConvertToByte(Fs_DataVector* pVecData, Fs_Utility::IStringGuard** pString, SerializeFileFormat fmt)
    {
        if (fmt != SerializeFileFormat::YAML &&
            fmt != SerializeFileFormat::XML &&
            fmt != SerializeFileFormat::JSON)
            return false;

        Fs_Utility::DataManager* _ImplDataMgr = dynamic_cast<Fs_Utility::DataManager*>(_dataMgr);
        if (!_ImplDataMgr)
            return false;

        if (!pVecData)
            return false;

        std::vector<Fs_Utility::IData*> vecData;
        for (std::size_t index = 0; index < pVecData->_Size(); index++)
            vecData.push_back(pVecData->_Memory(index));

        std::string strData;
        _convert->Convert(vecData, strData, SerializeConvert::ConvertFormat(int(fmt) * 2 - 1));

        Fs_Utility::IStringGuard* pStringGuard = _ImplDataMgr->CreateStringGuard(strData.c_str());
        *pString = pStringGuard;

        return !strData.empty();
    }

    bool Serializer::ConvertFromByte(Fs_Utility::IData* pData, const char* pStrData, SerializeFileFormat fmt)
    {
        if (!pData || (
            fmt != SerializeFileFormat::YAML &&
            fmt != SerializeFileFormat::XML &&
            fmt != SerializeFileFormat::JSON))
            return false;

        std::string strData = pStrData;
        return _convert->Convert(pData, strData, SerializeConvert::ConvertFormat(int(fmt) * 2));
    }

    bool Serializer::ConvertFromByte(Fs_DataVector* pVecData, const char* pStrData, SerializeFileFormat fmt)
    {
        if (fmt != SerializeFileFormat::YAML &&
            fmt != SerializeFileFormat::XML &&
            fmt != SerializeFileFormat::JSON)
            return false;

        std::string strData = pStrData;
        std::vector<Fs_Utility::IData*> vecData;
        bool IsSucess = _convert->Convert(vecData, strData, SerializeConvert::ConvertFormat(int(fmt) * 2));

        for (auto data : vecData)
            pVecData->_Push_Back(data);

        return IsSucess;
    }

    bool Serializer::ConvertFromFile(Fs_Utility::IData* pData, const char* strFileName, SerializeFileFormat fmt)
    {
        std::string strData;
        if (_convert->ReadFile(strFileName, strData, SerializeConvert::SerializedFormat(fmt)))
            return ConvertFromByte(pData, strData.c_str(), fmt);

        return false;
    }

    bool Serializer::ConvertFromFile(Fs_DataVector* pVecData, const char* strFileName, SerializeFileFormat fmt)
    {
        std::string strData;
        if (_convert->ReadFile(strFileName, strData, SerializeConvert::SerializedFormat(fmt)))
            return ConvertFromByte(pVecData, strData.c_str(), fmt);

        return false;
    }
}


//---------------------------------------------------------------------------------------------------------


Fs_Serialize::ISerializer* G_CreateSerializer(ISerializerMgr* mgr, Fs_Utility::IDataManager* dataMgr)
{
    return new Fs_Serialize::Serializer(mgr, dataMgr);
}
