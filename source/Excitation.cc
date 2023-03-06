#include "Excitation.hh"

#include "Recombination.hh"

#include "Ejection.hh"
#include "Relaxation.hh"

#include "Ionisation.hh"
#include "Scintillation.hh"

Excitation::Excitation(std::string material)
: material_(material) {
    material_params_ = initialise_material_parameters(material_);
}

Excitation::~Excitation()
{}

std::pair<ElectronCloud, PhotonRadiant> Excitation::create_excitation(double visible_deposit, double visible_linear_transfer, vector position)
{
    double expected_ionisations = visible_deposit / loss_per_ionisation_;

    if (expected_ionisations > 10) {
        double resolution = fano_factor_ * std::sqrt(expected_ionisations);
        num_ionisations_ = random_.Gaus(expected_ionisations, resolution);
    } else {
        num_ionisations_ = random_.Poisson(expected_ionisations);
    }

    double excitation_energy = visible_deposit - num_ionisations_ * (ionisation_threshold_ + thermal_loss_);
    num_excitations_ = excitation_energy / excitation_threshold_;

    std::tie(num_thermal_electrons_, num_optical_photons_) = Recombination::run_recombination(num_ionisations_, num_excitations_, visible_linear_transfer);

    return std::make_pair(create_electron_cloud(num_thermal_electrons_, position), create_photon_radiant(num_optical_photons_, position));
}

PhotonRadiant Excitation::create_photon_radiant(int radiant_size, const std::vector<doubble>& position)
{
    Relaxation relaxation_generator(material_params_);
    PhotonRadiant photon_radiant_;

    photon_radiant_.position_ = position;
    for (int i = 0; i < radiant_size; i++) {
        photon_radiant_.photons_.push_back(relaxation_generator.create_photon());
    }

    return photon_radiant_;
}

ElectronCloud Excitation::create_electron_cloud(int cloud_size, const std::vector<doubble>& position)
{
    Ejection ejection_generator();
    ElectronCloud electron_cloud_;

    electron_cloud_.position_ = position;
    for (int i = 0; i < cloud_size; i++) {
        electron_cloud_.electrons_.push_back(ejection_generator.create_electron());
    }

    return electron_cloud_;
}