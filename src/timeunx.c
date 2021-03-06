/* 
 * timeunx.c
 * Created: Wed Apr  4 21:47:19 2001 by tek@wiw.org
 * Revised: Sun Jun 24 04:21:31 2001 by tek@wiw.org
 * Copyright 2001 Julian E. C. Squires (tek@wiw.org)
 * This program comes with ABSOLUTELY NO WARRANTY.
 * $Id$
 * 
 */

#include <dentata/types.h>
#include <dentata/time.h>
#include <dentata/memory.h>

#include <sys/time.h>
#include <unistd.h>

void d_time_wait(dword);
d_timehandle_t *d_time_startcount(int, bool);
int d_time_endcount(d_timehandle_t *th);
extern bool d_time_iscountfinished(d_timehandle_t *th);

struct timehandle_s {
    struct timeval end;
};

void d_time_wait(dword us)
{
    usleep(us);
    return;
}

d_timehandle_t *d_time_startcount(int fps, bool wantdiff)
{
    struct timehandle_s *handle;

    int diff;
    handle = d_memory_new(sizeof(struct timehandle_s));
    gettimeofday(&handle->end, NULL);
    diff = 1e6/fps;
    if(diff+handle->end.tv_usec >= 1e6)
        handle->end.tv_sec++;
    handle->end.tv_usec = (handle->end.tv_usec+diff)%(int)1e6;

    return (d_timehandle_t *)handle;
}

bool d_time_iscountfinished(d_timehandle_t *th)
{
    struct timeval curtv;
    struct timehandle_s *handle = (struct timehandle_s *)th;

    gettimeofday(&curtv, NULL);
    if(curtv.tv_sec < handle->end.tv_sec ||
       (curtv.tv_sec == handle->end.tv_sec &&
        curtv.tv_usec < handle->end.tv_usec)) {
        return false;
    }
    return true;
}

int d_time_endcount(d_timehandle_t *th)
{
    struct timeval curtv;
    struct timehandle_s *handle = (struct timehandle_s *)th;
    int diff = 0;

    gettimeofday(&curtv, NULL);
    diff = (handle->end.tv_sec-curtv.tv_sec)*1e6+
           (handle->end.tv_usec-curtv.tv_usec);
    if(diff > 0) {
        d_time_wait(diff);
    }
    d_memory_delete(handle);
    return diff;
}

/* EOF timeunx.c */
