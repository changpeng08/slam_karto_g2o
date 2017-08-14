/*********************************************************************
*
*  Copyright (c) 2017, Stocked Robotics Inc. 
*  All rights reserved.
*
*********************************************************************/

/* Authors: Saurav Agarwal */


#ifndef KARTO_G2OSolver_H
#define KARTO_G2OSolver_H

#include <open_karto/Mapper.h>
#include "g2o/core/sparse_optimizer.h"

typedef std::vector<karto::Matrix3> CovarianceVector;

/**
 * @brief Wrapper for G2O to interface with Open Karto
 */
class G2OSolver : public karto::ScanSolver
{
  public:

    G2OSolver();
    
    virtual ~G2OSolver();

  public:
    
    /**
     * @brief Clear the vector of corrections
     * @details Empty out previously computed corrections
     */
    virtual void Clear();
    
    /**
     * @brief Solve the SLAM back-end
     * @details Calls G2O to solve the SLAM back-end
     */
    virtual void Compute();
    
    /**
     * @brief Get the vector of corrections
     * @details Get the vector of corrections
     * @return Vector with corrected poses
     */
    virtual const karto::ScanSolver::IdPoseVector& GetCorrections() const;

    /**
     * @brief Add a node to pose-graph
     * @details Add a node which is a robot pose to the pose-graph
     * 
     * @param pVertex the node to be added in
     */
    virtual void AddNode(karto::Vertex<karto::LocalizedRangeScan>* pVertex);
    
    /**
     * @brief Add an edge constraint to pose-graph
     * @details Adds a relative pose measurement constraint between two poses in the graph
     * 
     * @param pEdge [description]
     */
    virtual void AddConstraint(karto::Edge<karto::LocalizedRangeScan>* pEdge);

    /**
     * @brief Add a heading constraint to a graph node.
     * @details When heading estimates are available add a heading constraint to the node, this can improve SLAM accuracy.
     * 
     * @param headingEst mean of the heading estimate
     * @param headingEstVar variance of the heading estimate
     */
    virtual void AddHeadingConstraint(karto::LocalizedRangeScan* scanPose, const double& headingEst, const double& headingEstVar);

    /**
     * @brief Get the pose-graph 
     * @details Get the underlying graph from g2o, return the graph of constraints
     * 
     * @param g the graph
     */
    void getGraph(std::vector<Eigen::Vector2d> &nodes, std::vector<std::pair<Eigen::Vector2d, Eigen::Vector2d> > &edges);

  private:
    
    karto::ScanSolver::IdPoseVector corrections_;

    g2o::SparseOptimizer optimizer_;

    int latestNodeID_; // ID of the latest added node, this is used internally in AddHeadingConstraint

};

#endif // KARTO_G2OSolver_H

