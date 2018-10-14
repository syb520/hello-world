/*******************************************************************
*  Copyright(c) 2000-2017 SnailGame
*  All rights reserved.
*
*  文件: Serialize_API.h
*  作者: luwei
*  日期: 2018/08/06
*  版本: 1.0
*  说明:
******************************************************************/

#ifndef SERIALIZE_SERIALIZE_EXPORT_API_H_  
#define SERIALIZE_SERIALIZE_EXPORT_API_H_

#include <type_traits> 

// 管理类声明
#include "I_Serialize.h"

//
namespace Fs_Serialize {

    class ISerializerApi
    {
    public:
        // API's GUID
        virtual unsigned int UniqueId() = 0;

        // 获取序列化API
        virtual ISerializer* GetSerializer() = 0;
        
        // 获取序列化数据管理
        virtual Fs_Utility::IDataManager* GetDataManager() = 0;
        
        // 获取GUID生成器
        virtual Fs_Utility::IGuidGenerator* GetGuidGenerator() = 0;
        
        // 获取序列化管理类
        virtual ISerializerMgr* GetSerializerMgr() = 0;
        
        // 获取对象工厂
        virtual IObjectFactory* GetObjectFactory() = 0;
        
        // 获取对象管理
        virtual IObjectManager* GetObjectManager() = 0;
        
        // 获取蓝图API
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

// 若使用动态库，则需要加上预处理宏 SERIALIZE_DYNAMIC_LIB

#include "Serialize/Dynamic.h"


// 序列化宏
// 若类无成员变量需要序列化，可以不声明序列化宏
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

// 对象初始化
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