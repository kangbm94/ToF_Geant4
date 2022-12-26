#include "fvec.hh"
#define pi  3.14159265358979323846
Double_t norm(Double_t u,Double_t v)
{
	return 1/sqrt(1+u*u+v*v);
}

void BeamGen(Int_t ypos,Int_t ent)
{
	gRandom->SetSeed();
	Int_t pid;

	//	Int_t nbeam=100;
	Double_t p,px,py,pz,x,y,z,tof;
	TString name= "PionGen";
	TString dir="../build/Beam/";
	name=name+to_string(ypos);
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
	p=1;
	for(int i=0;i<ent;i++)
	{
		pid=211;
		px= 0;
		py=0;
		pz= p;
		x= 0;
		y= ypos;
		z= 10;
		tof=0;
		tree->Fill();
	}
	file->Write();
	cout<<"file "<<name<<" written at "<<dir<<endl;
}
void BeamGen()
{
	for(int i=0;i<8;i++)
	{
		cout<<i<<endl;
		BeamGen(i*50,10000);
	}
}
