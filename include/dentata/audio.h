/* 
 * audio.h
 * Created: Thu Jan 25 12:09:37 2001 by tek@wiw.org
 * Revised: Mon Jan 29 12:18:52 2001 by tek@wiw.org
 * Copyright 2001 Julian E. C. Squires (tek@wiw.org)
 * This program comes with ABSOLUTELY NO WARRANTY.
 * $Id$
 *
 * Dentata gen Beta
 * Base audio module
 */

#ifndef DENTATA_AUDIO_H
#define DENTATA_AUDIO_H

#include <dentata/types.h>
#include <dentata/sample.h>

typedef struct d_channelprops_s {
    byte volume;
    signed char panning;
    bool mute;
} d_channelprops_t;

extern bool             d_audio_new(d_audiomode_t, byte);
extern void             d_audio_delete(void);
extern void             d_audio_update(void);
extern void             d_audio_playsample(byte, d_sample_t *);
extern void             d_audio_stopsample(byte);
extern void             d_audio_setchanprops(byte, d_channelprops_t);
extern d_channelprops_t d_audio_getchanprops(byte);

#endif

/* EOF audio.h */
