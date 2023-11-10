#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <vector>
#include <map>
#include <chrono>
#include <fstream>
#include <thread>
#include <pthread.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <jni.h>
#include <android/log.h>
#include <elf.h>
#include <dlfcn.h>
#include <sys/system_properties.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/native_window.h>

#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "imgui_additional.h"
#include "imgui_themes.h"
#include "backends/imgui_impl_android.h"
#include "backends/imgui_impl_opengl3.h"
#include "fonts/GoogleSans.h"

#include "Tools/xDL/xdl.h"
#include "Tools/fake_dlfcn.h"
#include "Tools/Il2Cpp.h"
#include "Tools/Tools.h"

#include "struct/Vector3.hpp"
#include "struct/Vector2.h"
#include "struct/Rect.h"
#include "struct/Quaternion.h"

#include "config/setup.h"
#include "config/JNIStuff.h"

#include "TouchSystem.h"

#include "icon/DrawIcon.h"

#include "login/Login.h"

#include "feature/class.h"
#include "feature/room.h"
#include "Menu.h"
#include "feature/esp.h"
#include "feature/protection.h"

EGLBoolean (*orig_eglSwapBuffers)(...);
EGLBoolean _eglSwapBuffers (EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
	if (!(glWidth > 0 && glHeight > 0)) return orig_eglSwapBuffers(dpy, surface);
    if (!g_Initialized) {
        ImGui::CreateContext();
        ImGuiStyle* style = &ImGui::GetStyle();

		SetBlackGoldTheme();
		style->WindowBorderSize = 1.0f;
		style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style->ScaleAllSizes(3.0f);

        ImGuiIO* io = &ImGui::GetIO();
        io->IniFilename = nullptr;
		
		io->DisplaySize = ImVec2((float)glWidth, (float)glHeight);
		
        ImGui_ImplOpenGL3_Init("#version 300 es");

        ImFontConfig font_cfg;
        io->Fonts->AddFontFromMemoryCompressedTTF(GoogleSans_compressed_data, GoogleSans_compressed_size, 28.5f, &font_cfg, io->Fonts->GetGlyphRangesChineseFull());
		
		setRes(glWidth, glHeight);
		
        g_Initialized = true;
    }

    ImGuiIO* io = &ImGui::GetIO();
	
    ImGui_ImplOpenGL3_NewFrame();
	ImplAndroid_NewFrame();
    ImGui::NewFrame();
	
	if (screenWidth < glWidth && screenHeight < glHeight) setRes(glWidth, glHeight);
	
	// set the unity screen resolution to fix touch issue
    if (screenWidth != Screen::get_width() || screenHeight != Screen::get_height()) {
        Screen::SetResolution(screenWidth, screenHeight, true);
    }
	
	ImGui_GetTouch(io, screenHeight);
	
	auto hideShowMin = ImVec2(0, screenHeight - 80);
	auto hideShowMax = ImVec2(80, screenHeight);
	auto mousePos = io->MousePos;
	
	if  (mousePos.x >= hideShowMin.x && mousePos.x <= hideShowMax.x && mousePos.y >= hideShowMin.y && mousePos.y <= hideShowMax.y) {
		showMenu = true;
	}
	
	//ShowWindow
	if (showMenu) ShowMenu();
	
	if (bFullChecked) drawESP(ImGui::GetBackgroundDrawList(), screenWidth, screenHeight);
	
	if (!AttachIconDone) {
		AttachIcon();
		AttachIconDone = true;
	}
	
	if (!AttachSpellDone) {
		AttachSpell();
		AttachSpellDone = true;
	}
	
    ImGui::EndFrame();
    ImGui::Render();
	glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	if (clearMousePos) {
        io->MousePos = ImVec2(-1, -1);
        clearMousePos = false;
    }
	
    return orig_eglSwapBuffers(dpy, surface);
}

void *main_thread(void *) {
	
    while (!m_IL2CPP) {
        m_IL2CPP = Tools::GetBaseAddress("liblogic.so");
        sleep(1);
    }

    while (!m_EGL) {
        m_EGL = dlopen_ex("libEGL.so", RTLD_NOW);
        sleep(1);
    }
	
	Il2CppAttach("liblogic.so");
	
    Tools::Hook((void *) dlsym_ex(m_EGL, "eglSwapBuffers"), (void *) _eglSwapBuffers, (void **) &orig_eglSwapBuffers);
    Tools::Hook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("System/Net"), OBFUSCATE("Dns"), OBFUSCATE("GetHostByName_internal"), 4), (void *) oDns_GetHostByName_internal, (void **) &Dns_GetHostByName_internal);
    Tools::Hook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("System/Net"), OBFUSCATE("Dns"), OBFUSCATE("GetHostByAddr_internal"), 4), (void *) oDns_GetHostByAddr_internal, (void **) &Dns_GetHostByAddr_internal);
    Tools::Hook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("System/Net"), OBFUSCATE("Dns"), OBFUSCATE("hostent_to_IPHostEntry"), 3), (void *) oDns_hostent_to_IPHostEntry, (void **) &Dns_hostent_to_IPHostEntry);
    Tools::Hook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("System/Net"), OBFUSCATE("Dns"), OBFUSCATE("GetHostByAddressFromString"), 2), (void *) oDns_GetHostByAddressFromString, (void **) &Dns_GetHostByAddressFromString);
    Tools::Hook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("System/Net"), OBFUSCATE("Dns"), OBFUSCATE("GetHostEntry"), 1), (void *) oDns_GetHostEntry, (void **) &Dns_GetHostEntry);
    Tools::Hook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("System/Net"), OBFUSCATE("Dns"), OBFUSCATE("GetHostEntry"), 1), (void *) oDns_GetHostEntry, (void **) &Dns_GetHostEntry);
    Tools::Hook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("System/Net"), OBFUSCATE("Dns"), OBFUSCATE("GetHostAddresses"), 1), (void *) oDns_GetHostAddresses, (void **) &Dns_GetHostAddresses);
    Tools::Hook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("System/Net"), OBFUSCATE("Dns"), OBFUSCATE("GetHostByName"), 1), (void *) oDns_GetHostByName, (void **) &Dns_GetHostByName);
    Tools::Hook((void *) (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("System/Runtime/Remoting"), OBFUSCATE("ServerIdentity"), OBFUSCATE("DisposeServerObject")), (void *) DisposeServerObject, (void **) &oDisposeServerObject);
	pthread_t t;
    return 0;
}

jint (JNICALL *Real_JNI_OnLoad)(JavaVM *vm, void *reserved);
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
	
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
	g_vm = vm;
	
	std::string apkPkg = getPackageName(GetJNIEnv(g_vm));
	std::string libAkSound = std::string(OBFUSCATE("libAkSoundEngine.so"));
    std::string libAkSoundOri1 = std::string(OBFUSCATE("libAkSoundEngine2.bytes"));
    std::string libAkSoundOri2 = std::string(OBFUSCATE("libAkSoundEngine2.so"));
    
    std::string localPath = std::string(OBFUSCATE("/storage/emulated/0/Android/data/")) + apkPkg + std::string(OBFUSCATE("/files/dragon2017/assets/comlibs/")) + std::string(ARCH);
    std::string rootPath = std::string(OBFUSCATE("/data/data/")) + apkPkg + std::string(OBFUSCATE("/app_libs/comlibs/")) + std::string(ARCH);
    
    std::string pathAkSound = rootPath + std::string(OBFUSCATE("/")) + libAkSound;
    std::string pathAkSoundOri1 = localPath + std::string(OBFUSCATE("/")) + libAkSoundOri1;
    std::string pathAkSoundOri2 = rootPath + std::string(OBFUSCATE("/")) + libAkSoundOri2;
    
    if (CopyFile(pathAkSoundOri1.c_str(), pathAkSoundOri2.c_str())) {
        void *handle = dlopen(pathAkSoundOri2.c_str(), RTLD_NOW);
        if (!handle) {
            handle = dlopen(pathAkSoundOri2.c_str(), RTLD_NOW);
            sleep(1);
        }
        auto Hook_JNI_OnLoad = dlsym(handle, OBFUSCATE("JNI_OnLoad"));
        if (Hook_JNI_OnLoad) {
            Real_JNI_OnLoad = decltype(Real_JNI_OnLoad)(Hook_JNI_OnLoad);
            pthread_t t;
            pthread_create(&t, nullptr, main_thread, nullptr);
            if (CheckFile(pathAkSoundOri2.c_str())) {
                std::remove(pathAkSound.c_str());
                std::rename(pathAkSoundOri2.c_str(), pathAkSound.c_str());
            }
            return Real_JNI_OnLoad(vm, reserved);
        }
    }
    return JNI_ERR;
}
