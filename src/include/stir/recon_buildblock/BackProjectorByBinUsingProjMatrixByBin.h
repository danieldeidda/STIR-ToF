//
//


#ifndef _BackProjectorByBinUsingProjMatrixByBin_
#define _BackProjectorByBinUsingProjMatrixByBin_

/*!

  \file

  \brief Declaration of class stir::BackprojectorByBinUsingProjMatrixByBin

  \author Mustapha Sadki
  \author Kris Thielemans
  \author PARAPET project


*/
/*
    Copyright (C) 2000 PARAPET partners
    Copyright (C) 2000- 2009, Hammersmith Imanet Ltd
    This file is part of STIR.

    SPDX-License-Identifier: Apache-2.0 AND License-ref-PARAPET-license

    See STIR/LICENSE.txt for details
*/

#include "stir/recon_buildblock/ProjMatrixByBin.h"
#include "stir/recon_buildblock/BackProjectorByBin.h"
#include "stir/RegisteredParsingObject.h"
#include "stir/shared_ptr.h"
//#include "stir/DataSymmetriesForBins.h"
//#include "stir/RelatedViewgrams.h"

class Viewgrams;
template <typename elemT> class RelatedViewgrams;
class ProjDataInfoCylindricalArcCorr;


START_NAMESPACE_STIR

/*!
  \brief This implements the BackProjectorByBin interface, given any 
ProjMatrixByBin object
    
  */
class BackProjectorByBinUsingProjMatrixByBin: 
  public RegisteredParsingObject<BackProjectorByBinUsingProjMatrixByBin,
                                 BackProjectorByBin>
{ 
public:
    //! Name which will be used when parsing a BackProjectorByBin object
  static const char * const registered_name; 

  BackProjectorByBinUsingProjMatrixByBin();

  BackProjectorByBinUsingProjMatrixByBin (  
    const shared_ptr<ProjMatrixByBin>& proj_matrix_ptr);

  //! Stores all necessary geometric info
  /*! Note that the density_info_ptr is not stored in this object. It's only used to get some info on sizes etc.
  */
  virtual void set_up(		 
    const shared_ptr<const ProjDataInfo>& proj_data_info_ptr,
    const shared_ptr<const DiscretisedDensity<3,float> >& density_info_ptr // TODO should be Info only
    );
	 
  const DataSymmetriesForViewSegmentNumbers * get_symmetries_used() const;


  virtual void actual_back_project(DiscretisedDensity<3,float>& image,
                                   const RelatedViewgrams<float>&,
		                   const int min_axial_pos_num, const int max_axial_pos_num,
		                   const int min_tangential_pos_num, const int max_tangential_pos_num);


  shared_ptr<ProjMatrixByBin> &
    get_proj_matrix_sptr(){ return proj_matrix_ptr ;} 

  void enable_tof(ProjMatrixElemsForOneBin* );

  BackProjectorByBinUsingProjMatrixByBin* clone() const;
  
protected:

  shared_ptr<ProjMatrixByBin> proj_matrix_ptr;

  void actual_back_project(DiscretisedDensity<3,float>& image,
                                   const Bin& bin);

private:
  virtual void set_defaults();
  virtual void initialise_keymap();
  virtual bool post_processing();

  ProjMatrixElemsForOneBin* tof_row;

};


 

END_NAMESPACE_STIR

//#include "stir/recon_buildblock/BackProjectorByBinUsingProjMatrixByBin.inl"

#endif


