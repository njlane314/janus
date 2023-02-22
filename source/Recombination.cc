
Recombination::Recombination(int ionisations, int excitations, double stopping_power)
{
    double recombination_factor = get_recombination_factor(stopping_power); 

    thermal_electrons_ = random_.Gaus(ionisations * recombination_factor, ionisations * recombination_factor * (1 - recombination_factor));
    optical_photons_ = excitations + (ionisations - thermal_electrons_);
}

Recombination::~Recombination()
{}
