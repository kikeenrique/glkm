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

# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
ifneq ($(KERNELRELEASE),)
	obj-m := modulo.o

# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
endif

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(PROG)
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

