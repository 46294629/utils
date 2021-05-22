template <typename J>
struct NumRecordWrap
{
    NumRecordWrap()
    {
        record = 0;
    }
    NumRecordWrap(J record_) : record(record_) {}
    void Reset()
    {
        record = 0;
    }
    NumRecordWrap & operator-=(const NumRecordWrap &other)
    {
        record -= other.record;
        return *this;
    }
    NumRecordWrap & operator+=(const NumRecordWrap &other)
    {
        record += other.record;
        return *this;
    }
    bool operator>=(const J &record_)
    {
        return record >= record_;
    }
    bool operator<(const J &record_)
    {
        return record < record_;
    }
    J GetRecord()
    {
        return record;
    }
    NumRecordWrap operator/(const uint32 &num)
    {
        return NumRecordWrap(record / num);
    }
private:
    J record;
};
