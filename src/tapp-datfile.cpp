#include "tapp-datfile.hpp"
#include <iostream>
#include <string>

bool DatFile::load(std::istream &stream, std::vector<double> &destination,
                   Grid::Parameters &parameters) {
    if (stream.good()) {
        // Reading all data from the stream into m_data.
        // m_data.resize(dimensions.n * dimensions.m);
        // m_dimensions = dimensions;
        // m_bounds = bounds;
        // m_instrument_type = instrument_type;
        // m_smoothing_params = smoothing_params;
        // if (stream.read(reinterpret_cast<char *>(&m_data[0]),
        // m_data.size() * sizeof(double))) {
        // return true;
        //}
    }
    return false;
}

bool DatFile::write(std::ostream &stream, const std::vector<double> &source,
                    const Grid::Parameters &parameters) {
    // if (stream.good()) {
    // stream.write(reinterpret_cast<char *>(&source[0]),
    // sizeof(double) * m_data.size());
    // return stream.good();
    //}
    return false;
}

struct FileFooter {
    std::string file_type = "TAPP";
    char footer_length;
};

std::optional<Grid::Parameters> DatFile::load_parameters(std::istream &stream) {
    Grid::Parameters parameters = {};
    if (stream.good()) {
        std::cout << "GOOD STREAM" << std::endl;
        stream.seekg(0, stream.beg);
        auto stream_beg = stream.tellg();

        // Get to the end of the file to read the file footer.
        stream.seekg(-1, stream.end);
        // Read the length of the footer.
        char footer_length = 0;
        footer_length = stream.peek();
        return parameters;
    }
    return std::nullopt;
}
