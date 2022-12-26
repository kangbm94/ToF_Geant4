#include "BeamManager.hh"
#include <iostream>
#include <iomanip>
#include <sstream>

BeamManager * BeamManager::BeamManager_ = 0;
BeamManager::BeamManager()
{
}
BeamManager::~BeamManager()
{
	BeamManager_=0;
}

void BeamManager::Default()
{
	double px,py,pz,p,x,y,z,time;
	px=0;
	py=0;
	pz=1;
	p=sqrt(px*px+py*py+pz*pz);
	p=1;
	x=10;
	y=0;
	z=20;
	time=0;
	beam.nbeam=-1;
	beam.pid.push_back(211);//211: pi+; 321: k+; 2212: p
	beam.px.push_back(px);
	beam.py.push_back(py);
	beam.pz.push_back(pz);
	beam.p.push_back(p);
	beam.x.push_back(x);
	beam.y.push_back(y);
	beam.z.push_back(z);
	beam.tof.push_back(time);
	BeamManager_=this;
	std::cout<<"Defalut Beam Set: "<<std::endl;
	std::cout<<"Beam Vertex: ("<<x<<","<<y<<","<<z<<")"<<" [mm]"<<std::endl;
	std::cout<<"Beam Momentum: ("<<px<<","<<py<<","<<pz<<")"<<" [GeV/c]"<<std::endl;

}

void BeamManager::ReadFile(G4String beamname, double xsh, double ysh,int nth, int njob)
{

	//if(DCGeomManager_) delete DCGeomManager_;
	//  confManager_=0;

	file = new TFile(beamname,"READ");
	tree = (TTree*)file->Get("tree");
	tree->SetBranchAddress("pid",&pid);
	//	tree->SetBranchAddress("p",&p);
	tree->SetBranchAddress("px",&px);
	tree->SetBranchAddress("py",&py);
	tree->SetBranchAddress("pz",&pz);
	tree->SetBranchAddress("x",&x);
	tree->SetBranchAddress("y",&y);
	tree->SetBranchAddress("z",&z);
	tree->SetBranchAddress("polx",&polx);
	tree->SetBranchAddress("poly",&poly);
	tree->SetBranchAddress("polz",&polz);
	tree->SetBranchAddress("tof",&tof);
	tot=tree->GetEntries();
	if(nth>1)
	{
		std::cout<<"Using Multy-threading mode: "<<njob<<"Out of "<<nth<<"threads."<<std::endl;
		nbeam=tot/nth;
		nbeam_=tot/nth;
		res=tot-nbeam*nth;
		if(njob==nth-1)
		{
			nbeam=nbeam+res;
			std::cout<<"residue is :"<<res<<std::endl;
		}
		std::cout<<"nbeam is: "<<nbeam<<std::endl;
	}
	else
	{
		nbeam=tot;		
	}
	beam.nbeam=nbeam;

	for(int i=0;i<nbeam;i++)
	{	
		tree->GetEntry(i+njob*nbeam_);
		beam.pid.push_back(pid);
		//		std::cout<<beam.pid[i]<<std::endl;
		beam.px.push_back(px);
		beam.py.push_back(py);
		beam.pz.push_back(pz);
		beam.x.push_back(x-xsh);
		beam.y.push_back(y-ysh);
		beam.z.push_back(z);
		beam.polx.push_back(polx);
		beam.poly.push_back(poly);
		beam.polz.push_back(polz);
		beam.tof.push_back(tof);
		beam.p.push_back(sqrt(px*px+py*py+pz*pz));
	}
	file->Close();
	BeamManager_=this;
	std::cout<<"Beam Loaded with file: "<<beamname<<std::endl;
}
void BeamManager::LoadFile(G4String beamname){
	profilemode = true;
	file = new TFile(beamname,"READ");	
}
void BeamManager::ReadFile(G4String beamname, double xsh, double ysh)
{
	std::cout<<"Single-thread mode"<<std::endl;
	return BeamManager::ReadFile(beamname,xsh,ysh,1,0);
}
int BeamManager::GetBeamEntries()
{
	nbeam=beam.nbeam;
	return nbeam;
}
int BeamManager::GetBeamPid(int i)
{
	pid=beam.pid[i];
	return pid;
}
double BeamManager::GetBeamMomentum(int i)
{
	p=beam.p[i];
	return p;	
}
double BeamManager::GetBeamPX(int i)
{
	px=beam.px[i];
	return px;	
}

double BeamManager::GetBeamPY(int i)
{
	py=beam.py[i];
	return py;	
}
double BeamManager::GetBeamPZ(int i)
{
	pz=beam.pz[i];
	return pz;	
}

double BeamManager::GetBeamPOLX(int i)
{
	polx=beam.polx[i];
	return polx;	
}

double BeamManager::GetBeamPOLY(int i)
{
	poly=beam.poly[i];
	return poly;	
}
double BeamManager::GetBeamPOLZ(int i)
{
	polz=beam.polz[i];
	return polz;	
}

double BeamManager::GetBeamX(int i)
{
	x=beam.x[i];
	return x;	
}
double BeamManager::GetBeamY(int i)
{
	y=beam.y[i];
	return y;	
}
double BeamManager::GetBeamZ(int i)
{
	z=beam.z[i];
	return z;	
}
double BeamManager::GetBeamTime(int i)
{
	tof=beam.tof[i];
	return tof;	
}
