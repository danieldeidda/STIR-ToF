//
//
/*!

  \file
  \ingroup projdata

  \brief Inline implementations of class stir::Viewgram

  \author Sanida Mustafovic
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

#include "stir/IndexRange2D.h"

START_NAMESPACE_STIR

template <typename elemT>
int
Viewgram<elemT>::get_segment_num() const
{ return segment_num; }

template <typename elemT>
int
Viewgram<elemT>::get_view_num() const
{ return view_num; }

template <typename elemT>
int
Viewgram<elemT>::get_timing_pos_num() const
{ return timing_pos_num; }

template <typename elemT>
int
Viewgram<elemT>::get_min_axial_pos_num() const
  {return this->get_min_index();}

template <typename elemT>
int
Viewgram<elemT>::get_max_axial_pos_num() const
  { return this->get_max_index(); }

template <typename elemT>
int
Viewgram<elemT>::get_num_axial_poss() const
  { return this->get_length();}


template <typename elemT>
int
Viewgram<elemT>::get_num_tangential_poss() const
  { return this->get_length()==0 ? 0 : (*this)[get_min_axial_pos_num()].get_length();}


template <typename elemT>
int
Viewgram<elemT>::get_min_tangential_pos_num() const
  { return this->get_length()==0 ? 0 :(*this)[get_min_axial_pos_num()].get_min_index();}

template <typename elemT>
int
Viewgram<elemT>::get_max_tangential_pos_num() const
{ return this->get_length()==0 ? 0 :(*this)[get_min_axial_pos_num()].get_max_index(); }


template <typename elemT>
Viewgram<elemT>
Viewgram<elemT>::get_empty_copy(void) const
{
    Viewgram<elemT> copy(proj_data_info_sptr, get_view_num(), get_segment_num(), get_timing_pos_num());
    return copy;
}

template <typename elemT>
shared_ptr<const ProjDataInfo>
Viewgram<elemT>::get_proj_data_info_sptr() const
{
  return proj_data_info_sptr;
}


template <typename elemT>
Viewgram<elemT>::
Viewgram(const Array<2,elemT>& p, 
     const shared_ptr<const ProjDataInfo>& pdi_sptr,
	 const int v_num, const int s_num, const int t_num) 
  :
  Array<2,elemT>(p), proj_data_info_sptr(pdi_sptr),
  view_num(v_num), segment_num(s_num), timing_pos_num(t_num)
{
  assert(view_num <= proj_data_info_sptr->get_max_view_num());
  assert(view_num >= proj_data_info_sptr->get_min_view_num());
  // segment_num is already checked by doing get_max_axial_pos_num(s_num)

  assert( get_min_axial_pos_num() == pdi_sptr->get_min_axial_pos_num(s_num));
  assert( get_max_axial_pos_num() == pdi_sptr->get_max_axial_pos_num(s_num));
  assert( get_min_tangential_pos_num() == pdi_sptr->get_min_tangential_pos_num());
  assert( get_max_tangential_pos_num() == pdi_sptr->get_max_tangential_pos_num());
}

template <typename elemT>
Viewgram<elemT>::
Viewgram(const shared_ptr<const ProjDataInfo>& pdi_sptr, 
	 const int v_num, const int s_num, const int t_num) 
  : 
  Array<2,elemT>(IndexRange2D (pdi_sptr->get_min_axial_pos_num(s_num),
			       pdi_sptr->get_max_axial_pos_num(s_num),
			       pdi_sptr->get_min_tangential_pos_num(),
			       pdi_sptr->get_max_tangential_pos_num())),
  proj_data_info_sptr(pdi_sptr),
  view_num(v_num),
  segment_num(s_num),
  timing_pos_num(t_num)
{
  assert(view_num <= proj_data_info_sptr->get_max_view_num());
  assert(view_num >= proj_data_info_sptr->get_min_view_num());
  // segment_num is already checked by doing get_max_axial_pos_num(s_num)
}


END_NAMESPACE_STIR
