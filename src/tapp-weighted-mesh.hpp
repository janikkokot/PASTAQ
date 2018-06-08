#ifndef TAPP_GRID_WEIGHTEDMESH_HPP
#define TAPP_GRID_WEIGHTEDMESH_HPP

#include <vector>

#include "tapp-grid.hpp"
#include "tapp-mesh.hpp"

// This class extends the base Mesh class with addition m_weights, and m_counts
// data fields and the functions necessary for its manipulation.
class WeightedMesh : public Mesh {
   protected:
    std::vector<double> m_weights;
    std::vector<unsigned int> m_counts;

   public:
    WeightedMesh(Grid::Dimensions dimensions = {}, Grid::Bounds bounds = {},
                 Instrument::Config instrument_config = {Instrument::QUAD, 200,
                                                         0.001});

    // Getter methods for m_weights and m_counts.
    std::optional<double> weight_at(unsigned int i, unsigned int j);
    std::optional<double> counts_at(unsigned int i, unsigned int j);

    // Prints the mesh to std::out for debugging purposes.
    void print_all();

    // Perform gaussian splatting of the given point into the mesh, returns the
    // success or failure of the operation.
    bool splash(double mz, double rt, double value, double sigma_rt);
};

#endif /* TAPP_GRID_WEIGHTEDMESH_HPP */
