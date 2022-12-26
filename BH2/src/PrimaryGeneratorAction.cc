#include "PrimaryGeneratorAction.hh"

#include "Randomize.hh"
#include <iostream>
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalPhoton.hh"

//PrimaryGeneratorAction* PrimaryGeneratorAction::PrimaryGenerator_=0;
	PrimaryGeneratorAction::PrimaryGeneratorAction(BeamManager* beam)
: G4VUserPrimaryGeneratorAction(), 
	fParticleGun(0)
{
	particleTable = G4ParticleTable::GetParticleTable();
	BeManager = beam;
		//BeamManager::GetBeamManager();
	G4int n_particle = 1;
	fParticleGun = new G4ParticleGun();

	//	fParticleGun = new G4ParticleGun(n_particle);
//	PrimaryGenerator_=this;
	//create a messenger for this class
	nbeam=BeManager->GetBeamEntries();
	//	std::cout<<"Primary Generator: Beam Loaded with enetries: "<<nbeam<<std::endl;
	pid_pr=BeManager->GetBeamPid(0);
	px_pr=BeManager->GetBeamPX(0);  
	py_pr=BeManager->GetBeamPY(0);  
	pz_pr=BeManager->GetBeamPZ(0);  
	p_pr=BeManager->GetBeamMomentum(0);  
	x_pr=BeManager->GetBeamX(0);  
	y_pr=BeManager->GetBeamY(0);  
	z_pr=BeManager->GetBeamZ(0); 
	t_pr=BeManager->GetBeamTime(0); 
	//	std::cout<<"Vertex time set: t= "<<t<<" [ns]"<<std::endl;	
	if(pid_pr!=0){	
		fParticleGun -> SetParticleDefinition (particleTable -> FindParticle(pid_pr)); 
		G4cout<<"Particle set to ID: "<<pid_pr<<G4endl;
	}
	else{
		G4ParticleDefinition* particle = particleTable->FindParticle("e-");
		//					G4Strint particlename = particle->GetParticleName();
		//					fParticleGun->SetParticleDefinition(G4OpticalPhoton::OpticalPhotonDefinition());
		//					G4cout<<""<<G4endl;
		fParticleGun -> SetParticleDefinition (particle); 
		fParticleGun->SetParticlePolarization(G4ThreeVector(polx_pr,poly_pr,polz_pr));
	}
	//	std::cout<<"Particle set: "<<pid<<std::endl;
	//	std::cout<<"pid Loaded"<<std::endl;
	fParticleGun->SetParticleTime(t_pr*ns);
	//G4ParticleDefinition* particle = particleTable->FindParticle("pi-");
	fParticleGun->SetParticlePosition(G4ThreeVector(x_pr*mm,y_pr*mm,z_pr*mm));
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px_pr,py_pr,-pz_pr));
	fParticleGun->SetParticleMomentum(p_pr*GeV);
	std::cout<<"Primary Generator: Beam Loaded "<<std::endl;
	std::cout<<"Beam Entries: "<<nbeam<<std::endl;
	std::cout<<"Beam Vertex: "<<"("<<x_pr<<","<<y_pr<<","<<z_pr<<")"<<std::endl;
	std::cout<<"Beam Momentum: "<<"("<<px_pr<<","<<py_pr<<","<<pz_pr<<")"<<std::endl;
	std::cout<<"Primary Generator Initialized."<<std::endl;
	/*	if(nbeam==-1)
		{
		std::cout<<"Default setting."<<std::endl;
		}
		else
		{	
		beamname_out=BeamMan->GetBeamName();
		std::cout<<"Beam file"<<beamname_out<<std::endl;	
		}	*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fParticleGun;
	delete fGunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	//	if(nbeam!=-1)
	//	{
	nbeam=BeManager->GetBeamEntries();
	//	std::cout<<"Run number: "<<nrun<<std::endl;
	if(np<nbeam)
	{
		pid_pr=BeManager->GetBeamPid(np);
		px_pr=BeManager->GetBeamPX(np);  
		py_pr=BeManager->GetBeamPY(np);  
		pz_pr=BeManager->GetBeamPZ(np);  
		polx_pr=BeManager->GetBeamPOLX(np);  
		poly_pr=BeManager->GetBeamPOLY(np);  
		polz_pr=BeManager->GetBeamPOLZ(np);  
		p_pr=BeManager->GetBeamMomentum(np);  
		//	std::cout<<"Momentum Loaded: "<<p<<" GeV/c"<<std::endl;
		x_pr=BeManager->GetBeamX(np);  
		y_pr=BeManager->GetBeamY(np);  
		z_pr=BeManager->GetBeamZ(np); 
		t_pr=BeManager->GetBeamTime(np); 
		//	std::cout<<"particle id is: "<<pid<<std::endl;	
		if(pid_pr!=0){	
			fParticleGun -> SetParticleDefinition (particleTable -> FindParticle(pid_pr)); 
			G4cout<<"Particle set to ID: "<<pid_pr<<G4endl;
		}
		else{
			G4ParticleDefinition* particle = particleTable->FindParticle("opticalphoton");
			//					G4Strint particlename = particle->GetParticleName();
			//					fParticleGun->SetParticleDefinition(G4OpticalPhoton::OpticalPhotonDefinition());
			//					G4cout<<""<<G4endl;
			fParticleGun -> SetParticleDefinition (particle); 
			fParticleGun->SetParticlePolarization(G4ThreeVector(polx_pr,poly_pr,polz_pr));
		}

		//	std::cout<<"pid Loaded"<<std::endl;
		fParticleGun->SetParticleTime(t_pr*ns);
		fParticleGun->SetParticlePosition(G4ThreeVector(x_pr*mm,y_pr*mm,z_pr*mm));
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px_pr,py_pr,-pz_pr));
		fParticleGun->SetParticleMomentum(p_pr*GeV);
		//if(pid<400&&pid>300)
		//if(pid<0)
		//		{
		fParticleGun->GeneratePrimaryVertex(anEvent);
	std::cout<<"Momentum Loaded: "<<p_pr<<" GeV/c"<<std::endl;
	std::cout<<"Momentum Component: ( "<<px_pr<<" , "<<py_pr<<" , "<<pz_pr<<" )"<<std::endl;	
	std::cout<<"Vertex Loaded: ( "<<x_pr<<" , "<<y_pr<<" , "<<z_pr<<" )"<<std::endl;	

		std::cout<<"PrimaryGeneratoer:: number of particle is: "<<np<<std::endl;
		np++;
	}
	else
	{
		G4cout<<"Run End"<<G4endl;
		np++;
	}
	//		}
}

int PrimaryGeneratorAction::Getnbeam()
{
	nbeam=BeManager->GetBeamEntries();
	return nbeam;

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

*/
