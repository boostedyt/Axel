#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Library Files:
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "urlmon.lib")

// Windows Header Files:
#include <windows.h>
#include <winsdkver.h>
#include <sdkddkver.h>
#include <winternl.h>
#include <WinUser.h>
#include <d3d11.h>

#include <cassert>
#include <cinttypes>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <atomic>
#include <Mmsystem.h>
#include <xkeycheck.h>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <Psapi.h>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <timeapi.h>
#include <time.h>
#include <intrin.h>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <memory> 
#include <stdarg.h> 
#include <limits>
#include <mutex>
#include <optional>
#include <sstream>
#include <stack>
#include <ShlObj.h>
#include <string>
#include <xstring>
#include <xutility>
#include <thread>
#include <type_traits>
#include <vector>
#include <locale>
#include <codecvt>
#include <stdio.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Settings.hpp"
#include "Types.hpp"
#include "Logger.hpp"
#include "Util.hpp"
#include "Memory.hpp"
#include "Game.hpp"
#include "ScriptGlobal.hpp"
#include "Functions.hpp"
#include "Lists.hpp"
#include "Natives.hpp"
#include "UI/UIManager.hpp"
#include "UI/BoolOption.hpp"
#include "UI/ChooseOption.hpp"
#include "UI/NumberOption.hpp"
#include "UI/RegularOption.hpp"
#include "UI/SubOption.hpp"
#include "UI/RegularSubmenu.hpp"
#include "UI/PlayerSubmenu.hpp"
#include "Online.hpp"