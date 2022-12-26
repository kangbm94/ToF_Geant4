
#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "AnalysisManager.hh"
#include "BeamManager.hh"
#include "PrimaryGeneratorAction.hh"
class B4DetectorConstruction;

/// Action initialization class.
///

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization(AnalysisManager* ana,BeamManager* beam);
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

	private:
	 AnalysisManager* ana;
	 BeamManager* beam;
};

#endif
