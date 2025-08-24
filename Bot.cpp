#include <Windows.h>
#include <thread>
#include <atomic>
#include "Bot.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx9.h"

std::atomic<bool> botEnabled(true);

void BotLoop() {
    while (true) {
        if (botEnabled) {
            // TODO: Scan players, detect spinbots, aim/fire
        }
        Sleep(50); // ~20 FPS scan
    }
}

void RenderGUI() {
    ImGui::Begin("Anti-Spinbot");
    ImGui::Checkbox("Enable Bot", &botEnabled);
    ImGui::Text("Spinbot detection active");
    ImGui::End();
}

DWORD WINAPI MainThread(LPVOID lpReserved) {
    std::thread(BotLoop).detach();
    while (true) {
        RenderGUI();
        Sleep(16); // ~60 FPS GUI
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
    }
    return TRUE;
}
