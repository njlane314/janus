#include "MaterialResponse.hh"

#include "Excitation.hh"
#include "Recombination.hh"

#include "Scintillation.hh"
#include "Ionisation.hh"

MaterialResponse::MaterialResponse()
{
    scintillation_ = Scintillation();
    ionisation_ = Ionisation();
}

MaterialResponse::~MaterialResponse()
{}

Ionisation, Scintillation MaterialResponse::create_response(TrackStructure* aTrack)
{}

void MaterialResponse::process_energy_deposit(double visible_deposit, double visible_linear_transfer, std::vector<double> position)
{
    Excitation excitation_cluster(visible_deposit, visible_linear_transfer);
    Recombination after_recombination(excitation_cluster.get_ionisations(), excitation_cluster.get_excitations(), visible_linear_transfer);

    scintillation_.add_cluster(after_recombination.get_optical_photons(), position);
    ionisation_.add_cluster(after_recombination.get_thermal_electrons(), position);
}