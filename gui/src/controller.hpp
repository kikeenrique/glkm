/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gui
 * Copyright (C) Enrique García Álvarez 2008 <kike+glkm@eldemonionegro.com>
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

#ifndef _CONTROLLER_HPP
#define _CONTROLLER_HPP

class MainWindow;
class Hosts;
class NotebookHosts;
class IconViewHosts;
class NotebookPageHost;
class Host;
class HostSelectDialog;
class StatusBar;
class TreeViewHost;

class Controller{
  public:
	static Controller & instance();
	
	void action_host_selected();
	void action_host_connect();
	void action_host_synchronize();
	void action_processes_selected();

	void init_host_added();
	void set__pMainWindow(MainWindow * value);

  private:
	static Controller singleton;
	Controller();
	Controller(const Controller & source);
	Controller & operator=(const Controller & source);

	Hosts *		_pHosts;
	MainWindow *    _pMainWindow;
};

#endif // _CONTROLLER_HPP
