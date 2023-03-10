# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/home/shvarev/456/libakrypt-0.x-master;/home/shvarev/456/libakrypt-0.x-master/cmake-build-debug")
set(CPACK_CMAKE_GENERATOR "Ninja")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libbz2-1.0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Axel Kenzo")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/snap/clion/219/bin/cmake/linux/share/cmake-3.24/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "libakrypt built using CMake")
set(CPACK_GENERATOR "DEB")
set(CPACK_INSTALL_CMAKE_PROJECTS "/home/shvarev/456/libakrypt-0.x-master/cmake-build-debug;libakrypt;ALL;/")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "/home/shvarev/456/libakrypt-0.x-master/cmake")
set(CPACK_NSIS_DISPLAY_NAME "libakrypt 0.9.10")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "\$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "libakrypt 0.9.10")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "/home/shvarev/456/libakrypt-0.x-master/cmake-build-debug/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION "Библиотека, реализующая российские криптографические механизмы в пространстве пользователя")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/snap/clion/219/bin/cmake/linux/share/cmake-3.24/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "libakrypt built using CMake")
set(CPACK_PACKAGE_FILE_NAME "libakrypt-0.9.10-x86_64")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "libakrypt 0.9.10")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "libakrypt 0.9.10")
set(CPACK_PACKAGE_NAME "libakrypt")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Axel Kenzo и Компания изящной словесности")
set(CPACK_PACKAGE_VERSION "0.9.10")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "9")
set(CPACK_PACKAGE_VERSION_PATCH "10")
set(CPACK_RESOURCE_FILE_LICENSE "/snap/clion/219/bin/cmake/linux/share/cmake-3.24/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "/snap/clion/219/bin/cmake/linux/share/cmake-3.24/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/snap/clion/219/bin/cmake/linux/share/cmake-3.24/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TBZ2")
set(CPACK_SOURCE_IGNORE_FILES "\\.git/;.gitignore;.delme*;.kdev4/*;TAGS;CMakeLists.txt.user*;scratch*")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/shvarev/456/libakrypt-0.x-master/cmake-build-debug/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "libakrypt-0.9.10")
set(CPACK_STRIP_FILES "TRUE")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Linux")
set(CPACK_VERBATIM_VARIABLES "YES")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/shvarev/456/libakrypt-0.x-master/cmake-build-debug/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
