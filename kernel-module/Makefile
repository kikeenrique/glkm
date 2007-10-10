###########################################################################
#
# Makefile
# 
#	Project:
#	Desarrollo de herramientas de monitorización interna para Linux
#
###########################################################################
#
# Autor:
#	Enrique Garcia Alvarez (kikeenrique@users.sourceforge.net)
# License:
# 	GNU General Public License (http://www.gnu.org/copyleft/gpl.html)
#
# More documentacion at:
# http://tldp.org/LDP/lkmpg/2.6/html/lkmpg.html
#
###########################################################################


# If you are not actually running the kernel that you are building for,
# you can supply a KERNELDIR= option on the command line, set the KERNELDIR
# environment variable, or rewrite the line that sets KERNELDIR in the 
# makefile.

SHELL = /bin/sh
INSTALL = /usr/bin/install
mkdir_p = mkdir -p
EXTRA_CFLAGS = -DPROCMON_VERSION=\"$(VERSION)\"

# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
ifneq ($(KERNELRELEASE),)
#	obj-m := procmondev.o modulo.o
	obj-m := procmondev.o
	procmon-objs := 
else
	KERNELSRC ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
endif

VERSION = 0.2.0
ENABLE_PROCMON_MODULE=y

PROCMONDMODULEDIR = $(KERNELSRC)/drivers/misc/procmondev
PROCMONDMODULE := procmondev.ko

all: all-$(ENABLE_PROCMON_MODULE)
install: install-$(ENABLE_PROCMON_MODULE)
uninstall: uninstall-$(ENABLE_PROCMON_MODULE)

all-n:
install-n:
uninstall-n:

all-y: all-spec

install-y: all
	$(mkdir_p) $(DESTDIR)$(PROCMONDMODULEDIR)
	$(INSTALL) -m 644 $(PROCMONDMODULE) $(DESTDIR)$(PROCMONDMODULEDIR)/$(PROCMONDMODULE)
	-/sbin/depmod -a

uninstall-y:
	rm -f $(DESTDIR)$(PROCMONDMODULEDIR)/$(PROCMONDMODULE)
	-/sbin/depmod -a

all-spec:
	$(MAKE) -C $(KERNELSRC) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELSRC) M=$(PWD) clean
	rm -f $(PROCMONDMODULE) *.o .*.cmd *.mod.c *.ko *.s */*.o

distclean: clean
	rm -rf .tmp_versions

maintainer-clean: distclean
