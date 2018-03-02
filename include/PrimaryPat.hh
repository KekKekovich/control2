//
// Created by idalov on 10.05.17.
//

#ifndef FINAL_PRIMARYPAT_HH
#define FINAL_PRIMARYPAT_HH

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <map>



class PrimaryPat: public G4VUserPrimaryGeneratorAction {
private:
    G4ParticleGun *gun;


public:
    PrimaryPat();

    ~PrimaryPat() override;

    void GeneratePrimaries(G4Event *anEvent) override;
};


#endif //FINAL_PRIMARYPAT_HH
