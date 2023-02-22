
TrackStructure::TrackStructure() 
{}

TrackStructure::~TrackStructure() 
{}

void TrackStructure::process_step(double energy_deposit, double linear_energy_transfer)
{
    Excitation excitation_cluster(energy_deposit, linear_energy_transfer);
    Recombination after_recombination(excitation_cluster.get_ionisations(), excitation_cluster.get_excitations(), linear_energy_transfer);
    Relaxation relaxation_generator();

    std::vector<OpticalPhoton> scintillation;
    for (int i = 0; i < after_recombination.get_optical_photons(); i++) {
        scintillation.push_back(relaxation_generator.create_photon());
    }
}





/*bool TrackStructure::is_ionising(int particle_charge, double particle_energy) const
{
    if (particle_charge != 0 && particle_energy > 0) {
        return true;
    } else {
        return false;
    }
}*/


