/* 
 *
 * ***** BEGIN GPL/BL DUAL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version. The Blender
 * Foundation also sells licenses for use in proprietary software under
 * the Blender License.  See http://www.blender.org/BL/ for information
 * about this.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * This is a new part of Blender.
 *
 * Contributor(s): Michel Selten
 *
 * ***** END GPL/BL DUAL LICENSE BLOCK *****
*/

#include <stdio.h>
#include <string.h>
#include <Python.h>

#include <DNA_ID.h>
#include <DNA_scriptlink_types.h>

int StringEqual (char * string1, char * string2)
{
	return (strcmp(string1, string2)==0);
}

char * GetIdName (ID *id)
{
	return ((id->name)+2);
}

PyObject * PythonReturnErrorObject (PyObject * type, char * error_msg)
{
	PyErr_SetString (type, error_msg);
	return (NULL);
}

PyObject * PythonIncRef (PyObject *object)
{
	Py_INCREF (object);
	return (object);
}

char * event_to_name(short event)
{
	switch (event)
	{
		case SCRIPT_FRAMECHANGED:
			return "FrameChanged";
		case SCRIPT_ONLOAD:
			return "OnLoad";
		case SCRIPT_REDRAW:
			return "Redraw";
		default:
			return "Unknown";
	}
}	

