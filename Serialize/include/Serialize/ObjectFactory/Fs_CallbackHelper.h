/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Fs_CallbackHelper.h
 *  作者: luwei
 *  日期: 2018/07/16
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_CALLBACKHELPER_H_  
#define SERIALIZE_CALLBACKHELPER_H_



#include <functional>
#include <tuple>
#include <utility>


///////////////////////////////////////////////////////////////////
//变参回调

template<std::size_t N>
struct Fs_Obj_Callback {
    template<typename F, typename T, typename... A>
    static inline auto call(F && f, T && t, A &&... a)
        -> decltype(Fs_Obj_Callback<N - 1>::call(
            ::std::forward<F>(f), ::std::forward<T>(t),
            ::std::get<N - 1>(::std::forward<T>(t)),
            ::std::forward<A>(a)...
        ))
    {
        return Fs_Obj_Callback<N - 1>::call(::std::forward<F>(f),
            ::std::forward<T>(t),
            ::std::get<N - 1>(::std::forward<T>(t)),
            ::std::forward<A>(a)...
        );
    }
};

template<>
struct Fs_Obj_Callback<0> {
    template<typename F, typename T, typename... A>
    static inline auto call(F && f, T &&, A &&... a)
        -> decltype(::std::forward<F>(f)
        (::std::forward<A>(a)...))
    {
        return ::std::forward<F>(f)(::std::forward<A>
            (a)...);
    }
};

template<typename F, typename T>
inline auto _Fs_Obj_Callback_Functor_(F && f, T && t)
-> decltype(Fs_Obj_Callback< ::std::tuple_size<
    typename ::std::decay<T>::type
>::value>::call(::std::forward<F>(f),
    ::std::forward<T>(t)))
{
    return Fs_Obj_Callback< ::std::tuple_size<
        typename ::std::decay<T>::type
    >::value>::call(::std::forward<F>(f),
        ::std::forward<T>(t));
}



///////////////////////////////////////////////////////////////////
//变参构造
template<std::size_t N>
struct Fs_Obj_Constructor {
    template<typename C, typename T, typename... Args>
    static inline auto create(C c, T && t, Args &&... args)
        -> decltype(Fs_Obj_Constructor<N - 1>::create(
            ::std::forward<C>(c), ::std::forward<T>(t),
            ::std::get<N - 1>(::std::forward<T>(t)),
            ::std::forward<Args>(args)...
        ))
    {
        return Fs_Obj_Constructor<N - 1>::create(::std::forward<C>(c),
            ::std::forward<T>(t),
            ::std::get<N - 1>(::std::forward<T>(t)),
            ::std::forward<Args>(args)...
        );
    }
};

template<>
struct Fs_Obj_Constructor<0> {
    template<typename C, typename T, typename... Args>
    static inline auto create(C c, T &&, Args &&... args)
    {
        *c = new (::std::remove_pointer<
            ::std::remove_pointer<::std::decay<C>::type>::type
        >::type)(::std::forward<Args>(args)...);
    }
};

template<typename C, typename T>
inline auto _Fs_Obj_Constructor_Functor_(C c, T && t)
-> decltype(Fs_Obj_Constructor< ::std::tuple_size<
    typename ::std::decay<T>::type
>::value>::create(::std::forward<C>(c),
    ::std::forward<T>(t)))
{
    return Fs_Obj_Constructor< ::std::tuple_size<
        typename ::std::decay<T>::type
    >::value>::create(::std::forward<C>(c),
        ::std::forward<T>(t));
}

class Fs_Obj_ObjectConstructor
{
public:

    template<class T, class... Args>
    static T* CreateF(Args... args) {
        T* ptr = nullptr;
        _Fs_Obj_Constructor_Functor_(&ptr, std::make_tuple(std::forward<Args>(args)...));
        return ptr;
    }
};


#endif  // SERIALIZE_CALLBACKHELPER_H_
