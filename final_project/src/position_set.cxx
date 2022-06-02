/*******************************************/
/*** Imported From HW 6 Reversi ***/
/*******************************************/

#include "position_set.hxx"

Position_set::Position_set(std::initializer_list<value_type> elems)
        : Position_set(elems.begin(), elems.end())
{ }

Position_set
Position_set::universe()
{
    return ~Position_set();
}

bool
Position_set::empty() const
{
    return bits_.none();
}

size_t
Position_set::size() const
{
    return bits_.count();
}

bool
Position_set::operator[](Position_set::value_type p) const
{
    return bits_.test(index_of_checked_(p));
}

Position_set::reference
Position_set::operator[](Position_set::value_type p)
{
    return bits_[index_of_checked_(p)];
}

Position_set&
Position_set::operator&=(Position_set that)
{
    bits_ &= that.bits_;
    return *this;
}

Position_set&
Position_set::operator|=(Position_set that)
{
    bits_ |= that.bits_;
    return *this;
}

Position_set&
Position_set::operator^=(Position_set that)
{
    bits_ ^= that.bits_;
    return *this;
}

Position_set
Position_set::operator&(Position_set that) const
{
    Position_set result(*this);
    return result &= that;
}

Position_set
Position_set::operator|(Position_set that) const
{
    Position_set result(*this);
    return result |= that;
}

Position_set
Position_set::operator^(Position_set that) const
{
    Position_set result(*this);
    return result ^= that;
}

Position_set
Position_set::operator~() const
{
    Position_set result(*this);
    result.bits_ = ~result.bits_;
    return result;
}

void
Position_set::clear()
{
    bits_.reset();
}

Position_set::iterator
Position_set::begin() const
{
    for (size_t i = 0; i < index_limit; ++i) {
        if (bits_.test(i)) {
            return iterator_(position_of_(i));
        }
    }

    return end();
}

Position_set::iterator
Position_set::end() const
{
    return iterator_(position_of_(index_limit));
}

bool
operator==(Position_set a, Position_set b)
{
    return a.bits_ == b.bits_;
}

bool
operator!=(Position_set a, Position_set b)
{
    return !(a == b);
}

size_t
Position_set::index_of_checked_(value_type p)
{
    size_t index = index_of_(p);

    if (index >= index_limit) {
        throw ge211::Client_logic_error("Position_set: out of bounds");
    }

    return index;
}

size_t
Position_set::index_of_(value_type p)
{
    return size_t(coord_limit * p.x + p.y);
}

Position_set::value_type
Position_set::position_of_(size_t index)
{
    auto x = int(index / coord_limit);
    auto y = int(index % coord_limit);
    return {x, y};
}

Position_set::iterator
Position_set::iterator_(value_type p) const
{
    return {p, &bits_};
}

Position_set::iterator::iterator(value_type p, bits_t const *bits) noexcept
        : bits_(bits),
          current_(p)
{ }

Position_set::iterator::value_type
Position_set::iterator::operator*() const
{
    return current_;
}

Position_set::iterator::value_type *
Position_set::iterator::operator->() const
{
    return &current_;
}

Position_set::iterator&
Position_set::iterator::operator++()
{
    size_t current = index_of_(current_);

    do {
        current = ((current == index_limit) ? 0 : (current + 1));
    } while (!stopping_point_(current));

    current_ = position_of_(current);

    return *this;
}

Position_set::iterator&
Position_set::iterator::operator--()
{
    size_t current = index_of_(current_);

    do {
        current = ((current == 0) ? index_limit : (current - 1));
    } while (!stopping_point_(current));

    current_ = position_of_(current);

    return *this;
}

Position_set::iterator
Position_set::iterator::operator++(int)
{
    iterator result(*this);
    ++*this;
    return result;
}

Position_set::iterator
Position_set::iterator::operator--(int)
{
    iterator result(*this);
    --*this;
    return result;
}

bool
Position_set::iterator::stopping_point_(size_t index) const
{
    return index == index_limit || bits_->test(index);
}

bool
operator==(Position_set::iterator a, Position_set::iterator b)
{
    return *a == *b;
}

bool
operator!=(Position_set::iterator a, Position_set::iterator b)
{
    return !(a == b);
}

std::ostream&
operator<<(std::ostream& os, Position_set pset)
{
    os << "{";

    char const *before_elem = "";
    for (Position_set::value_type pos : pset) {
        os << before_elem << "{" << pos.x << ", " << pos.y << "}";
        before_elem = ", ";
    }

    return os << "}";
}
