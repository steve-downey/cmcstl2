// -*- compile-command: "(cd ~/cmcstl2/build && make iterator && ./test/iterator)" -*-

#include <stl2/concepts/core.hpp>
#include <stl2/concepts/iterator.hpp>

#include <cstddef>
#include <type_traits>

namespace associated_type_test {
using stl2::concepts::models::same;
using stl2::concepts::DifferenceType;
using stl2::concepts::DistanceType;
using stl2::concepts::IteratorCategory;
using stl2::concepts::ReferenceType;
using stl2::concepts::ValueType;

struct A { int& operator*(); };
struct B : A { using value_type = double; };
struct C : A { using element_type = double; };
struct D : A {
  using value_type = double;
  using element_type = char;
  using iterator_category = stl2::forward_iterator_tag;
};

static_assert(same<int&, ReferenceType<int*>>(), "");
static_assert(same<int&, ReferenceType<int[]>>(), "");
static_assert(same<int&, ReferenceType<int[4]>>(), "");
static_assert(same<int&, ReferenceType<A>>(), "");
static_assert(same<int&, ReferenceType<B>>(), "");
static_assert(same<int&, ReferenceType<C>>(), "");
static_assert(same<int&, ReferenceType<D>>(), "");
static_assert(same<const int&, ReferenceType<const int*>>(), "");

static_assert(same<int, ValueType<int*>>(), "");
static_assert(same<int, ValueType<int[]>>(), "");
static_assert(same<int, ValueType<int[4]>>(), "");
static_assert(same<int, ValueType<A>>(), "");
static_assert(same<double, ValueType<B>>(), "");
static_assert(same<double, ValueType<C>>(), "");
static_assert(same<double, ValueType<D>>(), "");
static_assert(same<int, ValueType<const int*>>(), "");

static_assert(same<std::ptrdiff_t, DifferenceType<int*>>(), "");
static_assert(same<std::ptrdiff_t, DifferenceType<int[]>>(), "");
static_assert(same<std::ptrdiff_t, DifferenceType<int[4]>>(), "");
static_assert(same<std::ptrdiff_t, DifferenceType<std::nullptr_t>>(), "");
static_assert(same<std::make_unsigned_t<std::ptrdiff_t>, DistanceType<int*>>(), "");

static_assert(same<int, DifferenceType<int>>(), "");
static_assert(same<unsigned, DistanceType<int>>(), "");

static_assert(same<IteratorCategory<int*>, stl2::contiguous_iterator_tag>(), "");
static_assert(same<IteratorCategory<const int*>, stl2::contiguous_iterator_tag>(), "");
static_assert(same<IteratorCategory<D>, stl2::forward_iterator_tag>(), "");
} // namespace associated_type_test

namespace readable_test {
using stl2::concepts::models::readable;
using stl2::concepts::ValueType;
using stl2::concepts::models::same;

struct A {
  int operator*() const;
};

static_assert(!readable<void>(), "");
static_assert(!readable<void*>(), "");
static_assert(readable<int*>(), "");
static_assert(readable<const int*>(), "");
static_assert(readable<A>(), "");
static_assert(same<ValueType<A>,int>(), "");
}

namespace writable_test {
using stl2::concepts::models::writable;

struct A {
  int& operator*() const;
};

static_assert(!writable<void, int>(), "");
static_assert(!writable<void*, void>(), "");
static_assert(writable<int*, int>(), "");
static_assert(writable<int*, int&>(), "");
static_assert(writable<int*, const int&>(), "");
static_assert(writable<int*, const int>(), "");
static_assert(!writable<const int*, int>(), "");
static_assert(writable<A, int>(), "");
static_assert(writable<A, double>(), "");
} // namespace writable_test

namespace weakly_incrementable_test {
using stl2::concepts::models::weakly_incrementable;

static_assert(weakly_incrementable<int>(), "");
static_assert(weakly_incrementable<unsigned int>(), "");
static_assert(!weakly_incrementable<void>(), "");
static_assert(weakly_incrementable<int*>(), "");
static_assert(weakly_incrementable<const int*>(), "");
} // namespace weakly_incrementable_test

namespace incrementable_test {
using stl2::concepts::models::incrementable;

static_assert(incrementable<int>(), "");
static_assert(incrementable<unsigned int>(), "");
static_assert(!incrementable<void>(), "");
static_assert(incrementable<int*>(), "");
static_assert(incrementable<const int*>(), "");
} // namespace incrementable_test

int main() {}