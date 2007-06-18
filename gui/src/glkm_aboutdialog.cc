/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * glkm_aboutdialog.cc
 * Copyright (C) Enrique García Álvarez 2007 <kike@eldemonionegro.com>
 * 
 * glkm_aboutdialog.cc is free software.
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

#include "glkm_aboutdialog.h"


GlkmAboutDialog::GlkmAboutDialog(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade)
: Gtk::Dialog(cobject),
  m_refGlademmXml(refGlade),
  m_pButton(0)
{
  //Get the Glade-instantiated Button, and connect a signal handler:
//  m_refGlademmXml->get_widget("quit_button", m_pButton);
  if(m_pButton)
  {
    m_pButton->signal_clicked().connect( sigc::mem_fun(*this, &GlkmAboutDialog::on_button_quit) ); 
  }
	//gnome_url_show_on_screen();
	//	m_refGlademmXml->get_widget("glkm_aboutdialog", pGlkm_AboutDialog);
//	if(pGlkm_AboutDialog){
//		std::cout << "hola" << std::endl;
//		pGlkm_AboutDialog->show();
//	pMenuItem->signal_activate().connect( sigc::mem_fun(&GlkmMainWindow::on_menu_item_activated) );
//	}

}

GlkmAboutDialog::~GlkmAboutDialog()
{
}

void GlkmAboutDialog::on_button_clicked()
{
}

void GlkmAboutDialog::on_button_quit()
{
	hide(); //hide() will cause main::run() to end.
}

