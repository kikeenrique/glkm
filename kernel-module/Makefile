#
# Makefile
# 
#	Project:
#	Desarrollo de herramientas de monitorización interna para Linux

#
# Autor:
#	Enrique Garcia Alvarez (kikeenrique@users.sourceforge.net)
# License:
# 	GNU General Public License (http://www.gnu.org/copyleft/gpl.html)
#
# More documentacion at:
# http://tldp.org/LDP/lkmpg/2.6/html/lkmpg.html


obj-m += modulo.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


