/*
  Copyright (C) 2000-2007, Hammersmith Imanet Ltd
  Copyright (C) 2013-2014 University College London

  Largely a copy of the ECAT7 version. 

  SPDX-License-Identifier: Apache-2.0

  See STIR/LICENSE.txt for details
*/
/*!
  \file
  \ingroup recon_buildblock

  \brief Declaration of class stir::ecat::BinNormalisationFromECAT8

  \author Kris Thielemans
*/


#ifndef __stir_recon_buildblock_BinNormalisationFromECAT8_H__
#define __stir_recon_buildblock_BinNormalisationFromECAT8_H__

#include "stir/recon_buildblock/BinNormalisation.h"
#include "stir/recon_buildblock/BinNormalisationWithCalibration.h"
#include "stir/RegisteredParsingObject.h"
#include "stir/ProjData.h"
#include "stir/shared_ptr.h"
#include "stir/ProjDataInfoCylindricalNoArcCorr.h"
#include "stir/data/SinglesRates.h"
#include "stir/Scanner.h"
#include "stir/Array.h"
#include "stir/IO/stir_ecat_common.h"
#include <string>

#ifndef STIR_NO_NAMESPACE
using std::string;
#endif

START_NAMESPACE_STIR
START_NAMESPACE_ECAT

/*!
  \ingroup recon_buildblock
  \ingroup ECAT
  \brief A BinNormalisation class that gets the normalisation factors from
  an ECAT8 3D normalisation file. Note that you have to point it to the
  "Interfile" header.

  \par Parsing example
  \verbatim
  Bin Normalisation type := from ecat7
  Bin Normalisation From ECAT8:=
  normalisation filename:= myfile.hn

  ; next keywords can be used to switch off some of the normalisation components
  ; do not use unless you know why
  ; use_gaps:=1
  ; use_detector_efficiencies:=1
  ; use_dead_time:=1
  ; use_geometric_factors:=1
  ; use_crystal_interference_factors:=1
  End Bin Normalisation From ECAT8:=
  \endverbatim

  \todo dead-time is not yet implemented

 
*/
class BinNormalisationFromECAT8 :
   public RegisteredParsingObject<BinNormalisationFromECAT8, BinNormalisation, BinNormalisationWithCalibration>
{
private:
  using base_type = BinNormalisationWithCalibration;
public:
  //! Name which will be used when parsing a BinNormalisation object
  static const char * const registered_name; 
  
  //! Default constructor
  /*! 
    \warning You should not call any member functions for any object just 
    constructed with this constructor. Initialise the object properly first
    by parsing.
  */
  BinNormalisationFromECAT8();

  //! Constructor that reads the projdata from a file
  BinNormalisationFromECAT8(const string& filename);

  virtual Succeeded set_up(const shared_ptr<const ExamInfo>& exam_info_sptr, const shared_ptr<const ProjDataInfo>& ) override;
  float get_uncalibrated_bin_efficiency(const Bin& bin) const override;

  bool use_detector_efficiencies() const;
  bool use_dead_time() const;
  bool use_geometric_factors() const;
  bool use_crystal_interference_factors() const;

private:
  Array<1,float> axial_t1_array;
  Array<1,float> axial_t2_array;
  Array<1,float> trans_t1_array;
  shared_ptr<SinglesRates> singles_rates_ptr;
  Array<2,float> geometric_factors;
  Array<2,float> efficiency_factors;
  Array<2,float> crystal_interference_factors;
  shared_ptr<Scanner> scanner_ptr;
  int num_transaxial_crystals_per_block;
  // TODO move to Scanner
  int num_axial_blocks_per_singles_unit;
  shared_ptr<const ProjDataInfo> proj_data_info_ptr;
  ProjDataInfoCylindricalNoArcCorr const * proj_data_info_cyl_ptr;
  shared_ptr<const ProjDataInfoCylindricalNoArcCorr> proj_data_info_cyl_uncompressed_ptr;
  int span;
  int mash;
  int num_blocks_per_singles_unit;
  float calib_factor, cross_calib_factor;

  bool _use_gaps;
  bool _use_detector_efficiencies;
  bool _use_dead_time;
  bool _use_geometric_factors;
  bool _use_crystal_interference_factors;

  void read_norm_data(const string& filename);
  float get_dead_time_efficiency ( const DetectionPosition<>& det_pos,
				  const double start_time, const double end_time) const;

  // parsing stuff
  virtual void set_defaults() override;
  virtual void initialise_keymap() override;
  virtual bool post_processing() override;

  string normalisation_ECAT8_filename;
};

END_NAMESPACE_ECAT
END_NAMESPACE_STIR

#endif
