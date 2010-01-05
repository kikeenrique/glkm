/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Enrique García Álvarez 2008 <kike+glkm@eldemonionegro.com>
 * 
 * main.cc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <unistd.h>
#include "config.h"

int main(int argc, char* argv[])
{
	pid_t pid;
	int ret;
	char **cmd;
//	char *cmd[] = { "ls", "-l", (char *)0 };

/*
	 Fork.
		ME -> die
		CHILD -> Launch daemon.
*/

	pid=fork();
	if (pid == -1) {
		//error
	}
	else if (pid == 0) {
		//child
		ret = execvp (PACKAGE, cmd);
	} else {
		//parent
	}
	
	return ret;
}
