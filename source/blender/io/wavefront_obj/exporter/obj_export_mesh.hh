/*
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
 * The Original Code is Copyright (C) 2020 Blender Foundation.
 * All rights reserved.
 */

/** \file
 * \ingroup obj
 */

#pragma once

#include <optional>

#include "BLI_float3.hh"
#include "BLI_utility_mixins.hh"
#include "BLI_vector.hh"

#include "bmesh.h"
#include "bmesh_tools.h"

#include "DNA_material_types.h"
#include "DNA_mesh_types.h"
#include "DNA_meshdata_types.h"

#include "IO_wavefront_obj.h"

namespace blender::io::obj {
/* Denote absence for usually non-negative numbers. */
const int NOT_FOUND = -1;
/* Any negative number other than `NOT_FOUND` to initialise usually non-negative numbers. */
const int NEGATIVE_INIT = -10;

/**
 * #std::unique_ptr deleter for BMesh.
 */
struct CustomBMeshDeleter {
  void operator()(BMesh *bmesh)
  {
    if (bmesh) {
      BM_mesh_free(bmesh);
    }
  }
};

using unique_bmesh_ptr = std::unique_ptr<BMesh, CustomBMeshDeleter>;

class OBJMesh : NonMovable, NonCopyable {
 private:
  Object *export_object_eval_;
  Mesh *export_mesh_eval_;
  /**
   * For curves which are converted to mesh, and triangulated meshes, a new mesh is allocated.
   */
  bool mesh_eval_needs_free_ = false;
  /**
   * Final transform of an object obtained from export settings (up_axis, forward_axis) and the
   * object's world transform matrix.
   */
  float world_and_axes_transform_[4][4];

  /**
   * Total UV vertices in a mesh's texture map.
   */
  int tot_uv_vertices_ = 0;
  /**
   * Per-polygon-per-vertex UV vertex indices.
   */
  Vector<Vector<int>> uv_indices_;
  /**
   * Total smooth groups in an object.
   */
  int tot_smooth_groups_ = NEGATIVE_INIT;
  /**
   * Polygon aligned array of their smooth groups.
   */
  int *poly_smooth_groups_ = nullptr;

 public:
  OBJMesh(Depsgraph *depsgraph, const OBJExportParams &export_params, Object *mesh_object);
  ~OBJMesh();

  int tot_vertices() const;
  int tot_polygons() const;
  int tot_uv_vertices() const;
  Span<int> uv_indices(const int poly_index) const;
  int tot_edges() const;

  int16_t tot_materials() const;
  const Material *get_object_material(const int16_t mat_nr) const;
  int16_t ith_poly_matnr(const int poly_index) const;

  void ensure_mesh_normals() const;
  void ensure_mesh_edges() const;

  void calc_smooth_groups(const bool use_bitflags);
  int tot_smooth_groups() const;
  int ith_smooth_group(const int poly_index) const;
  bool is_ith_poly_smooth(const int poly_index) const;

  const char *get_object_name() const;
  const char *get_object_mesh_name() const;
  const char *get_object_material_name(const int16_t mat_nr) const;

  float3 calc_vertex_coords(const int vert_index, const float scaling_factor) const;
  void calc_poly_vertex_indices(const int poly_index, Vector<int> &r_poly_vertex_indices) const;
  void store_uv_coords_and_indices(Vector<std::array<float, 2>> &r_uv_coords);
  float3 calc_poly_normal(const int poly_index) const;
  int calc_poly_normal_indices(const int poly_index,
                               const int object_tot_prev_normals,
                               Vector<int> &r_poly_normal_indices) const;
  void calc_loop_normals(const int poly_index, Vector<float3> &r_loop_normals) const;
  int16_t get_poly_deform_group_index(const int poly_index) const;
  const char *get_poly_deform_group_name(const int16_t def_group_index) const;

  std::optional<std::array<int, 2>> calc_loose_edge_vert_indices(const int edge_index) const;

 private:
  void free_mesh_if_needed();
  std::pair<Mesh *, bool> triangulate_mesh_eval();
  void set_world_axes_transform(const eTransformAxisForward forward, const eTransformAxisUp up);
};
}  // namespace blender::io::obj