#ifndef LISTFORALL_LIBRARY_H
#define LISTFORALL_LIBRARY_H

#include <stdlib.h>
typedef struct list_t
{
    // 列表实体
    void * list;
    // 列表尾指针
    void * tail;

    // 列表大小
    size_t list_size;
    // 列表剩余空间
    size_t list_remain;
    // 元素大小
    size_t element_size;

    // 元素个数
    int element_num;

    // 向列表尾部添加元素
    void (*list_append)(struct list_t * list, void * element);
    // 在列表中查找元素并删除
    void (*list_remove)(struct list_t * list, void * element);
    // 遍历列表并执行操作
    void (*list_foreach)(struct list_t * list, void (*func)(void * element));
    // 弹出列表头部元素
    void * (*list_pop_front)(struct list_t * list);
    // 弹出列表尾部元素
    void * (*list_pop_back)(struct list_t * list);
    // 查找元素并返回
    void * (*list_find)(struct list_t * list, void * element);
    // 清空列表
    void (*list_clear)(struct list_t * list);
    // 销毁列表
    void (*list_destroy)(struct list_t * list);
}list_t;

void list_init(list_t * list, size_t element_size, int element_num);

#endif //LISTFORALL_LIBRARY_H
