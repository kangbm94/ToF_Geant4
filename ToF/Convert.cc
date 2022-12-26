#include "Utils.hh"
void Convert(){
	int nlines = 6866296;
	int A[300],Z[300];
	double px[300],py[300],pz[300];
	int np=0;
	TString filename = "Sn132Sn124-soft-v3.dat";
	fstream file;
	file.open(filename.Data(),fstream::in);
	double data[11]={0};
	TFile* tf = new TFile("QMD.root","recreate");
	TTree* tree = new TTree("tree","tree");
	tree->Branch("np",&np,"np/I");
	tree->Branch("A",A,"A[np]/I");
	tree->Branch("Z",Z,"Z[np]/I");
	tree->Branch("px",px,"px[np]/D");
	tree->Branch("py",py,"py[np]/D");
	tree->Branch("pz",pz,"pz[np]/D");
	int evnum=1;
	int cnt = 0;
	while(ReadTSV(file,data)){
		Indicator(cnt,nlines);
		cnt++;
		if(data[0]==evnum){
			A[np]=data[2];Z[np]=data[3];px[np]=data[7];py[np]=data[8];pz[np]=data[9];
			if(A[np]<Z[np]){
				cout<<"Warning : A<Z evt "<<evnum<<" particle "<<np<<endl;
				cout<<A[np]<<" and "<<Z[np]<<endl;
			}
			np++;
		}
		else{
			tree->Fill();
			np=0;
			A[np]=data[2];Z[np]=data[3];px[np]=data[7];py[np]=data[8];pz[np]=data[9];
			np++;
		}
		evnum=data[0];
	}
	tf->Write();
	cout<<cnt<<endl;
}
