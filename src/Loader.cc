
#include "../include/Loader.hh"
#include "../include/Geometry.hh"

#include "../include/Action.hh"
#include <Shielding.hh>


Loader::Loader(int argc, char **argv) {

    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    CLHEP::HepRandom::setTheSeed(time(nullptr));
#ifdef G4MULTITHREADED
    runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());


#else
    Logger::Info("Geant4 have been run in non-MT mode");
    runManager = new G4RunManager;
#endif
    runManager->SetUserInitialization(new Geometry());
    runManager->SetUserInitialization(new Shielding);
    runManager->SetUserInitialization(new Action());


    runManager->Initialize();

#ifdef G4VIS_USE
    // Initialize visualization
    visManager = new G4VisExecutive;
    visManager->Initialize();
#endif

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if (argc != 1) {
        // batch mode
        std::string command = "/control/execute ";
        std::string fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
    else {
        // interactive mode : define UI session
#ifdef G4UI_USE
        G4UIExecutive *ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
        UImanager->ApplyCommand("/control/execute init_vis.mac");
#else
        UImanager->ApplyCommand("/control/execute init.mac");
#endif
        ui->SessionStart();
        delete ui;
#endif
    }


}

Loader::~Loader(){
    delete runManager;

}