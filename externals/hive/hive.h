/*
** repository: https://github.com/trumanzhao/luna
** trumanzhao, 2017-05-13, trumanzhao@foxmail.com
*/

#pragma once

#include "luna.h"

const int MAJOR_VERSION_NUMBER = 0;
const int MINOR_VERSION_NUMBER = 1;
const int REVISION_NUMBER = 1;

//文件沙盒及文件热加载 (hive.import)
//在hive中, 用户主要通过import函数加载lua文件.
//*import为每个文件创建了一个沙盒环境, 这使得各个文件中的变量名不会冲突.
//*通过import加载文件时, 可以通过环境变量设置根路径, 如: LUA_ROOT = / data / script /
//*在需要的地方, 用户也可以同时使用require加载所需文件.
//*多次import同一个文件, 实际上只会加重一次, import返回的是文件的环境表.
//*文件时间戳变化是, 会自动重新加载.
class hive final
{
public:
    hive() { printf("hive::ctor(): this = %p\n", this); }
    ~hive() { printf("hive::ctor(): this = %p\n", this); }
    int get_version(lua_State* L);
    time_t get_file_time(const char* filename);
    int get_full_path(lua_State* L);
    int64_t get_time_ms();
    int64_t get_time_ns();
    void sleep_ms(int ms);
    void daemon();
    void register_signal(int n);
    void default_signal(int n);
    void ignore_signal(int n);
public:
    void __gc() { printf("hive::__gc(): this = %p\n", this); } // custom gc, just do nothing
    void set_signal(int n);
    void die(const std::string& err);

    //https://en.cppreference.com/w/cpp/named_req/StandardLayoutType
    //初始化 (SandBox环境)
    int init(int argc, const char* argv[]);
    //初始化逻辑 (hive.init)
    int init();

    //热加载 (hive.reload)
    int reload();

    //启停与信号 (hive.run)
    //*程序启动后,首先加载入口文件 (program_entry.lua).
    //*如果程序需要持续执行,而不是仅仅执行一遍,那么在hive上定义一个名为'run'的函数.
    //*这样hive框架会一直循环的调用hive.run,如果程序想要退出,那么简单的将hive.run赋值为nil即可. 在循环调用的过程中,如果发现入口文件时间戳变化,会自动重新加载.
    //*用户可以注册信号hive.register_signal(signo),注册后,可以通过掩码hive.signal来检视.
    //*注意,用户需要在'hive.run'中调用sleep,否则会出现CPU完全占用的情况.
    //void run(int argc, const char* argv[]);
    int run();

    //错误处理
    //*一旦hive.run函数执行时抛出错误, hive将立即退出, 并将错误信息写入entry.lua.err文件中.
    //*这里entry.lua指的是入口文件的文件名, 建议一般的服务程序在hive.run函数中自行捕获错误.

    //结束逻辑 (hive.fini)
    int fini();

    DECLARE_LUA_CLASS(hive);

    //https://en.cppreference.com/w/cpp/named_req/StandardLayoutType
    //All non-static data members have the same access control
    //Has no virtual functions or virtual base classes
    //Has no non-static data members of reference type
    //All non-static data members and base classes are themselves standard layout types
//private:
    uint64_t m_signal = 0;
    int m_reload_time = 500; //ms
    std::string m_entry;
//public:
    //L (Lua single main thread/state)
    lua_State* L = nullptr;
//private:
    int64_t last_check = get_time_ms();
};

extern hive* g_app;

