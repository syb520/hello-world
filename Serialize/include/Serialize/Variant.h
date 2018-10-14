#ifndef SERIALIZE_VARIANT_H__
#define SERIALIZE_VARIANT_H__

#include <utility>
#include <cstring>

namespace Fs_Utility {

    /*
     * @brief Variant��������
     */
    class Variant final
    {
    public:
        template <bool B, typename T = void>
        using _ENABLE_IF_T = typename std::enable_if<B, T>::type;

        template <typename T>
        using _DECAY_T = typename std::decay<T>::type;

        template <typename T>
        using _IS_INTEGRAL = std::is_integral<T>;

        template <typename T>
        using _IS_FLOATING_POINT = std::is_floating_point<T>;

        template <typename T>
        using _IS_POINTER = std::is_pointer<T>;

        template <typename T, typename U>
        using _IS_SAME = std::is_same<T, U>;

        template <typename T>
        using _ENABLE_IF_NOT_VARIANT_T = _ENABLE_IF_T<!_IS_SAME<T, Variant>::value>;

        template <typename T>
        using _ENABLE_IF_VARIANT_TYPE_T = _ENABLE_IF_T<_IS_INTEGRAL<T>::value || _IS_FLOATING_POINT<T>::value || _IS_POINTER<T>::value>;

    public:
        /*
         * @brief Variant�п��Դ�ŵ���������
         */
        enum VarType
        {
            VT_Invalid = 0,   // Invalid
            VT_Bool = 1,   // bool
            VT_Char = 2,   // char
            VT_SChar = 3,   // signed char
            VT_UChar = 4,   // unsigned char
            VT_Char16 = 5,   // char16_t
            VT_Char32 = 6,   // char32_t
            VT_WChar = 7,   // wchar_t
            VT_Short = 8,   // short int
            VT_UShort = 9,   // unsigned short int
            VT_Int = 10,  // int
            VT_UInt = 11,  // unsigned int
            VT_Long = 12,  // long int
            VT_ULONG = 13,  // unsigned long int
            VT_LongLong = 14,  // long long int
            VT_ULongLong = 15,  // unsigned long long int
            VT_Float = 16,  // float
            VT_Double = 17,  // double
            VT_LDouble = 18,  // long double
            VT_String = 19,  // char*
            VT_Pointer = 20,  // void*
        };

    public:
        /*
         * @brief ���캯��
         */
        Variant() noexcept
            : mType(Variant::VT_Invalid),
            mBufLen(0),
            mCache(nullptr)
        {
            std::memset(&mData, 0, sizeof(VarData));
        }

        /*
         * @brief ���캯��������ת��
         */
        template <typename T,
            typename _Tp = _ENABLE_IF_VARIANT_TYPE_T<_DECAY_T<T>>>
            Variant(T&& rhs)
            : mType(Variant::VT_Invalid),
            mBufLen(0),
            mCache(nullptr)
        {
            std::memset(&mData, 0, sizeof(VarData));

            Set(std::forward<T>(rhs));
        }

        /*
         * @brief ���ƹ��캯��
         */
        Variant(const Variant& rhs)
            : mType(rhs.mType),
            mData(rhs.mData),
            mBufLen(rhs.mBufLen),
            mCache(nullptr)
        {
            if (mType == Variant::VT_String)
            {
                mData.str = new char[mBufLen + 1];

                std::memset(mData.str, 0, mBufLen + 1);
                std::memcpy(mData.str, rhs.mData.str, mBufLen);
            }
        }

        /*
         * @brief �ƶ����캯��
         */
        Variant(Variant&& rhs) noexcept
            : mType(rhs.mType),
            mData(rhs.mData),
            mBufLen(rhs.mBufLen),
            mCache(nullptr)
        {
            rhs.mType = Variant::VT_Invalid;
            std::memset(&rhs.mData, 0, sizeof(VarData));
            rhs.mBufLen = 0;
            delete[] rhs.mCache;
            rhs.mCache = nullptr;
        }

        /*
         * @brief ��������
         */
        ~Variant()
        {
            Reset();
        }

    public:
        /*
         * @brief ��ֵ����������ת��
         */
        template <typename T,
            typename _Tp = _ENABLE_IF_VARIANT_TYPE_T<_DECAY_T<T>>>
            Variant& operator =(T&& rhs)
        {
            Variant(std::forward<T>(rhs)).Swap(*this);

            return *this;
        }

        /*
         * @brief ��ֵ����
         */
        Variant& operator =(const Variant& rhs)
        {
            Variant(rhs).Swap(*this);

            return *this;
        }

        /*
         * @brief �ƶ���ֵ
         */
        Variant& operator =(Variant&& rhs) noexcept
        {
            Variant(std::move(rhs)).Swap(*this);

            return *this;
        }

    public:
        /*
         * @brief �е�
         */
        bool operator ==(const Variant& rhs) const
        {
            if (mType != rhs.mType || mBufLen != rhs.mBufLen)
            {
                return false;
            }

            if (mType != Variant::VT_String)
            {
                return std::memcmp(&mData, &rhs.mData, sizeof(VarData)) == 0;
            }
            else
            {
                return std::strcmp(mData.str, rhs.mData.str) == 0;
            }
        }

        /*
         * @brief �в���
         */
        bool operator !=(const Variant& rhs) const
        {
            return !this->operator==(rhs);
        }

    public:
        /*
         * @brief ��������
         */
        bool Empty() const noexcept
        {
            return mType == Variant::VT_Invalid;
        }

        /*
         * @brief ��������
         */
        Variant& Swap(Variant& rhs) noexcept
        {
            std::swap(mType, rhs.mType);
            std::swap(mData, rhs.mData);
            std::swap(mBufLen, rhs.mBufLen);
            std::swap(mCache, rhs.mCache);

            return *this;
        }

        /*
         * @brief ��������
         */
        void Reset() noexcept
        {
            if (mType == Variant::VT_String)
            {
                delete[] mData.str;
            }

            mType = Variant::VT_Invalid;
            std::memset(&mData, 0, sizeof(VarData));
            mBufLen = 0;
            delete[] mCache;
            mCache = nullptr;
        }

        /*
         * @brief ��������
         */
        VarType Type() const noexcept
        {
            return mType;
        }

        /*
         * @brief ��������
         */
        template <typename T, typename _Tp = _ENABLE_IF_VARIANT_TYPE_T<_DECAY_T<T>>>
        void Set(T&& val) noexcept
        {
            Reset();

            mType = TemplateType<T>();

            switch (mType)
            {
            case Variant::VT_Invalid:
            {
                break;
            }
            case Variant::VT_Bool:
            {
                std::memcpy(&mData.b, &val, sizeof(bool));
                break;
            }
            case Variant::VT_Char:
            {
                std::memcpy(&mData.c, &val, sizeof(char));
                break;
            }
            case Variant::VT_SChar:
            {
                std::memcpy(&mData.sc, &val, sizeof(signed char));
                break;
            }
            case Variant::VT_UChar:
            {
                std::memcpy(&mData.uc, &val, sizeof(unsigned char));
                break;
            }
            case Variant::VT_Char16:
            {
                std::memcpy(&mData.c16, &val, sizeof(char16_t));
                break;
            }
            case Variant::VT_Char32:
            {
                std::memcpy(&mData.c32, &val, sizeof(char32_t));
                break;
            }
            case Variant::VT_WChar:
            {
                std::memcpy(&mData.wc, &val, sizeof(wchar_t));
                break;
            }
            case Variant::VT_Short:
            {
                std::memcpy(&mData.si, &val, sizeof(short int));
                break;
            }
            case Variant::VT_UShort:
            {
                std::memcpy(&mData.usi, &val, sizeof(unsigned short int));
                break;
            }
            case Variant::VT_Int:
            {
                std::memcpy(&mData.i, &val, sizeof(int));
                break;
            }
            case Variant::VT_UInt:
            {
                std::memcpy(&mData.ui, &val, sizeof(unsigned int));
                break;
            }
            case Variant::VT_Long:
            {
                std::memcpy(&mData.li, &val, sizeof(long int));
                break;
            }
            case Variant::VT_ULONG:
            {
                std::memcpy(&mData.uli, &val, sizeof(unsigned long int));
                break;
            }
            case Variant::VT_LongLong:
            {
                std::memcpy(&mData.lli, &val, sizeof(long long int));
                break;
            }
            case Variant::VT_ULongLong:
            {
                std::memcpy(&mData.ulli, &val, sizeof(unsigned long long int));
                break;
            }
            case Variant::VT_Float:
            {
                std::memcpy(&mData.f, &val, sizeof(float));
                break;
            }
            case Variant::VT_Double:
            {
                std::memcpy(&mData.d, &val, sizeof(double));
                break;
            }
            case Variant::VT_LDouble:
            {
                std::memcpy(&mData.ld, &val, sizeof(long double));
                break;
            }
            case Variant::VT_String:
            {
                const char* ptr = nullptr;
                {
                    _DECAY_T<T> decay_ptr = static_cast<_DECAY_T<T>>(val);
                    std::memcpy(&ptr, &decay_ptr, sizeof(void*));
                }

                mBufLen = std::strlen(ptr);
                mData.str = new char[mBufLen + 1];

                std::memset(mData.str, 0, mBufLen + 1);
                std::memcpy(mData.str, ptr, mBufLen);

                break;
            }
            case Variant::VT_Pointer:
            {
                const void* ptr = nullptr;
                {
                    _DECAY_T<T> decay_ptr = static_cast<_DECAY_T<T>>(val);
                    std::memcpy(&ptr, &decay_ptr, sizeof(void*));
                }

                std::memcpy(&mData.ptr, &ptr, sizeof(void*));
                break;
            }
            default:
            {
                break;
            }
            }
        }

        /*
         * @brief תΪ bool
         */
        bool ToBool();

        /*
         * @brief תΪ char
         */
        char ToChar();

        /*
         * @brief תΪ signed char
         */
        signed char ToSignedChar();

        /*
         * @brief תΪ unsigned char
         */
        unsigned char ToUnSignedChar();

        /*
         * @brief תΪ char16_t
         */
        char16_t ToChar16();

        /*
         * @brief תΪ char32_t
         */
        char32_t ToChar32();

        /*
         * @brief תΪ wchar_t
         */
        wchar_t ToWChar();

        /*
         * @brief תΪ short int
         */
        short int ToShortInt();

        /*
         * @brief תΪ unsigned short int
         */
        unsigned short int ToUnSignedShortInt();

        /*
         * @brief תΪ int
         */
        int ToInt();

        /*
         * @brief תΪ unsigned int
         */
        unsigned int ToUnSignedInt();

        /*
         * @brief תΪ long int
         */
        long int ToLongInt();

        /*
         * @brief תΪ unsigned long int
         */
        unsigned long int ToUnSignedLongInt();

        /*
         * @brief תΪ long long int
         */
        long long int ToLongLongInt();

        /*
         * @brief תΪ unsinged long long int
         */
        unsigned long long int ToUnSignedLongLongInt();

        /*
         * @brief תΪ float
         */
        float ToFloat();

        /*
         * @brief תΪ double
         */
        double ToDouble();

        /*
         * @brief תΪ long double
         */
        long double ToLongDouble();

        /*
         * @brief תΪ�ַ���
         */
        const char* ToString();

        /*
         * @brief תΪָ��
         */
        void* ToPointer();

    private:
        /*
         * @brief ��ȡģ������T��Ӧ��VarType
         */
        template <typename T>
        VarType TemplateType()
        {
            if (_IS_SAME<_DECAY_T<T>, bool>::value)
            {
                return Variant::VT_Bool;
            }
            else if (_IS_SAME<_DECAY_T<T>, char>::value)
            {
                return Variant::VT_Char;
            }
            else if (_IS_SAME<_DECAY_T<T>, signed char>::value)
            {
                return Variant::VT_SChar;
            }
            else if (_IS_SAME<_DECAY_T<T>, unsigned char>::value)
            {
                return Variant::VT_UChar;
            }
            else if (_IS_SAME<_DECAY_T<T>, char16_t>::value)
            {
                return Variant::VT_Char16;
            }
            else if (_IS_SAME<_DECAY_T<T>, char32_t>::value)
            {
                return Variant::VT_Char32;
            }
            else if (_IS_SAME<_DECAY_T<T>, wchar_t>::value)
            {
                return Variant::VT_WChar;
            }
            else if (_IS_SAME<_DECAY_T<T>, short int>::value)
            {
                return  Variant::VT_Short;
            }
            else if (_IS_SAME<_DECAY_T<T>, unsigned short int>::value)
            {
                return  Variant::VT_UShort;
            }
            else if (_IS_SAME<_DECAY_T<T>, int>::value)
            {
                return Variant::VT_Int;
            }
            else if (_IS_SAME<_DECAY_T<T>, unsigned int>::value)
            {
                return  Variant::VT_UInt;
            }
            else if (_IS_SAME<_DECAY_T<T>, long int>::value)
            {
                return Variant::VT_Long;
            }
            else if (_IS_SAME<_DECAY_T<T>, unsigned long int>::value)
            {
                return Variant::VT_ULONG;
            }
            else if (_IS_SAME<_DECAY_T<T>, long long int>::value)
            {
                return Variant::VT_LongLong;
            }
            else if (_IS_SAME<_DECAY_T<T>, unsigned long long int>::value)
            {
                return Variant::VT_ULongLong;
            }
            else if (_IS_SAME<_DECAY_T<T>, float>::value)
            {
                return Variant::VT_Float;
            }
            else if (_IS_SAME<_DECAY_T<T>, double>::value)
            {
                return Variant::VT_Double;
            }
            else if (_IS_SAME<_DECAY_T<T>, long double>::value)
            {
                return Variant::VT_LDouble;
            }
            else if (_IS_SAME<_DECAY_T<T>, const char*>::value ||
                _IS_SAME<_DECAY_T<T>, char*>::value)
            {
                return Variant::VT_String;
            }
            else if (_IS_POINTER<_DECAY_T<T>>::value)
            {
                return Variant::VT_Pointer;
            }
            else
            {
                return Variant::VT_Invalid;
            }
        }

    private:
        // ���ݽṹ
        union VarData
        {
            bool b;
            char c;
            signed char sc;
            unsigned char uc;
            char16_t c16;
            char32_t c32;
            wchar_t wc;
            short int si;
            unsigned short int usi;
            int i;
            unsigned int ui;
            long int li;
            unsigned long int uli;
            long long int lli;
            unsigned long long int ulli;
            float f;
            double d;
            long double ld;
            char* str;
            void* ptr;
        };

        VarType mType;   // ����
        VarData mData;   // ����
        size_t  mBufLen; // ����������
        char*   mCache;  // ����
    };

    /*
     * @brief ����Variant
     */
    inline void swap(Variant& lhs, Variant& rhs) noexcept
    {
        lhs.Swap(rhs);
    }

}

#include "Variant_Impl.h"

#endif // SERIALIZE_VARIANT_H__
