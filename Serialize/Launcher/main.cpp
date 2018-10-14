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
    // 获取API                                                                            
    Fs_Serialize::ISerializerApi* pSerializerApi = Fs_Serialize::GlobalSerializerApi();

    // 获取管理类
    Fs_Serialize::ISerializer* pSerializer = pSerializerApi->GetSerializer();
    Fs_Utility::IDataManager* pDataMgr = pSerializerApi->GetDataManager();
    
    // 创建事务
    std::size_t transId = pSerializer->CreateSerializeTransaction();

    // 读取yaml
    std::string strYaml;
    QFile i_qfile(i_file);
    if (i_qfile.open(QIODevice::ReadOnly | QIODevice::Text))
        strYaml = i_qfile.readAll().toStdString();
    i_qfile.close();

    // 数据转化
    Fs_DataVector* pVecData = pDataMgr->CreateDataVectorGuard();
    pSerializer->ConvertFromByte(pVecData, strYaml.c_str(), Fs_Serialize::YAML);

    // 添加数据
    pSerializer->AppendDataToTransaction(pVecData, transId);

    // 反序列化
    pSerializer->StartDeSerialize(transId);

    // 序列化
    pSerializer->StartSerialize(transId);

    // 数据转化
    pVecData->Clear();
    pSerializer->SerializeTransactionResult(pVecData, transId);

    //
    Fs_Utility::IStringGuard* pMemory;
    pSerializer->ConvertToByte(pVecData, &pMemory, Fs_Serialize::YAML);

    // 保存yaml
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

    // 读取yaml
    std::string strYaml;
    QFile file(q_file);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        strYaml = file.readAll().toStdString();
    file.close();

    // 数据转化
    pSerializerApi->GetSerializer()->ConvertFromByte(pVecData, strYaml.c_str(), Fs_Serialize::YAML);
}

void TestWriteOnePrefab(int i, Fs_Utility::IData* pData, Fs_Utility::IDataManager* pDataMgr, Fs_Serialize::ISerializer* pSerializer)
{
    QString q_file;
    q_file = QString("..\\..\\Test\\TestFile\\Result\\test_prefab_result%1.yaml").arg(i);

    // 数据转化    
    Fs_Utility::IStringGuard* pMemory;
    pSerializer->ConvertToByte(pData, &pMemory, Fs_Serialize::YAML);

    // 保存yaml
    QFile file(q_file);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        file.write(pMemory->_Memory());
    file.close();

    pDataMgr->DestroyMemoryGuard(pMemory);
}

void TestPrefab()
{
    // 获取
    Fs_Serialize::ISerializerApi* pSerializerApi = Fs_Serialize::GlobalSerializerApi();
    Fs_Serialize::ISerializer* pSerializer = pSerializerApi->GetSerializer();
    Fs_Utility::IDataManager* pDataMgr = pSerializerApi->GetDataManager();
    std::size_t transId = pSerializer->CreateSerializeTransaction();

    // 读取数据                               
    Fs_DataVector* pVecData = pDataMgr->CreateDataVectorGuard();
    TestReadOnePrefab(pVecData, 1, pSerializerApi);
    //TestReadOnePrefab(vecData, 2);
    TestReadOnePrefab(pVecData, 3, pSerializerApi);

    // 添加数据
    pSerializer->AppendDataToTransaction(pVecData, transId);

    // 反序列化
    pSerializer->StartDeSerialize(transId);

    // 序列化
    pSerializer->StartSerialize(transId);

    pVecData->Clear();
    pSerializer->SerializeTransactionResult(pVecData, transId);

    for (std::size_t i = 0; i < pVecData->_Size(); i++)
        TestWriteOnePrefab(i + 1, pVecData->_Memory(i), pDataMgr, pSerializer);

    pDataMgr->DestroyMemoryGuard(pVecData);
}

void TestMap()
{
    // 获取api
    Fs_Serialize::ISerializerApi* pSerializerApi = Fs_Serialize::GlobalSerializerApi();
    Fs_Serialize::ISerializer* pSerializer = pSerializerApi->GetSerializer();
    Fs_Utility::IDataManager* pDataMgr = pSerializerApi->GetDataManager();
    IObjectManager* pObjectMgr = pSerializerApi->GetObjectManager();
    std::size_t transId = pSerializer->CreateSerializeTransaction();

    // 创建对象
    Fs_ClsObject* pObj = pObjectMgr->CreateObject(2);
    Fs_Utility::IData* pData2 = pSerializer->StartOneSerialize(pObj->ObjectId(), 0);

    Fs_Utility::IStringGuard* pMemory;
    pSerializer->ConvertToByte(pData2, &pMemory, Fs_Serialize::YAML);
    std::cout << pMemory->_Memory();

    pDataMgr->DestroyMemoryGuard(pMemory);
}

extern int bp_main(int argc, char **argv);



void TestNew() {

    // 获取API                                                                            
    Fs_Serialize::ISerializerApi* pSerializerApi = Fs_Serialize::GlobalSerializerApi();

    // 获取管理类
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
    // 获取API                                                                            
    Fs_Serialize::ISerializerApi* pSerializerApi = Fs_Serialize::GlobalSerializerApi();

    // 获取管理类
    Fs_Serialize::ISerializer* pSerializer = pSerializerApi->GetSerializer();
    IObjectManager* pObjMgr = pSerializerApi->GetObjectManager();
    Fs_Utility::IDataManager* pDataMgr = pSerializerApi->GetDataManager();

    // 创建对象, 指定测试使用的objid
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

    // 序列化
    std::cout << "==============Serialize::Result=============" << std::endl;
    Serialize();

    // 修改属性
    //std::string modifyText = "DllC_Derived:\n  ClassId: 2\n  ObjectId: 567890000\n  ObjectProperty:\n    x: 4";  // E_ADD
    std::string modifyText = "DllC_Derived:\n  ClassId: 2\n  ObjectId: 567890000\n  ObjectProperty:\n    x:\n      0: 5"; // E_MODIFY
    Fs_Utility::IData* pData = pDataMgr->CreateData();
    pSerializer->ConvertFromByte(pData, modifyText.c_str(), Fs_Serialize::YAML);

    // 显示修改 
    std::cout << "===================Modify===================" << std::endl;
    ShowText(pData);

    // 修改数据
    Fs_Utility::IDataModifier m;
    m.m_ObjectId = 567890000;
    m.m_Type = Fs_Utility::E_MODIFY;
    m.m_NewValue = pData;
    pSerializer->ModifyAttibute(m);

    // 显示修改后的结果
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
