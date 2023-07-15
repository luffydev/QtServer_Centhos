#ifndef __SINGLETON__
#define __SINGLETON__
#define DECLARE_SINGLETON(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;\
    public: \
        static Class& instance() \
        { \
            static Class instance; \
            return instance; \
        } 
   
#endif
