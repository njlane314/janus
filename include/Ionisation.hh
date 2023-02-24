#include <vector>
#include <iostream>

#include "ThermalElectron.hh"

struct ElectronCluster {
    std::vector<Electron> electrons_;
    std::vector<double> position_;
};

class Ionisation {

public:
    Ionisation() : ionisation_() {};

    void add_cluster(int cluster_size, const std::vector<double>& position) {
        ElectronCluster current_cluster_;

        current_cluster_.position_ = position;
        for (int i = 0; i < cluster_size; i++) {
            add_electron();
        }

        ionisation_.push_back(current_cluster_);
    }

    void add_electron(Electron anElectron) { current_cluster_.electrons_.push_back(anElectron); };
    
    const std::vector<ElectronCluster> get_ionisation() const { return ionisation_; }

    void print_ionisation() const {
        std::cout << "ionisation clusters:" << std::endl;
        for (const auto& cluster : ionisation_) {
            std::cout << "  Position: (";
            for (const auto& p : cluster.position_) {
                std::cout << p << ", ";
            }
            std::cout << "), electrons: " << cluster.electrons_.size() << std::endl;
        }
    }

    std::vector<double> get_cluster_positions() const {
        std::vector<double> cluster_positions;
        for (const auto& cluster : ionisation_) {
            for (const auto& pos : cluster.position_) {
                cluster_positions.push_back(pos);
            }
        }
        return cluster_positions;
    }

private:
    std::vector<ElectronCluster> ionisation_;
    ElectronCluster current_cluster_;
};
