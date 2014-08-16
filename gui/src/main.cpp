/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cpp
 * Copyright (C) Enrique García Álvarez 2007 <kike+glkm@eldemonionegro.com>
 *
 * gui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>

#include <gtkmm/main.h>
#include <glibmm/fileutils.h>

#include "config.h"
#ifdef ENABLE_NLS
#include <libintl.h>
#endif


#include "main-window.hpp"

#include "debug.hpp"

#ifdef DEBUG
TextViewDebug*  pDebug;
#endif // DEBUG

int main (int   argc, char  *argv[])
{

#ifdef ENABLE_NLS
    /*
        TODO
        bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
        bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
        domain(GETTEXT_PACKAGE);
        */
#endif

    Gtk::Main kit(argc, argv);

    RefPtrBuilder _refPtrBuilder;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
    try {
        _refPtrBuilder = Gtk::Builder::create_from_file(GLADE_FILE);
    }
    catch (const Glib::FileError& exception) {
        std::cerr << "FileError: " << exception.what() << std::endl;
        throw;
    }
    catch (const Gtk::BuilderError& exception) {
        std::cerr << "BuilderError: " << exception.what() << std::endl;
        throw;
    }
#else
    std::auto_ptr<Glib::Error> error;
    _refPtrBuilder = Gtk::Builder::create_from_file(GLADE_FILE, "", "", error);
    if (error.get()) {
        std::cerr << error->what() << std::endl;
        return 1;
    }
#endif //GLIBMM_EXCEPTIONS_ENABLED

    MainWindow* main_window;

    _refPtrBuilder->get_widget_derived("main_window", main_window);


    kit.run(*main_window);

    //Bye bye!!
    return 0;
}
