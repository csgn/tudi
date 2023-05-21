#ifdef _WIN32
#ifdef _WIN64
#define TUDI_PLATFORM_WINDOWS
#error "WIN64 is not supported!"
#else
#error "WIN86 is not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#define TUDI_PLATFORM_APPLE
#error "Apple is not supported!"
#elif defined(__ANDROID__)
#define HZ_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define HZ_PLATFORM_LINUX
#else
#error "Unknown platform!"
#endif
