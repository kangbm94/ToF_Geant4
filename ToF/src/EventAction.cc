#include "EventAction.hh"
#include "AnalysisManager.hh"
EventAction::EventAction(AnalysisManager *ana)://G4UserEventAction(),
	AnaManager(ana){
}

EventAction::~EventAction(){
}

void EventAction::BeginOfEventAction(const G4Event *anEvent){
	counter++;
	if(AnaManager) 
	{
//		G4cout<<"[EventAction:] Begin of Event"<<G4endl;
		AnaManager->BeginOfEvent(anEvent);
	}
}
void EventAction::EndOfEventAction(const G4Event *anEvent){
	if(AnaManager)
	{
	//	G4cout<<"[EventAction:] End of Event"<<G4endl;
		AnaManager->EndOfEvent(anEvent);
	}
	if(counter%10000==0){
		std::cout<<"Event: "<<counter<<std::endl;
	}
}
