#pragma once

template <typename T>
struct Singleton {
    static T& get_instance()
    {
        static T t;
        return t;
    }
};

template<typename T>
auto& St = Singleton<T>().get_instance();
