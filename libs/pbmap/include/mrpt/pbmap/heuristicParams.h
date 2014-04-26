/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2014, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

/*  Plane-based Map (PbMap) library
 *  Construction of plane-based maps and localization in it from RGBD Images.
 *  Writen by Eduardo Fernandez-Moral. See docs for <a href="group__mrpt__pbmap__grp.html" >mrpt-pbmap</a>
 */

#ifndef __HEURISTICPARAMS_H
#define __HEURISTICPARAMS_H

#include <mrpt/utils/CConfigFile.h>
#include <mrpt/system/filesystem.h>
#include <mrpt/pbmap/link_pragmas.h>

namespace mrpt {
namespace pbmap {

	/** A class used to define the heuristic parameters and thresholds used to match sets of planes.
	 *  These parameters are loaded from a configuration file.
	 *
	 * \ingroup mrpt_pbmap_grp
	 */
  struct PBMAP_IMPEXP config_heuristics
  {
    void load_params(const std::string &config_file_name)
    {
      ASSERT_FILE_EXISTS_(config_file_name)
      mrpt::utils::CConfigFile config_file(config_file_name);

      // global
      path_prev_pbmaps = config_file.read_string("global","path_prev_pbmaps","",false);
  //  std::cout << path_prev_pbmaps << std::endl;
      use_structure = config_file.read_bool("global","use_structure",true);
      use_completeness = config_file.read_bool("global","use_completeness",true);
      min_planes_recognition = config_file.read_int("global","min_planes_recognition",4);
      graph_mode = config_file.read_int("global","graph_mode",0);

      // Unary constraints
      color_threshold = config_file.read_float("unary","color_threshold",0.09);
//      colorDev_threshold = config_file.read_float("unary","colorDev_threshold",0.005);
      area_threshold = config_file.read_float("unary","area_threshold",3.0);
      area_threshold_inv = 1/area_threshold;
      area_full_threshold = config_file.read_float("unary","area_full_threshold",1.6);
      area_full_threshold_inv = 1/area_full_threshold;
      area_half_threshold = config_file.read_float("unary","area_half_threshold",2.0);
      area_half_threshold_inv = 1/area_half_threshold;
      elongation_threshold = config_file.read_float("unary","elongation_threshold",2.9);
      elongation_threshold_inv = 1/elongation_threshold;

      // Binary constraints
      dist_threshold = config_file.read_float("binary","dist_threshold",2.0);
      dist_threshold_inv = 1/dist_threshold;
      angle_threshold = config_file.read_float("binary","angle_threshold",7.0);
      height_threshold = config_file.read_float("binary","height_threshold",0.2);
      height_threshold_parallel = config_file.read_float("binary","height_threshold_parallel",0.2);
      cos_angle_parallel = config_file.read_float("binary","cos_angle_parallel",0.985);

    };

    // [global]
    std::string path_prev_pbmaps;
    unsigned min_planes_recognition;    // Minimum number of planes to accept a match between two neighborhoods of planes
    bool use_structure;                  // Use inferred knowledge
    bool use_completeness;               // Use inferred knowledge

    // [unary]
    float color_threshold;
//    float colorDev_threshold;
    float area_threshold, area_threshold_inv;
    float area_full_threshold, area_full_threshold_inv;
    float area_half_threshold, area_half_threshold_inv;     // Constraint with "half confidence": one plana is fully observed
    float elongation_threshold, elongation_threshold_inv;         // Unary constraint:
    int   graph_mode;  // This var selects the condition to create edges in the graph, either proximity of planar patches or co-visibility in a single frame

    // [binary]
    float dist_threshold, dist_threshold_inv;  // Binary constraint: distence between the centers of two pair of planes
    float angle_threshold;              // Binary constraint: the angle between the normals of two pair of planes
    float height_threshold;             // Binary constraint: Height from one plane wrt a neighbor (in meters)
    float height_threshold_parallel;    // Binary constraint: Height from one plane wrt a neighbor (in meters) for complete marked planes
    float cos_angle_parallel;

  };

} } // End of namespaces

#endif
