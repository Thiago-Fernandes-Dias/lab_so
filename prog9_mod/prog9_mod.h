#ifndef PROG9_MOD_H
#define PROG9_MOD_H

#define MSG_QTY 100
#define MAILBOX_FULL 453
#define MAILBOX_EMPTY 452

typedef struct
{
	long type;
	char content[100];
} message;

#endif