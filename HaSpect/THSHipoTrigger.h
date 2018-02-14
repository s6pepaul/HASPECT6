//Datareader class for converting Lund format txt files
//into THSParticles
#ifndef THSHIPOTRIGGER_h
#define THSHIPOTRIGGER_h

#include "THSHipoReader.h"

class THSHipoTrigger: public THSHipoReader{

 public :
  THSHipoTrigger();
  virtual ~THSHipoTrigger(){};

  //  virtual Bool_t Init(TString filename,TString name="");
  virtual Bool_t ReadEvent(Long64_t entry=0);
  virtual void InitOutput(TString filename);
  virtual Bool_t Init(TString filename,TString name);
  virtual void PostWrite();

  
  void SetSoftFTTrig(Int_t trig){fSoftFTTrig=trig;}
  Int_t GetSoftFTTrig(){return fSoftFTTrig;}
 private :

  //banks
  THipoBank* fRunConBank=nullptr;
  //  THipoBank* fRecEvBank=nullptr;

  //items in banks
  THipoItem* fRunTrig=nullptr;
  //THipoItem* fEvSTTime=nullptr;
  THipoItem* fRecEvNRun=nullptr;
  THipoItem* fRecEvNEVENT=nullptr;
  THipoItem* fRecEvTYPE=nullptr;
  THipoItem* fRecEvTRG=nullptr;
  THipoItem* fRecEvHelic=nullptr;
  THipoItem* fRecEvEVNTime=nullptr;
  THipoItem* fRecEvBCG=nullptr;
  THipoItem* fRecEvLT=nullptr;
  //  THipoItem* fRecEvSTTime=nullptr;
  THipoItem* fRecEvRFTime=nullptr;
  THipoItem* fRecEvPTIME=nullptr;
   //Trigger variables
  Int_t fSoftFTTrig=0;
  Int_t fFTHigh=0; 
  Int_t fFTLow=0;

  Int_t fNRun=0;//Run Number
  Int_t fNEvent=0;;//Event Number
  Float_t fEventTime=0;;//Event Time
  Int_t fType=0;;//Event Type (Data or MC)
  Int_t fTrig=0;;//Trigger Type (CLAS12_e-, FT_CLAS12_h,CLAS12_H,...) + Prescale Factor for that Trigger"}
 Float_t fBCG=0;;//Faraday Cup Gated (Coulomb)
  Float_t fLT=0;;//Clock
  Float_t fSTTime=0;;//Event Start Time (ns)
  Float_t fRFTime=0;;//RF Time (ns)
  Int_t fHelic=0;;//Helicity of Event
  Float_t fPTime=0;;//Event Processing Time (UNIX Time = seconds)
  

  
  Int_t fTrigBits[sizeof(int) * 8];

   void CreateBitPattern(long val);
 public :
  
 
};

#endif //ifdef THSHIPOTRIGGER
