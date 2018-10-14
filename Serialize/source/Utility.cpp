#include "Utility.h"
#include <time.h>


Fs_Utility::IGuidGenerator* G_GuidGenerator() {
    return new Fs_Utility::GUID_Generator();
}

namespace Fs_Utility 
{
    std::string GUID_Generator::Create()
    {
        return Fs_GUID::Build().Format();
    }

    std::string GUID_Generator::Create(std::size_t clsId)
    {
        return Fs_GUID::Build(clsId).Format();
    }

    std::string GUID_Generator::Create(std::size_t szID[4])
    {
        return Fs_GUID::Build(szID).Format();
    }

    std::string GUID_Generator::Create(std::size_t u1, std::size_t u2, std::size_t u3, std::size_t u4)
    {
        return Fs_GUID::Build(u1,u2,u3,u4).Format();
    }

    std::size_t GUID_Generator::Hash(const std::string& strGuid)
    {
        return std::hash<std::string>()(strGuid);
    }


    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////


    Fs_GUID Fs_GUID::Build()
    {
        return Build((std::size_t)0);
    }

    Fs_GUID Fs_GUID::Build(std::size_t clsId)
    {
        static size_t sGuidCount = 1;
        time_t ts = time(NULL);
        srand((unsigned)ts);
        return Build(clsId, (std::size_t)ts, (std::size_t)rand(), sGuidCount++);
    }

    Fs_GUID Fs_GUID::Build(std::size_t szID[4])
    {
        Fs_GUID guid;

        std::size_t* p = szID;
        for (int i = 0; i < 4; i++)
            guid._uuid[i] = *p++;

        return guid;
    }

    Fs_GUID Fs_GUID::Build(std::size_t u1, std::size_t u2, std::size_t u3, std::size_t u4)
    {
        Fs_GUID guid;
        guid._uuid[0] = u1;
        guid._uuid[1] = u2;
        guid._uuid[2] = u3;
        guid._uuid[3] = u4;
        return guid;
    }

    std::string Fs_GUID::Format()
    {
        char sz[65] = { 0 };
        sprintf_s(sz, "%16zX%16zX%16zX%16zX", _uuid[0], _uuid[1], _uuid[2], _uuid[3]);
        return sz;
    }

    std::size_t Fs_GUID::Hash()
    {
        return std::hash<std::string>()(Format());
    }

}

