
# C++
## 
Пусть у нас есть *большая* структура. 
``` 
struct big_struct {
	std::array<int, 10> data; 
};
```
При вызове функции `void foo(int)` передаётся копированием через регистры (У MS до четырёх, GCC до шести). Следующие аргументы будут передаваться на стек. С указателем ` int * ` то же самое.  Ссылки `int&` будут передаваться как указатели. 
При вызове `void foo (big_struct)` 

Пусть есть код: 
``` 
big_struct a; 
f(a); 
```
Есть два варианта:
```
1.  
{
	big_struct copy = a;
	f(copy); 
}
void f(big_struct&) { ... }

2. Использует компиляторы паскаля, например. 
f(a); 
void f(big_struct const& a) {
	big_struct copy = a;
	...
}
````
 Используют *все* компиляторы плюсов. Потому что копию в таком случае можно не делать, если a больше нигде не использоваться при вызове (например, rvalue). 

*Маленькие* структуры всё равно передаются в регистры (по значению). 

### Возвращение значений
`int foo()` возвращает значение в регистр. То же самое с указателями и ссылками. Если возвращаем *маленькую* структуру, то она тоже вернётся в регистры. В функции `big_struct foo()`  используется место в стеке. Вызов работает следующим образом: вызывающая сторона резервирует достаточное место для возвращения big_struct. 

``` 
big_struct f(); 
void g() {
	big_struct a = f(); 
} 
```
Как это транслируется:
```
void f(void * result) // void*, потому что на момент вызова функции конструктор ещё не вызван 
{
	...
	ctor_big_struct(result); 
}

void g() {
	char a_buf[sizeof(big_struct)];
	f(a_buf);
	big_struct& a = (big_struct&)a_buf; 
}
```
Посмотрим на такой код, сколько здесь копирований?
```
big_struct g(); 
void f(big_struct); 
f(g());
```
Здесь нет *ни одного* копирования. 
```
void h() {
	f(g());
}
```
Как работает h (результат вызова функции g -- rvalue): 
```
void f(big_struct); 
void g(void*); 
void h() {
	char tmp_buf[sizeof(big_struct)];
	g(tmp_buf); 
	big_struct& tmp = (big_struct&)tmp_buf; 
	f(tmp);
}
```
Ещё два места, где копирование **не** делается
Пусть у нас есть функция `g()`.
```
struct big_struct {
	big_struct(int, int, int); 
};

big_struct g() {
	...
	return big_struct(1, 2, 3);
}
```

Наивный вариант:
``` 
void g(void *result) {
	char tmp[sizeof(big_struct)];
	big_struct_ctor(tmp, 1, 2, 3); 
	big_struct_ctor(result, (big_struct&) tmp); 
```
В реальности:
``` 
void g(void *result) {
	big_struct_ctor(result, 1, 2, 3); 
}
```
В примере выше, даже если конструктор копирования имеет side-эффекты, он не будет вызван. 
В простонародии такое преобразование называется **Return Value Optimization (RVO)**. 

Рассмотрим другой пример:
```
big_struct g() {
	big_struct tmp(1, 2, 3); 
	...
	tmp.f(); 
	return tmp;
}
```
В таком случае тоже можно не делать копирования, для этого необходимо создать tmp на месте result.  А вот если на месте ... будет `if (...) return big_struct(4, 5, 6)`, подобное преобразование будет уже недопустимо. 
Вот что это преобразуется:
```
void g(void *result) {
	big_struct_ctor (result, 1, 2, 3); 
	...	
	(big_struct*)result -> f(); 
}
```
Последний пример кода не безопасен с точки зрения исключений, т.к. мы ожидаем, что при ошибке в `f()` не будет ничего записано в result, а в примере что-то будет. Поэтому на практике используют примерно:
``` 
try {
	(big_struct*)result -> f(); 
} catch (...) {
	(big_struct*)result -> ~big_struct(); 
	throw;
}
```
Это иногда называют **NRVO**. Её нельзя применять, если на момент создания tmp мы не знаем, будет ли он возвращён или нет. 

##
Копируем что-то большое и много:
```
std::vector<std::string> v; 
std::string s; 
v.push_back(s); 
```
Некопируемые объекты:
```
std::vector<file_descriptor> v; // В С++03 вектор с таким не будет работать
```
Как пофиксить в С++03:
`std::vector<file_descriptor*>` -- более-менее очевидное (не круто)
 `std::vector<boost::shared_ptr<file_descriptor>> v;` -- для прошаренных  (ещё менее круто) 
 А когда копировали что-то большое и много, не делали ничего,  копируется и копируется. 

### Move-семантика
Что такое move? Допустим, у нас есть конструктор копирования `string (string const&)`. Он берёт аргумент и создаёт точно такую же строчку, как передали. Однако, часто нам уже не нужно старое значение, старый объект. Идея такая: хочу создать новую строчку, которая такая же, как исходная, а исходную можешь испортить, это не имеет значения. Для большинства стандартных контейнеров он просто перебросит указатели, а в исходном занулит. Очень хорошая операция, не бросает исключения. 
Плюс в том, что многие объекты, которые не умеют копироваться, легко научить муваться. Например, непонятно, что значит скопировать файловый дескриптор, но понятно, как сделать его невалидную версию и переместить валидную. 

**NB**: если посортить вектор `auto_ptr`, многие (или все) элементы занулятся из-за строчки `T pivot = arr[i]`. 

Пусть есть функция  `push_back(...)`. Хочу понять. когда я могу испортить аргумент, который мне передали, а когда я обязан его не менять. В С++11 появилась возможность перегружать функции по lvalue и rvalue. 
Обычные ссылки `&` теперь называются lvalue-ссылки. Появились ссылки `&&`, которые называются rvalue-ссылки. 
```
int f();
int a = 5; 
int &b = a; // OK
int &&c = a; // error
int &d = f();  // error
int &&e = f(); // OK
```
Как работает `push_back` с двумя перегрузками:
```
push_back(T const&); 
push_back(T &&); 
```
Если объект lvalue или const, выберется первая перегрузка, иначе -- вторая. 
Если хотите, чтобы объект умел и копироваться, и муваться -- пишите два конструктора, например:
```
string (string const&); 
string (string &&); 
```
Оператор присваивания тоже нужно написать  дважды: копирующий и перемещающий. 

``` 
void push_back (T const& a) {
	...
	a;
	...
	a;
} // a -- lvalue

void push_back(T && a) {
	...
	a; 
	...
	a;
} // здесь а тоже lvalue. 
```
Т.е. следующий код не сработает:
```
void foo(T &&); 
void push_back(T && a) {
	foo(a); // error, т.к. a -- lvalue
}
```
Можно пофиксить таким образом: `foo(static_cast<T &&>(a))`.  Таких операций бывает много, поэтому существует специальная функция: 
```
template <typename T> 
T && move (T &obj) {
	return static_cast<T &&>(obj)l 
}
```
Как делать **не** нужно, типичная ошибка:
``` 
string foo() {
	string res = "hello"; 
	res += "world"l
	return res или return move(res)?
}
```
Здесь всё равно будет move, даже если вы ретурните локальную переменную. Надо писать просто `return res`. Написав `return move(res)`, вы подавите NRVO. 

Если ваш класс не поддерживает rvalue-ссылки, что произойдёт, когда вы напишете `std::move(a)`? Просто вызовется конструктор копирования. Поэтому стоит рассматривать move как подсказку, что здесь можно мувать, а не обязательство. Так же нужно беспокоиться о том, бросаются ли исключения в строчке `move(a)`. 
```
T* new_data = operator new(sizeof(t) * new_capacity); 
for (size_t i = 0; i != size(); ++i) 
	new (&new_data[i]) T(std::move(old_data[i])); 
```
Такое копирование не exception-safe, потому что T может не поддерживать move, и тогда вызовется обычный конструктор, поэтому так делать нельзя.
Поэтому есть два варианта. Если исключения могут возникнуть, то принимается решение просто копировать. Если же не могут, то работает реализация выше. 
Как это проверить? 
`string (string &&) noexcept ` -- `noexcept` означает, что не будет бросаться исключение. Можно использовать и в выражениях: `enable_if<noexcept(a + b)>::type`. Если у вас есть move-конструктор, следует пометить его noexcept, если он является таковым. Можно внутри скобок после `noexcept` написать *любое* булевое выражение. Например, `noexcept(false)` означает, что бросает. Деструкторы по-умолчанию помечаются как noexcept, поэтому из деструктора нельзя бросить исключение, если не будет помечено `noexcept(false)`.  ==Goto tr_1==

### SFINAE-ошибка
```
template <typename T>
typename T::type f(T); 
void f(int); 
f(42); 
```
Внутри int нет type, это приведёт к ошибке (но не хардовой, просто перегрузка не будет рассматриваться). 
**SFINAE** -- substitution failure is not an error

==tr_1== 
### Destructive-move
... 



## Perfect-forwarding 
Пусть у меня есть функция f: 
``` 
void f(int);
void f(char); 

template <typename T>
void g(T const &a) {
	f(a); 
}

template <typename T> 
void g(T &a) {
	f(a); 
}
``` 
Мы хотим как бы сохранить тип, который передали. Зачем это нужно? Например, если у меня есть `struct foo { foo(int, int, int) }`. 
`make_shared<foo>(1, 2, 3)` отфорвардит свои аргументы в конструктор foo. 
Такой тип форвардинга сохранят тип, но не сохраняет lvalue и rvalue. Независимо от пришедшего типа, `f` всегда получит lvalue. 
``` 
template <typename T> 
void f(T &&);

int a; 
int const b; 

f(a); // передаём lvalue. T -> int&
f(5); // передаём rvalue, T -> int
f(b); // передаём lvalue, T -> int const &
```
Так определили новые правила в С++11. 

Когда у нас были обычные ссылки, действовало следующее правило: 
```
typedef int& foo; 
typedef foo& bar; 
// ссылка на ссылку -- всё ещё ссылка (правило из С++03)
```

С появлением rvalue-ссылок, правило расширили:
```
&  &  -> &
&  && -> &
&& &  -> &
&& && -> && 
```
Сохраняет тип, сохраяет константность, сохраним r/l-value. 
```
template<typename T> 
void f(T&& a) 
{
	g(static_cast<T&&>(a)); 
}
```

Обычно так static_cast не пишут, существует стандартная функция:
```
template<typename T> 
T&& forward (T& a) {
	return static_cast<T&&> (a); 
}

template<typename T> 
void f(T&& a) {
	g(forward<T> (a));
}
```
Есть один *тонкий* момент между move и forward. 
В наших записях они выглядят одинаково, в библиотеке написаны по разному. В move мы не передаём темплейтные параметры, в forward мы явно передаём темплейтный параметр. 
В библиотеке:
```
template<typename T> 
T&& forward (typename remove_reference<T>::type& a);  //g(move(a))??? 
```
Теперь T не может вывестись, мы обязаны его явно передать. 

Что делать для n аргументов? 
```
template<typename ... T> // набор аргументов
void f(T&& ... a) {
	g(forward<T> (a) ...); 
}
```
Так, написан, например, `make_shared<T> (pointer)`. 

## Новая пара, новая жизнь 
### auto
```
std::vector<std::string> v; 
for (std::vector<std::string>::interator i = v.begin(); i != v.end(); ++i) {
	*i; 
}
// было -> стало
for (auto i = v.begin(); i != v.end(); ++i) {
	*i;
}
```
`auto a = f();` -- вывод типа происходит так же, как происходит в выводе типов в шаблонах. 
`auto &a = f();` -- `template <typename T> void b(T&);`

**BP:** если где-то можно написать auto, пожалуй, стоит так и делать. Однако, в некоторых случаях _явно_ написанный тип будет удобнее (повышает читаемость). 

`typedef std::vector<std::string> strings` -- ещё один способ заменить постоянное повторение в коде сложных типов. 

### Анонимные функции
Три способа передать компаратор в функцию `sort()`.
``` 
template <typename It, typename Comp> 
void sort(It first, It last, Comp comp) {
	...
}

bool abs_less(int a, int b) {
	return abs(a) < abs(b); 
}

struct abs_less1 {
	bool operator() (int a, int b) const {
		return abs(a) < abs(b);
	}
};

vector<int> v; 
sort(v.begin(), v.end(), abs_less);
sort(v.begin(), v.end(), std::less);
sort(v.begin(), v.end(), abs_less1());
```
Так жить можно, но грустно. Если это какая-то часто используемая функция, ещё ОК, но если эта функция используется один раз -- это вообще не круто. 

Как это можно было бы написать в С++11: 
```
sort(v.begin(), v.end(), [](int a, int b) {
	return abs(a) < abs(b); 
});
```
Что происходит внутри? Внутри компилятор заводит как будто бы локальную структуру. Он заводит в ней оператор круглые скобки и делает в ней то, что мы указали в теле функции. 

Что можно написать в `[]`? В них указывается, что лямбда должна захватывать из контекста. 

``` 

struct mod_less1 {
	mod_less(int n): n(n) {}
	bool operator() (int a, int b) const {
		return a % n < b % n;
	}
	int n; 
};

sort(v.begin(), v.end(), [k](int a, int b) {
	return a % k < b % k; 
}
int k;
```

В `[]` можно написать:
 -  `[]` -- ничего не нужно захватывать 
 - `[a, b, c]` -- захватить локальные переменные
 - `[&a, &b, &c]` -- захватить по ссылке 
 - `[=, &a, &b, &c]` -- а, b и c по ссылке, всё остальное по значению
 - `[&, a, b, c]` -- наоборот

Скобки у лямбы позволяют написать несколько дополнительных параметров : 
-   `[]()` -- ничего
- `[]() -> bool` -- явно указываем тип возвращаемого значения
- `[]() mutable -> bool` -- оператор `()` не const. 

Одну лямбду можно использовать в нескольких местах. 
`auto f = [](int a){};`


Такое вот не скомпилируется: 
```
auto cmp; 
...
if(flag)
	cmp = [](int a, int b) { return a < b };
else 
	cmp = [](int a, int b) { return b < a }; 
```
А вот так уже будет работать:
```
std::function<bool(int, int)> cmp; 
if(flag)
	cmp = [](int a, int b) { return a < b };
else 
	cmp = [](int a, int b) { return b < a }; 
```
Почему тогда лямбдам не назначили сразу тип std::function? 
```
bool f (int, int); 
bool y (int, int); 
bool h (int, int); 
//Динамический полиморфизм
sort(..., ..., &f); //одна и та же сортировка
sort(..., ..., &y); //просто "прыгаем" на компаратор
sort(..., ..., &h); 
//Статический полиморфизм
sort(..., ..., F()); //три разные сортировки
sort(..., ..., Y());
sort(..., ..., H());
```
Отличие по времени работы в разы. 

Оптимизация
```
for( ; ;) {
	if (cmp == &f) 
		f(a, b); 
	else if (cmp == &g)
		g(a, b); 
	else 
		cmp(a, b); 
}
```
Может быть преобразовано в: 
```
if (cmp == &f) 
	for ( ; ; ) 
		f(); 
else if (cmp == &y) 
	... 
```
Ответим, почему не `std::function`. Он в какой-то степени предполагает динамический полиморфизм. А лямбды позволяют сортам работать со статическим и работать быстрее. 

Если лямбда ничего не захватывает, она может быть приведена к указателю на функцию. 

## std::function
### type erasure
```
//std::function<bool(int, int)> cmp = [](){};

struct function {
	template <typename F>
	function (F f) :
		ptr (std::make_unique<model<F>>(std::move(f))){}
	function (function const &other) :
		ptr (other.ptr->copy());
	bool operator() (int a, int b) const {
		return ptr->call(a, b); 
	}
	
	private: 
		std::unique_ptr<concept> ptr;
};

struct function::concept {
	virtual ~concept();
	virtual unique_ptr<concept> copy() const; 
	virtual bool call(int a, int b); 
};

template <typename F> 
struct function::model : concept {
	model (F f): f(std::move(f)) {}
	unique_ptr<concept> copy() { return make_unique<model<F>>(f); }
	bool call(int a, int b) { return f(a, b); } 
	
	F f;
}
```
Примеры применения данной техники: 
- `any_iterator<int>`
- `any_range<int>`
- `any`

### Разные вещи
``` 
template <typename T, typename ... A> 
unique_ptr<T> make_unique(A && ... a) {
	return unique_ptr<T>(new T(forward<A>(a) ... )); 
}

//f(g(a...)) -> f(g(a0, a1, a2, ...))
//f(g(a)...) -> f(g(a0), g(a1), ...)
```
Несколько `...` должны иметь одинаковую длину, если мы хотим, чтобы они экспандились вместе. 

Специально для таких темплейтов существует `sizeof...` Позволяет узнать, сколько у темплейта параметров. 

Как могло бы выглядеть итерирование по шаблонам с переменным числом аргументов:
```
at<5, Ts ...>::type 

template<size_t N, typename T0, typename ... Ts>
struct at {
	typedef typename ar<N-1, Ts ...>::type type;
};

template <typename T0, typename ... Ts> 
struct ar<0, T0, Ts ... > {
	typedef T0 type;
}
```

##  Signals
Signals aka (listeners, observer) не то же самое, что UNIX-signals. 
```
struct signal { 
	struct connetion; 
	
	typedef function<void()> slot; 
		
	connetion connect(slot s) {
		slots.push_back(move(s)); 
	}
	
	void operator()() const {
		for (auto&&& s: slots) 
			try { 
				s(); 
			} catch (...) {
				log("..."); 
			}
	}
	
private:
	list<slot> slots;
}

struct signal::connection {
	connection(signal *sig, list<slot>::interator it)
								: sig(sig), it(it) {}
	void disconnect() {
		sig->slots.erase(it);
	}
private:
	signal* sig; 
	list<slot>::iterator it; 
}
```
Здесь есть _критическая_ ошибка.  "Не могу поинкрементить, неправильный итератор". Мы удалили объект из листа во время прохода по нему, если мы дисконнектнулись внутри `s`
```
void operator()() const {
	for (auto i = slots.begin(); i != slots.end(); ++i) 
		(*i)(); 
```
Как это пофиксить? Такая реализация уже имеет место быть, она даже популярна.
```
void operator()() const {
	vector<slot> copy = slots;
	for (auto i = copy.begin(); i != copy.end(); ++i) 
		(*i)(); 
```
Это чинит нашу проблему, сигнал теперь сам не ломается, но теперь у него есть очень странное свойство: когда сигнал `A` отписывает себя и сигнал `B`, сигнал `B` всё равно будет вызван. В этой реализации нет команды "Отписаться". Можно реализовать лишь "Отпишись через _какое-нибудь_ время". 

Используем bool:
```
struct signal { 
	struct connetion; 
	
	typedef function<void()> slot; 
		
	connetion connect(slot s) {
		slots.push_back(move(s)); 
	}
	
	void operator()() const {
		for(auto&& s: slots) {
			if (s.first) 
				s.second();
		slots.erase(remove_if(slots.begin(), slots.end(), [](pair<bool, slot> const& p) {return !p.first;}), slot.end());
	}
	
private:
	list<pair<bool, slot>> slots;
}
```
Выглядит, как будто этот код будет работать всегда, однако это не так. 
Call_stack:
```
signal::op()
|	A
|	|	signal::op()
|	|	|	B
|	|	|	|	disconnect
|	|	|	cleanup	
++i 
//В этом месте мы пытаемся разыменовать итератор,
//который был удалён в cleanup
```

Попробуем пофиксить:
```
struct signal { 
	struct connetion; 
	
	typedef function<void()> slot; 
		
	connetion connect(slot s) {
		slots.push_back(move(s)); 
	}
	
	void operator()() const {
		++rec_counter; 
		for (auto &&p: slots) 
			if(p.first) 
				p.second(); 
		--rec_counter; 
		if (rec_counter == 0)
			for (auto i = slots.begin(). i != slots.end(); ) 
				if(i->first)
					++i;
				else 
					i = slots.erase(i);
	}
	
private:
	size_t  rec_counter; 
	list<pair<bool, slot>> slots;
}


struct signal::connection {
	connection(signal *sig, list<slot>::interator it)
								: sig(sig), it(it) {}
	void disconnect() {
		if (sig->rec_counter == 0)
			sig.slots.erase(it);
		else 
			if->first = false;
	}
private:
	signal* sig; 
	list<slot>::iterator it; 
}

```
### Reentrancy - связанная с этим проблема
## Bind и variadic-templates 
```
void f(int, int, int) ; 
void g(int, int);
bind(f, 1, 2, 3)(); //f(1, 2, 3)
bind(f, 4, _1, 5)(6); //f(4, 6, 5) _1 == первый элемент, который передали в скобках
bind(f, _3, _2, _1)(7, 8, 9) //f(9, 8, 7)
bind(f, _2, _2, _3)(10, 11, 12) //f(11, 11, 12)
bind(f, _1, bind(g, _2, 42), 43)(44, 45) //f(44, g(45, 42), 43)
```
`_1` называется `std::placeholders<N>`

`bind(r, 1, 2, _1) (3) ` // 1, 2, _1, = b~i~, 3 = a~i~

```
template<typename F, typename ... Bs>
bind_t <F, Bs ...> bind(F f, Bs ... bs) {
	return bind_t<F, Br ...>(move(f), move(bs)...);
	}	
}

template <typename F, typename ... Bs> 
struct bind_t {
	bind_t(F f, Bs bs) : f(move(f)), gs(move(bs)...); 
	tuple<G<Bs>...> gs; //куда-то сюда вставить F f
}

template <typename T>
struct G {
	G(T value) : value(move(value)) {}
	template<typename ... As>
	T operator()(As const& ... as) {
		return value;
	}
};

template <size_t N>
struct G<placeholders<N>> {
	template <typename A, typename ... As> 
		auto operator()(A const& a0, As const& ... as) {
			return G<N-1>()(as);
		}
}

template <>
struct G<placeholders<0>> {
	template<typename A, typename ... As>
	A operator(A const& a, As const& ... as) {
		return a; 
	}
}

teamplate <typename ... As, size_t Indices>
auto call(index_tuple<Indices...>, As const& ... as) {
	return f(get<Indices>(gs)(as ...)...); 
}

template <typename ... As>
auto operator()(As const& as) const {
	return call(make_index_tuple<sizeof ...(Bs)>(), as ...); 
}

template <size_t N, size_t ... Indices>
struct make_index_tuple {
	typedef make_index_tuple<N - 1, N - 1, Indices ...>::type type;
};

template<size_t ... Indices> 
struct make_index_tuple <0>{
	typedef index_tuple<Indices ...> type; 
};
```


# Lecture 5 (various problems and their solutions with different features)

## [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#stdcommon_type-decltypeintroduction)std::common_type, decltype(introduction).

#### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#problem-1)Problem 1

```
vector<int> g(int, float)
char g(string, int)

template  <typename T>
T* g(T, T*)

template<typename ... T>
???	f(T&& ... args) { // how to code return type?
		return g(std::forward<T>(args)...);
}

```

#### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#problem-2)Problem 2

```
template <typename U, typename V>
??? max(U const& u, V const& v) {
	return u < v ? v : u;
}

```

#### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#solution)Solution

```
template <typename U, typename V>
typename std::common_type<U, V>:type max(U const& u, V const& v) {
	return u < v ? v : u;
}

```

It is cool that we can code  `common_type`  on our own. In boost that problem occurred also. As a result  `result_of`  was created to deal with it.

**NB:**  If you look at standard library you will notice that many staff is written with  `result_type`  which was implemented with  `typedef`.

However, why should we think about return types, when compilator should know it. Let's try to ask it.

```
//It is incorrect code
template<typename ... T>
decltype(g(std::forward<T>(args)...) f(T&& ... args) {
		return g(std::forward<T>(args)...);
}

```

This code doesn't work because we use args before it's declaration. We have 2 ways(tricks) to cope with it.

#### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#1-st-way-c11-trailing-return-type)1-st way. (C++11). Trailing return type

```
template<typename ... T>
auto  f(T&& ... args) -> decltype(g(std::forward<T>(args)...){
		return g(std::forward<T>(args)...);
}

```

We declare function and then use syntax to get the return type. What is more, we don't have any problems with variables. It is nonstandard usage of C++11 features. Not popular.

#### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#2-nd-way)2-nd way.

```
template<typename ... T>
auto  f(T&& ... args) -> decltype(g(std::forward<T>(T())...){
		return g(std::forward<T>(args)...);
}

```

Possible problems:

1.  T might not have default constructor. So we may have a substitution failure.
2.  `args`  is  _lvalue_.  `T()`  is  _rvalue_.

Inside  `sizeof()`  and  `decltype()`  we have non-evaluating values.

How to get a lvalue:

```
template<typename T>
T& declval();

```

So as the result we have:

```
template<typename ... T>
auto  f(T&& ... args) -> decltype(g(std::forward<T>(declval<T>())...){
		return g(std::forward<T>(args)...);
}

```

What is written in  **cppreference**: "Transforms any type to a reference of this type. Can be used only in non-evaluating context."

#### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#in-c14)In C++14.

```
template<typename ... T>
auto  f(T&& ... args) {
		return g(std::forward<T>(args)...);
}

```

However, function signature don't take part in SFINAE any more. So we can substitute anything but the error will occur inside a function. So this code is not fully equivalent to previous one.

## [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#decltype)Decltype

The story is amazing. We have two decltypes.

1.  `decltype(var)`  - returns the type.
    
    ```
     int a;
     decltype(a);	int
     int& b;
     dectype(b);		int&
    
    ```
    
2.  `dectype(expr)`
    
    **BREAKING NEWS:**  We have not only  `lvalue`  and  `rvalue`
    

```
graph LR
l[lvalue]
r[rvalue] --> pr[prvalue]
r-->px[xvalue]

```

```
T f();
T a = f(); - f() - prvalue (pure rvalue)

T&& f();
T a = f(); - f() -xvalue;

```

How 2-nd decltype(expr) works:

```
//Checks expression type and returns:
prvalue -> T
lvalue -> T&
xvalue -> T&&

```

## [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#nullptr)Nullptr

In C++03 we could use  `0`  as a null pointer.

```
int* p = 0; // OK
 
int a = 0;
int* p = a; //Error

```

`int`  can't be conversed to a pointer. But  `0`  can be considered as null pointer.

This phenomena may cause some problems.

```
void f(void*);
void f(int);

f(0); //f(int)

```

Another problem:

```
void g(void*);
template<typename T<
void f(T&& arg) {
	g(forward<T>(arg));
}
g(0);// works;
f(0);// error
f<int>(0) ok

```

Ok, from now on we have  `nullptr`  with a type  `nullptr_t`.

```
f(nullptr);
f<nullptr_t>

```

**Simple conclusion:**  use  `nullptr`  instead of  `0`  as a pointer, because of problem described above.

Theoretically we can implement  `nullptr_t`.

```
// Not full implementation.
template<typename R, typename T>
using mem_ptr = R T::*;

struct nullptr_t {
	template<typename T>
	operator T*() const {
		return 0;
	}
	template<typename R, typename T>
	operator mem_ptr<R, T, A...>() const {
		return 0;
	}
}

typedef decltype(nullptr) nullptr_t;

//What's going on?!
A*
A -> int(int)
	 int(*)(int)

B C::*
B -> int(int)
int (C::*)(int)

```

Modifying:

```
struct nullptr_t {
	template<typename T>
	operator T*() const {
		return 0;
	}
	template<typename R, typename T>
	operator R T::* () const {
		return 0;
	}
}

```

#### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#pointers-to-members)Pointers to members.

```
struct foo {
	int bar;
}

int foo::*p = &foo::bar;
foo v;
v.*p;
foo* p;
v->*p;

```

## [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#c17-expanding-of-standard-library)C++17 (expanding of standard library)

### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#stdoptional)std::optional

Sometimes we want want to store something or nothing. Examples:

1.  We want to save the date of last modification. But how can you react if there were no modifications at all.
2.  We store the file changes but can't use them immediately. How to store it if there were no changes.

**Question:**  Why should not we use exceptions?  **Answer:**  It depends. Sometimes we don't want to throw exceptions. And it is better to use them when we want to send information up.
```
optional<int> a;
optional<int> a = 5;
a = nullopt; // a is empty
if (a) {
	*a;
}

struct foo {
	foo(int, int, int);
}

optional<foo> a(in_place, 1, 2, 3) // create an optional object of foo with constructor agguments (1, 2, 3)

```

`in_place`  is a special marker for constructor. In fact, there are other markers for other constructors.

```
a.emplace(4, 5, 6); // if optional is already created.

```

#### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#comparing-unique_ptr-and-optional)Comparing unique_ptr and optional

1.  `unique_ptr`  stores objects in the heap while  `optional`  stores it inside itself(heap/stack). Objects may be very big, so in this case it is better to store them with  `unique_ptr`. If object is small and we want to store it as long as optional object it is better to use  `optional`.
    
2.  `unique_ptr`  is polymorphic. So it can store derived objects.
    
3.  **pimpl**  - pointer to implementation.
    
    // 1-st case struct foo { bar x; // must include bar }
    
    //2-nd case struct bar; struct foo { bar* x; //declaration is enough. }
    

In second case it is easier to add and remove members without breaking the user's code. Headers are usually compact. We can use our structure, but its implementation will be included or implemented in  **.cpp**.

```
struct foo_impl;
struct foo {
	...
	...
	...
	unique_ptr<foo_impl> imp;
}

```

Using of  `unique_ptr`  allows to have less dependencies and more flexible code.

4.  `unique_ptr`  keep data in one place, while  `optional`  may copy this data many times. In addition, class implemented with  `unique_ptr`  are easily movable.

Sometimes classes may have a very complicated state. At some moment, some members don't have any sense.  `optional`may make code more readable, but it is still imperfect and have disadvantages.

## [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture5.md#variant)Variant

```
variant<A, B, C> v; // may be of any of A, B, C types.

```

Imagine such situation:

```
variant<std::string, int> v = "hello"; // But we are giving char*

```

Variant will take a type which will be defined by overload resolution.

How to work with  `variant`:

```
struct visitor {
	void operator()(A) const;
	void operator()(B) const;
	...
}

visit(visitor(), v)

```

In case  `visit`  switches across all the types and takes the most appropriate.

```
variant<A, B> ab;
variant<C, D> cd;
visit(visitor(), ab, cd)

```

So visitor must know combinations:

-   (A, C)
-   (A, D)
-   (B, C)
-   (B, D)

# Lecture 6 (Multi threading)

Types of parallelism:

-   _Instruction Level Parallelism(TLP)_  - doesn't concern programmer.
-   _Simple Instruction Multiple Date(SIMD)_  - having multiple data in register and making one operation. We can store in long register multiple data and make one add operation with two registers. As a result in one operation we have multiple results. This method is usually used in video cards, because they have long SIMD. It is a really good boost for calculations. Theoretically, we can create such instructions. Ways of usage: writing assembler code, working with compilator features, compilator can vectorise our calculations.
-   _Hyper-threading_
-   _Multi core_

```
#include<thread>
int main() {
	std::thread t([]
	{
		std::cout << "hello";
	}
	//one of the next ways
	->t.join(); // wait while the thread is over
	->t.detach(); // thread works on his own. 
}	

```

**BUT if main is over  `cout`  will be deleted. Never use  `detach`. It must be used in a very-very rare situations**.

### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture6.md#code-example)Code example.

_The next code will be pseudo code. Because in C++ it all will be undefined behavior_  Let's imagine that we are a bankers and have a lot of accounts.

```
int accounts[10000];
void transport(size_t from, size_t to, int amount) {
	if (accounts[from] < amount) {
		throw runtime_error("insufficient funds");
	}
	accounts[from] -= amount;
	accounts[to] += amount;
}

```

This code is not usable by multi threading, because it is possible that two guys can use it, at the same time pass  `if`  and then get a negative amount of money. Because we can not guarantee how  `-=`  will work it is undefined behavior. That is why it is only pseudo code. Such error is called  **race condition**. The simplest way to make this code correct is to use  **mutex**.

## [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture6.md#mutex)Mutex

Mutex can be read as  _Mutual ex-closure_

The most important operations:

-   lock() - waits until mutex is unlocked and locks it
-   unlock() - unlocks mutex;

```
int accounts[10000];
std::mutex m;
void transport(size_t from, size_t to, int amount) {
	m.lock(); // waits until m is unlocked and then lock it;
	if (accounts[from] < amount) {
		throw runtime_error("insufficient funds"); // in case of exception we are locked forever.BAD!
	}
	accounts[from] -= amount;
	accounts[to] += amount;
	m.unlock(); // unlocks m;
}

```

```
//Incorrect. But if we consider that this code is performed correnctly in case of multi threading it is ok.
struct mutex
{
	void lock() {
		while (locked) {
			sched_gield(); // I'm busy let other mutex work;
			locked = true;
		}
	}
	bool unlock() { locked = false;}
	
	bool locked;
}

```

**futex**  - mutex that lulls thread until is unlocked.

```
//Now we have a correct code!
int accounts[10000];
std::mutex m;
void transport(size_t from, size_t to, int amount) {
	std::lock_guard<std::mutex> lg(m); // solves the problem with exception.
	if (accounts[from] < amount) {
		throw runtime_error("insufficient funds");
	}
	accounts[from] -= amount;
	accounts[to] += amount;
}

```

Let's create a correct  `mutex`;

```
struct mutex {
	void lock() {
		while (exchange(locked, true)) { // exchange is atomic
			sched_gield(); // I'm busy let other mutex work;
			locked = true;
		}
	}
	bool unlock() { locked = false;} // atomic too
	
	bool locked = false;
}

```

As a result we can consider that  `mutex`  is not very expensive.

## [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture6.md#amdal-lawawesome-formula)Amdal law.(Awesome formula)

Tp - what we can do parallel Ts - what we can do sequentially Tp + Ts - amount of work N - number of threads

Tp / N + Ts - boost We can consider N as infinity then the boost is just Ts.

### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture6.md#lets-continue-our-task)Let's continue our task

```
//Now we have a correct code!
int accounts[10000];
std::mutex m[10000];
void transport(size_t from, size_t to, int amount) {
	if (from == to) { return ;}
	std::lock_guard<std::mutex> lg(m[from]); // solves the problem with exception.
	//If we have to transfers (a->b && b->a) we get bad_lock. BAD!
	if (accounts[from] < amount) {
		throw runtime_error("insufficient funds");
	}
	accounts[from] -= amount;
	accounts[to] += amount;
}

```

If we find loop than it is bad. Because a problem like in example above occurs. In our case we have a loop m1--m2--m5--m1.

```
graph LR
m1[m1]
m2[m2]
m3[m3]
m4[m4]
m5[m5]
m1 --> m2
m1 --> m3
m2 --> m3
m2 --> m5
m5 --> m1
m4 --> m1
m4 --> m2

```

**NB:**  The number of stacks is limited by the size of stacks. That's why it depends on your memory configurations.

Nevertheless, 10000 mutexes is too many. We can create only 10, for example. As a result, we have less parallelism but less memory problems because not every but some mutexes may be quite expensive.

### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture6.md#stdatomic)std::atomic

```
struct mutex {
	void lock() {
		while (locked.exchange(true));
	}
	bool unlock() { locked.store(false)}
	
	std::atomic<bool> locked; //std::atomic maked type atomic_
}

```

-   compare_exchange - very useful tool in atomic types.
-   Compilator can't change positions of instruction between atomic types. In addition, it is guaranteed that everything above atomic on a action moment everything is fully completed and performed.

### [](https://github.com/IvanGusevGit/CPlusPlus-2018-/blob/master/Lecture6.md#new-example)New example

```
template<typename T>
struct queue {
	void push(T val) {
		lock_guard<mutex> lg(m);
		q.push_back(move(val));
	}
	
	bool empty() const {
		lock_guard<mutex> lg(m);
		return q.empty;
	}
	
	T pop() {
		lock_guard<mutex> lg(m);
		assert(q.empty());
		T res = move(q.front());
		q.pop_front();
		return res;
	}
	
	mutable mutex m; // mutable means it can be changed in const-methods
	deque<T> q;
}

```

The PROBLEM is that two guys have checked empty(). One pops, queue becomes empty, second one tries to pop empty queue and gets error. To deal with such problems we have to change our interface and create some functions like  _try_pop_or something like that.

Let's discuss  **std::condition_variable**.

-   _wait()_  - makes thread sleep it is waked.
-   _notify_one()_  - wakes one of waiting threads.
-   _notify_all()_  - wakes all waiting threads.

Mutex, condition_variable are  **not fair**  as most of multi thread . No guaranteed that a thread after a limited number of skipping forward we will finally get a control.

```
template<typename T>
struct queue {
	void push(T val) {
		lock_guard<mutex> lg(m);
		q.push_back(move(val));
		non_empty.notify_all();
	}
	
	bool empty() const {
		lock_guard<mutex> lg(m);
		return q.empty;
	}
	
	T pop() {
		lock_guard<mutex> lg(m);
		if (q.empty()) {
			non_empty.wait();
		}
		T res = move(q.front());
		q.pop_front();
		return res;
	}
	
	//mutex !bug! in push and pop

	mutable mutex m;
	condition_variable non_empty; // Attention!
	deque<T> q;
}

```

Fixing code.

```
template<typename T>
struct queue {
	void push(T val) {
		lock_guard<mutex> lg(m);
		q.push_back(move(val));
		non_empty.notify_all();
	}
	
	bool empty() const {
		lock_guard<mutex> lg(m);
		return q.empty;
	}
	
	T pop() {
		m.lock();
		while (q.empty()) {
			m.unlock();
			//MISTAKE!!!Let's imagine that at this monent someone locks mutex!
			non_empty.wait();
			m.lock();
		}
		T res = move(q.front());
		q.pop_front();
		m.unlock();
		return res;
	}

	mutable mutex m;
	condition_variable non_empty; // Attention!
	deque<T> q;
}

```

To solve this problem we have to know how to unlock and wait in atomic way. Here  **std::unique_lock**  comes.

```
template<typename T>
struct queue {
	void push(T val) {
		lock_guard<mutex> lg(m);
		q.push_back(move(val));
		non_empty.notify_all();
	}
	
	bool empty() const {
		lock_guard<mutex> lg(m);
		return q.empty;
	}
	
	T pop() {
		unique_lock<mutex> lock(m);
		while (q.empty()) {
			non_empty.wait();
		}
		T res = move(q.front());
		q.pop_front();
		return res;
	}

mutable mutex m:
	condition_variable non_empty; // Attention!
	deque<T> q;
}

```

However, after push we wake all, give an element for one who wants to pop and then all lulls. This problem is called  **thundering_herd**. At this moments use  `notify_one()`.

```
template<typename T>
struct queue {
	void push(T val) {
		lock_guard<mutex> lg(m);
		q.push_back(move(val));
		non_empty.notify_one(); // Only one wakes up.
	}
	
	bool empty() const {
		lock_guard<mutex> lg(m);
		return q.empty;
	}
	
	T pop() {
		unique_lock<mutex> lock(m);
		while (q.empty()) {
			non_empty.wait();
		}
		T res = move(q.front());
		q.pop_front();
		return res;
	}

mutable mutex m:
	condition_variable non_empty;
	deque<T> q;
}
```

## Продолжение многопоточности 
- Пара `promise + future`.  
`promise` отдаётся тому, кто что-то вычисляет, кто хочет получить получает `future`. 
Параметры `promise`:
`set-value` -- atomically stores the  `value`  into the shared state and makes the state ready.
`set-exception` -- atomically stores the exception pointer  `p`  into the shared state and makes the state ready.
Параметры `future`:
`get` -- Returns the value stored in the _shared state_ (or throws its exception) when the _shared state_ is _ready_.
- `packaged_task`  -- обёртка над `promise + future`
```
T f(); 
promise<T>; 
void(); 
```
- `std::async` 
`T f() -> future<T>`

__thread-pool__ -- концепция, при которой некоторое количество потоков не завершается, а складывается. Потом, когда придёт новая задача, можно воспользоваться одним из уже имеющихся потоков. 

 

> Это такой набор примитивов, просто о нём знайте. 
> 
__Cancellation point__ - точка в треде, в которой он сможет сам корректно завершиться, она необходима для того чтобы корректно освобождать ресурсы(RAII) и вообще просто корректной(ожидаемой) работы остановки треда
В `std` такого нет, вероятно это(яне нашел) `boost::thread::cancellation_point`. Однако есть [статья](https://habr.com/post/306332/) про реализацию `cancellation_token`
Cancellation point не добавляют в стандарт, потому что они тяжело коопрерируются с мютексами и `condition_variable`, а также замедление работы. Поэтому все пишут это сами.

__TLS (thread local storage)__ -- глобальные переменные, которые для каждого потока свои. Зачем? Иногда мы не хотим протаскивать через ф-ии некоторые параметры. 

__STM (software transactional memory)__ -- его не используют, но оно есть в теории. Мы хотим, чтобы кусок кода исполнился как будто он неделимый кусок. Т.е. либо мы видим целиком результат, либо не видим его вообще. Проблема в том, что на практике они оказываются медленными. 

__HTM__ -- у процессора есть кэш. Если мы начинаем транзакцию, и в L1 (например) меняются данные, никто другой не может оттуда прочитать, пока мы их не отдадим. Когда мы закончили, мы взяли и всем отдали эти данные. Проблема: пока транзакции делаются и всё хорошо -- всё работает. Как только одна транзакция рухнет, этот поток попробует взять мьютекс. Это обрушит __все__ остальные потоки. Они тоже попробуют взять мьютекс. Проблема.

Человек смог придумать довольно мало примитивов, которые удовлетворяли бы всех. 
Следующие примитивы -- `map` и `reduce`. 
В `map` можно легко распараллелить применение действий ко многим элементам одинаковых ( a->b, a~2~->b~2~, ...),  `reduce` для выражений вида (a * b * c * ... d * e * f, где разные потоки будут вычислять разные части произведения). 

`read` -- сидим  и ждём, пока какие-то данные не придут. Синхронный подход (blocking)
`non-blocking` -- другой подход. 
На одном потоке можно не успеть обработать большое количество данных. Например, если мы читаем 1Гбит/c проблем особых не возникнет. При обработке 10, а тем более 40Гбит/с возникнут большие проблемы даже при попытке записи этих данных, тем более при каких-либо действиях с ними. Поэтому обычно высоконагруженные сетевые системы не делают ничего серьёзного с данными: они просто получают их и перебрасывают куда-нибудь ещё. 

Не все задачи паралеллятся. Какие задачи вообще стоит пытаться распараллелить? 
Общие ресурсы:
- Пропускная способность памяти (__Memory bandwidth__)
- Кэши процессора (__caches__)
- __Hyper-threading__ -- общие __execution units__ 
- __Power usage__ -- давно встала проблема охлаждения процессоров. Поэтому мы вынуждены ограничивать максимальную частоту процессора, чтобы не вызывать тротлинг. 

Почему ещё распараллеливание может быть не очень хорошим? 
- __sharing__
- __false-sharing__
```
// sharing
++n;
// запускаю m потоков, каждый из которых увеличивает счётчик
// на одном потоке на компе Вани значение дошло до 320млн 
// на двух потоках 45-47млн (они работают на разных ядрах)
// на двух иногда достигается 240млн, если они работают на одном ядре в разных 
// гипертредингах  
// на трёх потоках 46млн
// на четырёх потоках 49млн 
```
```
// false-sharing
struct foo {
    int x;
    int y; 
};

static struct foo f;

/* The two following functions are running concurrently: */

int sum_a(void)
{
    int s = 0;
    int i;
    for (i = 0; i < 1000000; ++i)
        s += f.x;
    return s;
}

void inc_b(void)
{
    int i;
    for (i = 0; i < 1000000; ++i)
        ++f.y;
}
```
false-sharing -- потоки работают на разных ядрах, но имеют общую кэш-линию. 
В программах встречаются не так часто, но если встречаются, то последствия могут быть достаточно серьёзными. 

Примеры программ, где можно использовать другие механизмы (кроме многопоточности):
- __message loop__
> Я -- поток, и я хочу ждать сотни разных событий.  Хочу ждать, пока данные придут. Хочу ждать, пока пользователь нажмёт на кнопку и тд.

Один вариант -- крутиться в цикле и ждать, пока что-нибудь произойдёт. Таким образом работает подавляющее большинство UI программ.
 `QApplication.run()` в `QT` так и делает. Достали событие -- вызвали чувака.  
- __fiber__
Нам сыпятся данные в формате json. Мы не хотим по какой-то причине прочитать всё и спарсить, а хотим по частям. Можно было бы завести поток, который бы немного читал, немного парсил, если данных нет -- немного висел. Мы получим все минусы потоков, о которых говорилось выше (например, что делать, если новых данных нет и не будет, а вы висите в риде).
fiber ведут себя как потоке, но чтобы он начал работать, нужно явно указать "Хочу переключиться на тот fiber". Тогда ваш fiber заснёт, а тот начнёт работать. 

> Если вы хотите использовать вычислительную мощность процессора, вы вынуждены будете использовать потоки. Если же всё, что вы хотите, это ждать -- есть другие, более пригодные для этого механизмы.

 
