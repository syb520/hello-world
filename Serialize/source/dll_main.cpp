#include "../include/Serialize_API.h"
#include "../include/Serialize/Dynamic.h" 
#include "ObjectFactory/ObjectManager.h" 
#include "Utility.h"

#include <map>
#include <mutex>

#ifdef SERIALIZE_DYNAMIC_LIB
#define SERIALIZE_API __declspec(dllexport)
#else
#define SERIALIZE_API
#endif 

extern Fs_Serialize::ISerializer* G_CreateSerializer(ISerializerMgr*, Fs_Utility::IDataManager*);
extern ISerializerMgr* G_CreateSerializerMgr(IObjectManager*, Fs_Utility::IDataManager*);
extern IObjectManager* G_CreateObjectManager(IObjectFactory*, Fs_Serialize::ISerializerApi*);
extern IObjectFactory* G_GetObjectFactory();
extern Fs_Utility::IDataManager* G_CreateDataManager();
extern Fs_Utility::IGuidGenerator* G_GuidGenerator();
extern IBlueprintApi* G_CreateBlueprintApi(Fs_Serialize::ISerializer*, IObjectManager*, Fs_Utility::IDataManager*);


namespace Fs_Serialize {

    class SerializerApi : public ISerializerApi
    {
    public:
        unsigned int m_ApiId;
        IObjectFactory* p1{ nullptr };
        Fs_Utility::IGuidGenerator* p2{ nullptr };
        Fs_Utility::IDataManager* p3{ nullptr };
        IObjectManager* p4{ nullptr };
        ISerializerMgr* p5{ nullptr };
        ISerializer* p6{ nullptr };
        IBlueprintApi* p7{ nullptr };

    public:
        SerializerApi(unsigned int apiId) {
            m_ApiId = apiId;
            p1 = G_GetObjectFactory();
            p2 = G_GuidGenerator();
            p3 = G_CreateDataManager();
            p4 = G_CreateObjectManager(p1, this);
            p5 = G_CreateSerializerMgr(p4, p3);
            p6 = G_CreateSerializer(p5, p3);
            p7 = G_CreateBlueprintApi(p6, p4, p3);
        }
        inline virtual ~SerializerApi() {
            //delete p1; p1 = nullptr;
            delete p2; p2 = nullptr;
            delete p3; p3 = nullptr;
            delete p4; p4 = nullptr;
            //delete p5; p5 = nullptr;
            delete p6; p6 = nullptr;
            delete p7; p7 = nullptr;
        }
        inline unsigned int UniqueId() { return m_ApiId; }
        inline ISerializer* GetSerializer() { return p6; }
        inline Fs_Utility::IDataManager* GetDataManager() { return p3; }
        inline Fs_Utility::IGuidGenerator* GetGuidGenerator() { return p2; }
        inline ISerializerMgr* GetSerializerMgr() { return p5; }
        inline IObjectFactory* GetObjectFactory() { return p1; }
        inline IObjectManager* GetObjectManager() { return p4; }
        inline IBlueprintApi* GetBlurprintApi() { return p7; }
    };

    class SerializerApiMgr
    {

    public:
        static SerializerApiMgr& Instance() {
            static SerializerApiMgr mgr;
            return mgr;
        }
        SerializerApiMgr() {
        }
        ~SerializerApiMgr() {
            std::lock_guard<std::mutex> lock(mutex);
            delete g_api;
            for (auto iter : _apis)
                delete iter.second;
            _apis.clear();
        }
        ISerializerApi* g_api{ nullptr };
        std::map<unsigned int, ISerializerApi*> _apis;

        inline ISerializerApi* GlobalApi() {
            if (!g_api)
                g_api = new SerializerApi(0);
            return g_api;
        }

        inline ISerializerApi* CreateApi(unsigned int apiId) {
            if (apiId == 0)
                return GlobalApi();

            std::lock_guard<std::mutex> lock(mutex);
            if (_apis.find(apiId) != _apis.end())
                return _apis[apiId];

            SerializerApi* api = new SerializerApi(apiId);
            _apis.insert(std::make_pair(apiId, api));
            return api;
        }

        inline void DestoryApi(unsigned int apiId) {

            std::lock_guard<std::mutex> lock(mutex);

            if (!apiId || (_apis.find(apiId) == _apis.end()))
                return;

            delete _apis[apiId];
            _apis.erase(apiId);
        }

        std::mutex mutex;
    };
}


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    SERIALIZE_API Fs_Serialize::ISerializerApi* _GlobalSerializerApi()
    {
        return Fs_Serialize::SerializerApiMgr::Instance().GlobalApi();
    }

    SERIALIZE_API Fs_Serialize::ISerializerApi* _CreateSerializerApi(unsigned int apiId)
    {
        return Fs_Serialize::SerializerApiMgr::Instance().CreateApi(apiId);
    }

    SERIALIZE_API void _DestorySerializerApi(unsigned int apiId)
    {
        Fs_Serialize::SerializerApiMgr::Instance().DestoryApi(apiId);
    }

#ifdef __cplusplus
}
#endif // __cplusplus