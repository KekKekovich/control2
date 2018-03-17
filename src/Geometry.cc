
#include "../include/Geometry.hh"
#include <G4PVPlacement.hh>

#include <G4RunManager.hh>
#include <G4GeometryManager.hh>
#include <G4SolidStore.hh>
#include <G4VisAttributes.hh>
#include <G4Orb.hh>
#include <G4SubtractionSolid.hh>

Geometry::Geometry() {


    nist = G4NistManager::Instance();
    world_mat = nist->FindOrBuildMaterial("G4_Galactic");
    water_mat = nist->FindOrBuildMaterial("G4_WATER");
    




}


Geometry::~Geometry(){


}

G4VPhysicalVolume* Geometry::Construct() {
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    world = new G4Box("world", 50*m, 50*m, 50*m);
    world_log = new G4LogicalVolume(world, world_mat, "world_log");
    world_log->SetVisAttributes(G4VisAttributes::Invisible);
    world_VP = new G4PVPlacement(nullptr, G4ThreeVector(), world_log, "world_PV", nullptr, false, 0);



    auto box  = new G4Box("box", 2*m, 2*m, 2*m );


    auto orb = new G4Orb("orb",2.2*m);
    G4SubtractionSolid* Sub = new G4SubtractionSolid("My_sub", box, orb);
G4LogicalVolume *Sub_log = new G4LogicalVolume(Sub, world_mat, "my_sub_log");
    Sub_log -> SetVisAttributes(G4Colour::Cyan());
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            new G4PVPlacement (new G4RotationMatrix(15*i*deg,15*deg*j,0), G4ThreeVector(6*i*m,6*j*m,0), Sub_log, "my_sub_PVP", world_log, false,0);

        }

    }


    return world_VP;
}