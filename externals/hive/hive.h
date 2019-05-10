/*
** repository: https://github.com/trumanzhao/luna
** trumanzhao, 2017-05-13, trumanzhao@foxmail.com
*/

#pragma once

#include "luna.h"

const int MAJOR_VERSION_NUMBER = 0;
const int MINOR_VERSION_NUMBER = 1;
const int REVISION_NUMBER = 1;

//�ļ�ɳ�м��ļ��ȼ��� (hive.import)
//��hive��, �û���Ҫͨ��import��������lua�ļ�.
//*importΪÿ���ļ�������һ��ɳ�л���, ��ʹ�ø����ļ��еı����������ͻ.
//*ͨ��import�����ļ�ʱ, ����ͨ�������������ø�·��, ��: LUA_ROOT = / data / script /
//*����Ҫ�ĵط�, �û�Ҳ����ͬʱʹ��require���������ļ�.
//*���importͬһ���ļ�, ʵ����ֻ�����һ��, import���ص����ļ��Ļ�����.
//*�ļ�ʱ����仯��, ���Զ����¼���.
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
    //��ʼ�� (SandBox����)
    int init(int argc, const char* argv[]);
    //��ʼ���߼� (hive.init)
    int init();

    //�ȼ��� (hive.reload)
    int reload();

    //��ͣ���ź� (hive.run)
    //*����������,���ȼ�������ļ� (program_entry.lua).
    //*���������Ҫ����ִ��,�����ǽ���ִ��һ��,��ô��hive�϶���һ����Ϊ'run'�ĺ���.
    //*����hive��ܻ�һֱѭ���ĵ���hive.run,���������Ҫ�˳�,��ô�򵥵Ľ�hive.run��ֵΪnil����. ��ѭ�����õĹ�����,�����������ļ�ʱ����仯,���Զ����¼���.
    //*�û�����ע���ź�hive.register_signal(signo),ע���,����ͨ������hive.signal������.
    //*ע��,�û���Ҫ��'hive.run'�е���sleep,��������CPU��ȫռ�õ����.
    //void run(int argc, const char* argv[]);
    int run();

    //������
    //*һ��hive.run����ִ��ʱ�׳�����, hive�������˳�, ����������Ϣд��entry.lua.err�ļ���.
    //*����entry.luaָ��������ļ����ļ���, ����һ��ķ��������hive.run���������в������.

    //�����߼� (hive.fini)
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

