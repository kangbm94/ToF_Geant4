#define PI 3.141593
class fvec{
  private:
    Double_t p[4]={0};
    Double_t m;
    Double_t gamma(Double_t v){
      return 1/sqrt(1-v*v);
    }
  public:
    fvec(Double_t tmp){
      m=tmp;
    }
    void SetMass(Double_t tmp){
      m = tmp;
    }  
    void Init(){
      p[0]=m;
      for(int i=1;i<4;i++){
        p[i]= 0;
      }
    }
    void SetMomentum(Double_t tmp1,Double_t tmp2,Double_t tmp3){
      p[1]=tmp1;
      p[2]=tmp2;
      p[3]=tmp3;
      p[0]=sqrt(m*m+p[1]*p[1]+p[2]*p[2]+p[3]*p[3]);
    }
    void SetComponent(int i,Double_t tmp){
      p[i]=tmp;
    }
    Double_t GetMomentum(){
      return sqrt(p[1]*p[1]+p[2]*p[2]+p[3]*p[3]);
    }
    Double_t GetMass(){
      return sqrt(p[0]*p[0]-(p[1]*p[1]+p[2]*p[2]+p[3]*p[3]));
    }
    Double_t GetComponent(Int_t i){
      return p[i];
    }
    Double_t GetVelocityComponent(Int_t i)
    {
      return p[i]/p[0];
    } 
    Double_t GetBeta()
    {
      return sqrt(p[1]*p[1]+p[2]*p[2]+p[3]*p[3])/p[0];
    } 
    Double_t GetGamma()
    {
      return gamma(GetBeta()); 
    }
};
void fvecAdd(fvec p1,fvec p2,fvec &p3)
{ 
  for(int i=0;i<4;i++){
    Double_t tmp;
    tmp=p1.GetComponent(i)+p2.GetComponent(i);
    p3.SetComponent(i,tmp);
    //    cout<<"p3 is: "<<p3.GetComponent(i)<<endl;
  }
}
void GenRdmSphere(Double_t x, Double_t y, Double_t z)
{
	gRandom->SetSeed();
}
void Decay(fvec p1,fvec p2, fvec &p3,fvec &p4)
{
  fvec p12(0);
  p12.Init();
  fvecAdd(p1,p2,p12);
  Double_t v1[4]={0};
  Double_t tmp1[4]={0};
  Double_t tmp11[4]={0};
  Double_t v2[4]={0};
  Double_t tmp2[4]={0};
  Double_t tmp22[4]={0};
  Double_t m3= p3.GetMass();
  Double_t m4= p4.GetMass();
//  cout<<"m3 and m4 is "<<m3<<" and "<<m4<<endl;
  Double_t M = p12.GetMass();
//  cout<<"m1 is "<<p1.GetMass()<<" m2 is "<<p2.GetMass()<<endl;
//  cout<<"M is "<<M<<endl;
  Double_t v = p12.GetBeta();//Velocity of CoM at LAB frame.
  Double_t g = p12.GetGamma();
  Double_t vx = p12.GetComponent(1)/(g*M);
  Double_t vy = p12.GetComponent(2)/(g*M);
  Double_t vz = p12.GetComponent(3)/(g*M);
  Double_t phi=0;
  Double_t theta=0;
  if(v!=0)
  {
    theta = acos(vz/v);
    if(theta==0)
    {
      phi=0;
    }
    else
    {
      if(vy>0)
      {
        phi = -acos(vx/(v*sin(theta))); 
      }
      else
      {
        phi =-(2*PI -acos(vx/(v*sin(theta)))); 
      }
    }
  }
  //  cout<<"phi is: "<<phi<<endl;
  Double_t r1= gRandom->Rndm();
  Double_t r2= gRandom->Rndm();
  //  Double_t r1 = 0;
  //  Double_t r2 = 0;
  tmp1[0]=(M*M+m3*m3-m4*m4)/(2*M);
  tmp2[0]=(M*M+m4*m4-m3*m3)/(2*M);
  Double_t p = sqrt((M-m3-m4)*(M-m3+m4)*(M+m3-m4)*(M+m3+m4))/(2*M);
  tmp1[1] = p*sin(PI*r1)*cos(2*PI*r2);
  tmp2[1]=-tmp1[1];
  tmp1[2] = p*sin(PI*r1)*sin(2*PI*r2);
  tmp2[2]=-tmp1[2];
  tmp1[3] = p*cos(PI*r1);
  tmp2[3]=-tmp1[3];
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
  p3.SetComponent(0,tmp11[0]);
  p3.SetComponent(1,cos(-theta)*cos(-phi)*tmp11[1]-sin(-phi)*tmp11[2]-cos(-phi)*sin(-theta)*tmp11[3]); 
  p3.SetComponent(2,cos(-theta)*sin(-phi)*tmp11[1]+cos(-phi)*tmp11[2]-sin(-theta)*sin(-phi)*tmp11[3]);
  p3.SetComponent(3,sin(-theta)*tmp11[1]+cos(-theta)*tmp11[3]);
  p4.SetComponent(0,tmp22[0]);
  p4.SetComponent(1,cos(-theta)*cos(-phi)*tmp22[1]-sin(-phi)*tmp22[2]-cos(-phi)*sin(-theta)*tmp22[3]); 
  p4.SetComponent(2,cos(-theta)*sin(-phi)*tmp22[1]+cos(-phi)*tmp22[2]-sin(-theta)*sin(-phi)*tmp22[3]);
  p4.SetComponent(3,sin(-theta)*tmp22[1]+cos(-theta)*tmp22[3]);
}
void Decay3(fvec p1,fvec p2, fvec &p3, fvec &p4, fvec &p5)
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
  fvecAdd(p1,p2,tmp);
  Double_t MCoM=tmp.GetMass();
  Double_t Mtmp=r1*(p4.GetMass()+p5.GetMass())+(MCoM-p3.GetMass())*(1-r1);//The physics.
  fvec tmp2(Mtmp);
  tmp2.Init();
  Decay(p1,null,p3,tmp2);
  null.Init();
  Decay(tmp2,null,p4,p5);
  fvec tmp3(0);
  fvecAdd(p4,p5,tmp3);
  fvec tmp4(0);
  tmp4.Init();
  fvecAdd(p3,tmp3,tmp4);
  }



