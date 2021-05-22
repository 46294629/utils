/*
用以保存一段时间内（如一分钟内）的记录，并保存记录总和。记录长度可变
record_info中每一个节点代表一个记录内容
*/

#include <vector>

template <typename T>
struct Record
{
    Record()
    {
        record_idx = 0;
    }
    void Reset()
    {
        std::vector<T> empty_record;
        empty_record.swap(record_info);
        record_idx = 0;
        total_record.Reset();
    }
    T InsertRecord(const unsigned &max_record_size, const T &record)
    {
        unsigned size = record_info.size();
        if (size < max_record_size)
        {
            record_info.push_back(record);
            record_idx = size;
            AddTotalRecord(record);
            return total_record;
        }

        if (size > max_record_size)
        {
            record_idx += size;
            ResizeRecord(max_record_size, record);
            record_idx = max_record_size - 1;
        }
        record_idx = (record_idx + 1) % max_record_size;
        CalTotalRecord(record, record_info[record_idx]);
        record_info[record_idx] = record;
        return total_record;
    }
    unsigned GetRecordSize()
    {
        return record_info.size();
    }
    T GetTotalRecord()
    {
        return total_record;
    }
    T GetAverageRecord()
    {
        uint32 size = record_info.size();
        if (0 == size)
        {
            return T();
        }
        return total_record / size;
    }
    T GetLastRecord()
    {
        uint32 size = record_info.size();
        if (0 == size)
        {
            return T();
        }
        return record_info[record_idx % size];
    }

private:
    void AddTotalRecord(const T &new_record)
    {
        total_record += new_record;
    }
    void CalTotalRecord(const T &new_record, const T &ori_record)
    {
        total_record += new_record;
        total_record -= ori_record;
    }
    void ResizeRecord(const unsigned &max_record_size, const T &record)
    {
        std::vector<T> lastest_record_info(max_record_size, T());
        unsigned size = 0;
        total_record.Reset();
        unsigned idx = 0;
        while (size < max_record_size)
        {
            idx = max_record_size - size - 1;
            lastest_record_info[idx] = record_info[record_idx--];
            total_record += lastest_record_info[idx];
            ++size;
        }
        record_info.swap(lastest_record_info);
    }

    T total_record; //sum
    unsigned record_idx; //上次插入load数组中的下标
    std::vector<T> record_info;
};
