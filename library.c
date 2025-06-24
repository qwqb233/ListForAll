#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/*
 * @brief: 向列表尾部追加一个元素
 * @list: 列表
 * @element: 要追加的元素
 */
void list_append(list_t * list, void * element)
{
    if(list->list_remain == 0 || list->list_remain < list->element_size)
    {
        return;
    }
    memcpy(list->tail, element, list->element_size);
    list->tail = (char*)list->tail + list->element_size;
    list->list_remain -= list->element_size;
    list->element_num++;
}

/*
 * @brief: 从列表中删除一个元素
 * @list: 列表
 * @element: 要删除的元素
 */
void list_remove(list_t * list,void * element)
{
    if(list->list_remain == list->list_size)
        return;
    for(int i = 0; i < list->element_num; i++) {
        if (memcmp(list->list + i * list->element_size, element, list->element_size) == 0) {
            for (int j = i;j < list->element_num - 1;j++)
                memcpy(list->list + j * list->element_size, \
               list->list + (j+1) * list->element_size, \
               list->element_size);
            list->element_num--;
            list->list_remain += list->element_size;
            return;
        }
    }
}

/*
 * @brief: 查找列表中是否存在一个元素
 * @list: 列表
 * @element: 要查找的元素
 * @return: 如果存在，返回该元素的地址；否则，返回NULL
 */
void * list_find(list_t * list,void * element) {
    for (int i = 0; i < list->element_num; i++)
    {
        if (memcmp(list->list + i * list->element_size, element, list->element_size) == 0)
            return list->list + i * list->element_size;
    }
    return NULL;
}

/*
 * @brief: 清空列表
 * @list: 列表
 */
void list_clear(list_t * list)
{
    for(int i = 0; i < list->element_num; i++) {
        memset(list->list + i * list->element_size, 0, list->element_size);
        list->list_remain == list->list_size;
        list->element_num = 0;
        list->tail = list->list;
    }
}

/*
 * @brief: 遍历链表，对每个元素调用func函数
 * @list: 链表
 * @func: 回调函数
 */
void list_foreach(list_t * list, void (*func)(void * element))
{
    if(list->list_size == list->list_remain)
        return;
    for(int i = 0; i < list->element_num; i++)
    {
        func(list->list + i * list->element_size);
    }
}

/*
 * @brief: 弹出列表第一个元素
 * @list: 列表
 * @return: 弹出的元素
 */
void * list_pop_front(list_t * list)
{
    if(list->list_remain == list->list_size)
        return NULL;
    void * element = malloc(list->element_size);
    if(element != NULL)memcpy(element, list->list, list->element_size);
    else return NULL;
    for(int i = 0; i < list->element_num - 1; i++)
        memcpy(list->list + i * list->element_size, \
               list->list + (i+1) * list->element_size, \
               list->element_size);
    list->element_num--;
    list->list_remain += list->element_size;
    return element;
}

/*
 * @brief: 弹出列表最后一个元素
 * @list: 列表
 * @return: 弹出的元素
 */
void * list_pop_back(list_t * list)
{
    if(list->list_remain == list->list_size)
        return NULL;
    void * element = malloc(list->element_size);
    if(element != NULL)memcpy(element, list->tail - list->element_size, list->element_size);
    else return NULL;
    list->tail -= list->element_size;
    list->element_num--;
    list->list_remain += list->element_size;
    return element;
}

/*
 * @brief: 销毁列表
 * @list: 列表
 */
void list_destroy(list_t * list)
{
    free(list->list);
    list->list = NULL;
    list->list_size = 0;
    list->list_remain = 0;
    list->tail = NULL;
    list->element_size = 0;
    list->element_num = 0;
}

/*
 * @brief: 初始化列表
 * @list: 列表
 * @element_size: 元素大小
 * @element_num: 元素数量
 */
void list_init(list_t * list, size_t element_size, int element_num)
{
    if(list == NULL)
        return;
    list->list = calloc(element_num, element_size);
    list->list_size = element_size * element_num;
    list->list_remain = list->list_size;
    list->tail = list->list;
    list->element_size = element_size;
    list->element_num = 0;

    list->list_append = list_append;
    list->list_remove = list_remove;
    list->list_foreach = list_foreach;
    list->list_pop_front = list_pop_front;
    list->list_pop_back = list_pop_back;
    list->list_find = list_find;
    list->list_clear = list_clear;
    list->list_destroy = list_destroy;
}

