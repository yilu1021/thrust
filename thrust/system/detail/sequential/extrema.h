/*
 *  Copyright 2008-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*! \file extrema.h
 *  \brief Sequential implementations of extrema functions.
 */

#pragma once

#include <thrust/detail/config.h>
#include <thrust/pair.h>
#include <thrust/detail/function.h>
#include <thrust/system/detail/sequential/tag.h>

namespace thrust
{
namespace system
{
namespace detail
{
namespace sequential
{


template<typename ForwardIterator,
         typename BinaryPredicate>
__host__ __device__
ForwardIterator min_element(tag,
                            ForwardIterator first, 
                            ForwardIterator last,
                            BinaryPredicate comp)
{
  // wrap comp
  thrust::detail::host_device_function<
    BinaryPredicate,
    bool
  > wrapped_comp(comp);

  ForwardIterator imin = first;

  for(; first != last; first++)
  {
    if(wrapped_comp(*first, *imin))
    {
      imin = first;
    }
  }

  return imin;
}


template<typename ForwardIterator,
         typename BinaryPredicate>
ForwardIterator max_element(tag,
                            ForwardIterator first, 
                            ForwardIterator last,
                            BinaryPredicate comp)
{
  // wrap comp
  thrust::detail::host_device_function<
    BinaryPredicate,
    bool
  > wrapped_comp(comp);

  ForwardIterator imax = first;

  for(; first != last; first++)
  {
    if(wrapped_comp(*imax, *first))
    {
      imax = first;
    }
  }

  return imax;
}


template<typename ForwardIterator,
         typename BinaryPredicate>
__host__ __device__
thrust::pair<ForwardIterator,ForwardIterator> minmax_element(tag,
                                                             ForwardIterator first, 
                                                             ForwardIterator last,
                                                             BinaryPredicate comp)
{
  // wrap comp
  thrust::detail::host_device_function<
    BinaryPredicate,
    bool
  > wrapped_comp(comp);
  
  ForwardIterator imin = first;
  ForwardIterator imax = first;

  for(; first != last; first++)
  {
    if(wrapped_comp(*first, *imin))
    {
      imin = first;
    }

    if(wrapped_comp(*imax, *first))
    {
      imax = first;
    }
  }

  return thrust::make_pair(imin, imax);
}


} // end namespace sequential
} // end namespace detail
} // end namespace system
} // end namespace thrust

