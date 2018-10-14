/*******************************************************************
*  Copyright(c) 2000-2017 SnailGame
*  All rights reserved.
*
*  �ļ�: Serialize_API.h
*  ����: luwei
*  ����: 2018/08/06
*  �汾: 1.0
*  ˵��:
******************************************************************/

#ifndef SERIALIZE_SERIALIZE_EXPORT_API_H_  
#define SERIALIZE_SERIALIZE_EXPORT_API_H_

#include <type_traits> 

// ����������
#include "I_Serialize.h"

//
namespace Fs_Serialize {

    class ISerializerApi
    {
    public:
        // API's GUID
        virtual unsigned int UniqueId() = 0;

        // ��ȡ���л�API
        virtual ISerializer* GetSerializer() = 0;
        
        // ��ȡ���л����ݹ���
        virtual Fs_Utility::IDataManager* GetDataManager() = 0;
        
        // ��ȡGUID������
        virtual Fs_Utility::IGuidGenerator* GetGuidGenerator() = 0;
        
        // ��ȡ���л�������
        virtual ISerializerMgr* GetSerializerMgr() = 0;
        
        // ��ȡ���󹤳�
        virtual IObjectFactory* GetObjectFactory() = 0;
        
        // ��ȡ�������
        virtual IObjectManager* GetObjectManager() = 0;
        
        // ��ȡ��ͼAPI
        virtual IBlueprintApi* GetBlurprintApi() = 0;
    };

#ifdef __cplusplus
    extern "C" {
#endif // __cplusplus
        
        Fs_Serialize::ISerializerApi* GlobalSerializerApi();
        Fs_Serialize::ISerializerApi* CreateSerializerApi(unsigned int apiId);
        void DestorySerializerApi(unsigned int apiId);
       
#ifdef __cplusplus
    }
#endif // __cplusplus

}

// ��ʹ�ö�̬�⣬����Ҫ����Ԥ����� SERIALIZE_DYNAMIC_LIB

#include "Serialize/Dynamic.h"


// ���л���
// �����޳�Ա������Ҫ���л������Բ��������л���
#ifndef MAKE_SERIALIZE
#define MAKE_SERIALIZE(CLSNAME,BASECLS,...)
#endif

#ifndef MAKE_SERIALIZE_WITH_GUID
#define MAKE_SERIALIZE_WITH_GUID(CLSNAME,BASECLS,_GUID_,...)
#endif 

#ifndef MAKE_SERIALIZE_T
#define MAKE_SERIALIZE_T(CLSNAME,BASECLS,...)
#endif

#ifndef MAKE_SERIALIZE_EXTRA_T
#define MAKE_SERIALIZE_EXTRA_T(CLSNAME,BASECLS)
#endif

#ifndef MAKE_SERIALIZE_WITH_GUID_T
#define MAKE_SERIALIZE_WITH_GUID_T(CLSNAME,BASECLS,_GUID_,...)
#endif 

#ifndef MAKE_SERIALIZE_EXTRA_WITH_GUID_T
#define MAKE_SERIALIZE_EXTRA_WITH_GUID_T(CLSNAME,BASECLS,_GUID_)
#endif 

// �����ʼ��
#ifndef MAKE_REGIST_OBJECT
#define MAKE_REGIST_OBJECT(_OBJ_,_IOBJ_,_REPLACED_,...)
#endif

#ifndef MAKE_REGIST_OBJECT_WITH_GUID
#define MAKE_REGIST_OBJECT_WITH_GUID(_OBJ_,_IOBJ_,_ID_SELF_,_REPLACED_,...)
#endif 

#ifndef MAKE_REGIST_OBJECT_CALLBACK
#define MAKE_REGIST_OBJECT_CALLBACK(_OBJ_,_IOBJ_,_REPLACED_,_CALLBACK_,...)
#endif

#ifndef MAKE_REGIST_OBJECT_CALLBACK_WITH_GUID
#define MAKE_REGIST_OBJECT_CALLBACK_WITH_GUID(_OBJ_,_IOBJ_,_ID_SELF_,_REPLACED_,_CALLBACK_,...)
#endif

//
#ifndef MAKE_GUID
#define MAKE_GUID(CLSNAME)
#endif

//#include "Serialize/Serialize/Serialize_Micro.h" 
#include "Serialize/ObjectFactory/Fs_RegistObject.h"


#endif  // SERIALIZE_SERIALIZE_EXPORT_API_H_