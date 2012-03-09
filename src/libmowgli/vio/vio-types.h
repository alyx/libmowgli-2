/*
 * Copyright (c) 2012 Elizabeth J. Myers. All rights reserved. 
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __MOWGLI_VIO_TYPES_H__
#define __MOWGLI_VIO_TYPES_H__

/* vio.c */
typedef struct _mowgli_vio mowgli_vio_t;

typedef enum {
	MOWGLI_VIO_ERR_NONE,
	MOWGLI_VIO_ERR_REMOTE_HANGUP,
	MOWGLI_VIO_ERR_ERRCODE,
	MOWGLI_VIO_ERR_API,
	MOWGLI_VIO_ERR_CUSTOM,
} mowgli_vio_error_type_t;

typedef enum {
	MOWGLI_VIO_ERR_OP_NONE,
	MOWGLI_VIO_ERR_OP_SOCKET,
	MOWGLI_VIO_ERR_OP_LISTEN,
	MOWGLI_VIO_ERR_OP_ACCEPT,
	MOWGLI_VIO_ERR_OP_CONNECT,
	MOWGLI_VIO_ERR_OP_READ,
	MOWGLI_VIO_ERR_OP_WRITE,
	MOWGLI_VIO_ERR_OP_OTHER,
} mowgli_vio_error_op_t;

typedef struct _mowgli_vio_error {
	mowgli_vio_error_op_t op;
	mowgli_vio_error_type_t type;
	int code;
	char string[128];
} mowgli_vio_error_t;

#define MOWGLI_VIO_RETURN_ERRCODE(v, s, e) 		\
{							\
	v->error.type = MOWGLI_VIO_ERR_ERRCODE; 	\
	v->error.code = e;				\
	v->flags &= ~MOWGLI_VIO_FLAGS_ISCONNECTING;	\
	v->flags |= MOWGLI_VIO_FLAGS_ISCLOSED;		\
	mowgli_strlcpy(v->error.string, s(e), sizeof((v)->error.string)); \
	return mowgli_vio_error((v)); 			\
}

#ifdef HAVE_OPENSSL

#define MOWGLI_VIO_RETURN_SSLERR_ERRCODE(v, e)		\
{							\
	(v)->error.type = MOWGLI_VIO_ERR_ERRCODE;	\
	(v)->error.code = e;				\
	v->flags &= ~MOWGLI_VIO_FLAGS_ISCONNECTING;	\
	v->flags |= MOWGLI_VIO_FLAGS_ISCLOSED;		\
	ERR_error_string_n(e, (v)->error.string, sizeof((v)->error.string)); \
	return mowgli_vio_error(v);			\
}

#else

#define MOWGLI_VIO_RETURN_SSL_ERRCODE(v, e) MOWGLI_VIO_RETURN_ERRCODE(v, strerror, e)

#endif

typedef int mowgli_vio_func_t(mowgli_vio_t *);
typedef int mowgli_vio_rw_func_t(mowgli_vio_t *, void *, size_t);
typedef int mowgli_vio_connect_func_t(mowgli_vio_t *, const struct sockaddr *, socklen_t);
typedef int mowgli_vio_accept_func_t(mowgli_vio_t *, mowgli_vio_t *, struct sockaddr *, socklen_t *);
typedef int mowgli_vio_listen_func_t(mowgli_vio_t *, int);
typedef int mowgli_vio_socket_func_t(mowgli_vio_t *, int, int, int);

typedef struct {
	mowgli_vio_socket_func_t *socket;
	mowgli_vio_connect_func_t *connect;
	mowgli_vio_listen_func_t *listen;
	mowgli_vio_accept_func_t *accept;
	mowgli_vio_rw_func_t *read;
	mowgli_vio_rw_func_t *write;
	mowgli_vio_func_t *error;
	mowgli_vio_func_t *close;
} mowgli_vio_ops_t;

struct _mowgli_vio {
	mowgli_vio_ops_t ops;

	mowgli_eventloop_t *eventloop;
	mowgli_eventloop_io_t *io;
	mowgli_descriptor_t fd;

	mowgli_vio_error_t error;

	int flags;
	
	void *userdata;
	void *privdata;
};

#define MOWGLI_VIO_FLAGS_ISCONNECTING		0x00001
#define MOWGLI_VIO_FLAGS_ISCLOSED		0x00002
#define MOWGLI_VIO_FLAGS_ISCLIENT		0x00004
#define MOWGLI_VIO_FLAGS_ISSERVER		0x00008

#endif
