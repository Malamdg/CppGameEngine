class ParticleForceGenerator :
	public:
		struct ParticleForceRegistration
		{
			Particle *particle;
			ParticleForceGenerator* Fg;
		};