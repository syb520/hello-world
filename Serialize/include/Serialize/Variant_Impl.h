/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Variant_Impl.h
 *  作者: luwei
 *  日期: 2018/08/31
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_VARIANT_IMPL_H__  
#define SERIALIZE_VARIANT_IMPL_H__


#include "Variant.h"
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <string>

namespace Fs_Utility
{

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    /*
    * @brief 字符串转为 bool
    */
    inline bool StringToBool(const char* cstr)
    {
        std::string str(cstr);

        if (str.empty())
        {
            return false;
        }

        if (str == "0")
        {
            return false;
        }

        std::transform(str.begin(), str.end(), str.begin(), std::toupper);
        if (str == "FALSE")
        {
            return false;
        }

        return true;
    }

    /*
    * @brief 字符串转为 int
    */
    inline int StringToInt(const char* cstr)
    {
        std::string str(cstr);

        return std::stoi(str);
    }

    /*
    * @brief 字符串转为 long long int
    */
    inline long long int StringToLongLongInt(const char* cstr)
    {
        std::string str(cstr);

        return std::stoll(str);
    }

    /*
    * @brief 转为 字符串转为 long double
    */
    inline long double StringToLongDouble(const char* cstr)
    {
        std::string str(cstr);

        return std::stold(cstr);
    }

    /*
    * @brief 指针值
    */
    inline int PointerValue(void* ptr)
    {
        int* pptr = (int*)(&ptr);
        return *pptr;
    }

    /*
    * @brief 转为 bool
    */
    template <typename DT, typename TT>
    inline TT ConvertToBool(const DT& data, const Variant::VarType& type)
    {
        TT ret = false;

        switch (type)
        {
        case Variant::VT_Invalid:
            break;
        case Variant::VT_Bool:
            ret = data.b;
            break;
        case Variant::VT_Char:
            ret = data.c != '\0';
            break;
        case Variant::VT_SChar:
            ret = data.sc != '\0';
            break;
        case Variant::VT_UChar:
            ret = data.uc != '\0';
            break;
        case Variant::VT_Char16:
            ret = data.c16 != '\0';
            break;
        case Variant::VT_Char32:
            ret = data.c32 != '\0';
            break;
        case Variant::VT_WChar:
            ret = data.wc != '\0';
            break;
        case Variant::VT_Short:
            ret = data.si != 0;
            break;
        case Variant::VT_UShort:
            ret = data.usi != 0;
            break;
        case Variant::VT_Int:
            ret = data.i != 0;
            break;
        case Variant::VT_UInt:
            ret = data.ui != 0;
            break;
        case Variant::VT_Long:
            ret = data.li != 0;
            break;
        case Variant::VT_ULONG:
            ret = data.uli != 0;
            break;
        case Variant::VT_LongLong:
            ret = data.lli != 0;
            break;
        case Variant::VT_ULongLong:
            ret = data.ulli != 0;
            break;
        case Variant::VT_Float:
            ret = std::abs(data.f) <= 1e-6;
            break;
        case Variant::VT_Double:
            ret = std::abs(data.d) >= 1e-15;
            break;
        case Variant::VT_LDouble:
            ret = std::abs(data.ld) >= 1e-18;
            break;
        case Variant::VT_String:
            ret = StringToBool(data.str);
            break;
        case Variant::VT_Pointer:
            break;
        default:
            break;
        }

        return ret;
    }

    /*
    * @brief 转为 char
    */
    template <typename DT, typename TT>
    inline TT ConvertToChar(const DT& data, const Variant::VarType& type)
    {
        TT ret = '\0';

        switch (type)
        {
        case Variant::VT_Invalid:
            break;
        case Variant::VT_Bool:
            ret = data.b ? '1' : '0';
            break;
        case Variant::VT_Char:
            ret = static_cast<TT>(data.c);
            break;
        case Variant::VT_SChar:
            ret = static_cast<TT>(data.sc);
            break;
        case Variant::VT_UChar:
            ret = static_cast<TT>(data.uc);
            break;
        case Variant::VT_Char16:
            ret = static_cast<TT>(data.c16);
            break;
        case Variant::VT_Char32:
            ret = static_cast<TT>(data.c32);
            break;
        case Variant::VT_WChar:
            ret = static_cast<TT>(data.wc);
            break;
        case Variant::VT_Short:
            ret = static_cast<TT>(data.si);
            break;
        case Variant::VT_UShort:
            ret = static_cast<TT>(data.usi);
            break;
        case Variant::VT_Int:
            ret = static_cast<TT>(data.i);
            break;
        case Variant::VT_UInt:
            ret = static_cast<TT>(data.ui);
            break;
        case Variant::VT_Long:
            ret = static_cast<TT>(data.li);
            break;
        case Variant::VT_ULONG:
            ret = static_cast<TT>(data.uli);
            break;
        case Variant::VT_LongLong:
            ret = static_cast<TT>(data.lli);
            break;
        case Variant::VT_ULongLong:
            ret = static_cast<TT>(data.ulli);
            break;
        case Variant::VT_Float:
            ret = static_cast<TT>(static_cast<long long int>(data.f));
            break;
        case Variant::VT_Double:
            ret = static_cast<TT>(static_cast<long long int>(data.d));
            break;
        case Variant::VT_LDouble:
            ret = static_cast<TT>(static_cast<long long int>(data.ld));
            break;
        case Variant::VT_String:
            ret = static_cast<TT>(StringToLongLongInt(data.str));
            break;
        case Variant::VT_Pointer:
            break;
        default:
            break;
        }

        return ret;
    }

    /*
    * @brief 转为 number
    */
    template <typename DT, typename TT>
    inline TT ConvertToNumber(const DT& data, const Variant::VarType& type)
    {
        TT ret = 0;

        switch (type)
        {
        case Variant::VT_Invalid:
            break;
        case Variant::VT_Bool:
            ret = data.b ? 1 : 0;
            break;
        case Variant::VT_Char:
            ret = static_cast<TT>(data.c);
            break;
        case Variant::VT_SChar:
            ret = static_cast<TT>(data.sc);
            break;
        case Variant::VT_UChar:
            ret = static_cast<TT>(data.uc);
            break;
        case Variant::VT_Char16:
            ret = static_cast<TT>(data.c16);
            break;
        case Variant::VT_Char32:
            ret = static_cast<TT>(data.c32);
            break;
        case Variant::VT_WChar:
            ret = static_cast<TT>(data.wc);
            break;
        case Variant::VT_Short:
            ret = static_cast<TT>(data.si);
            break;
        case Variant::VT_UShort:
            ret = static_cast<TT>(data.usi);
            break;
        case Variant::VT_Int:
            ret = static_cast<TT>(data.i);
            break;
        case Variant::VT_UInt:
            ret = static_cast<TT>(data.ui);
            break;
        case Variant::VT_Long:
            ret = static_cast<TT>(data.li);
            break;
        case Variant::VT_ULONG:
            ret = static_cast<TT>(data.uli);
            break;
        case Variant::VT_LongLong:
            ret = static_cast<TT>(data.lli);
            break;
        case Variant::VT_ULongLong:
            ret = static_cast<TT>(data.ulli);
            break;
        case Variant::VT_Float:
            ret = static_cast<TT>(static_cast<long long int>(data.f));
            break;
        case Variant::VT_Double:
            ret = static_cast<TT>(static_cast<long long int>(data.d));
            break;
        case Variant::VT_LDouble:
            ret = static_cast<TT>(static_cast<long long int>(data.ld));
            break;
        case Variant::VT_String:
            ret = static_cast<TT>(StringToLongLongInt(data.str));
            break;
        case Variant::VT_Pointer:
            break;
        default:
            break;
        }

        return ret;
    }

    /*
    * @brief 转为 real number
    */
    template <typename DT, typename TT>
    inline TT ConvertToRealNumber(const DT& data, const Variant::VarType& type)
    {
        TT ret = 0.0f;

        switch (type)
        {
        case Variant::VT_Invalid:
            break;
        case Variant::VT_Bool:
            ret = data.b ? 1.0f : 0.0f;
            break;
        case Variant::VT_Char:
            ret = static_cast<TT>(data.c);
            break;
        case Variant::VT_SChar:
            ret = static_cast<TT>(data.sc);
            break;
        case Variant::VT_UChar:
            ret = static_cast<TT>(data.uc);
            break;
        case Variant::VT_Char16:
            ret = static_cast<TT>(data.c16);
            break;
        case Variant::VT_Char32:
            ret = static_cast<TT>(data.c32);
            break;
        case Variant::VT_WChar:
            ret = static_cast<TT>(data.wc);
            break;
        case Variant::VT_Short:
            ret = static_cast<TT>(data.si);
            break;
        case Variant::VT_UShort:
            ret = static_cast<TT>(data.usi);
            break;
        case Variant::VT_Int:
            ret = static_cast<TT>(data.i);
            break;
        case Variant::VT_UInt:
            ret = static_cast<TT>(data.ui);
            break;
        case Variant::VT_Long:
            ret = static_cast<TT>(data.li);
            break;
        case Variant::VT_ULONG:
            ret = static_cast<TT>(data.uli);
            break;
        case Variant::VT_LongLong:
            ret = static_cast<TT>(data.lli);
            break;
        case Variant::VT_ULongLong:
            ret = static_cast<TT>(data.ulli);
            break;
        case Variant::VT_Float:
            ret = static_cast<TT>(data.f);
            break;
        case Variant::VT_Double:
            ret = static_cast<TT>(data.d);
            break;
        case Variant::VT_LDouble:
            ret = static_cast<TT>(data.ld);
            break;
        case Variant::VT_String:
            ret = static_cast<TT>(StringToLongDouble(data.str));
            break;
        case Variant::VT_Pointer:
            break;
        default:
            break;
        }

        return ret;
    }

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    inline bool Variant::ToBool()
    {
        return ConvertToBool<Variant::VarData, bool>(mData, mType);
    }

    inline char Variant::ToChar()
    {
        return ConvertToChar<Variant::VarData, char>(mData, mType);
    }

    inline signed char Variant::ToSignedChar()
    {
        return ConvertToChar<Variant::VarData, signed char>(mData, mType);
    }

    inline unsigned char Variant::ToUnSignedChar()
    {
        return ConvertToChar<Variant::VarData, unsigned char>(mData, mType);
    }

    inline char16_t Variant::ToChar16()
    {
        return ConvertToChar<Variant::VarData, char16_t>(mData, mType);
    }

    inline char32_t Variant::ToChar32()
    {
        return ConvertToChar<Variant::VarData, char32_t>(mData, mType);
    }

    inline wchar_t Variant::ToWChar()
    {
        return ConvertToChar<Variant::VarData, wchar_t>(mData, mType);
    }

    inline short int Variant::ToShortInt()
    {
        return ConvertToNumber<Variant::VarData, short int>(mData, mType);
    }

    inline unsigned short int Variant::ToUnSignedShortInt()
    {
        return ConvertToNumber<Variant::VarData, unsigned short int>(mData, mType);
    }

    inline int Variant::ToInt()
    {
        return ConvertToNumber<Variant::VarData, int>(mData, mType);
    }

    inline unsigned int Variant::ToUnSignedInt()
    {
        return ConvertToNumber<Variant::VarData, unsigned int>(mData, mType);
    }

    inline long int Variant::ToLongInt()
    {
        return ConvertToNumber<Variant::VarData, long int>(mData, mType);
    }

    inline unsigned long int Variant::ToUnSignedLongInt()
    {
        return ConvertToNumber<Variant::VarData, unsigned long int>(mData, mType);
    }

    inline long long int Variant::ToLongLongInt()
    {
        return ConvertToNumber<Variant::VarData, long long int>(mData, mType);
    }

    inline unsigned long long int Variant::ToUnSignedLongLongInt()
    {
        return ConvertToNumber<Variant::VarData, unsigned long long int>(mData, mType);
    }

    inline float Variant::ToFloat()
    {
        return ConvertToRealNumber<Variant::VarData, float>(mData, mType);
    }

    inline double Variant::ToDouble()
    {
        return ConvertToRealNumber<Variant::VarData, double>(mData, mType);
    }

    inline long double Variant::ToLongDouble()
    {
        return ConvertToRealNumber<Variant::VarData, long double>(mData, mType);
    }

    inline const char* Variant::ToString()
    {
        if (mCache)
        {
            return mCache;
        }

        std::string str;

        switch (mType)
        {
        case Variant::VT_Invalid:
        {
            break;
        }
        case Variant::VT_Bool:
        {
            str = mData.b ? "true" : "false";
            break;
        }
        case Variant::VT_Char:
        {
            std::to_string(static_cast<int>(mData.c));
            break;
        }
        case Variant::VT_SChar:
        {
            std::to_string(static_cast<int>(mData.sc));
            break;
        }
        case Variant::VT_UChar:
        {
            std::to_string(static_cast<unsigned int>(mData.uc));
            break;
        }
        case Variant::VT_Char16:
        {
            std::to_string(static_cast<unsigned int>(mData.c16));
            break;
        }
        case Variant::VT_Char32:
        {
            std::to_string(static_cast<unsigned int>(mData.c32));
            break;
        }
        case Variant::VT_WChar:
        {
            std::to_string(static_cast<long long int>(mData.wc));
            break;
        }
        case Variant::VT_Short:
        {
            str = std::to_string(static_cast<int>(mData.si));
            break;
        }
        case Variant::VT_UShort:
        {
            str = std::to_string(static_cast<unsigned int>(mData.usi));
            break;
        }
        case Variant::VT_Int:
        {
            str = std::to_string(mData.i);
            break;
        }
        case Variant::VT_UInt:
        {
            str = std::to_string(mData.ui);
            break;
        }
        case Variant::VT_Long:
        {
            str = std::to_string(mData.li);
            break;
        }
        case Variant::VT_ULONG:
        {
            str = std::to_string(mData.uli);
            break;
        }
        case Variant::VT_LongLong:
        {
            str = std::to_string(mData.lli);
            break;
        }
        case Variant::VT_ULongLong:
        {
            str = std::to_string(mData.ulli);
            break;
        }
        case Variant::VT_Float:
        {
            str = std::to_string(mData.f);
            break;
        }
        case Variant::VT_Double:
        {
            str = std::to_string(mData.d);
            break;
        }
        case Variant::VT_LDouble:
        {
            str = std::to_string(mData.ld);
            break;
        }
        case Variant::VT_String:
        {
            str = mData.str;
            break;
        }
        case Variant::VT_Pointer:
        {
            str = std::to_string(PointerValue(mData.ptr));
            break;
        }
        default:
        {
            break;
        }
        }

        const char* data = str.c_str();
        size_t len = str.size();

        mCache = new char[len + 1];
        std::memset(mCache, 0, len + 1);
        std::memcpy(mCache, data, len);

        return mCache;
    }

    inline void* Variant::ToPointer()
    {
        void* ret = nullptr;

        switch (mType)
        {
        case VT_Invalid:
        case VT_Bool:
        case VT_Char:
        case VT_SChar:
        case VT_UChar:
        case VT_Char16:
        case VT_Char32:
        case VT_WChar:
        case VT_Short:
        case VT_UShort:
        case VT_Int:
        case VT_UInt:
        case VT_Long:
        case VT_ULONG:
        case VT_LongLong:
        case VT_ULongLong:
        case VT_Float:
        case VT_Double:
        case VT_LDouble:
        {
            break;
        }
        case VT_String:
        {
            int num = StringToInt(mData.str);
            std::memcpy(&ret, &num, sizeof(int));
            break;
        }
        case VT_Pointer:
        {
            ret = mData.ptr;
            break;
        }
        default:
        {
            break;
        }
        }

        return ret;
    }

}


#endif  // SERIALIZE_VARIANT_IMPL_H__