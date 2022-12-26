#ifndef BeamManager_hh
#define BeamManager_hh 1
#include "TNtuple.h"
#include "TTree.h"
#include "TBranch.h"
#include "math.h"
#include "G4ThreeVector.hh"
#include "TFile.h"
#include <vector>
class TFile;
class TTree;
using  std::vector;
struct BEAM
{
		int nbeam;
		vector<int> pid;
		vector<double> p;
		vector<double> px;
		vector<double> py;
		vector<double> pz;
		vector<double> polx;
		vector<double> poly;
		vector<double> polz;
		vector<double> x;
		vector<double> y;
		vector<double> z;
		vector<double> tof;
		//		G4ThreeVector Mom;
};
class BeamManager
{
	public:

		BeamManager();
		~BeamManager();
		void Default(void);
		void ReadFile(G4String beamname,double xsh, double ysh, int nth, int njob);
		void ReadFile(G4String beamname,double xsh, double ysh);
		void LoadFile(G4String beamname);
		bool ProfileMode(){
			return profilemode;
		}
		TFile* GetBeam(){
			return file;
		}
		int GetBeamPid( int i ); 
		int GetBeamEntries( void); 
		double GetBeamMomentum( int i );
		double GetBeamPX( int i );
		double GetBeamPY( int i );
		double GetBeamPZ( int i );
		double GetBeamPOLX( int i );
		double GetBeamPOLY( int i );
		double GetBeamPOLZ( int i );
		double GetBeamX( int i );
		double GetBeamY( int i );
		double GetBeamZ( int i ) ;
		double GetBeamTime( int i ); 
		static BeamManager *GetBeamManager( void ) { return BeamManager_; }
	private:
		static BeamManager *BeamManager_;
		TFile *file;
		TTree *tree;
		BEAM beam;	
		G4String beamname;
		bool profilemode = false; 
		






		int tot;
		int nbeam;
		int nbeam_;
		int res;
		int pid;
		double p;
		double px;
		double py;
		double pz;
		double polx;
		double poly;
		double polz;
		double x;
		double y;
		double z;
		double tof;
		//		G4ThreeVector Mom;
		//		G4ThreeVector Pos;
		double xsh;
		double ysh;
};
#endif
