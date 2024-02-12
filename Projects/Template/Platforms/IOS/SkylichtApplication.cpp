#include "pch.h"
#include "SkylichtApplication.h"

#include "common/system_utils.h"

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;

CApplication *g_mainApp = NULL;
IrrlichtDevice *g_device = NULL;

SkylichtApplication::SkylichtApplication(int argc, char **argv, int width, int height)
    :AngleApplication(std::string("Skylicht Engine"), argc, argv, 3, 0, width, height)
{
    g_mainApp = new CApplication();
    
    std::vector<std::string> params;
    for (int i = 1; i < argc; i++)
        params.push_back(std::string(argv[i]));
    g_mainApp->setParams(params);
}

SkylichtApplication::~SkylichtApplication()
{
    
}

bool SkylichtApplication::initialize()
{
    AngleApplication::initialize();
    
    int w = getWindow()->getWidth();
    int h = getWindow()->getHeight();

    OSWindow* window = getWindow();
    
    SIrrlichtCreationParameters p;
    p.DriverType = video::EDT_OPENGLES;
    p.WindowSize = dimension2d<u32>(w, h);
    p.Bits = (u8)32;
    p.Fullscreen = false;
    p.Stencilbuffer = false;
    p.Vsync = false;
    p.EventReceiver = g_mainApp;
    p.WindowId = window->getNativeOSWindow();
    
    // init irrlicht engine
    g_device = createDeviceEx(p);
    
    // change working directory
    std::string appFolder = angle::GetExecutableDirectory();
    g_device->getFileSystem()->changeWorkingDirectoryTo(appFolder.c_str());
    
    // init application
    g_mainApp->initApplication(g_device);
    
    return true;
}

void SkylichtApplication::destroy()
{
    g_mainApp->destroyApplication();

    g_device->drop();

    delete g_mainApp;
    g_mainApp = NULL;
    g_device = NULL;
    
    AngleApplication::destroy();
}

void SkylichtApplication::step(float dt, double totalTime)
{
    AngleApplication::step(dt, totalTime);
}

void SkylichtApplication::draw()
{
    g_device->run();
    g_mainApp->mainLoop();
}

void SkylichtApplication::onResized(int width, int height)
{
    irr::SEvent event;
    event.EventType = irr::EET_GAME_RESIZE;
    event.UserEvent.UserData1 = (s32)width;
    event.UserEvent.UserData2 = (s32)height;
    
    IrrlichtDevice *dev  = getIrrlichtDevice();
    if (dev)
        dev->postEventFromUser(event);
}
