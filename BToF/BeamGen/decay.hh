#define PI 3.141593
class fvec{
  private:
    Double_t p[4];
  public:
    Double_t InvMass(){
      return sqrt(p[0]*p[0]-p[1]*p[1]-p[2]*p[2]-p[3]*p[3]);
    }
};


Double_t gamma(Double_t v)
{
  return 1/sqrt(1-v*v);
}
Double_t Mag(Double_t *p)
{
}
Double_t Inp(Double_t *p1,Double_t *p2)
{
  Double_t tmp[4];
  for(int k=0;k<4;k++)
  {
    tmp[k]=p1[k]+p2[k];
  }
  return Mag(tmp);
}

void Decay(Double_t *p3,Double_t *p4,Double_t *p1,Double_t *p2)
{
  Double_t v1[4]={0};
  Double_t tmp1[4]={0};
  Double_t tmp11[4]={0};
  Double_t v2[4]={0};
	Double_t m1=p1.GetMass();
	Double_t m2=p2.GetMass();
  Double_t tmp2[4]={0};
  Double_t tmp22[4]={0};
  Double_t M = Inp(p3,p4);
  Double_t vx = (p3[1]+p4[1])/(p3[0]+p4[0]);
  Double_t vy = (p3[2]+p4[2])/(p3[0]+p4[0]);
  Double_t vz = (p3[3]+p4[3])/(p3[0]+p4[0]);
  //  cout<<"vz is: "<<vz<<endl;
  Double_t v = sqrt(vx*vx+vy*vy+vz*vz);//Velocity of CoM at LAB frame.
  Double_t g = gamma(v);
  //  cout<<"g is: "<<g<<endl;
  Double_t theta = acos(vz/v);
  Double_t phi=0;
  if(theta==0)
  {
    phi=0;
  }
  if(theta!=0)
  {
    if(vy>0)
    {
      phi = acos(vx/(v*sin(theta))); 
    }
    else
    {
      phi =(2*PI -acos(vx/(v*sin(theta)))); 
    }
  }
  //  cout<<"phi is: "<<phi<<endl;
  Double_t r1= gRandom->Rndm();
  Double_t r2= gRandom->Rndm();
  //  Double_t r1 = 0;
  //  Double_t r2 = 0;
  tmp1[0]=(M*M+m1*m1-m2*m2)/(2*M);
  tmp2[0]=(M*M+m2*m2-m1*m1)/(2*M);
  Double_t p = sqrt((M-m1-m2)*(M-m1+m2)*(M+m1-m2)*(M+m1+m2))/(2*M);
  tmp1[1] = p*sin(PI*r1)*cos(2*PI*r2);
  tmp2[1]=-tmp1[1];
  tmp1[2] = p*sin(PI*r1)*sin(2*PI*r2);
  tmp2[2]=-tmp1[2];
  tmp1[3] = p*cos(PI*r1);
  tmp2[3]=-tmp1[3];
  //  cout<<"tmp2 is: "<<Mag(tmp2)<<endl;
  //tmp1, tmp2 are Momentums at the CoM frame.
  //tmp11, tmp22 are after lorentz boost. It needs to be rotated.
  tmp11[0] = g*(tmp1[0]+v*tmp1[3]);
  tmp11[1] = tmp1[1];
  tmp11[2] = tmp1[2];
  tmp11[3] = g*(tmp1[3]+v*tmp1[0]);
  tmp22[0] = g*(tmp2[0]+v*tmp2[3]);
  tmp22[1] = tmp2[1];
  tmp22[2] = tmp2[2];
  tmp22[3] = g*(tmp2[3]+v*tmp2[0]);
  //  cout<<"tmp22 is: "<<Mag(tmp22)<<endl;
  // Need More Consideration;
  p1[0]= tmp11[0];
  p1[1]= cos(-theta)*cos(-phi)*tmp11[1]-sin(-phi)*tmp11[2]-cos(-phi)*sin(-theta)*tmp11[3]; 
  p1[2]= cos(-theta)*sin(-phi)*tmp11[1]+cos(-phi)*tmp11[2]-sin(-theta)*sin(-phi)*tmp11[3];
  p1[3]= sin(-theta)*tmp11[1]+cos(-theta)*tmp11[3];
  p2[0]= tmp22[0];
  p2[1]= cos(-theta)*cos(-phi)*tmp22[1]-sin(-phi)*tmp22[2]-cos(-phi)*sin(-theta)*tmp22[3]; 
  p2[2]= cos(-theta)*sin(-phi)*tmp22[1]+cos(-phi)*tmp22[2]-sin(-theta)*sin(-phi)*tmp22[3];
  p2[3]= sin(-theta)*tmp22[1]+cos(-theta)*tmp22[3];
  /*  for(Int_t j=0;j<4;j++)
      {
      cout<<j<<" component of 1 is "<<p1[j]<<endl;
      cout<<j<<" component of 2 is "<<p2[j]<<endl;
      }
      cout<<"Invariant mass of 1 is: "<<Mag(p1)<<endl;
      cout<<"Invariant mass of 2 is: "<<Mag(p2)<<endl;
   */
}
void decay3(fvec p1,fvec p2, fvec &p3, fvec &p4, fvec &p5)
{
  fvec null(0);
  null.Init();
  Double_t pr1= gRandom->Rndm();
  Double_t pr2= gRandom->Rndm();
  Double_t pr3= gRandom->Rndm();
  Double_t nr= pr1+pr2+pr3;
  Double_t r1=pr1/nr;
  Double_t r2=pr2/nr;
  Double_t r3=pr3/nr;
  fvec tmp(0);
  tmp.Init();
  Double_t Mtmp=p4.GetMass()+p5.GetMass(); 
  fvecAdd(p1,p2,tmp);
  Double_t MCoM=tmp.GetMass();
  fvec tmp2(MCoM-Mtmp);
  tmp2.Init();
  Decay(p1,null,p3,tmp);
  Decay(tmp,null,p4,p5);
}



