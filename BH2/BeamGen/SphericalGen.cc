#include "fvec.hh"
#define pi  3.14159265358979323846
Double_t norm(Double_t u,Double_t v)
{
	return 1/sqrt(1+u*u+v*v);
}

void PhotonGen(Double_t theta,Int_t ent)
{
	gRandom->SetSeed();
	Int_t pid;

	//	Int_t nbeam=100;
	Double_t p,px,py,pz,x,y,z,tof;
	TString name= "SphericalPhoton";
	TString dir="../build/Beam/";
	Int_t th=theta;
	string ang=to_string(th);
	name=name+ang;
	TFile* file = new TFile(dir+name+".root","RECREATE","Output");
	TTree* tree = new TTree("tree","tree");
	tree->Branch("pid",&pid,"pid/I");
	tree->Branch("p",&p,"p/D");
	tree->Branch("px",&px,"px/D");
	tree->Branch("py",&py,"py/D");
	tree->Branch("pz",&pz,"pz/D");
	tree->Branch("x",&x,"x/D");
	tree->Branch("y",&y,"y/D");
	tree->Branch("z",&z,"z/D");
/*
	tree->Branch("polx",&polx_,"polx/D");
	tree->Branch("poly",&poly_,"poly/D");
	tree->Branch("polz",&polz_,"polz/D");
*/
	tree->Branch("tof",&tof,"tof/D");
	theta=TMath::Pi()*theta/180;
	Double_t r=10;
	p=3e-9;
	for(int i=0;i<ent;i++)
	{
		pid=0;
		px= p*sin(theta);
		py=0;
		pz= p*cos(theta);
		x= -r*sin(theta);
		y=0;
		z= r*cos(theta);	
		tof=0;
		tree->Fill();
	}
	file->Write();
	cout<<"file "<<name<<" written at "<<dir<<endl;
}
void SphericalGen()
{
	for(int i=0;i<10;i++)
	{
		cout<<i<<endl;
		PhotonGen(i*10,10000);
	}
}
