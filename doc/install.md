# Install

At the moment the following systems have been tested.

- Ubuntu 24.04 (both of native and WSL2 on Windows11)
- AlmaLinux 9.5 (both of native and WSL2 on Windows11)

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
- **AlmaLinax 9**
```
sudo dnf update
sudo dnf upgrade
# sudo dnf install dnf-plugins-core     (<-- this may not be neccessary)
# sudo dnf config-manager --enable crb  (<-- this may not be neccessary)
sudo dnf install epel-release
sudo dnf install epel-next-release
sudo dnf install g++
sudo dnf install plplot-devel
sudo dnf install readline-devel
```
- **Windows 10 or 11**

The easiest way is to run the Linux distribution on WLS2.

official : https://learn.microsoft.com/windows/wsl/install  


## (2) Configure and make tip executable

Access to https://github.com/shu-htk/tip-dev

from the **"Code"** pulldown menu button, choose **"Download zip"**

or directly download from
 https://github.com/shu-htk/tip-dev/archive/refs/heads/main.zip

copy downloaded zip file to your working directry on the Linux terminal

extract zip file
```
unzip tip-dev-main.zip
```

then do
```
cd tip-dev-main
./configure
make
```
The executable is comipled and output to `./bin/tip`

If your shell has command path to $HOME/bin,
copy the executable file to `$HOME/bin`
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

The executable file `my_macro` is also installed when you install `tip`.  
It is the sample program using the ferture of [thl::MacroTool](ref/MacroTool.md)
but not using graphic drawing feture of PLPLOT.

