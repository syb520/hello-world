/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Dynamic.h
 *  作者: luwei
 *  日期: 2018/08/13
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_DYNAMIC_H_  
#define SERIALIZE_DYNAMIC_H_


#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


#ifndef SERIALIZE_DYNAMIC_LIB

    Fs_Serialize::ISerializerApi* _GlobalSerializerApi();
    Fs_Serialize::ISerializerApi* _CreateSerializerApi(unsigned int);
    void _DestorySerializerApi(unsigned int);

#endif

    namespace Fs_Serialize {


#ifdef SERIALIZE_DYNAMIC_LIB

        inline HMODULE Fs_GetModule() {
            const wchar_t* DLL = L"SerializeApi.dll";
            HMODULE hModulue = GetModuleHandleW(DLL);
            if (NULL == hModulue) {
                hModulue = LoadLibraryW(DLL);
            }
            if (hModulue == NULL) {
                abort();
            }
            return hModulue;
        }
#endif

        inline ISerializerApi* GlobalSerializerApi()
        {
#ifdef SERIALIZE_DYNAMIC_LIB
            typedef ISerializerApi* (*_GLOBALSERIALIZERAPI_)();
            _GLOBALSERIALIZERAPI_ pFunc = (_GLOBALSERIALIZERAPI_)GetProcAddress(Fs_GetModule(), "_GlobalSerializerApi");
            return pFunc();
#else
            return ::_GlobalSerializerApi();
#endif
        }

        inline ISerializerApi* CreateSerializerApi(unsigned int apiId)
        {
#ifdef SERIALIZE_DYNAMIC_LIB
            typedef ISerializerApi* (*_CREATESERIALIZERAPI_)(unsigned int);
            _CREATESERIALIZERAPI_ pFunc = (_CREATESERIALIZERAPI_)GetProcAddress(Fs_GetModule(), "_CreateSerializerApi");
            return pFunc(apiId);
#else
            return ::_CreateSerializerApi(apiId);
#endif
        }

        inline void DestorySerializerApi(unsigned int apiId)
        {
#ifdef SERIALIZE_DYNAMIC_LIB
            typedef void (*_DESTORYSERIALIZERAPI_)(unsigned int);
            _DESTORYSERIALIZERAPI_ pFunc = (_DESTORYSERIALIZERAPI_)GetProcAddress(Fs_GetModule(), "_DestorySerializerApi");
            pFunc(apiId);
#else
            ::_DestorySerializerApi(apiId);
#endif
        }
    }

#ifdef __cplusplus
}
#endif // __cplusplus


#endif  // SERIALIZE_DYNAMIC_H_