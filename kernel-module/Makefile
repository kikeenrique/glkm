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
# More documentacion about linux kernel modules and linux makefiles at:
# http://tldp.org/LDP/lkmpg/2.6/html/lkmpg.html
# http://www.ravnborg.org/kbuild/makefiles.html
#
###########################################################################


PROCMON_VERSION = 0.2.0alpha
PROCMON_MODULE = procmon_dev
ENABLE_PROCMON_MODULE=y

SHELL = /bin/sh
INSTALL = /usr/bin/install
mkdir_p = mkdir -p
EXTRA_CFLAGS += -DPROCMON_VERSION=\"$(PROCMON_VERSION)\"
ifdef DEBUG
	EXTRA_CFLAGS += -DPROCMON_DEBUG
endif


# If you are not actually running the kernel that you are building for,
# you can supply a KERNELDIR= option on the command line, set the KERNELDIR
# environment variable, or rewrite the line that sets KERNELDIR in the 
# makefile.
# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
ifneq ($(KERNELRELEASE),)
#	obj-m := $(PROCMON_MODULE).o modulo.o
	obj-m := $(PROCMON_MODULE).o
	procmon-objs := 
else
	KERNELSRC ?= /lib/modules/$(shell uname -r)/build
	MODLIB ?= /lib/modules/$(shell uname -r)/
	PWD := $(shell pwd)
endif

PROCMON_INSTALL_DIR = $(MODLIB)kernel/misc/$(PROCMON_MODULE)

all:	   all-$(ENABLE_PROCMON_MODULE)

install:   install-$(ENABLE_PROCMON_MODULE)
uninstall: uninstall-$(ENABLE_PROCMON_MODULE)

all-n:
install-n:
uninstall-n:

all-y:	all-spec

install-y: all
	$(mkdir_p) $(PROCMON_INSTALL_DIR)
	$(INSTALL) -m 644 $(PROCMON_MODULE).ko $(PROCMON_INSTALL_DIR)/$(PROCMON_MODULE).ko
	-/sbin/depmod -a
uninstall-y:
	-rm -f $(PROCMON_INSTALL_DIR)/$(PROCMON_MODULE).ko
	-rm -rf $(PROCMON_INSTALL_DIR)
	-/sbin/depmod -a

all-spec:
	$(MAKE) -C $(KERNELSRC) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELSRC) M=$(PWD) clean
	-rm -f *.o .*.cmd *.mod.c *.ko *.s */*.o

distclean: clean
	-rm -rf .tmp_versions

maintainer-clean: distclean
cleanall: distclean
