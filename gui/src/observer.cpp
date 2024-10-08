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

#include "observer.hpp"

Observer::~Observer() {
}

Subject::~Subject() {
}

void Subject::attach(Observer & observer) {
//	_observers.insert(_observers.end(), observer);
	_observers.insert(&observer);
}

void Subject::detach(Observer & observer) {
//	_observers.remove(observer); 
	_observers.erase(&observer);
}

void Subject::notify() {
	std::set<Observer *>::iterator it;

	for ( it=_observers.begin(); it!=_observers.end(); it++) {
		(*it)->update(this);
	} 
}

void Subject::notify(Argument * arg) {
	std::set<Observer *>::iterator it;

	for ( it=_observers.begin(); it!=_observers.end(); it++) {
		(*it)->update(this, arg);
	} 
}

Subject::Subject() {
}
