/* 
 * fontgen.c
 * Created: Fri Apr 13 20:38:07 2001 by tek@wiw.org
 * Revised: Sat Jun 23 04:09:46 2001 by tek@wiw.org
 * Copyright 2001 Julian E. C. Squires (tek@wiw.org)
 * This program comes with ABSOLUTELY NO WARRANTY.
 * $Id$
 * 
 */

#include <dentata/types.h>
#include <dentata/image.h>
#include <dentata/font.h>
#include <dentata/file.h>
#include <dentata/memory.h>
#include <dentata/error.h>
#include <dentata/random.h>
#include <dentata/util.h>

d_font_t *d_font_load(char *);
d_font_t *d_font_dup(d_font_t *);
void d_font_printf(d_image_t *, d_font_t *, d_point_t, byte *, ...);
word d_font_gettextwidth(d_font_t *, byte *, ...);
void d_font_delete(d_font_t *);
void d_font_convertdepth(d_font_t *fnt, byte bpp);
void d_font_extendalpha(d_font_t *fnt, byte alpha);
void d_font_silhouette(d_font_t *fnt, d_color_t c, byte alpha);

static bool loadv0font(d_file_t *fp, d_font_t *fnt);

d_font_t *d_font_load(char *filename)
{
    d_font_t *fnt;
    d_file_t *fp;

    fnt = d_memory_new(sizeof(d_font_t));
    if(fnt == NULL) return NULL;

    fp = d_file_open(filename);
    if(fp == NULL) return NULL;

    if(d_file_getbyte(fp) != 'F' ||
       d_file_getbyte(fp) != 'N' ||
       d_file_getbyte(fp) != 'T') {
        d_error_push("d_font_load: bad magic.");
        return NULL;
    }

    switch(d_file_getbyte(fp)) {
    case 0: /* version 0 -- bitmapped font */
        if(loadv0font(fp, fnt) != success)
            return NULL;
        break;

    default:
        d_error_push("d_font_load: unsupported font version.");
        return NULL;
    }

    d_file_close(fp);
    return fnt;
}

d_font_t *d_font_dup(d_font_t *fnt)
{
    d_font_t *fnt2;
    int i;

    fnt2 = d_memory_new(sizeof(d_font_t));
    if(fnt2 == NULL) return NULL;

    fnt2->desc = fnt->desc;
    fnt2->start = fnt->start;
    fnt2->nchars = fnt->nchars;
    fnt2->chars = d_memory_new(sizeof(d_image_t *)*fnt2->nchars);
    if(fnt2->chars == NULL) return NULL;
    for(i = 0; i < fnt2->nchars; i++)
        fnt2->chars[i] = d_image_dup(fnt->chars[i]);

    return fnt2;
}

bool loadv0font(d_file_t *fp, d_font_t *fnt)
{
    int i, j;
    byte k, l;

    fnt->desc.w = d_file_getword(fp);
    fnt->desc.h = d_file_getword(fp);
    fnt->desc.bpp = 1;
    fnt->desc.alpha = 1;
    fnt->desc.paletted = false;
    fnt->desc.cspace = RGB;
    fnt->start = d_file_getbyte(fp);
    fnt->nchars = d_file_getbyte(fp);
    fnt->chars = d_memory_new(sizeof(d_image_t *)*fnt->nchars);
    if(fnt->chars == NULL) return failure;

    for(i = 0; i < fnt->nchars; i++) {
        fnt->chars[i] = d_image_new(fnt->desc);
        if(fnt->chars[i] == NULL) return failure;
        d_file_read(fp, fnt->chars[i]->data, fnt->desc.h);
        for(j = 0; j < fnt->desc.h; j++) {
            for(k = 0, l = 0; k < 8; k++) {
                l |= ((fnt->chars[i]->data[j]&(1<<k))>>k)<<(7-k);
            }
            fnt->chars[i]->data[j] = l;
        }
        d_memory_copy(fnt->chars[i]->alpha, fnt->chars[i]->data,
                      fnt->desc.h);
    }

    return success;
}

void d_font_printf(d_image_t *image, d_font_t *fnt, d_point_t pt, byte *fmt,
                   ...)
{
    void *args;
    byte *p;
    int i, len;

    args = &fmt+1;
    len = d_util_printflen(fmt, args);
    p = d_memory_new(len+1);
    d_util_sprintf(p, fmt, args);

    for(i = 0; i < len; i++) {
        d_image_blit(image, fnt->chars[(unsigned)p[i]-fnt->start], pt);
        pt.x += fnt->desc.w+1;
    }
    d_memory_delete(p);
    return;
}

word d_font_gettextwidth(d_font_t *fnt, byte *fmt, ...)
{
    void *args;

    args = fmt+sizeof(byte *);
    return d_util_printflen(fmt, args)*(fnt->desc.w+1);
}

void d_font_convertdepth(d_font_t *fnt, byte bpp)
{
    int i;

    for(i = fnt->start; i < fnt->start+fnt->nchars; i++)
        d_image_convertdepth(fnt->chars[i], bpp);
    return;
}

void d_font_extendalpha(d_font_t *fnt, byte alpha)
{
    int i;

    for(i = fnt->start; i < fnt->start+fnt->nchars; i++)
        d_image_extendalpha(fnt->chars[i], alpha);
    return;
}

void d_font_silhouette(d_font_t *fnt, d_color_t c, byte alpha)
{
    int i;

    for(i = fnt->start; i < fnt->start+fnt->nchars; i++)
        d_image_silhouette(fnt->chars[i], c, alpha);
    return;
}

void d_font_delete(d_font_t *fnt)
{
    int i;

    for(i = 0; i < fnt->nchars; i++)
        d_image_delete(fnt->chars[i]);
    d_memory_delete(fnt->chars);
    d_memory_delete(fnt);
    return;
}

/* EOF fontgen.c */