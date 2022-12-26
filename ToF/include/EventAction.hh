#ifndef EventAction_h
#define EventAction_h
#include "globals.hh"
#include "G4UserEventAction.hh"
#include "AnalysisManager.hh"
class EventAction: public G4UserEventAction
{
	public:
		EventAction(AnalysisManager *analysManager=0);
		~EventAction();

	private:
		EventAction(const EventAction&);
		EventAction&operator=(const EventAction&);
	public:
		void BeginOfEventAction(const G4Event *anEvent);
		void EndOfEventAction(const G4Event *anEvent);
	protected:
		AnalysisManager* AnaManager;
		int counter = 0;
};
#endif
