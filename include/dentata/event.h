/**
 * event.h
 * Created: Wed Jan 24 11:40:52 2001 by tek@wiw.org
 * Revised: Mon Jul  9 16:08:44 2001 by tek@wiw.org
 * Copyright 2001 Rhombus Software/Julian E. C. Squires (tek@wiw.org)
 * $Id$
 *
 * Module: event
 *
 * Note that some implementations require that the raster module
 * be initialized before they may be initialized. Implementations which
 * function in windowing systems generally require that the raster
 * module has already been started, and a window opened. To err on
 * the side of safety, this should be obeyed. Additionally, the event
 * module should be closed and reinitialized every time the raster
 * mode is changed.
 *
 * Include dentata/types.h before dentata/event.h.
 */

#ifndef DENTATA_EVENT_H
#define DENTATA_EVENT_H

/**
 * d_event_new(byte mask)
 * Initialize the event module.
 *
 * Takes: mask - specifies which devices to initialize. The mask parameter
 *               is a bitwise or of the D_EVENT_<device> constants.
 *
 * Returns: a byte in the same form as the mask parameter, specifying which
 *          input devices the current event driver supports and has
 *          initialized.
 *
 * Pushes an error if a supported input device fails to initialize, or
 * if this implementation requires the raster module and it has not been
 * initialized.
 */
extern byte d_event_new(byte);

/**
 * d_event_delete()
 * Shuts down the event module.
 */
extern void d_event_delete(void);

/**
 * d_event_map(byte handle, byte event)
 * Associates an input event with an arbitrary handle. Note that
 * d_event_map() can be called multiple times with the same handle
 * to associate multiple events with a single handle.
 *
 * Takes: handle - an arbitrary handle chosen by the programmer.
 *        event - the event to associate with handle. This should be
 *                one of the values defined in dentata/event.h.
 *
 * Returns: success if the mapping succeeded, failure if the event
 *          is already associated with this mapping or if some other
 *          error occurred.
 */
extern bool d_event_map(byte, byte);

/**
 * d_event_unmap(byte handle)
 * Removes _all_ events associated with the supplied handle.
 *
 * Takes: handle - the handle from which to remove event mappings.
 */
extern void d_event_unmap(byte);

/**
 * d_event_ispressed(byte handle)
 * Checks if any of the events associated with handle have occured.
 *
 * Takes: handle - the handle to check.
 *
 * Returns: true if any of the events have occured, false otherwise.
 */
extern bool d_event_ispressed(byte);

/**
 * d_event_update()
 * Updates internal event driver data. Should be called once per
 * frame.
 */
extern void d_event_update(void);

#define D_EVENT_KEYBOARD   0x01
#define D_EVENT_MOUSE      0x02
#define D_EVENT_CONTROLLER 0x04
/* 0x08, 0x10, 0x20, 0x40, 0x80 reserved for expansion */

/* event mappings are:
   0          nothing
   1-127      keyboard codes
   128-130    mouse buttons
   131-163    controller digital inputs
   164-255    reserved
*/

#define D_EVENT_NONE      0
/* keyboard scancodes/mappings [these follow the PC scancodes, but still
   apply on systems with different scancodes] */
#define D_KBD_FIRST       1
#define D_KBD_ESCAPE      1
#define D_KBD_1           2
#define D_KBD_2           3
#define D_KBD_3           4
#define D_KBD_4           5
#define D_KBD_5           6
#define D_KBD_6           7
#define D_KBD_7           8
#define D_KBD_8           9
#define D_KBD_9           10
#define D_KBD_0           11
#define D_KBD_MINUS       12
#define D_KBD_EQUALS      13
#define D_KBD_BS          14
#define D_KBD_TAB         15
#define D_KBD_Q           16
#define D_KBD_W           17
#define D_KBD_E           18
#define D_KBD_R           19
#define D_KBD_T           20
#define D_KBD_Y           21
#define D_KBD_U           22
#define D_KBD_I           23
#define D_KBD_O           24
#define D_KBD_P           25
#define D_KBD_LBRACK      26
#define D_KBD_RBRACK      27
#define D_KBD_ENTER       28
#define D_KBD_LEFTCONTROL 29
#define D_KBD_A           30
#define D_KBD_S           31
#define D_KBD_D           32
#define D_KBD_F           33
#define D_KBD_G           34
#define D_KBD_H           35
#define D_KBD_J           36
#define D_KBD_K           37
#define D_KBD_L           38
#define D_KBD_SEMICOLON   39
#define D_KBD_APOSTROPHE  40
#define D_KBD_GRAVE       41
#define D_KBD_LEFTSHIFT   42
#define D_KBD_BACKSLASH   43
#define D_KBD_Z           44
#define D_KBD_X           45
#define D_KBD_C           46
#define D_KBD_V           47
#define D_KBD_B           48
#define D_KBD_N           49
#define D_KBD_M           50
#define D_KBD_COMMA       51
#define D_KBD_PERIOD      52
#define D_KBD_SLASH       53
#define D_KBD_RIGHTSHIFT  54
#define D_KBD_PADASTERIX  55
#define D_KBD_LEFTALT     56
#define D_KBD_SPACE       57
#define D_KBD_CAPSLOCK    58
#define D_KBD_F1          59
#define D_KBD_F2          60
#define D_KBD_F3          61
#define D_KBD_F4          62
#define D_KBD_F5          63
#define D_KBD_F6          64
#define D_KBD_F7          65
#define D_KBD_F8          66
#define D_KBD_F9          67
#define D_KBD_F10         68

/* numlock scrolllock keypad7 <lots more keypad junk> */

#define D_KBD_PADENTER    96
#define D_KBD_RIGHTCONTROL 97
#define D_KBD_PADDIVIDE   98
#define D_KBD_PRINTSCR    99
#define D_KBD_RIGHTALT    100
#define D_KBD_BREAK       101
#define D_KBD_HOME        102
#define D_KBD_CURSORUP    103
#define D_KBD_PAGEUP      104
#define D_KBD_CURSORLEFT  105
#define D_KBD_CURSORRIGHT 106
#define D_KBD_END         107
#define D_KBD_CURSORDOWN  108
#define D_KBD_PAGEDOWN    109
#define D_KBD_INSERT      110
#define D_KBD_DELETE      111
#define D_KBD_LAST        127

/* PC mouse button mappings */
#define D_MOUSE_FIRST     128
#define D_MOUSE_LEFT      128
#define D_MOUSE_RIGHT     129
#define D_MOUSE_MIDDLE    130
#define D_MOUSE_LAST      130

/* Controller mappings, based on PSX */
#define D_CTRLR_LEFT     131
#define D_CTRLR_RIGHT    132
#define D_CTRLR_UP       133
#define D_CTRLR_DOWN     134
#define D_CTRLR_START    135
#define D_CTRLR_SELECT   136

/* a lot of synonymous buttons here... despite the fact that I'm a
   sega kind of guy, I generally make SNES<->PSX synonymities
   over Saturn or Dreamcast... that is, the number for square and
   button Y is the same, and button X is the same number as triangle. */
#define D_CTRLR_SQUARE   137
#define D_CTRLR_BUTTONY  137
#define D_CTRLR_CIRCLE   138
#define D_CTRLR_BUTTONA  138
#define D_CTRLR_TRIANGLE 139
#define D_CTRLR_BUTTONX  139
#define D_CTRLR_CROSS    140
#define D_CTRLR_BUTTONB  140

#define D_CTRLR_BUTTONC  141
#define D_CTRLR_BUTTONZ  142

#define D_CTRLR_TRIGGERL1 143
#define D_CTRLR_TRIGGERL  143
#define D_CTRLR_TRIGGERL2 144
#define D_CTRLR_TRIGGERL3 145 /* left analog stick press */

#define D_CTRLR_TRIGGERR1 146
#define D_CTRLR_TRIGGERR  146
#define D_CTRLR_TRIGGERR2 147
#define D_CTRLR_TRIGGERR3 148 /* right analog stick press */

#define D_EVENT_MAXEVENTS 255

#endif

/* EOF event.h */
