#include "Relaxation.hh"
#include "OpticalPhoton.hh"

Relaxation::Relaxation(double t_global, double singlet_to_triplet, double singlet_lifetime, double triplet_lifetime)
: t_(t_global), singlet_lifetime_(singlet_lifetime), triplet_lifetime_(triplet_lifetime)
{
	singlet_abundance_ = singlet_to_triplet / (1 + singlet_to_triplet);
	triplet_abundance_ = 1 - singlet_abundance_;
}

Relaxation::~Relaxation()
{}

OpticalPhoton Relaxation::create_photon()
{
	OpticalPhoton aPhoton;

	aPhoton.set_time(sample_emission());
	//aPhoton.set_wavelength(sample_wavelength());

	return aPhoton;
}

void Relaxation::sample_emission()
{
	std::random_device rd;
	generator_ = std::mt19937(rd());
	emission_distribution_ = std::uniform_real_distribution<double> dis(0, 1);

	double random_number = dist(gen);

	double t_initial = 0.;
	double t_final = 1000.;

	double t_step = 1.;

	double t = t_initial;

	double probability = 0.;
	while (probability < random_number && t < t_final)
	{
		probability += emission_probability(t) * (t_final - t_initial);
		t += t_step;
	}

	return t_ += t;
}

double Relaxation::emission_probability(double t)
{
    return singlet_abundance_ * std::exp(-t / singlet_lifetime_) + triplet_abundance_ * std::exp(-t / triplet_lifetime_);
}