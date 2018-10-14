/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Serialize_Micro.h
 *  作者: luwei
 *  日期: 2018/08/06
 *  版本: 1.0 
 *  说明: 模块内部文件，不直接对外包含
 ******************************************************************/  
  
#ifndef SERIALIZE_MICRO_H_  
#define SERIALIZE_MICRO_H_

#include "../Traits.h"
#include "../Define.h"

/////////////////////////////////////////////////////////////////////////////////////////////
//普通类序列化

#ifndef MAKE_META_DATA_IMPL
#define MAKE_META_DATA_IMPL(CLSNAME, BASECLS, _GUID_, N, ...)                                                                       \
public:                                                                                                                             \
    inline static auto Fs_METAOBJECT(const CLSNAME&) {                                                                              \
        struct METAOBJECT {                                                                                                         \
            using type = void;                                                                                                      \
            using size_type = std::integral_constant<size_t, N>;                                                                    \
            constexpr static const char* name() { return #CLSNAME; }                                                                \
            constexpr static size_t value() { return size_type::value; }                                                            \
            constexpr decltype(auto) static staticMetaObject() { return std::make_tuple(__VA_ARGS__); }                             \
            static std::array<const char* const, N> metaIndexArray() { return Fs_METAINDEXARRAY(); }                                \
            static auto Execr() { return GetExecr(); }                                                                              \
            static auto Register() { return (Fs_Creator_<CLSNAME, BASECLS>*)nullptr; }                                              \
        }; static auto _ = METAOBJECT{};                                                                                            \
        return _;                                                                                                                   \
    } 
#endif

#ifndef MAKE_META_DATA
#define MAKE_META_DATA(CLSNAME, BASECLS, _GUID_, N, ...)                                                                            \
    MAKE_META_DATA_IMPL(CLSNAME, BASECLS, _GUID_, N, MAKE_ARG_LIST(N, &CLSNAME::FIELD, __VA_ARGS__))                                \
protected:                                                                                                                          \
    class Fs_RegisterHelper{ public :Fs_RegisterHelper() {GetExecr();}}; Fs_RegisterHelper m_Fs_RegisterHelper;                     \
    virtual void Fs_Virtual() {}                                                                                                    \
    inline static Fs_Serialize::Serialize_ExecrT<CLSNAME,BASECLS>* GetExecr(){                                                      \
        if (!Fs_Serialize::Serialize_ExecrT<CLSNAME,BASECLS>::_self) {                                                              \
            static Fs_Serialize::Serialize_ExecrT<CLSNAME,BASECLS> _(_GUID_, #CLSNAME); return &_; }                                \
        return Fs_Serialize::Serialize_ExecrT<CLSNAME,BASECLS>::_self; }                                                            \
    inline static std::array<const char* const, N> Fs_METAINDEXARRAY() {                                                            \
        static std::array<const char* const, N> _ = { MARCO_EXPAND(MACRO_CONCAT(CON_STR, N)(__VA_ARGS__))  }; return _; }
#endif

#ifdef MAKE_SERIALIZE
#undef MAKE_SERIALIZE
#endif
#define MAKE_SERIALIZE(CLSNAME, BASECLS, ...) \
    MAKE_META_DATA(CLSNAME, BASECLS, MAKE_GUID(CLSNAME), GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)


#ifdef MAKE_SERIALIZE_WITH_GUID
#undef MAKE_SERIALIZE_WITH_GUID
#endif
#define MAKE_SERIALIZE_WITH_GUID(CLSNAME, BASECLS, _GUID_, ...) \
    MAKE_META_DATA(CLSNAME, BASECLS, _GUID_, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)



/////////////////////////////////////////////////////////////////////////////////////////////
//模板类序列化

#ifndef MAKE_META_DATA_IMPL_T
#define MAKE_META_DATA_IMPL_T(CLSNAME, BASECLS, _GUID_, N, ...)                                                                     \
public:                                                                                                                             \
    template<typename ... Args>                                                                                                     \
    inline static auto Fs_METAOBJECT(const CLSNAME<Args...>&) {                                                                     \
        struct METAOBJECT {                                                                                                         \
            using type = void;                                                                                                      \
            using size_type = std::integral_constant<size_t, N>;                                                                    \
            constexpr static const char* name() { return #CLSNAME; }                                                                \
            constexpr static size_t value() { return size_type::value; }                                                            \
            constexpr decltype(auto) static staticMetaObject() { return std::make_tuple(__VA_ARGS__); }                             \
            static std::array<const char* const, N> metaIndexArray() { return Fs_METAINDEXARRAY(); }                                \
            static auto Execr() {                                                                                                   \
                if (!Fs_Serialize::Serialize_ExecrT<CLSNAME<Args...>,BASECLS<Args...>>::_self) {                                    \
                    static Fs_Serialize::Serialize_ExecrT<CLSNAME<Args...>,BASECLS<Args...>> _(_GUID_, #CLSNAME); return &_; }      \
                return Fs_Serialize::Serialize_ExecrT<CLSNAME<Args...>,BASECLS<Args...>>::_self;  }                                 \
            static auto Register() { static Fs_Creator_<CLSNAME<Args...>,BASECLS<Args...>> _(_GUID_, #CLSNAME, true); return &_; }  \
        }; static auto _ = METAOBJECT{};                                                                                            \
        return _;                                                                                                                   \
    }
#endif

#ifndef MAKE_META_DATA_T
#define MAKE_META_DATA_T(CLSNAME, CLSBASE, _GUID_, N, ...)                                                                          \
    MAKE_META_DATA_IMPL_T(CLSNAME, CLSBASE, _GUID_, N, MAKE_ARG_LIST(N, &CLSNAME<Args...>::FIELD, __VA_ARGS__))                     \
protected:                                                                                                                          \
    virtual void Fs_Virtual() {}                                                                                                    \
    inline static std::array<const char* const, N> Fs_METAINDEXARRAY() {                                                            \
        static std::array<const char* const, N> _ = { MARCO_EXPAND(MACRO_CONCAT(CON_STR, N)(__VA_ARGS__)) }; return _; }
#endif

#ifndef MAKE_META_DATA_IMPL_EXTRA_T
#define MAKE_META_DATA_IMPL_EXTRA_T(CLSNAME, BASECLS, _GUID_)                                                                       \
    template<typename ... Args>                                                                                                     \
    inline static auto Fs_METAOBJECT_T(const CLSNAME<Args...>&) {                                                                   \
        struct METAOBJECT {                                                                                                         \
            using type = void;                                                                                                      \
            static auto Execr() { static Fs_Serialize::Serialize_ExecrT<CLSNAME<Args...>, BASECLS<Args...>>                         \
                _(_GUID_,#CLSNAME); return &_; }                                                                                    \
            static auto Register() { static Fs_Creator_<CLSNAME<Args...>,BASECLS<Args...>> _(_GUID_, #CLSNAME, true); return &_; }  \
        };static auto _ = METAOBJECT{};                                                                                             \
        return _;                                                                                                                   \
    }
#endif

#ifdef MAKE_SERIALIZE_EXTRA_T
#undef MAKE_SERIALIZE_EXTRA_T
#endif
#define MAKE_SERIALIZE_EXTRA_T(CLSNAME, CLSBASE) \
    MAKE_META_DATA_IMPL_EXTRA_T(CLSNAME, CLSBASE, MAKE_GUID(CLSNAME))

#ifdef MAKE_SERIALIZE_T
#undef MAKE_SERIALIZE_T
#endif
#define MAKE_SERIALIZE_T(CLSNAME, CLSBASE,...) \
    MAKE_META_DATA_T(CLSNAME, CLSBASE, MAKE_GUID(CLSNAME), GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
    
#ifdef MAKE_SERIALIZE_EXTRA_WITH_GUID_T
#undef MAKE_SERIALIZE_EXTRA_WITH_GUID_T
#endif
#define MAKE_SERIALIZE_EXTRA_WITH_GUID_T(CLSNAME, CLSBASE, _GUID_) \
    MAKE_META_DATA_IMPL_EXTRA_T(CLSNAME, CLSBASE, _GUID_)

#ifdef MAKE_SERIALIZE_WITH_GUID_T
#undef MAKE_SERIALIZE_WITH_GUID_T
#endif
#define MAKE_SERIALIZE_WITH_GUID_T(CLSNAME, CLSBASE, _GUID_, ...) \
    MAKE_META_DATA_T(CLSNAME, CLSBASE, _GUID_, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)

/////////////////////////////////////////////////////////////////////////////////////////////
//序列化通用方法，内置推导函数

namespace Fs_Serialize
{    
    template<typename T>
    using METAOBJECT = decltype(T::Fs_METAOBJECT(std::declval<T>()));
    template<typename T>
    using METAOBJECT_T = decltype(Fs_METAOBJECT_T(std::declval<T>()));
    	
    template <typename T, typename = void>
    struct is_serialize : std::false_type {
    };

    template <typename T, typename = void>
    struct is_serialize_T : std::false_type {
    };

    //template <typename ... Args>
    //struct voider
    //{
    //    using type = void;
    //};
    //
    //template <typename ... Args>
    //using voider_t = typename voider<Args...>::type;
    //template <typename T>
    //struct is_serialize<T, voider_t<typename METAOBJECT<T>::type>> : std::true_type
    //{
    //};

    template <typename T>
    struct is_serialize<T, std::void_t<typename METAOBJECT<T>::type>> : std::true_type {
    };
    
    template <typename T>
    struct is_serialize_T<T, std::void_t<typename METAOBJECT_T<T>::type>> : std::true_type {
    };


    template<size_t Index, typename T>
    inline constexpr decltype(auto) Get(T&& t)
    {
        using M = decltype(Fs_METAOBJECT(std::forward<T>(t)));
        using U = decltype(std::forward<T>(t).*(std::get<Index>(M::staticMetaObject())));

        if constexpr(std::is_array_v<U>) {
            auto s = std::forward<T>(t).*(std::get<Index>(M::staticMetaObject()));
            std::array<char, sizeof(U)> arr;
            memcpy(arr.data(), s, arr.size());
            return arr;
        }
        else
            return std::forward<T>(t).*(std::get<I>(M::staticMetaObject()));
    }

    template <typename T, size_t ... Is>
    inline constexpr auto GetImpl(T const& t, std::index_sequence<Is...>)
    {
        return std::make_tuple(get<Is>(t)...);
    }

    template <typename T, size_t ... Is>
    inline constexpr auto GetImpl(T& t, std::index_sequence<Is...>)
    {
        return std::make_tuple(std::ref(get<Is>(t))...);
    }

    template <typename T>
    inline constexpr auto Get(T const& t)
    {
        using M = decltype(Fs_METAOBJECT(t));
        return GetImpl(t, std::make_index_sequence<M::value()>{});
    }

    template <typename T>
    inline constexpr auto GetRef(T& t)
    {
        using M = decltype(Fs_METAOBJECT(t));
        return GetImpl(t, std::make_index_sequence<M::value()>{});
    }

    template<typename T, size_t I>
    inline constexpr const char* GetName()
    {
        using M = decltype(std::declval<T>().Fs_METAOBJECT(std::declval<T>()));
        static_assert(I < M::value(), "out of range");
        return M::metaIndexArray()[I];
    }

    template<typename T>
    inline constexpr const char* GetName(size_t i)
    {
        using M = decltype(Fs_METAOBJECT(std::declval<T>()));
        //		static_assert(I<M::value(), "out of range");
        return M::metaIndexArray()[i];
    }

    template<typename T>
    inline constexpr const char* GetName()
    {
        using M = decltype(Fs_METAOBJECT(std::declval<T>()));
        return M::name();
    }

    template<typename T>
    inline constexpr std::enable_if_t<is_serialize<T>::value, size_t> GetValue()
    {
        using M = decltype(Fs_METAOBJECT(std::declval<T>()));
        return M::value();
    }

    template<typename T>
    inline constexpr std::enable_if_t<!is_serialize<T>::value, size_t> GetValue()
    {
        return 1;
    }

    template<typename T>
    inline constexpr auto GetArray()
    {
        using M = decltype(Fs_METAOBJECT(std::declval<T>()));
        return M::metaIndexArray();
    }

    template<typename T>
    inline auto GetIndex(const char* name)
    {
        using M = decltype(T::Fs_METAOBJECT(std::declval<T>()));
        auto arr = M::metaIndexArray();

        auto it = std::find_if(arr.begin(), arr.end(), [name](auto str) {
            return !strcmp(str, name);
        });

        return std::distance(arr.begin(), it);
    }

    template <class Tuple, class F, std::size_t...Is>
    inline void TupleAt(std::size_t i, Tuple&& t, F&& f, std::index_sequence<Is...>) {
        std::make_tuple((((i == Is) && (std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(t))), false)))...);
    }

    template <typename... Args, typename F, std::size_t... Idx>
    inline void for_each(std::tuple<Args...>& t, F&& f, std::index_sequence<Idx...>)
    {
        std::make_tuple(std::forward<F>(f)(std::get<Idx>(t), std::integral_constant<size_t, Idx>{})...);
    }

    template <typename... Args, typename F, std::size_t... Idx>
    inline void for_each(const std::tuple<Args...>& t, F&& f, std::index_sequence<Idx...>)
    {
        std::make_tuple(std::forward<F>(f)(std::get<Idx>(t), std::integral_constant<size_t, Idx>{})...);
    }

    template<typename T, typename F>
    inline std::enable_if_t<is_serialize<T>::value> for_each(T&& t, F&& f)
    {
        using M = decltype(T::Fs_METAOBJECT(std::forward<T>(t)));
        for_each(M::staticMetaObject(), std::forward<F>(f), std::make_index_sequence<M::value()>{});
    }

    template<typename T, typename F>
    inline std::enable_if_t<is_tuple<std::decay_t<T>>::value> for_each(T&& t, F&& f)
    {
        constexpr const size_t SIZE = std::tuple_size_v<std::decay_t<T>>;
        for_each(std::forward<T>(t), std::forward<F>(f), std::make_index_sequence<SIZE>{});
    }

}

#endif  // SERIALIZE_MICRO_H_