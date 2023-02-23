#include "Excitation.hh"

Excitation::Excitation(double energy_deposit, double stopping_power) 
{
    double expected_ionisations = energy_deposit / loss_per_ionisation_;

    if (expected_ionisations > 10)
    {
        double resolution = fano_factor_ * std::sqrt(expected_ionisations);
        ionisations_ = random_.Gaus(expected_ionisations, resolution);
    } else {
        ionisations_ = random_.Poisson(expected_ionisations);
    }

    double excitation_energy = energy_deposit - ionisations_ * (ionisation_threshold_ + thermal_loss_);
    excitations_ = excitation_energy / excitation_threshold_;
}

Excitation::~Excitation() 
{}

