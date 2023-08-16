# invary-test-probe

The Invary Test Probe is a very simple Linux kernel module which only inserts a symbol into the kernel symbol table for discovery by the Invary sensor software.  It does not modify the running system in any other way.


## Finding the Pre-built Module for your System

Invary maintains pre-built modules for a large number of Linux distributions/versions and their supported kernel versions.  These are maintained in the <b>archive</b> directory of this repository.

To see if your Linux environment is supported, run the <b>uname -a</b> command:

```
$ uname -a
Linux testMachine 6.2.0-26-generic #26~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Thu Jul 13 16:27:29 UTC 2 x86_64 x86_64 x86_64 GNU/Linux
```
From this example, the machine is a x86_64 system running Ubuntu-22.04 with kernel version 6.2.0.26-generic.  If you navigate to <b>archive/ubuntu/22.04/x86_64</b>, you will find the compressed tar file with the pre-built module.

```
$ cp ~/invary-test-probe/archive/ubuntu/22.04/x86_64/invary-test-probe-ubuntu-22.04-6.2.0.26-generic.tar.gz .
$ tar xvfz invary-test-probe-ubuntu-22.04-6.2.0.26-generic.tar.gz
$ cd invary-test-probe
$ ls
invary-test-probe.ko
```

## Building the Module

If your Linux system is currently not supported by Invary, you can easily build the kernel module from the provided sources.

First, you will need to install the required packages to support building a Linux kernel module.  For Debian/Ubuntu, these are:
```
# Debian
sudo apt-get install linux-headers-$(uname -r) build-essential

# Ubuntu - later versions may also need gcc-12
sudo apt-get install build-essential linux-headers-$(uname -r)
```
For RHEL, Centos, Amazon Linux, Rocky and AlmaLinux, these are:
```
sudo yum install gcc kernel-devel make kernel-devel-$(uname -r)
```

Once these packages have been installed, you will just need to run <b>make</b> in the source folder:

```
$ cd ~/invary-test-probe/src/
$ make
make W=1 -C /lib/modules/`uname -r`/build M=$PWD
make[1]: Entering directory '/usr/src/linux-headers-6.2.0-26-generic'
  CC [M]  /home/tester/invary-test-probe/src/invary-test-probe.o
  MODPOST /home/tester/invary-test-probe/src/Module.symvers
  CC [M]  /home/tester/invary-test-probe/src/invary-test-probe.mod.o
  LD [M]  /home/tester/invary-test-probe/src/invary-test-probe.ko
  BTF [M] /home/tester/invary-test-probe/src/invary-test-probe.ko
make[1]: Leaving directory '/usr/src/linux-headers-6.2.0-26-generic'
```

## Installing the Module

Now that you have the module, from the archive file or a local build, to install just use the <b>insmod</b> command as root:

```
sudo insmod invary-test-probe.ko
```
If you did build the module locally, there is a short-cut:
```
make load
```


## Issues with Secure Boot

If you run into an error such as this when attempting to load the module, your system requires modules to be signed to be loaded:

```
$ sudo insmod invary-test-probe.ko
insmod: ERROR: could not insert module invary-test-probe.ko: Key was rejected by service
```

The details of signing a kernel module are beyond the scope of this document and can vary depending on the Linux distribution.  Please consult the Linux kernel documentation (https://www.kernel.org/doc/html/v4.15/admin-guide/module-signing.html) or information provided by your Linux distribution (e.g. - https://ubuntu.com/blog/how-to-sign-things-for-secure-boot).


## Testing the Module

To confirm that the module did load correctly, run the following commands:
```
$ lsmod | grep invary_test_probe
invary_test_probe           16384  0

$ sudo cat /proc/kallsyms | grep invary_test_probe
ffffffffc23d0060 r __crc_invary_test_probe	[invary_test_probe]
ffffffffc23d0024 r _note_10	[invary_test_probe]
ffffffffc23d003c r _note_9	[invary_test_probe]
ffffffffc23d0064 r __kstrtab_invary_test_probe	[invary_test_probe]
ffffffffc23d0071 r __kstrtabns_invary_test_probe	[invary_test_probe]
ffffffffc23d0054 r __ksymtab_invary_test_probe	[invary_test_probe]
ffffffffc23d1018 d __UNIQUE_ID___addressable_cleanup_module195	[invary_test_probe]
ffffffffc23d1040 d __this_module	[invary_test_probe]
ffffffffc23cf010 t invary_test_probe_init	[invary_test_probe]
ffffffffc23cf040 t cleanup_module	[invary_test_probe]
ffffffffc23d1010 D invary_test_probe	[invary_test_probe]
ffffffffc23cf010 t init_module	[invary_test_probe]
ffffffffc23cf040 t invary_test_probe_exit	[invary_test_probe]
ffffffffc23cf000 t __pfx_init_module	[invary_test_probe]
ffffffffc23cf030 t __pfx_cleanup_module	[invary_test_probe]
```
<b>Note:</b> The module name is changed from <b>invary-test-probe</b> to <b>invary_test_probe</b> by the Linux kernel.

If the Invary Sensor is running, the results of a failed appraisal can be found in the Invary console (https://console.invary.com).  If you do not have an account, you can sign up at https://invary.com/services or use Invary RISe at https://invary.com/rise.


## Removing the Module

The module can easily be removed with the <b>rmmod</b> command as root:
```
sudo rmmod invary_test_probe
```
If the module was built locally, there is a short-cut:
```
make unload
```
