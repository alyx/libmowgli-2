/*
 * libmowgli: A collection of useful routines for programming.
 * mowgli_queue.h: Double-ended queues, also known as deque.
 *
 * Copyright (c) 2007 William Pitcock <nenolod -at- sacredspiral.co.uk>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __MOWGLI_QUEUE_H__
#define __MOWGLI_QUEUE_H__

typedef struct mowgli_queue_ {
	struct mowgli_queue_ *prev, *next;
	void *data;
} mowgli_queue_t;

extern void mowgli_queue_init(void);
extern mowgli_queue_t *mowgli_queue_push(mowgli_queue_t *head, void *data);
extern mowgli_queue_t *mowgli_queue_shift(mowgli_queue_t *head, void *data);
extern mowgli_queue_t *mowgli_queue_remove(mowgli_queue_t *head);
extern mowgli_queue_t *mowgli_queue_find(mowgli_queue_t *head, void *data);
extern mowgli_queue_t *mowgli_queue_remove_data(mowgli_queue_t *head, void *data);
extern void mowgli_queue_free(mowgli_queue_t *head);
extern mowgli_queue_t *mowgli_queue_skip(mowgli_queue_t *head, int amt);
extern mowgli_queue_t *mowgli_queue_rewind(mowgli_queue_t *head, int amt);
extern mowgli_queue_t *mowgli_queue_head(mowgli_queue_t *n);
extern mowgli_queue_t *mowgli_queue_tail(mowgli_queue_t *n);
extern void *mowgli_queue_pop_head(mowgli_queue_t **n);
extern void *mowgli_queue_pop_tail(mowgli_queue_t **n);
extern int mowgli_queue_length(mowgli_queue_t *head);

#endif
