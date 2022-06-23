/*Koning Yannick 312CB*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TCoada.h"
#include "TStiva.h"

void CreateThreadStack(void *s, size_t N)
{
    Thread t;

    for (; N > 0;)
    {
        t.ID = --N;

        if (!Push(s, &t))
            return;
    }
}
void InsSortQ(void *q, Task t)
{
    void *q_aux;
    q_aux = InitQ(sizeof(Task));
    int ok = 0;

    while (!VidaQ(q))
    {
        Task aux;
        ExtrQ(q, &aux);
        if (aux.prio < t.prio)
            ok = 1;
        else if (aux.prio == t.prio)
        {
            if (aux.exec_t > t.exec_t)
                ok = 1;
            else if (aux.exec_t == t.exec_t)
            {
                if (aux.ID > t.ID)
                    ok = 1;
            }
        }
        if (ok == 1)
        {
            IntrQ(q_aux, &t);
            IntrQ(q_aux, &aux);
            break;
        }

        IntrQ(q_aux, &aux);
    }
    if (ok == 0)
    {
        IntrQ(q_aux, &t);
    }

    ConcatQ(q_aux, q);
    ConcatQ(q, q_aux);
}

void add_task(void *q, int **avalaible_id, int num_tasks, int exec_t, int prio, FILE *output)
{
    Task t;
    int ID = 0;

    for (; num_tasks > 0; num_tasks--)
    {
        t.exec_t = exec_t;
        t.remain_t = exec_t;
        t.prio = prio;

        while ((*avalaible_id)[ID] != 0)
        {
            ID++;
        }
        (*avalaible_id)[ID] = 1;
        t.ID = ++ID;

        InsSortQ(q, t);

        fprintf(output, "Task created successfully : ID %d.\n", ID);
    }
}

void get_task(int ID, void *q_wait, void *q_run, void *q_finish, FILE *output)
{
    int ok = 0;
    void *q_aux;
    q_aux = InitQ(sizeof(Task));
    if (ok == 0)
    {
        Task t;
        while (ExtrQ(q_run, &t))
        {
            if (t.ID == ID && ok == 0)
            {
                fprintf(output, "Task %d is running (remaining_time = %d).\n", ID, t.exec_t);
                ok = 1;
            }
            IntrQ(q_aux, &t);
        }
        ConcatQ(q_run, q_aux);
    }
    if (ok == 0)
    {
        Task t;
        while (ExtrQ(q_wait, &t))
        {
            if (t.ID == ID && ok == 0)
            {
                fprintf(output, "Task %d is waiting (remaining_time = %d).\n", ID, t.exec_t);
                ok = 1;
            }
            IntrQ(q_aux, &t);
        }
        ConcatQ(q_wait, q_aux);
    }
    if (ok == 0)
    {
        Task t;
        while (ExtrQ(q_finish, &t))
        {
            if (t.ID == ID && ok == 0)
            {
                fprintf(output, "Task %d is finished (executed_time = %d).\n", ID, t.exec_t);
                ok = 1;
            }
            IntrQ(q_aux, &t);
        }
        ConcatQ(q_finish, q_aux);
    }
    if (ok == 0)
        fprintf(output, "Task %d not found.\n", ID);
}

void get_thread(int ID, void *q, void *s, FILE *output)
{
    void *q_aux;
    q_aux = InitQ(sizeof(Task));
    void *s_aux;
    s_aux = InitS(sizeof(Thread));
    int ok = 0;
    if (ok == 0)
    {
        while (!VidaS(s))
        {
            Thread thread;
            Pop(s, &thread);
            if (thread.ID == ID && ok == 0)
            {
                fprintf(output, "Thread %d is idle.\n", ID);
                ok = 1;
            }
            Push(s_aux, &thread);
        }
        Rastoarna(s, s_aux);
    }
    if (ok == 0)
    {
        while (!VidaQ(q))
        {
            Task t;
            ExtrQ(q, &t);
            if (t.thread.ID == ID && ok == 0)
            {
                fprintf(output, "Thread %d is running task %d (remaining_time = %d).\n", ID, t.ID, t.remain_t);
                ok = 1;
            }
            IntrQ(q_aux, &t);
        }
        ConcatQ(q, q_aux);
    }
}

int run(int time, int D, void *q_run, void *q_finished, void *q_wait, void *s_thread, int **avalaible_id)
{
    Thread thread1;
    Task task1;

    int total_time = 0, total_time_aux = 0;
    if (time > D)
    {
        while (time >= D)
        {
            total_time_aux = run(D, D, q_run, q_finished, q_wait, s_thread, avalaible_id);
            if (total_time_aux > total_time)
                total_time = total_time_aux;
            time -= D;
        }
        if (time >= 0)
        {
            total_time += run(time, D, q_run, q_finished, q_wait, s_thread, avalaible_id);
            if (total_time_aux > total_time)
                total_time = total_time_aux;
        }
        return total_time;
    }

    while (!VidaQ(q_wait) && !VidaS(s_thread))
    {
        Pop(s_thread, &thread1);
        ExtrQ(q_wait, &task1);
        task1.thread.ID = thread1.ID;
        InsSortQ(q_run, task1);
    }

    Task task;
    void *q_aux;
    q_aux = InitQ(sizeof(Task));
    int ok = 0;

    while (ExtrQ(q_run, &task))
    {
        int time_remain = task.remain_t - time;
        if (time_remain <= 0)
        {
            Thread thread;
            thread.ID = task.thread.ID;
            Push(s_thread, &thread);
            IntrQ(q_finished, &task);
            (*avalaible_id)[task.ID - 1] = 0;
            if (ok == 0 || total_time < task.exec_t)
            {
                total_time = task.exec_t;
                ok = 1;
            }
        }
        else
        {
            task.remain_t = task.remain_t - time;
            IntrQ(q_aux, &task);
        }
    }
    ConcatQ(q_run, q_aux);

    Thread thread2;
    Task task2;
    while (!VidaQ(q_wait) && !VidaS(s_thread))
    {
        Pop(s_thread, &thread2);
        ExtrQ(q_wait, &task2);
        task1.thread.ID = thread2.ID;
        InsSortQ(q_run, task2);
    }

    return total_time;
}

void print_wait(void *q, FILE *output)
{
    Task t;
    void *q_aux;
    q_aux = InitQ(sizeof(Task));

    fprintf(output, "====== Waiting queue =======\n");
    fprintf(output, "[");

    if (!VidaQ(q))
    {
        ExtrQ(q, &t);
        fprintf(output, "(%d: priority = %d, remaining_time = %d)", t.ID, t.prio, t.exec_t);
        IntrQ(q_aux, &t);
        while (!VidaQ(q))
        {
            Task aux;
            ExtrQ(q, &aux);
            fprintf(output, ",\n");
            fprintf(output, "(%d: priority = %d, remaining_time = %d)", aux.ID, aux.prio, aux.exec_t);
            IntrQ(q_aux, &aux);
        }
    }

    fprintf(output, "]\n");

    ConcatQ(q, q_aux);
}

void print_run(void *q, FILE *output)
{
    Task t;
    void *q_aux;
    q_aux = InitQ(sizeof(Task));

    fprintf(output, "====== Running in parallel =======\n");
    fprintf(output, "[");

    if (!VidaQ(q))
    {
        ExtrQ(q, &t);
        fprintf(output, "(%d: priority = %d, remaining_time = %d, running_thread = %d)", t.ID, t.prio, t.remain_t, t.thread.ID);
        IntrQ(q_aux, &t);
        while (!VidaQ(q))
        {
            Task aux;
            ExtrQ(q, &aux);
            fprintf(output, ",\n");
            fprintf(output, "(%d: priority = %d, remaining_time = %d, running_thread = %d)", aux.ID, aux.prio, aux.remain_t, aux.thread.ID);
            IntrQ(q_aux, &aux);
        }
    }

    fprintf(output, "]\n");

    ConcatQ(q, q_aux);
}

void print_finish(void *q, FILE *output)
{
    Task t;
    void *q_aux;
    q_aux = InitQ(sizeof(Task));

    fprintf(output, "====== Finished queue =======\n");
    fprintf(output, "[");

    if (!VidaQ(q))
    {
        ExtrQ(q, &t);
        fprintf(output, "(%d: priority = %d, executed_time = %d)", t.ID, t.prio, t.exec_t);
        IntrQ(q_aux, &t);
        while (!VidaQ(q))
        {
            Task aux;
            ExtrQ(q, &aux);
            fprintf(output, ",\n");
            fprintf(output, "(%d: priority = %d, executed_time = %d)", aux.ID, aux.prio, aux.exec_t);
            IntrQ(q_aux, &aux);
        }
    }
    fprintf(output, "]\n");

    ConcatQ(q, q_aux);
}

int main(int argc, char *argv[])
{
    FILE *input;
    input = fopen(argv[1], "rt");
    FILE *output;
    output = fopen(argv[2], "wt");

    // number of threads and quantum of time
    int D, C, N;
    fscanf(input, "%d", &D);
    fscanf(input, "%d", &C);
    N = C * 2;

    // init stack of threads with their id-s and init the 3 queues
    void *s_thread, *q_wait, *q_run, *q_finished;

    // stack
    s_thread = InitS(sizeof(Thread));
    CreateThreadStack(s_thread, N);

    // 3 queues
    q_wait = InitQ(sizeof(Task));
    q_run = InitQ(sizeof(Task));
    q_finished = InitQ(sizeof(Task));

    // read
    char *line = malloc(256);
    int *avalaible_id = calloc(1, sizeof(int));
    int total_time = 0;

    while (fgets(line, 256, input))
    {
        char *instr = strtok(line, " ");

        if (!strcmp(instr, "add_tasks"))
        {
            char *string1, *string2, *string3;
            string1 = strtok(NULL, " ");
            string2 = strtok(NULL, " ");
            string3 = strtok(NULL, " ");

            int num_tasks, exec_t, prio;
            num_tasks = atoi(string1);
            exec_t = atoi(string2);
            prio = atoi(string3);

            add_task(q_wait, &avalaible_id, num_tasks, exec_t, prio, output);
        }
        else if (!strcmp(instr, "get_task"))
        {
            char *string1;
            string1 = strtok(NULL, " ");

            int ID;
            ID = atoi(string1);

            get_task(ID, q_wait, q_run, q_finished, output);
        }
        else if (!strcmp(instr, "get_thread"))
        {
            char *string1;
            string1 = strtok(NULL, " ");

            int ID;
            ID = atoi(string1);
            if (ID < N)
                get_thread(ID, q_run, s_thread, output);
        }
        else if (!strcmp(instr, "run"))
        {
            char *string1;
            string1 = strtok(NULL, " ");

            int time;
            time = atoi(string1);
            fprintf(output, "Running tasks for %d ms...\n", time);

            total_time += run(time, D, q_run, q_finished, q_wait, s_thread, &avalaible_id);
        }
        else if (!strcmp(instr, "print"))
        {
            char *string1;
            string1 = strtok(NULL, " \n");
            if (!strcmp(string1, "waiting"))
                print_wait(q_wait, output);
            else if (!strcmp(string1, "running"))
                print_run(q_run, output);
            else if (!strcmp(string1, "finished"))
                print_finish(q_finished, output);
        }
        else if (!strcmp(instr, "finish\n"))
        {
            while (!VidaQ(q_run) || !VidaQ(q_wait))
            {
                total_time += run(D, D, q_run, q_finished, q_wait, s_thread, &avalaible_id);
            }
            fprintf(output, "Total time: %d", total_time);
            break;
        }
    }

    DistrS(&s_thread);
    DistrQ(&q_wait);
    DistrQ(&q_run);
    DistrQ(&q_finished);
    return 0;
}