#pragma once
#include "view_traits.hpp"
#include <tuple>
#include <type_traits>
namespace mcpputil
{
  /**
   * \brief Partition a container over some other container using a lambda.
   *
   * On every element of over container, call F(over container element, make_tuple(begin,end)).
   * Where begin and end are iterators over a segment of the partitioned container
   * such that the segments are as close to equal length as possible.
   * @param pc Container to partition
   * @param oc Container to partition over.
   * @param f Function to call on over container elements and segments.
   **/
  template <typename PartitionContainer, typename OverContainer, typename F>
  void equipartition(PartitionContainer &&pc, OverContainer &&oc, F &&f)
  {
    if (oc.empty() || pc.empty())
      return;
    using over_container_type = typename ::std::decay_t<OverContainer>;
    const auto num_over = ::gsl::narrow<typename view_traits_t<over_container_type>::difference_type>(oc.size());
    const auto num_partition =
        ::gsl::narrow<typename view_traits_t<::std::decay_t<PartitionContainer>>::difference_type>(pc.size());
    const auto data_per_partition = num_partition / num_over;
    for (::std::remove_cv_t<decltype(num_over)> i = 0; i < num_over - 1; ++i)
      f(oc[static_cast<typename view_traits_t<over_container_type>::index_type>(i)],
        ::std::make_tuple(pc.begin() + data_per_partition * i, pc.begin() + data_per_partition * (i + 1)));
    f(oc.back(), ::std::make_tuple(pc.begin() + data_per_partition * (num_over - 1), pc.end()));
  }
}
