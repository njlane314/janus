#include "Excitation.hh"

#include "Recombination.hh"

Excitation::Excitation(double visible_deposit, double visible_linear_transfer) 
{
    double expected_ionisations = visible_deposit / loss_per_ionisation_;

    if (expected_ionisations > 10) {
        double resolution = fano_factor_ * std::sqrt(expected_ionisations);
        ionisations_ = random_.Gaus(expected_ionisations, resolution);
    } else {
        ionisations_ = random_.Poisson(expected_ionisations);
    }

    double excitation_energy = visible_deposit - ionisations_ * (ionisation_threshold_ + thermal_loss_);
    excitations_ = excitation_energy / excitation_threshold_;

    std::tie(thermal_electrons_, optical_photons_) = Recombination::run_recombination(ionisations_, excitations_, visible_linear_transfer);
}

Excitation::~Excitation() 
{}
