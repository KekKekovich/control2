//
// Created by idalov on 10.05.17.
//

#ifndef FINAL_GEOMETRY_HH
#define FINAL_GEOMETRY_HH

#include <G4VUserDetectorConstruction.hh>
#include <G4Box.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4Colour.hh>
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include <G4Tubs.hh>
#include <G4AssemblyVolume.hh>



class Geometry: public G4VUserDetectorConstruction {
private:
    G4Box               *world;
    G4LogicalVolume     *world_log;
    G4VPhysicalVolume   *world_VP;

    G4NistManager*      nist;
    G4Material*         world_mat;
    G4Material*         water_mat;

    G4VPhysicalVolume *Construct() override;



public:
    Geometry();

    ~Geometry() override;

private:
    G4double size;

};

#endif //FINAL_GEOMETRY_HH
