/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2014, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */
#ifndef GRAPH_SLAM_SOLVERS_H
#define GRAPH_SLAM_SOLVERS_H

#include <mrpt/graphslam/types.h>
#include <mrpt/graphslam/levmarq.h>

namespace mrpt { namespace graphslam { namespace solvers {
	using mrpt::utils::TNodeID; 

	/** Batch GraphSLAM Levenberg-Marquardt solver: wrapper for mrpt::graphslam::GraphSlamEngine<>
	  */
	struct GS_SolverLevMarq
	{
		GS_SolverLevMarq()
		{
		}

		template <class GRAPH_T>
		void optimizeSingle(GRAPH_T &graph, const TNodeID curNodeID)
		{
			TResultInfoSpaLevMarq solver_results;
			std::set<TNodeID> nodes_to_optimize;
			nodes_to_optimize.insert(curNodeID);

			mrpt::utils::TParametersDouble extra_params;
			extra_params["verbose"]= params.verbose ? 1:0;
			extra_params["max_iterations"] = params.single_max_iters;

			try {
				mrpt::graphslam::optimize_graph_spa_levmarq(graph, solver_results, &nodes_to_optimize, extra_params);
				std::cout << "[optimizeSingle] Solved in " << solver_results.num_iters << " iters, final_total_sq_error=" << solver_results.final_total_sq_error << std::endl;
				//static int i=0; graph.saveToTextFile(mrpt::format("__graph%06i.txt",i++));
			} catch (std::exception &e)
			{
				// No observations yet, etc.
				std::cout << "[optimizeSingle] Skipped for: " << e.what() << std::endl;
			}
		}

		template <class GRAPH_T>
		void optimizeFull(GRAPH_T &graph)
		{
			TResultInfoSpaLevMarq solver_results;

			mrpt::utils::TParametersDouble extra_params;
			extra_params["verbose"]= params.verbose ? 1:0;
			extra_params["max_iterations"] = params.full_max_iters;

			try {
				mrpt::graphslam::optimize_graph_spa_levmarq(graph, solver_results, NULL /*optimize all keyframes*/, extra_params);
				std::cout << "[optimizeFull] Solved in " << solver_results.num_iters << " iters, final_total_sq_error=" << solver_results.final_total_sq_error << std::endl;
				//static int i=0; graph.saveToTextFile(mrpt::format("__graph%06i.txt",i++));
			} catch (std::exception &e)
			{
				// No observations yet, etc.
				std::cout << "[optimizeFull] Skipped for: " << e.what() << std::endl;
			}
		}

		struct TParams
		{
			bool verbose; //!< Verbose output (default:false)
			unsigned int single_max_iters; //!< Max iterations for single node optimizations (default: 5)
			unsigned int full_max_iters;  //!< Max iterations for full map optimization (default: 100)

			TParams() : verbose(false),single_max_iters(5),full_max_iters(100) { }
		};
		
		TParams params;
	};


}}} // end namespaces


#endif