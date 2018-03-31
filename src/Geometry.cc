
#include "../include/Geometry.hh"
#include <G4PVPlacement.hh>

#include <G4RunManager.hh>
#include <G4GeometryManager.hh>
#include <G4SolidStore.hh>
#include <G4VisAttributes.hh>
#include <G4Orb.hh>
#include <G4Sphere.hh>
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

    std:: ofstream fout("../result.txt");



    G4Element *La = new G4Element("Lanthanum", "La", 57, 138.905*g/mole);
    G4Element *Br = new G4Element("Bromine", "Br", 35, 79.904*g/mole);
    G4Element *Ce = new G4Element("Cerium", "Ce", 58, 140.116*g/mole);
    G4Material *fuel = new G4Material("Scintillator", 6.23*g/cm3, 3, kStateSolid, 400*kelvin, 1*10e6*pascal);
    fuel ->AddElement(La,0.2);
    fuel ->AddElement(Br,0.6);
    fuel ->AddElement(Ce,0.2);


    G4Element* La1 = nist -> FindOrBuildElement(57);
    G4Element* Br1 = nist -> FindOrBuildElement(35);
    G4Element* Ce1 = nist -> FindOrBuildElement(58);
    G4Material *fuel1 = new G4Material("Scintillator1", 6.23*g/cm3, 3, kStateSolid, 400*kelvin, 1*10e6*pascal);
    fuel1 ->AddElement(La1,0.2);
    fuel1 ->AddElement(Br1,0.6);
    fuel1 ->AddElement(Ce,0.2);




    G4Element* Fe2 = nist -> FindOrBuildElement(26);
    G4Element* Si2 = nist -> FindOrBuildElement(14);
    G4Element* Mn2 = nist -> FindOrBuildElement(25);
    G4Element* Ti2 = nist -> FindOrBuildElement(22);
    G4Element* Al2 = nist -> FindOrBuildElement(13);
    G4Material *fuel2 = new G4Material("AMG2", 2.69*g/cm3, 5, kStateSolid, 400*kelvin, 1*10e8*pascal);
    fuel2 ->AddElement(Al2,0.94);
    fuel2 ->AddElement(Si2,0.04);
    fuel2 ->AddElement(Mn2,0.01);
    fuel2 ->AddElement(Ti2,0.005);
    fuel2 ->AddElement(Fe2,0.005);














    auto box = new G4Box("box",2*m, 2*m, 2*m);
    auto box_log = new G4LogicalVolume(box, fuel1, "box_log");
    box_log -> SetVisAttributes(G4Colour::Blue());
    auto box_PV = new G4PVPlacement(0, G4ThreeVector(0,0,0), box_log, "box_PV", world_log, false, 0);



    auto tube = new G4Tubs("tube",0, 1*m, 2.2*m, 0, 360*deg);
    auto tube_log = new G4LogicalVolume(tube, fuel2, "tube_log");
    tube_log -> SetVisAttributes(G4Colour::Magenta());
    auto tube_PV = new G4PVPlacement(0, G4ThreeVector(10*m,10*m,10*m), tube_log, "tube_PV", world_log, false, 0);

    auto sphere = new G4Sphere("sphere", 0.5*m, 1*m, 0, 360*deg, 0, 360*deg);
    auto sphere_log = new G4LogicalVolume(sphere, fuel, "tube_log");
    sphere_log -> SetVisAttributes(G4Colour::Green());
    auto sphere_PV = new G4PVPlacement(0, G4ThreeVector(-10*m,-10*m,-10*m), sphere_log, "sphere_PV", world_log, false, 0);


    fout << fuel;
    fout << fuel1;
    fout << fuel2;








    return world_VP;
}