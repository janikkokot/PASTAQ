#include <iomanip>
#include <iostream>

#include "centroid.hpp"
#include "doctest.h"

TEST_CASE("Find local maxima") {
    Grid::Parameters parameters = {
        {}, {0, 100, 0, 100}, {50.0, 5.0, 5.0}, Instrument::QUAD, 0x00};
    Grid::calculate_dimensions(parameters);
    std::vector<double> data(parameters.dimensions.n * parameters.dimensions.m);
    // Simulating one isotope with three adjacent peaks and an artifact peak.
    // Peak 1
    CHECK(Grid::splat({20, 40, 3}, parameters, data));
    CHECK(Grid::splat({20, 50, 5}, parameters, data));
    CHECK(Grid::splat({20, 57, 5.5}, parameters, data));
    CHECK(Grid::splat({20, 60, 6}, parameters, data));
    CHECK(Grid::splat({20, 63, 5}, parameters, data));
    CHECK(Grid::splat({20, 65, 4}, parameters, data));
    // Peak 2
    CHECK(Grid::splat({50, 50, 4}, parameters, data));
    CHECK(Grid::splat({50, 57, 4.5}, parameters, data));
    CHECK(Grid::splat({50, 60, 6}, parameters, data));
    CHECK(Grid::splat({50, 63, 4}, parameters, data));
    CHECK(Grid::splat({50, 65, 3}, parameters, data));
    // Peak 3
    CHECK(Grid::splat({80, 57, 4.5}, parameters, data));
    CHECK(Grid::splat({80, 60, 5}, parameters, data));
    CHECK(Grid::splat({80, 63, 3}, parameters, data));
    CHECK(Grid::splat({80, 65, 2}, parameters, data));
    // Artifact peak
    CHECK(Grid::splat({10, 10, 4}, parameters, data));

    auto points = Centroid::find_local_maxima(parameters, data);
    CHECK(points.size() == 4);
}

TEST_CASE("Find peak points") {
    Grid::Parameters parameters = {
        {}, {0, 100, 0, 100}, {50.0, 5.0, 5.0}, Instrument::QUAD, 0x00};
    Grid::calculate_dimensions(parameters);
    std::vector<double> data(parameters.dimensions.n * parameters.dimensions.m);
    // Simulating one isotope with three adjacent peaks and an artifact peak.
    // Peak 1
    CHECK(Grid::splat({20, 40, 3}, parameters, data));
    CHECK(Grid::splat({20, 50, 5}, parameters, data));
    CHECK(Grid::splat({20, 57, 5.5}, parameters, data));
    CHECK(Grid::splat({20, 60, 6}, parameters, data));
    CHECK(Grid::splat({20, 63, 5}, parameters, data));
    CHECK(Grid::splat({20, 65, 4}, parameters, data));
    // Peak 2
    CHECK(Grid::splat({50, 50, 4}, parameters, data));
    CHECK(Grid::splat({50, 57, 4.5}, parameters, data));
    CHECK(Grid::splat({50, 60, 6}, parameters, data));
    CHECK(Grid::splat({50, 63, 4}, parameters, data));
    CHECK(Grid::splat({50, 65, 3}, parameters, data));
    // Peak 3
    CHECK(Grid::splat({80, 57, 4.5}, parameters, data));
    CHECK(Grid::splat({80, 60, 5}, parameters, data));
    CHECK(Grid::splat({80, 63, 3}, parameters, data));
    CHECK(Grid::splat({80, 65, 2}, parameters, data));
    // Artifact peak
    CHECK(Grid::splat({10, 10, 4}, parameters, data));

    auto local_max_points = Centroid::find_local_maxima(parameters, data);
    CHECK(local_max_points.size() == 4);

    std::vector<size_t> expected_size = {
        25,
        50,
        40,
        35,
    };

    for (size_t i = 0; i < local_max_points.size(); ++i) {
        auto local_max = local_max_points[i];
        auto peak_points =
            Centroid::find_peak_points(local_max, parameters, data);
        CHECK(expected_size[i] == peak_points.size());
    }
}

TEST_CASE("Find peak boundaries") {
    Grid::Parameters parameters = {
        {}, {0, 100, 0, 100}, {50.0, 5.0, 5.0}, Instrument::QUAD, 0x00};
    Grid::calculate_dimensions(parameters);
    std::vector<double> data(parameters.dimensions.n * parameters.dimensions.m);
    // Simulating one isotope with three adjacent peaks and an artifact peak.
    // Peak 1
    CHECK(Grid::splat({20, 40, 3}, parameters, data));
    CHECK(Grid::splat({20, 50, 5}, parameters, data));
    CHECK(Grid::splat({20, 57, 5.5}, parameters, data));
    CHECK(Grid::splat({20, 60, 6}, parameters, data));
    CHECK(Grid::splat({20, 63, 5}, parameters, data));
    CHECK(Grid::splat({20, 65, 4}, parameters, data));
    // Peak 2
    CHECK(Grid::splat({50, 50, 4}, parameters, data));
    CHECK(Grid::splat({50, 57, 4.5}, parameters, data));
    CHECK(Grid::splat({50, 60, 6}, parameters, data));
    CHECK(Grid::splat({50, 63, 4}, parameters, data));
    CHECK(Grid::splat({50, 65, 3}, parameters, data));
    // Peak 3
    CHECK(Grid::splat({80, 57, 4.5}, parameters, data));
    CHECK(Grid::splat({80, 60, 5}, parameters, data));
    CHECK(Grid::splat({80, 63, 3}, parameters, data));
    CHECK(Grid::splat({80, 65, 2}, parameters, data));
    // Artifact peak
    CHECK(Grid::splat({10, 10, 4}, parameters, data));

    auto local_max_points = Centroid::find_local_maxima(parameters, data);
    CHECK(local_max_points.size() == 4);

    std::vector<size_t> expected_size = {
        25,
        50,
        40,
        35,
    };

    // Only interested in the indices, ignoring the value for now, but we assume
    // it's correct.
    std::vector<std::vector<Centroid::Point>> expected_boundary = {
        {
            {0, 0, 0},
            {1, 0, 0},
            {2, 0, 0},
            {3, 0, 0},
            {4, 0, 0},
            {0, 1, 0},
            {4, 1, 0},
            {0, 2, 0},
            {4, 2, 0},
            {0, 3, 0},
            {4, 3, 0},
            {0, 4, 0},
            {1, 4, 0},
            {2, 4, 0},
            {3, 4, 0},
            {4, 4, 0},
        },
        {
            {2, 6, 0},  {3, 6, 0},  {4, 6, 0},  {5, 6, 0},  {6, 6, 0},
            {2, 7, 0},  {6, 7, 0},  {2, 8, 0},  {6, 8, 0},  {2, 9, 0},
            {6, 9, 0},  {2, 10, 0}, {6, 10, 0}, {2, 11, 0}, {6, 11, 0},
            {2, 12, 0}, {6, 12, 0}, {2, 13, 0}, {6, 13, 0}, {2, 14, 0},
            {6, 14, 0}, {2, 15, 0}, {3, 15, 0}, {4, 15, 0}, {5, 15, 0},
            {6, 15, 0},
        },
        {
            {8, 8, 0},   {9, 8, 0},   {10, 8, 0},  {11, 8, 0},  {12, 8, 0},
            {8, 9, 0},   {12, 9, 0},  {8, 10, 0},  {12, 10, 0}, {8, 11, 0},
            {12, 11, 0}, {8, 12, 0},  {12, 12, 0}, {8, 13, 0},  {12, 13, 0},
            {8, 14, 0},  {12, 14, 0}, {8, 15, 0},  {9, 15, 0},  {10, 15, 0},
            {11, 15, 0}, {12, 15, 0},
        },
        {
            {14, 9, 0},  {15, 9, 0},  {16, 9, 0},  {17, 9, 0},  {18, 9, 0},
            {14, 10, 0}, {18, 10, 0}, {14, 11, 0}, {18, 11, 0}, {14, 12, 0},
            {18, 12, 0}, {14, 13, 0}, {18, 13, 0}, {14, 14, 0}, {18, 14, 0},
            {14, 15, 0}, {15, 15, 0}, {16, 15, 0}, {17, 15, 0}, {18, 15, 0},
        }};
    for (size_t i = 0; i < local_max_points.size(); ++i) {
        auto local_max = local_max_points[i];
        auto peak_points =
            Centroid::find_peak_points(local_max, parameters, data);
        CHECK(expected_size[i] == peak_points.size());
        auto boundary = Centroid::find_boundary(peak_points);
        CHECK(boundary.size() == expected_boundary[i].size());
        for (size_t j = 0; j < boundary.size(); ++j) {
            CHECK(boundary[j].i == expected_boundary[i][j].i);
            CHECK(boundary[j].j == expected_boundary[i][j].j);
        }
    }
}

TEST_CASE("Find peak points (Recursive)") {
    Grid::Parameters parameters = {
        {}, {0, 100, 0, 100}, {50.0, 5.0, 5.0}, Instrument::QUAD, 0x00};
    Grid::calculate_dimensions(parameters);
    std::vector<double> data(parameters.dimensions.n * parameters.dimensions.m);
    // Simulating one isotope with three adjacent peaks and an artifact peak.
    // Peak 1
    CHECK(Grid::splat({20, 40, 3}, parameters, data));
    CHECK(Grid::splat({20, 50, 5}, parameters, data));
    CHECK(Grid::splat({20, 57, 5.5}, parameters, data));
    CHECK(Grid::splat({20, 60, 6}, parameters, data));
    CHECK(Grid::splat({20, 63, 5}, parameters, data));
    CHECK(Grid::splat({20, 65, 4}, parameters, data));
    // Peak 2
    CHECK(Grid::splat({50, 50, 4}, parameters, data));
    CHECK(Grid::splat({50, 57, 4.5}, parameters, data));
    CHECK(Grid::splat({50, 60, 6}, parameters, data));
    CHECK(Grid::splat({50, 63, 4}, parameters, data));
    CHECK(Grid::splat({50, 65, 3}, parameters, data));
    // Peak 3
    CHECK(Grid::splat({80, 57, 4.5}, parameters, data));
    CHECK(Grid::splat({80, 60, 5}, parameters, data));
    CHECK(Grid::splat({80, 63, 3}, parameters, data));
    CHECK(Grid::splat({80, 65, 2}, parameters, data));
    // Artifact peak
    CHECK(Grid::splat({10, 10, 4}, parameters, data));

    auto local_max_points = Centroid::find_local_maxima(parameters, data);
    CHECK(local_max_points.size() == 4);

    std::vector<size_t> expected_size = {
        25,
        50,
        40,
        35,
    };

    for (size_t i = 0; i < local_max_points.size(); ++i) {
        auto local_max = local_max_points[i];
        std::vector<Centroid::Point> peak_points;
        Centroid::explore_peak_slope(local_max.i, local_max.j, -1, parameters,
                                     data, peak_points);
        std::vector<Centroid::Point> boundary_points = Centroid::find_boundary(peak_points);
        CHECK(expected_size[i] == peak_points.size());
        std::cout << "INNER POINTS: " << std::endl;
        for (const auto &point : peak_points) {
            std::cout << "i: " << point.i << " j: " << point.j
                      << " height: " << point.height << std::endl;
        }
        std::cout << "BOUNDARY POINTS: " << std::endl;
        for (const auto &point : boundary_points) {
            std::cout << "i: " << point.i << " j: " << point.j
                      << " height: " << point.height << std::endl;
        }
    }
}
