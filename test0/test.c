/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-07-09 20:12:39
 * @LastEditTime : 2021-07-24 16:38:49
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/test.c
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct test
{
    int a;
} test;

int main()
{
    /* test *t = (test *)malloc(sizeof(struct test));

    t->a = 10;
    printf("before:%d\n", t->a);
    ++t->a;
    printf("after:%d\n", t->a);

    free(t);
    t = NULL;
*/
    int i = 5;
    while (1)
    {
        if (i < 0)
            return -1;
        else
        {
            printf("i = %d\n", i);
            i -= 2;
        }
    }
    printf("return -1\n");
    /*
    char buff[10] = "hello";
    printf("buff:%s, sizeof(buff):%d\n", buff, sizeof(buff));
    for (int i = 0; i < strlen(buff); ++i)
    {
        if ('\0' != buff[i])
            printf("buff[%d]=%s", i, buff[i]);
        printf("\n");
        break;
    }
    char *tmp = (char *)malloc(sizeof(strlen("hello,world") + 1));
    tmp = strcpy(tmp, buff);
    tmp[strlen(buff)] = '\0';
    for (int i = 0; i < strlen(tmp); ++i)
    {
        if ('\0' != tmp[i])
            printf("tmp[%d]=%s", i, tmp[i]);
        printf("\n");
        break;
    }
    printf("tmp:%s, sizeof(tmp):%d\n", tmp, sizeof(tmp));
    free(tmp);
    tmp = NULL;

    char c[] = "123";
    char c1[1024] = {0};
    for (int i = 0; i < 5; ++i)
    {
        printf("c1:%s, sizeof(c1):%d\n", c1, sizeof(c1));
        strncat(c1 + strlen(c1), c, strlen(c));
    } */

    return 0;
}
