
#include "../include/Geometry.hh"
#include <G4PVPlacement.hh>

#include <G4RunManager.hh>
#include <G4GeometryManager.hh>
#include <G4SolidStore.hh>
#include <G4VisAttributes.hh>
Geometry::Geometry() {


    nist = G4NistManager::Instance();
    world_mat = nist->FindOrBuildMaterial("G4_Galactic");
    water_mat = nist->FindOrBuildMaterial("G4_WATER");
    


    size = 15 * m;

}


Geometry::~Geometry(){


}

G4VPhysicalVolume* Geometry::Construct() {
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    world = new G4Box("world", size / 2., size / 2., size / 2.);
    world_log = new G4LogicalVolume(world, world_mat, "world_log");
    world_log->SetVisAttributes(G4VisAttributes::Invisible);
    world_VP = new G4PVPlacement(nullptr, G4ThreeVector(), world_log, "world_PV", nullptr, false, 0);

    G4Tubs* water = new G4Tubs("tube",3*cm,10*cm,40/2*cm,0,270*deg);
    G4LogicalVolume * water_log = new G4LogicalVolume(water,water_mat,"water_log");
    water_log->SetVisAttributes(G4Colour::Blue());
    new G4PVPlacement(new G4RotationMatrix(0, 45*deg, 0),G4ThreeVector(5*m,0,0),water_log,"water_PVP",world_log,false,0);

    auto Box  = new G4Box("box", 2*m, 2*m, 2*m );
    auto Box_log = new G4LogicalVolume(Box, water_mat, "box_log");
    Box_log->SetVisAttributes(G4Colour::Cyan());
    auto Box_PV = new G4PVPlacement(0, G4ThreeVector(), Box_log, "Box_PV", world_log, false,0);


    auto Box1  = new G4Box("box1", 1*m, 1*m, 1*m );
    auto Box1_log = new G4LogicalVolume(Box1, water_mat, "box1_log");
    Box1_log->SetVisAttributes(G4Colour::Red());
    auto Box1_PV = new G4PVPlacement(0, G4ThreeVector(0,3*m, 0), Box1_log, "Box1_PV", world_log, false,0);


    auto Box2  = new G4Box("box2", 1*m, 1*m, 1*m );
    auto Box2_log = new G4LogicalVolume(Box2, water_mat, "box2_log");
    Box2_log->SetVisAttributes(G4Colour::Black());
    auto Box2_PV = new G4PVPlacement(0, G4ThreeVector(-3*m,0, 0), Box2_log, "Box2_PV", world_log, false,0);



    return world_VP;
}