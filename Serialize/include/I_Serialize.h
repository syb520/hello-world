/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  �ļ�: ISerialize.h
 *  ����: luwei
 *  ����: 2018/08/31
 *  �汾: 1.0 
 *  ˵��: 
 ******************************************************************/  
  
#ifndef SERIALIZE_ISERIALIZE_H_  
#define SERIALIZE_ISERIALIZE_H_

#include <utility>
#include <vector>
#include <map> 
#include "I_Data.h"
#include "I_Data_Helper.h"
#include "Serialize/Define.h"
#include "Blueprint/I_Blueprint.h"


// ����
class Fs_ClsObject;
class Fs_ObjectCreator;
class Fs_ObjectNodeProperty;

// �������
class IObjectFactory {
public:
    virtual void Merge(IObjectFactory* pFactory) = 0;
    virtual Fs_Basic* CreateBasic(std::size_t classId, const char* name) = 0;
    virtual void Regist(std::size_t classId, Fs_ObjectCreator* pCreator, bool bReplaced = true) = 0;
    virtual void UnRegistCreator(std::size_t classId, Fs_ObjectCreator* pCreator, bool bReplaced = true) = 0;
};
class IObjectManager {
public:
    virtual void Merge(IObjectManager*) = 0;
    virtual Fs_ClsObject* CreateObject(std::size_t ClsId, std::size_t ObjectId = 0) = 0;
    virtual Fs_ClsObject* CreateObject(std::size_t ClsId, const char* ClsName, std::size_t FactoryId, const char* Method, std::size_t ObjectId = 0/**/) = 0;
    virtual Fs_ClsObject* FindObjectByObjectId(std::size_t ObjectId) = 0;
    virtual Fs_ClsObject* FindObjectByInstanceId(std::size_t InstanceId) = 0;
    virtual bool ExistObject(std::size_t InstanceId) = 0;
    virtual bool DeleteObject(std::size_t, bool AlsoAutoDeleteInstance = false) = 0;
};

// ���л�����
namespace Fs_Serialize {

    enum SerializeFileFormat {
        YAML = 1,
        XML  = 2,
        JSON = 3
    };

    class ISerializer
    {
    public:
        // ����
        virtual std::size_t CreateSerializeTransaction() = 0;
        virtual void FinishSerializeTransaction(std::size_t) = 0;

        // ��ȡ���
        virtual void SerializeTransactionResult(Fs_DataVector* pVecData, std::size_t) = 0;
        virtual void DeSerializeTransactionResult(Fs_ClsObjectVector* pVecObject, std::size_t) = 0;

        // �����л�
        virtual void StartDeSerialize(std::size_t transId = 0) = 0;
        virtual Fs_ClsObject* StartOneDeSerialize(std::size_t objId, std::size_t transId = 0) = 0;
        virtual bool AppendDataToTransaction(Fs_Data*, std::size_t transId = 0) = 0;
        virtual bool AppendDataToTransaction(Fs_DataVector*, std::size_t transId = 0) = 0;

        // ���л�
        virtual void StartSerialize(std::size_t transId = 0) = 0;
        virtual Fs_Data* StartOneSerialize(std::size_t objId, std::size_t transId = 0) = 0;
        virtual bool AppendObjectToTransaction(Fs_ClsObject*, std::size_t transId = 0) = 0;
        virtual bool AppendObjectToTransaction(Fs_ClsObjectVector*, std::size_t transId = 0) = 0;

        // �޸Ķ�������
        virtual void ModifyAttibute(const Fs_DataModifier&) = 0;

        // ���ݶ������ı�ת��
        virtual bool ConvertToByte(AGR_IN Fs_Data*, AGR_OUT Fs_StringGuard** pString, SerializeFileFormat) = 0;
        virtual bool ConvertToByte(AGR_IN Fs_DataVector*, AGR_OUT Fs_StringGuard** pString, SerializeFileFormat) = 0;
        virtual bool ConvertFromByte(AGR_OUT Fs_Data*, AGR_IN const char* strData, SerializeFileFormat) = 0;
        virtual bool ConvertFromByte(AGR_OUT Fs_DataVector*, AGR_IN const char* strData, SerializeFileFormat) = 0;
        virtual bool ConvertFromFile(AGR_OUT Fs_Data*, AGR_IN const char* strFileName, SerializeFileFormat) = 0;
        virtual bool ConvertFromFile(AGR_OUT Fs_DataVector*, AGR_IN const char* strFileName, SerializeFileFormat) = 0;
    };

    class Serialize_Execr;
}

class ISerializerMgr {
public:
    virtual void Merge(ISerializerMgr* pMgr) = 0;
    virtual void RegistSerializeExecr(Fs_Serialize::Serialize_Execr*) = 0;
    virtual Fs_Serialize::Serialize_Execr* GetSerializeExecr(std::size_t ClsId) = 0;
};


#endif  // SERIALIZE_ISERIALIZE_H_
