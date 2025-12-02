# Install

At the moment the following systems have been tested.

- Ubuntu 24.04 (both of native and WSL2 on Windows11)
- AlmaLinux 9.5 (both of native and WSL2 on Windows11)
- macOS 12.7.6 (MacBook Air 2015 MJVM2J/A)

In principle you can install the tip on the system
which PLPLOT and GNU readline are installed.

## (1) Install PLPLOT, GNU-readline

- **Ubuntu 24.04**
```
sudo apt update
sudo apt upgrade
sudo apt install g++
sudo apt install libplplot-dev
sudo apt install plplot-driver-cairo
sudo apt install libreadline-dev
```
- **AlmaLinux 9**
```
sudo dnf update
sudo dnf upgrade
sudo dnf install dnf-plugins-core     (<-- this may not be necessary)
sudo dnf config-manager --enable crb
sudo dnf install epel-release
sudo dnf install epel-next-release
sudo dnf install g++
sudo dnf install plplot-devel
sudo dnf install readline-devel
```
- **Windows 11**

The easiest way is to run the Linux on WSL2.

official : https://learn.microsoft.com/windows/wsl/install  

- **macOS 12.7.6**
1. install MacPorts
   https://www.macports.org
2. install XQuartz
   https://www.xquartz.org
3. install PLPLOT, readline from the terminal  
```
sudo port install plplot
sudo port install readline
```

## (2) Configure and make the tip executable

Access to https://github.com/shu-htk/tip-dev

From the **"Code"** pull-down menu, choose **"Download zip"**

or directly download from
 https://github.com/shu-htk/tip-dev/archive/refs/heads/main.zip

Copy downloaded zip file to your working directory.

On the Linux terminal, extract zip file,
```
unzip tip-dev-main.zip
```

then do
```
cd tip-dev-main
./configure
make
```
The executable is compiled and outputted to `./bin/tip`

If your shell has command path to $HOME/bin,
copy the executable file to `$HOME/bin` by
```
make install
```
<!--
edit $HOME/.bashrc and add the following line
```
export PATH=$PATH:$HOME/bin
```
-->

## (3) About my_macro 

The executable file `my_macro` is also installed when you install the `tip`.  
It is a simple example using [MacroTool](ref/MacroTool.md).

## (4) Enable EPICS CA (optional)

If it is already installed the EPICS in your computer,
just check if the environment variable `EPICS_BASE` is set in your shell.
If it is set,
the [configure script of the Tip](#2-configure-and-make-the-tip-executable)
generate Makefile to enable the EPICS CA.

If it is not installed the EPICS, you need to make and setup the
EPICS environment as following.

Download the archive of the EPICS source.

- stable:: 
https://epics-controls.org/download/base/base-3.15.9.tar.gz
- new:
https://epics-controls.org/download/base/base-7.0.9.tar.gz

For example, installing new version to $HOME/epics

```
mkdir -p $HOME/epics
cp base-7.0.9.tar.gz $HOME/epics
cd $HOME/epics
tar zxf base-7.0.9.tar.gz
cd base-7.0.9
make
```
It takes for a while to complete compiling.

After that you should set the environment variable as following.

```
export EPICS_BASE=$HOME/epics/base-7.0.9
```


