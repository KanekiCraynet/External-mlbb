#pragma once
#include "curl/curl.h"
#include "Tools.h"
#include "json.hpp"

#include "obfuscate/obfuscate.h"

using json = nlohmann::ordered_json;
std::string g_Token, g_Auth;
std::string expired, title, version, battleData;
std::string UUID;

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;
    mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        return 0;
    }
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

std::string Login(JavaVM *vm, const char *user_key, bool *success) {
    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);
    auto object = getJNIContext(env);
    std::string hwid = user_key;
    hwid += GetAndroidID(env, object);
    hwid += GetDeviceModel(env);
    hwid += GetDeviceBrand(env);
    std::string UUID = GetDeviceUniqueIdentifier(env, hwid.c_str());
    vm->DetachCurrentThread();
    std::string errMsg;

    struct MemoryStruct chunk {};
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        std::string URL_AUTH = OBFUSCATE("https://vipgoatmod.my.id//connect");
        curl_easy_setopt(curl, CURLOPT_URL, URL_AUTH.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        headers = curl_slist_append(headers, "Charset: UTF-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        std::string data = "game=MLBB";
		data += "&appVer=v1.2";
		data += "&user_key=" + std::string(user_key);
		data += "&serial=" + UUID;
		curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json result = json::parse(chunk.memory);
                auto STATUS = std::string{OBFUSCATE("status")};
                if (result[STATUS] == true) {
                    auto DATA = std::string{OBFUSCATE("data")};
                    auto TOKEN = std::string{OBFUSCATE("token")};
                    auto RNG = std::string{OBFUSCATE("rng")};
					auto EXPIRED = std::string{OBFUSCATE("expired")};
                    auto TITLE = std::string{OBFUSCATE("title")};
					auto VERSION = std::string{OBFUSCATE("version")};
                    auto BATTLEDATA = std::string{OBFUSCATE("btData")};
                    std::string token = result[DATA][TOKEN].get<std::string>();
                    time_t rng = result[DATA][RNG].get<time_t>();
					expired = result[DATA][EXPIRED].get<std::string>();
                    title = result[DATA][TITLE].get<std::string>();
					version = result[DATA][VERSION].get<std::string>();
					battleData = result[DATA][BATTLEDATA].get<std::string>();
                    if (rng + 30 > time(0)) {
                        std::string auth = OBFUSCATE("MLBB");
                        auth += std::string(OBFUSCATE("-"));
                        auth += user_key;
                        auth += std::string(OBFUSCATE("-"));
                        auth += UUID;
                        auth += std::string(OBFUSCATE("-"));
                        auth += std::string(OBFUSCATE("SENSEI-CHEAT"));
                        std::string outputAuth = Tools::CalcMD5(auth);
                        g_Token = token;
                        g_Auth = outputAuth;
                        *success = g_Token == g_Auth;
                        if (success) {
                            pthread_t t;
                        }
                    } else {		
						*success = false;
						errMsg = std::string{OBFUSCATE("TIME ERROR!")};
					}
                } else {
					*success = false;
                    auto REASON = std::string{OBFUSCATE("reason")};
                    errMsg = result[REASON].get<std::string>();
                }
            } catch (json::exception &e) {
               // errMsg = e.what();
            }
        } else {
			*success = false;
            errMsg = std::string(curl_easy_strerror(res));
        }
    }
    curl_easy_cleanup(curl);
    return errMsg;
}
