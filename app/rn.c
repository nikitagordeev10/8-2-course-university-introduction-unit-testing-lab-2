/**
* rn.c - реализует функцию удаления строки после текущей
*
* Copyright (c) 2022, Nikita Gordeev <gordeev@petrsu.ru>
*
* This code is licensed under a MIT-style license.
*/

#include "_text.h"


/**
 * Удаляет строку после текущей
 */
void rn(text txt)
{
   /* Проверяем, имеется ли текст */
   if (txt == NULL) {
       fprintf(stderr, "The text doesn't exist!\n");
       return;
   }

   /* Если список изначально пуст, делать ничего не надо */
   if (txt->length == 0) {
       return;
   }

   /* Текст ненулевой длины должен содержать хотя бы одну строку */
   assert(txt->begin != NULL && txt->end != NULL);

   /* Стартуем с первого элемента списка */
   node* current = txt->cursor->line;
   if (current->next) {
       node* next = current->next;
       current->next = next->next;
       next->next->previous = current;
       free(next);
   }
}
