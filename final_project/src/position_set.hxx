/*******************************************/
/*** Imported From HW 6 Reversi ***/
/*******************************************/

#pragma once

#include <ge211.hxx>

#include <bitset>
#include <cstddef>
#include <initializer_list>

/// An efficient set of `ge211::Posn`s.
///
/// The allowed range of the positions is limited by the constant
/// `coord_limit` below. Right now it's 8, which means that the largest
/// position a set can hold is {7, 7}.
class Position_set
{
public:
    /// All position coordinates must be between 0 (inclusive) and
    /// `coord_limit` (exclusive).
    static constexpr int coord_limit = 50; //BRENNAN: CHANGED

    /// The element type of the set.
    using value_type = ge211::Posn<int>;

private:
    // Maximum number of possible positions.
    static constexpr std::size_t index_limit = coord_limit * coord_limit;

    // Private representation type.
    using bits_t = std::bitset<index_limit>;

    // The actual data
    bits_t bits_;

public:
    //
    // CONSTRUCTORS AND STATIC FACTORIES
    //

    /// Constructs the default position set.
    Position_set() noexcept = default;

    /// Returns the set of all possible positions. Because `coord_limit`
    /// is fixed and finite, this set isn't infinite---It has
    /// `coord_limit * coord_limit` elements.
    static Position_set universe();

    /// Constructs the position set containing the given positions.
    ///
    /// ## Example
    ///
    /// ```
    /// return Position_set{p1, p2};
    /// ```
    Position_set(std::initializer_list<value_type> elems);

    /// Constructs a position set given an iterator range of positions.
    ///
    /// ## Example
    ///
    /// ```
    /// std::vector<ge211::Posn<int>> v;
    /// ...
    ///
    /// Position_set pos_set(v.begin(), v.end());
    /// ```
    template <class FWD_ITER>
    explicit Position_set(FWD_ITER begin, FWD_ITER end);


    //
    // BASIC OPERATIONS
    //

    /// Returns whether this set is empty.
    bool empty() const;

    /// Returns the number of positions contained in this set.
    std::size_t size() const;

    /// Returns whether position `p` is present in this set.
    ///
    /// ## Preconditions
    ///
    ///  - 0 <= p.x < coord_limit
    ///
    ///  - 0 <= p.y < coord_limit
    ///
    /// ## Example
    ///
    /// ```
    /// if (set[pos]) {
    ///     std::cout << "Position " << pos << " is in the set.\n";
    /// }
    /// ```
    bool operator[](value_type p) const;

    /// A proxy class that allows assigning a `bool` to add or remove
    /// a position. This is returned by `operator[](value_type)` to
    /// allow assigning a bool to the result (see below).
    using reference = bits_t::reference;

    /// Returns an object that, when assigned to, changes whether `p` is
    /// in the set.
    ///
    /// ## Preconditions
    ///
    ///  - 0 <= p.x < coord_limit
    ///
    ///  - 0 <= p.y < coord_limit
    ///
    /// ## Example
    ///
    /// ```
    /// set[pos1] = false;  // remove pos1 from set
    /// set[pos2] = true;   // add pos2 to set
    /// ```
    reference operator[](value_type p);

    /// Removes all positions from the set.
    void clear();


    //
    // SET-LIKE OPERATIONS
    //

    /// Sets the elements of `*this` to be the intersection `*this` and
    /// `that`. That is, `*this` will contain only the positions that
    /// were in both.
    ///
    /// # Example
    ///
    /// This will remove from set1 any positions not present in set2:
    ///
    /// ```
    /// set1 &= set2;
    /// ```
    Position_set& operator&=(Position_set that);

    /// Sets the elements of `*this` to be the union `*this` and `that`.
    /// That is, `*this` will contain all the positions of both.
    Position_set& operator|=(Position_set that);

    /// Sets the elements of `*this` to be the symmetric
    /// difference of `*this` and `that`. That is, `*this` will
    /// contain the positions that were in one or the other but
    /// not both.
    Position_set& operator^=(Position_set that);

    /// Returns the intersection of two sets.
    Position_set operator&(Position_set) const;

    /// Returns the union of two sets.
    Position_set operator|(Position_set) const;

    /// Returns the symmetric difference of two sets.
    Position_set operator^(Position_set) const;

    /// Returns the complement of this set, containing all positions
    /// that `*this` does not, and no positions that it does.
    ///
    /// ## Example
    ///
    /// The complement of the empty set is the universe:
    ///
    /// ```
    /// CHECK( ~Position_set() == Position_set::universe() );
    /// ```
    Position_set operator~() const;


    //
    // ITERATOR OPERATIONS
    //

    /// An iterator over the positions of a set of positions. This is
    /// used not only for iteration, but as the result of `find(value_type)`,
    /// which checks for set membership.
    ///
    /// It means you can write this to iterate over all the positions in
    /// a set:
    ///
    /// ```
    /// for (ge211::Posn<int> pos : set) {
    ///     ...
    /// }
    /// ```
    class iterator;

    /// Returns an iterator to the first position in the set.
    iterator begin() const;

    /// Returns an iterator one past the end of the set.
    iterator end() const;


    //
    // FRIENDS
    //

    /// Are two position sets equal?
    friend bool operator==(Position_set, Position_set);

    /// Are two position sets unequal?
    friend bool operator!=(Position_set, Position_set);

private:
    //
    // HELPERS
    //

    static std::size_t index_of_checked_(value_type);
    static std::size_t index_of_(value_type);
    static value_type position_of_(std::size_t);
    iterator iterator_(value_type) const;
};


// Iterator class, declared above inside Position_set and defined right here:
class Position_set::iterator
        : public std::iterator<
                std::input_iterator_tag,
                Position_set::value_type const>
{
    bits_t const *bits_;
    Position_set::value_type current_;

public:
    /// Returns the current `Posn`.
    value_type operator*() const;

    /// Returns a pointer to the current `Posn`.
    value_type *operator->() const;

    /// Advances to the next element of the set.
    iterator& operator++();

    /// Retreats to the previous element of the set.
    iterator& operator--();

    /// Advances to the next element of the set.
    iterator operator++(int);

    /// Retreats to the previous element of the set.
    iterator operator--(int);

private:
    friend Position_set;

    iterator(value_type, bits_t const *) noexcept;

    bool stopping_point_(std::size_t index) const;
};


//
// FREE FUNCTIONS ASSOCIATED WITH THE CLASS
//

/// Two iterators are equal when they dereference to
/// the same position (even if they refer to different
/// `Position_set`s).
bool
operator==(Position_set::iterator, Position_set::iterator);

/// Two iterators are unequal when they aren't equal.
bool
operator!=(Position_set::iterator, Position_set::iterator);

/// Prints a `Position_set`; suitable for debugging.
std::ostream&
operator<<(std::ostream&, Position_set);


//
// MEMBER TEMPLATE IMPLEMENTATIONS
//

/// Implementation of range constructor (declared in class above).
template <class FWD_ITER>
Position_set::Position_set(FWD_ITER begin, FWD_ITER end)
{
    for (; begin != end; ++begin) {
        (*this)[*begin] = true;
    }
}
