//
//
/*
    Copyright (C) 2003- 2007, Hammersmith Imanet Ltd
    This file is part of STIR.

    SPDX-License-Identifier: Apache-2.0

    See STIR/LICENSE.txt for details
*/
/*!

  \file
  \ingroup symmetries

  \brief Declaration of class stir::TrivialDataSymmetriesForBins

  \author Kris Thielemans

*/
#ifndef __stir_recon_buildblock_TrivialDataSymmetriesForBins_H__
#define __stir_recon_buildblock_TrivialDataSymmetriesForBins_H__

#include "stir/recon_buildblock/DataSymmetriesForBins.h"

START_NAMESPACE_STIR


/*!
  \ingroup symmetries
  \brief A class derived from DataSymmetriesForBins that says that there are
  no symmetries at all.

*/
class TrivialDataSymmetriesForBins : public DataSymmetriesForBins
{
public:
  TrivialDataSymmetriesForBins(const shared_ptr<const ProjDataInfo>& proj_data_info_ptr);

  virtual 
#ifndef STIR_NO_COVARIANT_RETURN_TYPES
    TrivialDataSymmetriesForBins 
#else
    DataSymmetriesForViewSegmentNumbers
#endif
    * clone() const;

  virtual void
    get_related_bins(std::vector<Bin>&, const Bin& b,
                      const int min_axial_pos_num, const int max_axial_pos_num,
                      const int min_tangential_pos_num, const int max_tangential_pos_num,
					  const int min_timing_pos_num = 0, const int max_timing_pos_num = 0) const;

  virtual void
    get_related_bins_factorised(std::vector<AxTangPosNumbers>&, const Bin& b,
                                const int min_axial_pos_num, const int max_axial_pos_num,
                                const int min_tangential_pos_num, const int max_tangential_pos_num) const;

  virtual int
    num_related_bins(const Bin& b) const;

  virtual unique_ptr<SymmetryOperation>
    find_symmetry_operation_from_basic_bin(Bin&) const;

  virtual bool
    find_basic_bin(Bin& b) const;

  virtual bool
    is_basic(const Bin& v_s) const;

  virtual unique_ptr<SymmetryOperation>
    find_symmetry_operation_from_basic_view_segment_numbers(ViewSegmentNumbers&) const;

  virtual void
    get_related_view_segment_numbers(std::vector<ViewSegmentNumbers>&, const ViewSegmentNumbers&) const;

  virtual int
    num_related_view_segment_numbers(const ViewSegmentNumbers&) const;
  virtual bool
    find_basic_view_segment_numbers(ViewSegmentNumbers&) const;

private:
  virtual bool blindly_equals(const root_type * const) const;
};

END_NAMESPACE_STIR


#endif

