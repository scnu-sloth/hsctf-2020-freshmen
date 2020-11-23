#include <cstdio>
#include <cstring>
#include <unistd.h>

#ifdef ENABLE_OLLVM
#define OLLVM_FLAG(flag) __attribute((__annotate__((flag))))
#else
#define OLLVM_FLAG(flag)
#endif

//OLLVM_FLAG("sub")
//OLLVM_FLAG("bcf")
//OLLVM_FLAG("fla")
OLLVM_FLAG("strenc")
void showFlag() {
    printf("Flag: %s\n", "HSCTF{K7wgngW4SCx3nAWBWDtR}");
}

OLLVM_FLAG("strenc")
void checkFlag(char *pwd) {
    // pY*PDK*H&hQp938%BZ!dh87h8fWhF6
    if (strstr(pwd, "pY*PDK*H&hQp938%BZ!dh87h8fWhF6") != nullptr) {
        printf("Correct password!\n");
        showFlag();
    } else {
        printf("Incorrect password!\n");
    }
}

int main() {
    char *pwd = new char[getpagesize()];
    memset(pwd, 0, getpagesize());
    size_t len = 0;
    printf("Please input password:\n");
    getline(&pwd, &len, stdin);
    checkFlag(pwd);
    delete [] pwd;
    printf("^_^\n");
    return 0;
}
