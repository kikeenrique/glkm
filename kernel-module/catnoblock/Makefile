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

# use "gcc" to compile source files.
CC 	= gcc
# the linker is also "gcc". It might be something else with other compilers.
LD 	= gcc
# Compiler flags go here.
CFLAGS 	= -g -Wall
# Linker flags go here. Currently there aren't any, but if we'll switch to
# code optimization, we might add "-s" here to strip debug info and symbols.
LDFLAGS =
# use this command to erase files.
RM = /bin/rm -f

# list of generated object files.
OBJS 	= cat_noblock.o
# program executable file name.
PROG 	= cat_noblock

all: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

cat_noblock.o: cat_noblock.c
	$(CC) $(CFLAGS) -c cat_noblock.c

# rule for cleaning re-compilable files.
clean:
	$(RM) $(OBJS) *.bak *~ core
