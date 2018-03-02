
#include <PrimaryPat.hh>

#include <G4SystemOfUnits.hh>

#include <Randomize.hh>
#include <G4Neutron.hh>
#include <G4RunManager.hh>


PrimaryPat::PrimaryPat() {

    gun = new G4ParticleGun(1);
    gun->SetParticleDefinition(G4Neutron::NeutronDefinition());
    gun->SetParticleEnergy(14*MeV);
    gun->SetParticlePosition(G4ThreeVector(0,0,0));
}

PrimaryPat::~PrimaryPat() {


    delete gun;

}

void PrimaryPat::GeneratePrimaries(G4Event* anEvent) {

    G4double X, Y, Z;
    G4double l;
    do {
        X = 2 * G4UniformRand() - 1;
        Y = 2 * G4UniformRand() - 1;
        Z = 2 * G4UniformRand() - 1;
        l = sqrt(X * X + Y * Y + Z * Z);
    } while (l <= 1);
    gun->SetParticleMomentumDirection(G4ThreeVector(X / l, Y / l, Z / l));
    gun->GeneratePrimaryVertex(anEvent);


}
