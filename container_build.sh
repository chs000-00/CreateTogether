# Use this for compiling your mods in the github container. Copy this file over.
# If there are issues with executing it, such as permissions, use chmod +x build.sh

export SPLAT_DIR=~/xwin/splat
export TOOLCHAIN_REPO=~/xwin/toolchain
export HOST_ARCH=x64
export MSVC_BASE=$SPLAT_DIR/crt
export WINSDK_BASE=$SPLAT_DIR/sdk

cmake \
   -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
   -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_REPO/clang-cl-msvc.cmake \
   -DCMAKE_BUILD_TYPE=RelWithDebInfo -B build \
   -DGEODE_DISABLE_FMT_CONSTEVAL=1 -G Ninja

cmake --build build --config RelWithDebInfo