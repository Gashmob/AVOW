#ifndef VERSION_H
#define VERSION_H

#define VERSION_MAJOR 0
#define VERSION_MINOR 2
#define VERSION_PATCH 0

#define MAKE_VERSION(major, minor, patch) ((major) * 1000000 + (minor) * 1000 + (patch))
#define MAKE_VERSION_STRING(major, minor, patch) std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch)

#define VERSION MAKE_VERSION(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH)
#define VERSION_STRING MAKE_VERSION_STRING(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH)

#define LICENSE "GPL-3.0"

#endif // VERSION_H
