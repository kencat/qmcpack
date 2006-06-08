//////////////////////////////////////////////////////////////////
// (c) Copyright 2003-  by Jeongnim Kim
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//   National Center for Supercomputing Applications &
//   Materials Computation Center
//   University of Illinois, Urbana-Champaign
//   Urbana, IL 61801
//   e-mail: jnkim@ncsa.uiuc.edu
//   Tel:    217-244-6319 (NCSA) 217-333-3324 (MCC)
//
// Supported by 
//   National Center for Supercomputing Applications, UIUC
//   Materials Computation Center, UIUC
//////////////////////////////////////////////////////////////////
// -*- C++ -*-
#ifndef QMCPLUSPLUS_LR_RPAJASTROW_H
#define QMCPLUSPLUS_LR_RPAJASTROW_H

#include "QMCWaveFunctions/OrbitalBase.h"
#include "Optimize/VarList.h"
#include "OhmmsData/libxmldefs.h"
#include "OhmmsPETE/OhmmsVector.h"
#include "OhmmsPETE/OhmmsMatrix.h"

namespace qmcplusplus {

  class LRTwoBodyJastrow: public  OrbitalBase {
    
    IndexType NumPtcls;
    IndexType NumSpecies;
    IndexType NumKpts;
    ///Omega 
    RealType Omega;
    ///4*pi*Omega 
    RealType FourPiOmega;
    ///1.0/Omega 
    RealType OneOverOmega;
    ///Rs 
    RealType Rs;
    ValueType curVal, curLap;
    GradType curGrad;
    ValueVectorType U,d2U;
    GradVectorType dU;
    Matrix<ComplexType> rokbyF;
    Vector<ComplexType> Rhok;

    const StructFact* skRef;
  public:

    ///Coefficients
    Vector<RealType> Fk; 

    LRTwoBodyJastrow(ParticleSet& p);

    void reset();
    void resize();

    //evaluate the distance table with els
    void resetTargetParticleSet(ParticleSet& P);

    ValueType evaluateLog(ParticleSet& P,
		         ParticleSet::ParticleGradient_t& G, 
		         ParticleSet::ParticleLaplacian_t& L);

    inline ValueType evaluate(ParticleSet& P,
			      ParticleSet::ParticleGradient_t& G, 
			      ParticleSet::ParticleLaplacian_t& L) {
      return std::exp(evaluateLog(P,G,L));
    }


    ValueType ratio(ParticleSet& P, int iat);

    ValueType ratio(ParticleSet& P, int iat,
		    ParticleSet::ParticleGradient_t& dG,
		    ParticleSet::ParticleLaplacian_t& dL)  {
      return std::exp(logRatio(P,iat,dG,dL));
    }

    ValueType logRatio(ParticleSet& P, int iat,
		    ParticleSet::ParticleGradient_t& dG,
		    ParticleSet::ParticleLaplacian_t& dL);

    void restore(int iat);
    void acceptMove(ParticleSet& P, int iat);
    void update(ParticleSet& P, 
		ParticleSet::ParticleGradient_t& dG, 
		ParticleSet::ParticleLaplacian_t& dL,
		int iat);


    ValueType registerData(ParticleSet& P, PooledData<RealType>& buf);
    ValueType updateBuffer(ParticleSet& P, PooledData<RealType>& buf);
    void copyFromBuffer(ParticleSet& P, PooledData<RealType>& buf);
    ValueType evaluate(ParticleSet& P, PooledData<RealType>& buf);

    ///process input file
    bool put(xmlNodePtr cur, VarRegistry<RealType>& vlist);

    inline RealType getRPACoeff(RealType ksq) {
      return FourPiOmega*(1.0/ksq-1.0/(ksq+OneOverOmega));
    }

  };
}
#endif
/***************************************************************************
 * $RCSfile$   $Author$
 * $Revision$   $Date$
 * $Id$ 
 ***************************************************************************/
