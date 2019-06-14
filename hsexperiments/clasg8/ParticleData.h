////////////////////////////////////////////////////////////////
///     CLAS G8 EXPERIMENT
///Class:               ParticleData
///Description:
///            A derived class to be used as tree branches !
///            This class has to be defined for each experiment
///            It will be linked to the experiment THSParticle
///            Construct with e.g. ParticleData("Proton",&fProton);
///
#ifndef PARTICLEDATA_h
#define PARTICLEDATA_h 
#include "BaseParticleData.h"
#include "FiledTree.h"
#include "THSParticle.h"
#include <TMath.h>

namespace HS{

  class ParticleData: public BaseParticleData{

  public:
    /////////////////////////////////////////////////
    /// data member for tree branches below here
    /// Experiment developers add your own data members
    /// if you want them in the tree
    /// then assign them in  ParticleData::FillData()
    Float_t P=0;
    Float_t Theta=0;
    Float_t Phi=0;
    Float_t Time=0;
    //Float_t Edep=0;
    Float_t DeltaE=0;
    Float_t Vz=0;
    /////////////////////////////////////////////////
 
    ParticleData()=default;
    ParticleData(TString name,HS::THSParticle* p)
      : BaseParticleData(name,p){};
    ParticleData(const ParticleData&)=default;
    ParticleData(ParticleData&&)=default;
    virtual ~ParticleData()=default;

    void FillData() final;

    //Function required to set tree branches
    //This should not need changed
    void Branches(HS::ttree_ptr tree) final{
      TreeData::Branches(tree,Class()->GetListOfDataMembers());
    }
    
 
  private:
    
    ClassDefOverride(ParticleData,1);

  };//class ParticleData

  ////////////////////////////////////////////////////
  /// Fill in the data from the THSParticle functions
  /// Experiment developers fill your own data members here....
  inline void ParticleData::FillData(){
    auto r2d=TMath::RadToDeg();
 
    P     =  fParticle->P4p()->P();
    Theta =  fParticle->P4p()->Theta()*r2d;
    Phi   =  fParticle->P4p()->Phi()*r2d;
    Time  =  fParticle->DeltaTime();
    //Edep  =  fParticle->Edep();
    DeltaE=  fParticle->DeltaE();
    Vz    =  fParticle->Vertex().Z();

  }
}//namespace HS
#endif
