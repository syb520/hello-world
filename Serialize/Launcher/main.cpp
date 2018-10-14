#include <QtCore/QCoreApplication>
#include <QDir>
#include <QLibrary>
#include <QDebug>

#include "../Serialize/include/Serialize_API.h" 


void Resolve(QFileInfo fi) {

    QLibrary lib(fi.absoluteFilePath());

    if (!lib.load())
        return;

#ifndef SERIALIZE_DYNAMIC_LIB

    typedef void(*_INIT_MANAGER_)(ObjectManager*);
    typedef void(*_INIT_FACTORY_)(Fs_ObjectFactory*);
    typedef void(*_INIT_SERIALIZE_)(Fs_SerializerMgr*);

    _INIT_MANAGER_ _init_mgr = (_INIT_MANAGER_)(lib.resolve("InitObjectManager"));
    _INIT_FACTORY_ _init_fac = (_INIT_FACTORY_)(lib.resolve("InitObjectFactory"));
    _INIT_SERIALIZE_ _init_ser = (_INIT_SERIALIZE_)(lib.resolve("InitSerializerMgr"));

    if (!_init_mgr || !_init_fac || !_init_ser)
        return;

    _init_mgr(Fs_Serialize::GetObjectManager());
    _init_fac(Fs_Serialize::GetObjectFactory());
    _init_ser(Fs_Serialize::GetSerializerMgr());

#endif

}

void Load() {

    QDir dir(qApp->applicationDirPath());
    QFileInfoList fileInfoList = dir.entryInfoList(QStringList() << "*.dll", QDir::Files);

    for (QFileInfo fi : fileInfoList)
        Resolve(fi);
}



void TestFile(const char* i_file, const char* o_file)
{
    // ��ȡAPI                                                                            
    Fs_Serialize::ISerializerApi* pSerializerApi = Fs_Serialize::GlobalSerializerApi();

    // ��ȡ������
    Fs_Serialize::ISerializer* pSerializer = pSerializerApi->GetSerializer();
    Fs_Utility::IDataManager* pDataMgr = pSerializerApi->GetDataManager();
    
    // ��������
    std::size_t transId = pSerializer->CreateSerializeTransaction();

    // ��ȡyaml
    std::string strYaml;
    QFile i_qfile(i_file);
    if (i_qfile.open(QIODevice::ReadOnly | QIODevice::Text))
        strYaml = i_qfile.readAll().toStdString();
    i_qfile.close();

    // ����ת��
    Fs_DataVector* pVecData = pDataMgr->CreateDataVectorGuard();
    pSerializer->ConvertFromByte(pVecData, strYaml.c_str(), Fs_Serialize::YAML);

    // �������
    pSerializer->AppendDataToTransaction(pVecData, transId);

    // �����л�
    pSerializer->StartDeSerialize(transId);

    // ���л�
    pSerializer->StartSerialize(transId);

    // ����ת��
    pVecData->Clear();
    pSerializer->SerializeTransactionResult(pVecData, transId);

    //
    Fs_Utility::IStringGuard* pMemory;
    pSerializer->ConvertToByte(pVecData, &pMemory, Fs_Serialize::YAML);

    // ����yaml
    QFile o_qfile(o_file);
    if (o_qfile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        o_qfile.write(pMemory->_Memory());
    o_qfile.close();

    pDataMgr->DestroyMemoryGuard(pMemory);
    pDataMgr->DestroyMemoryGuard(pVecData);
}

void TestFile(int i)
{
    QString i_file, o_file;
    i_file = QString("..\\..\\Test\\TestFile\\test%1.yaml").arg(i);
    o_file = QString("..\\..\\Test\\TestFile\\Result\\test%1_result.yaml").arg(i);

    TestFile(i_file.toStdString().c_str(), o_file.toStdString().c_str());
}

void TestOnlyOneFile()
{
    //TestFile(1);
    //TestFile(2);
    //TestFile(3);
    TestFile(4);
    //TestFile(5);
    //TestFile(6);
    //TestFile(7);
}



void TestReadOnePrefab(Fs_DataVector* pVecData, int i, Fs_Serialize::ISerializerApi* pSerializerApi)
{
    QString q_file;
    q_file = QString("..\\..\\Test\\TestFile\\test_prefab%1.yaml").arg(i);

    // ��ȡyaml
    std::string strYaml;
    QFile file(q_file);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        strYaml = file.readAll().toStdString();
    file.close();

    // ����ת��
    pSerializerApi->GetSerializer()->ConvertFromByte(pVecData, strYaml.c_str(), Fs_Serialize::YAML);
}

void TestWriteOnePrefab(int i, Fs_Utility::IData* pData, Fs_Utility::IDataManager* pDataMgr, Fs_Serialize::ISerializer* pSerializer)
{
    QString q_file;
    q_file = QString("..\\..\\Test\\TestFile\\Result\\test_prefab_result%1.yaml").arg(i);

    // ����ת��    
    Fs_Utility::IStringGuard* pMemory;
    pSerializer->ConvertToByte(pData, &pMemory, Fs_Serialize::YAML);

    // ����yaml
    QFile file(q_file);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        file.write(pMemory->_Memory());
    file.close();

    pDataMgr->DestroyMemoryGuard(pMemory);
}

void TestPrefab()
{
    // ��ȡ
    Fs_Serialize::ISerializerApi* pSerializerApi = Fs_Serialize::GlobalSerializerApi();
    Fs_Serialize::ISerializer* pSerializer = pSerializerApi->GetSerializer();
    Fs_Utility::IDataManager* pDataMgr = pSerializerApi->GetDataManager();
    std::size_t transId = pSerializer->CreateSerializeTransaction();

    // ��ȡ����                               
    Fs_DataVector* pVecData = pDataMgr->CreateDataVectorGuard();
    TestReadOnePrefab(pVecData, 1, pSerializerApi);
    //TestReadOnePrefab(vecData, 2);
    TestReadOnePrefab(pVecData, 3, pSerializerApi);

    // �������
    pSerializer->AppendDataToTransaction(pVecData, transId);

    // �����л�
    pSerializer->StartDeSerialize(transId);

    // ���л�
    pSerializer->StartSerialize(transId);

    pVecData->Clear();
    pSerializer->SerializeTransactionResult(pVecData, transId);

    for (std::size_t i = 0; i < pVecData->_Size(); i++)
        TestWriteOnePrefab(i + 1, pVecData->_Memory(i), pDataMgr, pSerializer);

    pDataMgr->DestroyMemoryGuard(pVecData);
}

void TestMap()
{
    // ��ȡapi
    Fs_Serialize::ISerializerApi* pSerializerApi = Fs_Serialize::GlobalSerializerApi();
    Fs_Serialize::ISerializer* pSerializer = pSerializerApi->GetSerializer();
    Fs_Utility::IDataManager* pDataMgr = pSerializerApi->GetDataManager();
    IObjectManager* pObjectMgr = pSerializerApi->GetObjectManager();
    std::size_t transId = pSerializer->CreateSerializeTransaction();

    // ��������
    Fs_ClsObject* pObj = pObjectMgr->CreateObject(2);
    Fs_Utility::IData* pData2 = pSerializer->StartOneSerialize(pObj->ObjectId(), 0);

    Fs_Utility::IStringGuard* pMemory;
    pSerializer->ConvertToByte(pData2, &pMemory, Fs_Serialize::YAML);
    std::cout << pMemory->_Memory();

    pDataMgr->DestroyMemoryGuard(pMemory);
}

extern int bp_main(int argc, char **argv);



void TestNew() {

    // ��ȡAPI                                                                            
    Fs_Serialize::ISerializerApi* pSerializerApi = Fs_Serialize::GlobalSerializerApi();

    // ��ȡ������
    Fs_Serialize::ISerializer* pSerializer = pSerializerApi->GetSerializer();
    IObjectManager* pObjMgr = pSerializerApi->GetObjectManager();
    Fs_Utility::IDataManager* pDataMgr = pSerializerApi->GetDataManager();

    Fs_ClsObject* pObj = pObjMgr->CreateObject(123);
    
    Fs_Utility::IData* pData = pSerializer->StartOneSerialize(pObj->ObjectId(), 0);

    Fs_Utility::IStringGuard* pMemory;
    pSerializer->ConvertToByte(pData, &pMemory, Fs_Serialize::YAML);
    std::cout << pMemory->_Memory();

    pDataMgr->DestroyMemoryGuard(pMemory);
}


void TestModify()
{
    // ��ȡAPI                                                                            
    Fs_Serialize::ISerializerApi* pSerializerApi = Fs_Serialize::GlobalSerializerApi();

    // ��ȡ������
    Fs_Serialize::ISerializer* pSerializer = pSerializerApi->GetSerializer();
    IObjectManager* pObjMgr = pSerializerApi->GetObjectManager();
    Fs_Utility::IDataManager* pDataMgr = pSerializerApi->GetDataManager();

    // ��������, ָ������ʹ�õ�objid
    Fs_ClsObject* pObj = pObjMgr->CreateObject(2, 567890000);
    

    auto ShowText = [&](Fs_Utility::IData* _arg_data)
    {
        Fs_Utility::IStringGuard* pMemory;
        pSerializer->ConvertToByte(_arg_data, &pMemory, Fs_Serialize::YAML);
        std::cout << pMemory->_Memory() << std::endl;
        pDataMgr->DestroyMemoryGuard(pMemory);
    };

    auto Serialize = [&]()
    {
        // 
        Fs_Utility::IData* _pData = pSerializer->StartOneSerialize(pObj->ObjectId(), 0);
        //
        ShowText(_pData);
    };

    // ���л�
    std::cout << "==============Serialize::Result=============" << std::endl;
    Serialize();

    // �޸�����
    //std::string modifyText = "DllC_Derived:\n  ClassId: 2\n  ObjectId: 567890000\n  ObjectProperty:\n    x: 4";  // E_ADD
    std::string modifyText = "DllC_Derived:\n  ClassId: 2\n  ObjectId: 567890000\n  ObjectProperty:\n    x:\n      0: 5"; // E_MODIFY
    Fs_Utility::IData* pData = pDataMgr->CreateData();
    pSerializer->ConvertFromByte(pData, modifyText.c_str(), Fs_Serialize::YAML);

    // ��ʾ�޸� 
    std::cout << "===================Modify===================" << std::endl;
    ShowText(pData);

    // �޸�����
    Fs_Utility::IDataModifier m;
    m.m_ObjectId = 567890000;
    m.m_Type = Fs_Utility::E_MODIFY;
    m.m_NewValue = pData;
    pSerializer->ModifyAttibute(m);

    // ��ʾ�޸ĺ�Ľ��
    std::cout << "===============Modify::Result===============" << std::endl;
    Serialize();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDir::setCurrent(a.applicationDirPath());

    Load();

    //TestNew();

    //TestPrefab();

    //bp_main(argc, argv);

    //TestOnlyOneFile();

    //TestMap();

    TestModify();

    return a.exec();
}
