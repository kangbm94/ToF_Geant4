#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "PhysicsList.hh"
#include "OpticalTest.hh"
#include "ActionInitialization.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
namespace {
	void PrintUsage() {
		G4cerr << " Usage: " << G4endl;
		G4cerr << "  [-m macro ] [-u UIsession] [-t nThreads] [-r seed] [-n filename] [-b beamProfile]"
			<< G4endl;
		G4cerr << "   note: -t option is available only for multi-threaded mode."
			<< G4endl;
		G4cerr << "   note: without -n option, file name will be [Out.root]."
			<< G4endl;
	}
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
	// Evaluate arguments
	//
	if ( argc > 17 ) {
		PrintUsage();
		return 1;
	}

	G4int beamflg=0;
	G4String macro;
	//="optPhoton.mac";
	G4String session;
	G4String filename="Out";
	G4String beamname;
	G4double xsh=0;
	G4double ysh=0;
#ifdef G4MULTITHREADED
	G4int nThreads = 8;
#endif

	AnalysisManager* AnaManager = new AnalysisManager();
	BeamManager* BeManager = new BeamManager();
	G4long myseed = 345313;
	for ( G4int i=1; i<argc; i=i+2 ) {
		if      ( G4String(argv[i]) == "-m" ) macro   = argv[i+1];
		else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
		else if ( G4String(argv[i]) == "-n" ) filename = argv[i+1];
		else if ( G4String(argv[i]) == "-b" ) {
			beamname = argv[i+1];
			beamflg++;
		}
		else if ( G4String(argv[i]) == "-r" ) myseed  = atoi(argv[i+1]);
		else if ( G4String(argv[i]) == "-x" ) xsh  = atof(argv[i+1]);
		else if ( G4String(argv[i]) == "-y" ) ysh  = atof(argv[i+1]);
#ifdef G4MULTITHREADED
		else if ( G4String(argv[i]) == "-t" ) {
			nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
		}
#endif
		else {
			PrintUsage();
			return 1;
		}
	}
	AnaManager->CreateFile(filename);
	if(beamflg==1)
	{
		BeManager->ReadFile(beamname,xsh,ysh);
//		G4cout<<"Beam Manager Loaded"<<G4endl;
	}
	else
	{
		BeManager->Default();
	}
	// Choose the Random engine
	//
	G4Random::setTheEngine(new CLHEP::RanecuEngine);

	// Construct the default run manager
	//
#ifdef G4MULTITHREADED
//	G4MTRunManager * runManager = new G4MTRunManager;
//	if ( nThreads > 0 ) runManager->SetNumberOfThreads(nThreads);
	G4RunManager * runManager = new G4RunManager;
#else
	G4RunManager * runManager = new G4RunManager;
#endif


	// Seed the random number generator manually
	G4Random::setTheSeed(myseed);

	// Set mandatory initialization classes
	//
	// Detector construction
	runManager-> SetUserInitialization(new OpticalTest());
	G4cout<<"Detector Construction Initialized"<<G4endl;
	// Physics list
	runManager-> SetUserInitialization(new PhysicsList());
	G4cout<<"PhysicsList Initialized"<<G4endl;
	// User action initialization
	runManager-> SetUserInitialization(new ActionInitialization(AnaManager,BeManager));
	G4cout<<"User Action Initialized"<<G4endl;

//	G4UserRunAction* run_action = new RunAction(AnaManager);
//	runManager->SetUserAction(run_action);
	//  runManager->SetUserInitialization(new ActionInitialization());
	//Generator
/*	G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction();
	runManager->SetUserAction(gen_action);
	G4cout<<"PrimaryGenerator Set"<<G4endl;

	//StepAction
	SteppingAction *StepAction = new SteppingAction(AnaManager);
	runManager->SetUserAction(StepAction);
	G4cout<<"SteppingAction Set"<<G4endl;

	StackingAction* stackAction = new StackingAction();
 	runManager->SetUserAction(stackAction);
*/
	// Initialize G4 kernel
	//
	runManager->Initialize();
	G4cout<<"RunManager Initialized"<<G4endl;

#ifdef G4VIS_USE
	// Initialize visualization
	//
	G4VisManager* visManager = new G4VisExecutive;
	// G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
	// G4VisManager* visManager = new G4VisExecutive("Quiet");
	visManager->Initialize();
#endif

	// Get the pointer to the User Interface manager
	//
	G4UImanager* UImanager = G4UImanager::GetUIpointer(); 
	UImanager->ApplyCommand("/tracking/verbose 0");
	UImanager->ApplyCommand("/control/verbose 0");
	UImanager->ApplyCommand("/LACSim/phys/verbose 0");
	if ( macro.size() ) {
		// Batch mode
		G4String command = "/control/execute ";
		UImanager->ApplyCommand(command+macro);
	}
	else // Define UI session for interactive mode
	{
#ifdef G4UI_USE
		G4UIExecutive * ui = new G4UIExecutive(argc,argv,session);
#ifdef G4VIS_USE
		UImanager->ApplyCommand("/control/execute vis.mac");
#else
		UImanager->ApplyCommand("/control/execute .in");
#endif
		if (ui->IsGUI())
			UImanager->ApplyCommand("/control/execute gui.mac");
		ui->SessionStart();
		delete ui;
#endif
	}

	// Job termination
	// Free the store: user actions, physics_list and detector_description are
	//                 owned and deleted by the run manager, so they should not
	//                 be deleted in the main() program !

#ifdef G4VIS_USE
	delete visManager;
#endif
	delete runManager;
	delete BeManager;
	delete AnaManager;

	return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
