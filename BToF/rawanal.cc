int trkfg,detfg,i,j,k,l,rfl,u1,u2,d1,d2,lost,absorb,Nrun,cntfg,mb,ufg,dfg=0;
void rawanal()
{
//  gRandom->SetSeed();
  double en,x,y,z;
  Long64_t time;
  int entries=0;
  float nce=0;
  float neff=0;
  TH1D* E = new TH1D("Energy","Energy",32,2,4.2);
  TH1D* T = new TH1D("Reflection","Reflection",20,0,20);
  TH2D* L = new TH2D("L","DetU",70,-350,350,120,-600,600);
  TH2D* R = new TH2D("R","DetD",70,-350,350,120,-600,600);
  TCanvas *c1 = new TCanvas("c1","c1",1200,600);
  TCanvas *c2 = new TCanvas("c2","c2",1200,600);
  TFile *file = new TFile("Out.root");
  TTree *tree = (TTree *)file->Get("tree");
  tree->SetBranchAddress("eng",&en);
  tree->SetBranchAddress("rfl",&rfl);
  tree->SetBranchAddress("posx",&x);
  tree->SetBranchAddress("posy",&y);
  tree->SetBranchAddress("posz",&z);
  int nev = tree->GetEntries();
  cout<<nev<<endl;
  for(int i=0;i<nev;i++)
  {
    tree->GetEntry(i);
      if(x>0)
      {
        L->Fill(z-350,y);
      }
      else
      {
        R->Fill(z-350,y);
      }
      E->Fill(en);
      T->Fill(rfl);
  }
  c1->Divide(2,1);
  c2->Divide(2,1);
  c1->cd(1);
  E->GetXaxis()->SetTitle("Energy of Photon[eV]");
  E->GetYaxis()->SetTitle("detection[#]");
  E->Draw();
  c1->cd(2);
  T->GetXaxis()->SetTitle("Reflection[#]");
  T->GetYaxis()->SetTitle("detection[#]");
  T->Draw();
  c2->cd(1);
  L->GetXaxis()->SetTitle("Xposition[mm]");
  L->GetYaxis()->SetTitle("Yposition[mm]");
  L->Draw("COLZ");
  c2->cd(2);
  R->GetXaxis()->SetTitle("Xposition[mm]");
  R->GetYaxis()->SetTitle("Yposition[mm]");
  R->Draw("COLZ");
}
