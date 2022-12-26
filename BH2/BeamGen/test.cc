#include "fvec.hh"
void test(){
  fvec Proton(938);
  fvec Pion(139);
  fvec Proton2(938);
  fvec Pion2(139);
  Pion.Init();
fvec tmp1(0);
//  fvec LambdaC(1478);
  TH2D *K = new TH2D("h","h",200,0,2,300,-1,2);
  for(int i=0;i<100000;i++)
  {
  Proton.Init();
  Pion.Init();
	Pion.SetMomentum(0,0,1800);
  Proton2.Init();
  Pion2.Init();
  Decay(Pion,Proton,Proton2,Pion2);
//  cout<<tmp2.GetMass()<<endl;
  K->Fill(Pion2.GetMomentum()/1000,Pion2.GetComponent(1)/1000);
  }
  K->Draw("COLZ");
  }
