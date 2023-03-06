#include "MaterialResponse.hh"

#include "Excitation.hh"
#include "TrackStructure.hh"

#include "Scintillation.hh"
#include "Ionisation.hh"

MaterialResponse::MaterialResponse()
{
    scintillation_ = Scintillation();
    ionisation_ = Ionisation();
}

MaterialResponse::~MaterialResponse()
{}

void MaterialResponse::create_response(TrackStructure* track_structure)
{}

void MaterialResponse::process_energy_deposit(double visible_deposit, double visible_linear_transfer, std::vector<double> position)
{
    ElectronCloud electron_cloud_; PhotonRadiant photon_radiant_;

    std::tie(electron_cloud_, photon_radiant_) = Excitation::create_excitation(visible_deposit, visible_linear_transfer, position);

    ionisation_.add_cloud(electron_cloud_);
    scintillation_.add_radiant(photon_radiant_);
}