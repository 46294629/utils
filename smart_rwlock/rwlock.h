#ifndef SMART_RWLOCK
#define SMART_RWLOCK

#include <pthread.h>

struct RLock
{
    RLock(pthread_rwlock_t *lock)
    {
        rd_lock = lock;
        pthread_rwlock_rdlock(rd_lock);
    }
    ~RLock()
    {
        pthread_rwlock_unlock(rd_lock);
    }
    pthread_rwlock_t *rd_lock;
};

struct WLock
{
    WLock(pthread_rwlock_t *lock)
    {
        wr_lock = lock;
        pthread_rwlock_wrlock(wr_lock);
    }
    ~WLock()
    {
        pthread_rwlock_unlock(wr_lock);
    }
    pthread_rwlock_t *wr_lock;
};

#endif
