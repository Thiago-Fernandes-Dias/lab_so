#include <sys/wait.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include "prog9_mod.h"

int main()
{
	int flag, msgflg, msq_empty_id, msq_full_id;
	message m;

	msgflg = MSG_NOERROR;
	msq_empty_id = msgget(MAILBOX_EMPTY, 0666 | IPC_CREAT);
	msq_full_id = msgget(MAILBOX_FULL, 0666 | IPC_CREAT);
	if (msq_empty_id <= 0)
	{
		perror("Erro na criação da MailBox");
	}
	for (int i = 0; i < MSG_QTY; i++)
	{
		m.type = 1;
		sprintf(m.content, "%d° mensagem vazia enviada do consumidor", i + 1);
		flag = msgsnd(msq_empty_id, &m, strlen(m.content) + 1, 0);
		printf("Resultado da %d° mensagem vazia: %d\n", i + 1, flag);
	}
	while (1)
	{
		flag = msgrcv(msq_full_id, &m, 100, 0, msgflg);
		if (flag >= 0)
		{
			printf("Tipo da mensagem: %ld\n", m.type);
			printf("Conteúdo da mensagem: %s\n", m.content);
			printf("Resultado do recebimento da mensagem cheia: %d\n", flag);
		}
		else
		{
			perror("Erro na recepção da mensagem");
		}
		printf("Enviando mensagem vazia de volta para o Produtor...\n");
		m.type = 1;
		sprintf(m.content, "%s", "Mensagem vazia.");
		flag = msgsnd(msq_empty_id, &m, strlen(m.content) + 1, 0);
		printf("Resultado do envio da mensagem vazia: %d\n", flag);
	}
}
