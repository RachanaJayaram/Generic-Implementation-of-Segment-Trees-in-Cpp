namespace st
{
template <typename T>
class Iterator
{
public:
    explicit Iterator(T *p_it = nullptr) : p_it_(p_it) {}
    bool operator==(const Iterator &rhs) const
    {
        return p_it_ == rhs.p_it_;
    }
    bool operator!=(const Iterator &rhs) const
    {
        return !(*this == rhs);
    }
    Iterator operator+(const int x)
    {
        return Iterator((*this).p_it_ + x);
    }
    Iterator operator-(const int x)
    {
        return Iterator((*this).p_it_ - x);
    }
    T operator*()
    {
        return *p_it_;
    }
    Iterator &operator++()
    {
        ++p_it_;
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator temp(*this);
        ++*this;
        return temp;
    }
    Iterator &operator--()
    {
        --p_it_;
        return *this;
    }
    Iterator operator--(int)
    {
        Iterator temp(*this);
        --*this;
        return temp;
    }

private:
    T *p_it_;
};

template <typename T>
class ReverseIterator
{
public:
    explicit ReverseIterator(T *p_it = nullptr) : p_it_(p_it) {}
    bool operator==(const ReverseIterator &rhs) const
    {
        return p_it_ == rhs.p_it_;
    }
    bool operator!=(const ReverseIterator &rhs) const
    {
        return !(*this == rhs);
    }
    bool operator+(const int x)
    {
        return ((*this).p_it_ - x);
    }
    bool operator-(const int x) const
    {
        return ((*this).p_it_ + x);
    }
    T operator*()
    {
        return *p_it_;
    }
    ReverseIterator &operator++()
    {
        --p_it_;
        return *this;
    }
    ReverseIterator operator++(int)
    {
        ReverseIterator temp(*this);
        --*this;
        return temp;
    }
    ReverseIterator &operator--()
    {
        ++p_it_;
        return *this;
    }
    ReverseIterator operator--(int)
    {
        ReverseIterator temp(*this);
        ++*this;
        return temp;
    }

private:
    T *p_it_;
};
} // namespace st