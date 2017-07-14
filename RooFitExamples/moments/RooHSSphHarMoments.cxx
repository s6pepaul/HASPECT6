/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "RooHSSphHarMoments.h" 
#include <RooWorkspace.h>
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "Math/SpecFunc.h"
#include "TMath.h" 

ClassImp(RooHSSphHarMoments) 

RooHSSphHarMoments::RooHSSphHarMoments(const char *name, const char *title,RooAbsReal& _Z, RooAbsReal& _Phi,Int_t _Lmax,Int_t _Mmax) :
RooHSAbsEventsPDF(name,title),
  Z("Z","Z",this,_Z),
  Phi("Phi","Phi",this,_Phi),
  Lmax(_Lmax),
  Mmax(_Mmax)
{
  MakeSets();
  Z.SetName(_Z.GetName());
  Phi.SetName(_Phi.GetName());
  //Lmax.SetName(_Lmax.GetName());
 }
RooHSSphHarMoments::~RooHSSphHarMoments(){
  for(UInt_t ip=0;ip<fParSet.size();ip++){
    //RooRealVar* var=dynamic_cast<RooRealVar*>(fMoms.at(ip));
    RooRealProxy *prox=fParSet[ip];
    if(fMoms.find(prox->GetName())) delete prox;
  }
  
}
RooHSSphHarMoments::RooHSSphHarMoments(const char *name, const char *title,RooAbsReal& _Z, RooAbsReal& _Phi,Int_t _Lmax,Int_t _Mmax,const RooArgList& coefList) :
  RooHSAbsEventsPDF(name,title),
  Z("Z","Z",this,_Z),
  Phi("Phi","Phi",this,_Phi),
  fMoms("moments","List of moments",this),
  Lmax(_Lmax),
  Mmax(_Mmax)
{ 
  TIterator* coefIter = coefList.createIterator() ;
  RooAbsArg* coef ;
  while((coef = (RooAbsArg*)coefIter->Next())) {
    if (!dynamic_cast<RooAbsReal*>(coef)) {
      std::cerr << "RooHSSphHarMoments::ctor(" << GetName() <<
	") ERROR: coefficient " << coef->GetName() <<
	" is not of type RooAbsReal" << std::endl ;
      R__ASSERT(0) ;
    }
    fMoms.add(*coef) ;
  }
  
  delete coefIter ;

  MakeSets();
  Z.SetName(_Z.GetName());
  Phi.SetName(_Phi.GetName());
  //Lmax.SetName(_Lmax.GetName());
  // CreateSpHarmonic(pars,_Z,_Phi);
  //fYSet=(RooArgSet*)pars.clone(pars.GetName());
  
  // for(Int_t iL=0;iL<=Lmax;iL++)
  //   for(Int_t iM=-iL;iM<=iL;iM++){
  //     RooRealVar* var=(RooRealVar*)fYSet->find(Form("MomY_%d_%d",iL,iM));
  //     fMoms.push_back(RooRealProxy( var->GetName(),var->GetName(),this,*var));
  //   }
  
  

}
//void RooHSSphHarMoments::CreateSpHarmonic(RooArgSet pars,RooAbsReal& _Z, RooAbsReal& _Phi){

RooHSSphHarMoments::RooHSSphHarMoments(const RooHSSphHarMoments& other, const char* name) :  
   RooHSAbsEventsPDF(other,name),
   Z("Z",this,other.Z),
   Phi("Phi",this,other.Phi),
   fMoms("moments",this,other.fMoms),
   Lmax(other.Lmax),
   Mmax(other.Mmax)
 {
   cout<<"CLONE "<<endl;
   MakeSets();
   Z.SetName(other.Z.GetName());
   Phi.SetName(other.Phi.GetName());
  
   // for(UInt_t iY=0;iY<other.fMoms.size();iY++)
   //   fMoms.push_back(RooRealProxy(other.fMoms[iY].GetName(),this,other.fMoms[iY]));
  // fYSet=(RooArgSet*)other.fYSet->clone(other.fYSet->GetName());
  // for(Int_t iL=0;iL<=Lmax;iL++)
  //   for(Int_t iM=-iL;iM<=iL;iM++){
  //     RooRealVar* var=(RooRealVar*)fYSet->find(Form("MomY_%d_%d",iL,iM));
  //     fMoms.push_back(RooRealProxy( var->GetName(),var->GetName(),this,*var));
  //   }

     
   if(fEvTree) SetEvTree(fEvTree);//Needs fProxSet filled first
 } 
RooArgSet RooHSSphHarMoments::CreateMoments(Int_t _lmax,Int_t _Mmax){
  RooArgSet parSet("MomY");
  //L=0 +ve
  Double_t N00=1.; //normalises integral = 1
  //  Double_t N00=1./sqrt(4*TMath::Pi()); //normalises integral = 1
  RooRealVar* Y00=new RooRealVar(Form("MomY_%d_%d",0,0),Form("MomY_%d_%d",0,0),N00,0,N00);
  Y00->setConstant();//from eqn 27 Grayer with t0=1 in evaluate we still add Y0(Z,Phi) = const = 1/sqrt(4pi)
  parSet.add(*Y00);
  
  for(Int_t iL=1;iL<=_lmax;iL++)
    //   for(Int_t iM=-iL;iM<=iL;iM++){
    for(Int_t iM=0;iM<=iL;iM++){
      if(iM>_Mmax)continue;
      //Set range : MomYLM*YLM<MomY00*Y00
      Double_t NLM=evalN(iL,iM)*TMath::Factorial(iL+iM)/TMath::Power(2,iL)/TMath::Factorial(iL); //SH*Legendre coefficients.
      NLM=N00/NLM;
      parSet.add(*(new RooRealVar(Form("MomY_%d_%d",iL,iM),Form("MomY_%d_%d",iL,iM),-NLM,NLM)));
      //parSet.add(*(new RooRealVar(Form("MomY_%d_%d",iL,iM),Form("MomY_%d_%d",iL,iM),-1,1)));
    }
  return parSet;
}

void RooHSSphHarMoments::MakeSets(){
   fProxSet.push_back(&Z);
   fProxSet.push_back(&Phi);
   for(Int_t ip=0;ip<fMoms.getSize();ip++){
     RooRealVar* var=dynamic_cast<RooRealVar*>(fMoms.at(ip));
     fParSet.push_back(new RooRealProxy(var->GetName(),var->GetName(),this,*var));
   }
   //   fParSet.push_back(&Lmax);
   InitSets();
}
Double_t RooHSSphHarMoments::evalN(Int_t _L,Int_t _M) {
  Double_t n = sqrt( double(2*_L+1)/(4*TMath::Pi())*TMath::Factorial(_L-(_M))/TMath::Factorial(_L+(_M)) );
  return n;
  //Double_t n = sqrt( 1./(4*TMath::Pi()));
  //cout<<" N "<<n<<endl;
  //  return _M==0 ? n : TMath::Sqrt2() * n; //real form of SphHar
  // return _M==0 ? n : 0.5 * n; //standard complex form
}
Double_t RooHSSphHarMoments::evalRealSphHarmonic(Double_t _Z,Double_t _Phi,Int_t _L,Int_t _M) const{
  //return real part of spherical harmonic
  //Double_t val =evalLegendre(_Z,_L,_M);//I think evalN is done in assoc_legendre
  Double_t val =evalN(_L,_M)*evalLegendre(_Z,_L,_M);//I think evalN is done in assoc_legendre
  //Double_t val =evalLegendre(_Z,_L,_M);
  if(_M!=0) val *= cos(_M*_Phi) ;
  // if(_M%2==1)val*=-1; //(-1)^M phase factor inc in assoc_legendre
  //  if(_M!=0) val *= (_M<0 ? sin(TMath::Abs(_M)*_Phi) : cos(TMath::Abs(_M)*_Phi) ); //real Sphar
  // cout<<" SH "<<val<<endl;
  return val;
}
Double_t RooHSSphHarMoments::evalLegendre(Double_t _Z,Int_t _L,Int_t _M) const{
#ifdef R__HAS_MATHMORE
  Double_t r = 1;
  Double_t ctheta = std::max(-1., std::min((double)_Z, +1.));
  //note returns from gsl sqrt((2l+1)/(4pi)) sqrt((l-m)!/(l+m)!) P_l^m(x)
  //RooSpHarmonic also multiplies by this factor, seems to be done twice...
  r *= ROOT::Math::assoc_legendre(_L,(_M),ctheta);
  // cout<<" Leg "<<r<<endl;
  return r;
#else
  throw std::string("RooLegendre: ERROR: This class require installation of the MathMore library") ;
  return 0 ;
#endif
}
 Double_t RooHSSphHarMoments::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE
   Double_t val=0;
   Int_t iY=0;
   for(Int_t iL=0;iL<=Lmax;iL++)
     for(Int_t iM=0;iM<=iL;iM++){
       if(iM>Mmax) continue;
       //     for(Int_t iM=-iL;iM<=iL;iM++){
       Double_t YLM=((RooAbsReal&)fMoms[iY++]).getVal();
       //  cout<<"L M "<<iL<<" "<<iM<<" "<<YLM<<" "<<evalRealSphHarmonic(Z,Phi,iL,iM)<<endl;
       val+= YLM*evalRealSphHarmonic(Z,Phi,iL,iM);
     }
   //cout<<Z<<" "<<Phi<<" "<<val<<endl;
   return val;
 }

Double_t RooHSSphHarMoments::evaluateMC() const {
// ENTER IDENTICAL EXPRESSION TO evaluate() IN TERMS OF MC VARIABLE ARGUMENTS HERE
  Double_t mcZ=fMCVar.at(0);
  Double_t mcPhi=fMCVar.at(1);
  Double_t val=0;
   Int_t iY=0;
   for(Int_t iL=0;iL<=Lmax;iL++)
     for(Int_t iM=0;iM<=iL;iM++){
       if(iM>Mmax) continue;
       //     for(Int_t iM=-iL;iM<=iL;iM++){
       Double_t YLM=((RooAbsReal&)fMoms[iY++]).getVal();
       //  cout<<"L M "<<iL<<" "<<iM<<" "<<YLM<<" "<<evalRealSphHarmonic(Z,Phi,iL,iM)<<endl;
       val+= YLM*evalRealSphHarmonic(mcZ,mcPhi,iL,iM);
     }
   //  cout<<mcZ<<" "<<mcPhi<<" "<<val<<endl;
   return val;
 
}


// Int_t RooHSSphHarMoments::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars,const char* rangeName) const
// {
//   return 0; 
// }
// Double_t RooHSSphHarMoments::analyticalIntegral(Int_t code,const char* rangeName) const
// {
//   return 1;
// }
