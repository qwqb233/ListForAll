//
// Created by qwqb233 on 2025/6/24.
//

#include "library.h"
#include <stdio.h>
// 定义一个函数，用于传入列表遍历回调函数
// 注意该函数必须为：void func(void * data)
void print_list(void * data)
{
    printf("%d\n", *(int*)data);
}


int main() {
    // 创建一个空的列表
    list_t list;
    // 初始化列表, 元素大小为 int, 最大容量为 100
    list_init(&list, sizeof(int), 100);

    // 向列表中添加元素,这里添加整数
    for (int i = 0; i < 10; i++) {
        list.list_append(&list, &i);
    }

    // 遍历列表, 并调用回调函数 print_list 打印元素
    list.list_foreach(&list, print_list);

    //弹出列表头元素
    int * pop_num = (int *) list.list_pop_front(&list);
    printf("pop_num_front: %d\n", *pop_num);
    free(pop_num);
    // 弹出列表尾元素
    int * pop_num2 =  (int *) list.list_pop_back(&list);
    printf("pop_num_back: %d\n", *pop_num2);
    free(pop_num2);
    // 遍历列表, 查看弹出效果
    list.list_foreach(&list, print_list);

    // 查找元素，找到了返回元素，没找到返回NULL
    int num = 5;
    int *find_num = (int *) list.list_find(&list, &num);
    if (find_num != NULL) printf("find element: %d\n", *find_num);
    else printf("not found element\n");

    // 移除元素 5
    list.list_remove(&list, &num);
    // 再次查找元素
    find_num = (int *) list.list_find(&list, &num);
    if (find_num != NULL) printf("find element: %d\n", *find_num);
    else printf("not found element\n");

    // 清空列表
    list.list_clear(&list);
    // 再次遍历列表, 看看清空效果
    list.list_foreach(&list, print_list);

    // 销毁列表
    list.list_destroy(&list);
    return 0;
}
