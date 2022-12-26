#ifndef TargetSD_h
#define TargetSD_h
#include "TargetHit.hh"
#include "G4DataVector.hh"
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class TargetSD : public G4VSensitiveDetector
{
	public:
		TargetSD(G4String name);
		~TargetSD();
		void Initialize(G4HCofThisEvent*);
		G4bool ProcessHits(G4Step* aStep,G4TouchableHistory*);
		void EndOfEvent(G4HCofThisEvent*);
		void clear();
		G4int dummy_trid;
		G4double tof;
	private:
		TargetHitsCollection* TargetCollection;
};


#endif
