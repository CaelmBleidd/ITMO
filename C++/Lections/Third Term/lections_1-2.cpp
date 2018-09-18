Intrusive container

Реализация, например, StarCraft

/**
  Можно оптимизировать эту реализацию
*/

set<unit> unit;
set<unit> moving_unit;

/**
  В каждом объекте, который может двигаться, будем хранить два указателя next и prev.
  Свяжем их в двусвязный список (не совсем, свяжем их в intrusive_list).
*/

struct node {
  node * next;
  node * prev;
};

struct unit {
  ...
  node link;
  ...
};

unit to_unit(node *p) {
  return (unit)((char *)p - offset(unit, link));
};

/**
  old                                    new

  2 + 1 + 2(optional) pointers           4 pointers always


  bimap

  Наивная реализация:
  map<A, B>
  map<B, A>
  Проблема в том, что если A или B большие, то придётся тратить очень много памяти просто так,
  поэтому можно использовать A* и B*.
*/

/**
  Попробуем сравнить intrusive контейнеры и не intrusive контейнеры
                  intrusive                                   non_intrusive

  size            less (?)                                    greater(?)

  number of
  allocation      smaller                                     bigger

  required        yes                                         no

  something has lost
  */

//============================================

/** multi-index containers
    Examples: bimap (два дерева, но на одних и тех же нодах), lru_cache(мапа, но которая хранит не более чем указанное число элементов,
    если пытаемся вставить больше -- выбрасываем самый старый элемент. Дерево и двусвязный список на одних и тех же нодах).
    Предположим, что мы делаем какую-нибудь штуку с паспортными данным людей. Нам нужно их хранить.
*/

struct person{
  string name;
  int age;
  person_id id;
};

map<string, person*> by_name;
map<person_id, person*> by_id;

/**
  Проблемы: безопасность исключений низкая, храним одни и те же данные несколько раз. Код с несколькими мапами параллельно часто очень плох
  в плане исключений.


  Heterogenous lookup
*/




//============================================
/** Shared pointers

  Опасно создавать несколько ШП от "Сырого" указателя, так будут неправильно созданы счётчики,
  второй ШП будет пытаться удалить уже не существующий объект.

  1. SP разрешает вам передать свой собственный deliter.
  ...
  aliasong constructor (погуглить)
  shared_ptr<my_type> q = make_shared<my_type>(1, 2, 3);
  static_pointer_cast позволяет кастить смартпоинтеры разных классов
