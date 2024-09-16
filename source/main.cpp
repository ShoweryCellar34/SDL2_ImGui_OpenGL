#include <string>
#include <vector>
#include <Pentagram.hpp>
#include <defines_and_globals.hpp>
#include <fileInterfaces.hpp>
#include <node.hpp>
#include <imguiDraw.hpp>

void eventCallback(PNT::Window* window, PNT::windowEvent event) {
    switch(event.type) {
    case PNT_EVENT_TYPE_KEYBOARD:
        switch(event.keyboard.key) {
        case GLFW_KEY_S:
            if(event.keyboard.mods == GLFW_MOD_CONTROL + GLFW_MOD_SHIFT && event.keyboard.action == GLFW_RELEASE) {
                saveAsNode(g_currentScene);
            } else if(event.keyboard.mods == GLFW_MOD_CONTROL && event.keyboard.action == GLFW_RELEASE) {
                saveScene(g_currentScene);
            }
            break;

        case GLFW_KEY_O:
            if(event.keyboard.mods == GLFW_MOD_CONTROL && event.keyboard.action == GLFW_RELEASE) {
                loadProject(g_currentScene);
            }
            break;
        }
        break;
    }
}

int main(int argc, char* argv[]) {
    stbi_set_flip_vertically_on_load(true);

    if(!PNT::init()) {
        exit(EXIT_FAILURE);
    }

    g_window.createWindow("Ghoul Engine", 1200, 675, 250, 250, ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable);
    refreshTitle();
    g_window.setAspectRatio(16, 9);
    g_window.setEventCallback(eventCallback);
    g_window.setClearColor(0.33f, 0.33f, 0.33f, 1.0f);

    g_currentScene = new node(nullptr, nullptr, "", "ROOT");
    g_scenes.push_back(g_currentScene);

    while(!g_window.shouldClose()) {
        PNT::processEvents();
        g_window.startFrame();

        drawGlobalDockingWindow();
        drawMainMenuBar();
        drawNodeTree(g_currentScene);
        drawNodeInspector(g_currentScene);

        g_window.endFrame();
    }

    for(nodeRef scene : g_scenes) {
        delete scene;
    }
    g_scenes.clear();
    g_currentScene = nullptr;

    PNT::deinit();
    return 0;
}
