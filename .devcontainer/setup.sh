#!/bin/bash

sudo apt-get update
sudo apt-get -y install wget software-properties-common gnupg
# i shouldnt NEED to do this but the latest ver on ubuntu is clang-14!?
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 19
sudo apt-get update
sudo apt-get -y install unzip pip ninja-build
sudo apt install -y git clang-19 clang-tools-19 lld-19
pip install cmake --upgrade --break-system-packages # because for whatever reason it installs an outdated version, ig source repos arent up to date!
rm llvm.sh

export CLANG_VER=19
export LLVM_VER=19
echo "export export CLANG_VER=19" >> ~/.bashrc
echo "export export LLVM_VER=19" >> ~/.bashrc

wget https://github.com/geode-sdk/cli/releases/download/v3.8.0/geode-cli-v3.8.0-linux.zip
unzip geode-cli-v3.8.0-linux.zip
chmod +x geode
sudo mv geode /usr/local/bin/
rm geode-cli-v3.8.0-linux.zip

wget https://github.com/Jake-Shadle/xwin/releases/download/0.9.0/xwin-0.9.0-x86_64-unknown-linux-musl.tar.gz
tar -xzf xwin-0.9.0-x86_64-unknown-linux-musl.tar.gz
chmod +x xwin-0.9.0-x86_64-unknown-linux-musl/xwin
sudo mv xwin-0.9.0-x86_64-unknown-linux-musl/xwin /usr/local/bin/
rm -rf xwin-0.9.0-x86_64-unknown-linux-musl
rm xwin-0.9.0-x86_64-unknown-linux-musl.tar.gz

mkdir -p ~/xwin/splat
cd ~/xwin
xwin --arch x86_64 --accept-license splat --include-debug-libs --output splat

git clone https://github.com/matcool/clang-msvc-sdk.git toolchain

sudo mkdir /home/GeometryDashFake/
sudo touch /home/GeometryDashFake/GeometryDash.exe

geode profile add --name GeodeContainer /home/GeometryDashFake/GeometryDash.exe win

geode sdk install ~/geode
export GEODE_SDK=~/geode
geode sdk install-binaries

sudo apt-get clean
sudo rm -rf /var/lib/apt/lists/*

echo "export GEODE_SDK=~/geode" >> ~/.bashrc