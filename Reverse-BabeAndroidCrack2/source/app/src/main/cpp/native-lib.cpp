#include <jni.h>
#include <string>
#include <openssl/aes.h>
#include <openssl/md5.h>

jstring getFlag(JNIEnv *env, jobject, jstring km) {
    const char *km_ = env->GetStringUTFChars(km, nullptr);
    size_t size = strlen(km_);
    jstring result = nullptr;

//    unsigned char flags[] = "HSCTF{SuAn_n1_Niu_b@}";
    unsigned char out[PAGE_SIZE];
    unsigned char iv[] = {1, 2, 3, 4, 5, 6, 7, 8, 8, 7, 6, 5, 5, 1, 2, 1};
    unsigned char cipher[] = {
            117, 119, 43, 38, 124, 54, 99, 49, 74, 255, 69, 163, 129, 69, 21, 209, 175, 214, 236,
            187, 20, 114, 198, 7, 37, 36, 91, 106, 162, 210, 86,67, 0
    };
    size_t cipher_size = 22;
    unsigned char key_buf[AES_BLOCK_SIZE];
    unsigned char ivec[AES_BLOCK_SIZE];
    AES_KEY key;

    if (size != 8) {
        result = env->NewStringUTF("卡密不正确");
        goto end;
    }

    MD5(reinterpret_cast<const unsigned char *>(km_), size, key_buf);
//    AES_set_encrypt_key(key_buf, AES_BLOCK_SIZE*8, &key);
//
//    memcpy(ivec, iv, AES_BLOCK_SIZE);
//    AES_cbc_encrypt(flags, out, strlen(reinterpret_cast<const char *const>(flags)) + 1, &key, ivec, AES_ENCRYPT);

    AES_set_decrypt_key(key_buf, AES_BLOCK_SIZE * 8, &key);
    memcpy(ivec, iv, AES_BLOCK_SIZE);
    AES_cbc_encrypt(cipher, out, cipher_size, &key, ivec, AES_DECRYPT);

    result = env->NewStringUTF(reinterpret_cast<const char *>(out));

    end:
    env->ReleaseStringUTFChars(km, km_);
    return result;
}

JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *) {
    JNIEnv *env = nullptr;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }

    JNINativeMethod methods[] = {

            {"getFlag", "(Ljava/lang/String;)Ljava/lang/String;", (void *) getFlag},
    };

    jclass inheritance = env->FindClass("cn/edu/scnu/ctf/babeandroidcrack2/PanelActivity");
    env->RegisterNatives(inheritance, methods,
                         sizeof(methods) / sizeof(methods[0]));

    return JNI_VERSION_1_4;
}
