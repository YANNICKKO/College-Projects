#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <inttypes.h>


data_structure *insert(char *line)
{
	data_structure *data = malloc(sizeof(data_structure));
	data->header = malloc(sizeof(head));
	data->header->len = 0;
	data->data = NULL;

	char *read = strtok(NULL, " ");

	//tipul
	data->header->type = read[0];

	char *char1;
	char1 = strtok(NULL, " ");

	//primul
	data->data = malloc(strlen(char1) + 1);
	memcpy(data->data, char1, strlen(char1) + 1);
	data->header->len = data->header->len + strlen(char1) + 1;

	int num1 = atoi(strtok(NULL, " "));
	int num2 = atoi(strtok(NULL, " "));

	//numerele
	if (data->header->type == '1')
	{
		num1 = (int8_t)num1;
		num2 = (int8_t)num2;

		void *aux = realloc(data->data, data->header->len + sizeof(int8_t) + sizeof(int8_t));
		if (aux)
		{
			data->data = aux;
		}
		memcpy(data->data + data->header->len, &num1, sizeof(int8_t));
		data->header->len += sizeof(int8_t);
		memcpy(data->data + data->header->len, &num2, sizeof(int8_t));
		data->header->len += sizeof(int8_t);
	}
	else if (data->header->type == '2')
	{
		num1 = (int16_t)num1;
		num2 = (int32_t)num2;

		void *aux = realloc(data->data, data->header->len + sizeof(int16_t) + sizeof(int32_t));
		if (aux)
		{
			data->data = aux;
		}
		memcpy(data->data + data->header->len, &num1, sizeof(int16_t));
		data->header->len += sizeof(int16_t);
		memcpy(data->data + data->header->len, &num2, sizeof(int32_t));
		data->header->len += sizeof(int32_t);
	}
	else
	{
		num1 = (int32_t)num1;
		num2 = (int32_t)num2;
		void *aux = realloc(data->data, data->header->len + sizeof(int32_t) + sizeof(int32_t));
		if (aux)
		{
			data->data = aux;
		}
		memcpy(data->data + data->header->len, &num1, sizeof(int32_t));
		data->header->len += sizeof(int32_t);
		memcpy(data->data + data->header->len, &num2, sizeof(int32_t));
		data->header->len += sizeof(int32_t);
	}

	char *char2;
	char2 = strtok(NULL, " ");

	void *ax = NULL;
	ax = realloc(data->data, data->header->len + strlen(char2) + 1);
	if (ax)
	{
		data->data = ax;
	}
	//al doilea cuvant
	memcpy(data->data + data->header->len, char2, strlen(char2) + 1);
	data->header->len += strlen(char2) + 1;

	return data;
}

void print(void *arr, int len)
{
	int count = 0;
	//mergem pana la len maxim
	while (count < len)
	{
		printf("Tipul %c\n", *(char *)(arr + count));
		int count_char = sizeof(head) + count;
		//primul cuv
		do
		{
			printf("%c", *(char *)(arr + count_char));
			count_char++;
		} while (*(char *)(arr + count_char) != '\0');

		printf(" pentru ");

		//tinem minte unde sunt numerele
		int count_int = count_char + 1;
		if (*(char *)(arr + count) == '1')
			count_char += 2 * sizeof(int8_t) + 1;
		else if (*(char *)(arr + count) == '2')
			count_char += sizeof(int16_t) + sizeof(int32_t) + 1;
		else
			count_char += 2 * sizeof(int32_t) + 1;

		//al doilea
		do
		{
			printf("%c", *(char *)(arr + count_char));
			count_char++;
		} while (*(char *)(arr + count_char) != '\0');
		printf("\n");


		//numerele
		if (*(char *)(arr + count) == '1')
		{
			printf("%" PRId8 "\n", *(int8_t *)(arr + count_int));
			count_int += sizeof(int8_t);
			printf("%" PRId8 "\n\n", *(int8_t *)(arr + count_int));
		}
		else if (*(char *)(arr + count) == '2')
		{
			printf("%" PRId16 "\n", *(int16_t *)(arr + count_int));
			count_int += sizeof(int16_t);
			printf("%" PRId32 "\n\n", *(int32_t *)(arr + count_int));
		}
		else
		{
			printf("%" PRId32 "\n", *(int32_t *)(arr + count_int));
			count_int += sizeof(int32_t);
			printf("%" PRId32 "\n\n", *(int32_t *)(arr + count_int));
		}
		count = count_char + 1;
	}
}

int add_last(void **arr, int *len, data_structure *data)
{
	if (*arr != NULL)
	{
		void *aux;
		aux = realloc(*arr, *len + sizeof(head) + data->header->len);
		if (aux)
		{
			*arr = aux;
		}
	}
	else
		*arr = malloc(sizeof(head) + data->header->len);

	//bagam in arr din struct
	memcpy(*arr + *len, data->header, sizeof(head));
	memcpy(*arr + *len + sizeof(head), data->data, data->header->len);
	*len += sizeof(head) + data->header->len;

	return 0;
}

int find_index(void *data_block, int len, int index)
{
	if (index < 0)
		return -1;

	int index_len = 0;

	int count = 0;
	//mergem pana la final
	while (count < len)
	{
		if (index_len == index)
		{
			return count;
		}

		int inceput = count;
		count += sizeof(head);
		//primul cuvant
		do
		{
			count++;
		} while (*(char *)(data_block + count) != '\0');
		count++;
		if (*(char *)(data_block + inceput) == '1')
			count += 2 * sizeof(int8_t);
		else if (*(char *)(data_block + inceput) == '2')
			count += sizeof(int16_t) + sizeof(int32_t);
		else
			count += 2 * sizeof(int32_t);
		//al doilea
		do
		{
			count++;

		} while (*(char *)(data_block + count) != '\0');
		count++;
		index_len++;
	}

	return -1;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
	int aux = find_index(*arr, *len, index);
	if (aux == -1)
	{
		add_last(arr, len, data);
		return 0;
	}
	void *temp = realloc(*arr, *len + data->header->len + sizeof(head));
	if (temp)
	{
		*arr = temp;
	}
	//mutam in dreapta si bagam
	memmove((*arr + aux + data->header->len + sizeof(head)), *arr + aux, *len - aux);
	memcpy(*arr + aux, data->header, sizeof(head));
	memcpy(*arr + aux + sizeof(head), data->data, data->header->len);

	*len += sizeof(head) + data->header->len;

	return 0;
}

void find(void *data_block, int len, int index)
{
	int aux = find_index(data_block, len, index);
	print(data_block + aux, 1);
}

int delete_at(void **arr, int *len, int index)
{
	int aux = find_index(*arr, *len, index);
	if (aux == -1)
		return -1;
	*len -= *(int *)(*arr + aux + 4) + sizeof(head);
	//mutam in stanga
	memmove(*arr + aux, *arr + aux + *(int *)(*arr + aux + 4) + sizeof(head), *len - aux);
	void *temp = realloc(*arr, *len);
	if (temp != NULL)
	{
		*arr = temp;
	}
	return 0;
}

int main()
{
	void *arr = NULL;
	int len = 0;

	char *line = (char *)malloc(sizeof(char) * 257);
	char *aux;
	while (fgets(line, 257, stdin))
	{
		line[strlen(line) - 1] = '\0';
		aux = strtok(line, " ");
		if (!strcmp(aux, "insert"))
		{
			data_structure *data;
			data = insert(aux);
			add_last(&arr, &len, data);

			free(data->header);
			free(data->data);
			free(data);
		}
		else if (!strcmp(aux, "print"))
		{
			print(arr, len);
		}
		else if (!strcmp(aux, "find"))
		{
			int index = atoi(strtok(NULL, " "));
			find(arr, len, index);
		}
		else if (!strcmp(aux, "insert_at"))
		{
			int index = atoi(strtok(NULL, " "));
			data_structure *data;
			data = insert(aux);
			add_at(&arr, &len, data, index);

			free(data->header);
			free(data->data);
			free(data);
		}
		else if (!strcmp(aux, "delete_at"))
		{
			int index = atoi(strtok(NULL, " "));
			delete_at(&arr, &len, index);
		}
		else if (!strcmp(aux, "exit"))
		{
			free(arr);
		}
	}
	free(line);

	return 0;
}
