/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Enrique García Álvarez 2007 <kike@eldemonionegro.com>
 * 
 * main.cc is free software.
 * 
 * You may redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 * 
 * main.cc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with main.cc.  If not, write to:
 * 	The Free Software Foundation, Inc.,
 * 	51 Franklin Street, Fifth Floor
 * 	Boston, MA  02110-1301, USA.
 */

#include <gtkmm/main.h>
#include "glkm_mainwindow.h"

#include "config.h"

#ifdef ENABLE_NLS
#include <libintl.h>
#endif
 
int 
main (int argc, 
	  	  char *argv[])
{
#ifdef ENABLE_NLS
//      bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
    //  bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
        //domain(GETTEXT_PACKAGE);
#endif

	Gtk::Main kit(argc, argv);

	GlkmMainWindow main_window;

	  //Shows the window and returns when it is closed.
		kit.run(main_window);

	return 0;
}
