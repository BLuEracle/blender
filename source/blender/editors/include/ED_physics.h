/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2007 by Janne Karhu.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file ED_physics.h
 *  \ingroup editors
 */

#ifndef __ED_PHYSICS_H__
#define __ED_PHYSICS_H__

struct bContext;
struct ReportList;
struct wmKeyConfig;

struct Scene;
struct Object;

/* particle_edit.c */
bool PE_poll(struct bContext *C);
bool PE_hair_poll(struct bContext *C);
bool PE_poll_view3d(struct bContext *C);

/* rigidbody_object.c */
bool ED_rigidbody_object_add(struct Main *bmain, struct Scene *scene, struct Object *ob, int type, struct ReportList *reports);
void ED_rigidbody_object_remove(struct Main *bmain, struct Scene *scene, struct Object *ob);

/* rigidbody_constraint.c */
bool ED_rigidbody_constraint_add(struct Main *bmain, struct Scene *scene, struct Object *ob, int type, struct ReportList *reports);
void ED_rigidbody_constraint_remove(struct Main *bmain, struct Scene *scene, struct Object *ob);

/* operators */
void ED_operatortypes_physics(void);
void ED_keymap_physics(struct wmKeyConfig *keyconf);

#endif /* __ED_PHYSICS_H__ */
