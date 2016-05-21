#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct stack_s stack_t;

//���� ���������� �� ��������

typedef void (*event1_fn) (stack_t *, int); //��� ������������
typedef int (*event2_fn) (stack_t *);  //��� �����������
typedef void (*stack_event) (char *);  //������������� ����������� � ������������


stack_t *stack_new ();
void stack_free (stack_t *self);

//������� ��� �����

void stack_push (stack_t *self, int element);
int stack_pop (stack_t *self);
int stack_getCount(stack_t *stack);
int stack_peek(stack_t *stack);

void stack_print (stack_t *self);

//��������

void stack_cb1 (stack_t *stack, int element);  //������� ������������
int stack_cb2 (stack_t *stack);    //������� �����������

//����������

void stack_subsEventOverFlow (stack_t *self, stack_t *observer, event1_fn callback); //�������, ������� �����������
void stack_subsEventUnderFlow (stack_t *self, stack_t *observer, event2_fn callback);

void stack_addOver (stack_t *self, stack_event ev);  //��������� ������� � ��������������
void stack_addUnder (stack_t *self, stack_event ev);

#endif
