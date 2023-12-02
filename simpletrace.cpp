#include <dlfcn.h>
#include <iostream>

extern "C" {
void __cyg_profile_func_enter(void *func_address, void *call_site);
void __cyg_profile_func_exit(void *func_address, void *call_site);
}

// dladdrを用いて関数アドレスから関数シンボルへ変換
const char *addr2name(void *address) {
    Dl_info dli;
    if(0 != dladdr(address, &dli)) {
        return dli.dli_sname;
    }
    return 0;
}

void __cyg_profile_func_enter(void *func_address, void *call_site) {
    const char *func_name = addr2name(func_address);
    if(func_name) {
        std::cout << "simple tracer: enter - " << func_name << std::endl;
    }
}

void __cyg_profile_func_exit(void *func_address, void *call_site) {
    const char *func_name = addr2name(func_address);
    if(func_name) {
        std::cout << "simple tracer: exit  - " << func_name << std::endl;
    }
}
