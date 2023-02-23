#include "Scintillation.hh"

#include <vector>
#include <iostream>

#include "OpticalPhoton.hh"

struct PhotonCluster {
    std::vector<OpticalPhoton> photons_;
    std::vector<double> position_;
};

class Scintillation {

public:
    Scintillation() : scintillation_() {};

    void add_cluster(int cluster_size, const std::vector<doubble>& position)
    {
        Relaxation relaxation_generator();
        PhotonCluster current_cluster_;

        current_cluster_.position_ = position;
        for (int i = 0; i < cluster_size; i++) {
            add_photon(relaxation_generator.create_photon());
        }

        scintillation_.push_back(current_cluster_);
    }

    void add_photon(OpticalPhoton aPhoton) { current_cluster_.photons_.push_back(aPhoton); };
    
    const std::vector<PhotonCluster> get_scintillation() const { return scintillation_; }

    void print_scintillation() const {
        std::cout << "Scintillation clusters:" << std::endl;
        for (const auto& cluster : scintillation_) {
            std::cout << "  Position: (";
            for (const auto& p : cluster.position_) {
                std::cout << p << ", ";
            }
            std::cout << "), photons: " << cluster.photons_.size() << std::endl;
        }
    }

    std::vector<double> get_emission_times() const {
        std::vector<double> emission_times;
        for (const auto& cluster : scintillation_) {
            for (const auto& photon : cluster.photons_) {
                emission_times.push_back(photon.get_time());
            }
        }
        return emission_times;
    }

    std::vector<double> get_cluster_positions() const {
        std::vector<double> cluster_positions;
        for (const auto& cluster : scintillation_) {
            for (const auto& pos : cluster.position_) {
                cluster_positions.push_back(pos);
            }
        }
        return cluster_positions;
    }


private:
    std::vector<PhotonCluster> scintillation_;
    PhotonCluster current_cluster_;
}