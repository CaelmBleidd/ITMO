
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
