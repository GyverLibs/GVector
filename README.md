[![latest](https://img.shields.io/github/v/release/GyverLibs/GVector.svg?color=brightgreen)](https://github.com/GyverLibs/GVector/releases/latest/download/GVector.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GVector.svg)](https://registry.platformio.org/libraries/gyverlibs/GVector)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GVector?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GVector
Библиотека для работы с 2-х мерными векторами

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Использование](#usage)
- [Версии](#versions)
- [Установка](#install)
- [Баги и обратная связь](#feedback)

<a id="usage"></a>

## Использование
### Класс GVector
#### Конструктор
```cpp
float x = 0;
float y = 0;

constexpr GVector();
constexpr GVector(float x, float y);
```

#### Фабрики
```cpp
// создать из угла (единичный)
static GVector fromAngle(float rad);

// создать из полярных координат
static GVector fromPolar(float rad, float mag);

// создать нулевой
static GVector fromZero();
```

#### Статические методы
```cpp
// из радиан в градусы
static float toDeg(float rad);

// из градусов в радианы
static float toRad(float deg);

// кратчайший угол поворота из from в to (радианы)
static float shortAngle(float from, float to);

// кратчайший угол поворота из from в to (градусы)
static int shortAngleDeg(int from, int to);

// угол между
static float angleBetween(const GVector& a, const GVector& b);

// расстояние между в квадрате
static float distSq(const GVector& a, const GVector& b);

// расстояние между
static float dist(const GVector& a, const GVector& b);

// скалярное произведение (== 0 - перпендикулярны, > 0 в одну сторону, < 0 в противоположные)
static float dot(const GVector& a, const GVector& b);

// векторное произведение (< 0 — по часовой, > 0 против часовой)
static float cross(const GVector& a, const GVector& b);

// векторная проекция на другой вектор
static GVector project(const GVector& a, const GVector& b);

// проекция точки P на линию AB
static GVector projectPoint(const GVector& A, const GVector& B, const GVector& P);

// расстояние (перпендикуляр) от точки P до линии AB
static float distToLine(const GVector& A, const GVector& B, const GVector& P);

// сложить
static GVector add(const GVector& v1, const GVector& v2);
static GVector add(const GVector& v1, float s);

// вычесть
static GVector sub(const GVector& v1, const GVector& v2);
static GVector sub(const GVector& v1, float s);

// умножить
static GVector mul(const GVector& v1, const GVector& v2);
static GVector mul(const GVector& v1, float s);

// разделить
static GVector div(const GVector& v1, const GVector& v2);
static GVector div(const GVector& v1, float s);
```

#### Арифметика
```cpp
// ================ ADD ================
GVector& add(float v);
GVector& operator+=(float v);
GVector operator+(float v);

GVector& add(const GVector& v);
GVector& operator+=(const GVector& v);
GVector operator+(const GVector& v);

// ================ SUB ================
GVector& sub(float v);
GVector& operator-=(float v);
GVector operator-(float v);

GVector& sub(const GVector& v);
GVector& operator-=(const GVector& v);
GVector operator-(const GVector& v);

GVector operator-();

// ================ MUL ================
GVector& mul(float v);
GVector& operator*=(float v);
GVector operator*(float v);

GVector& mul(const GVector& v);
GVector& operator*=(const GVector& v);
GVector operator*(const GVector& v);

// ================ DIV ================
GVector& div(float v);
GVector& operator/=(float v);
GVector operator/(float v);

GVector& div(const GVector& v);
GVector& operator/=(const GVector& v);
GVector operator/(const GVector& v);
```

#### Сравнение
```cpp
// проверка равенства с учетом epsilon
bool equals(const GVector& v, float tolerance = 1e-6f);

bool operator==(const GVector& v);

bool operator!=(const GVector& v);

// проверка на нулевую длину
operator bool();
```

#### Получение
```cpp
// создать копию
GVector copy();

// длина в квадрате
float magSq();

// длина
float mag();

// скалярное произведение (== 0 - перпендикулярны, > 0 в одну сторону, < 0 в противоположные)
float dot(const GVector& v);

// векторное произведение (поворот к v: < 0 — по часовой, > 0 против часовой)
float cross(const GVector& v);

// сравнение по направлению с угловой толерантностью
bool isParallelTo(const GVector& v, float tolerance = 1e-6f);

// угол между
float angleBetween(const GVector& v);

// нормаль
GVector normal();

// нормализованная копия
GVector normalized();

// длина проекции на вектор
float projectMag(const GVector& v);

// векторная проекция на другой вектор
GVector project(const GVector& v);

// проекция точки на линию AB
GVector projectPoint(const GVector& A, const GVector& B);

// расстояние (перпендикуляр) до линии AB
float distToLine(const GVector& A, const GVector& B);

// расстояние в квадрате
float distSq(const GVector& v);

// расстояние до
float dist(const GVector& v);

// текущий угол между вектором и осью X
float heading();

// текущий угол между вектором и осью X
float headingDeg();

// проверка на ноль или epsilon
bool isZero(float epsilon = 1e-6f);
```

#### Модификация
```cpp
// установить
inline GVector& set(float x, float y);

// установить в 0
GVector& setZero();

// повернуть на угол
GVector& rotate(float rad);

// повернуть по направлению вектора
GVector& rotateTo(const GVector& target);

// повернуть на +90°
GVector& rotate90CCW();

// повернуть на -90°
GVector& rotate90CW();

// повернуть на 180 (отразить вдоль себя)
GVector& rotate180();

// отразить по оси Х
GVector& reflectX();

// отразить по оси Y
GVector& reflectY();

// отразить по нормали (должна быть нормализована)
GVector& reflect(const GVector& normal);

// нормализовать
GVector& normalize();

// установить длину
GVector& setMag(float v);

// ограничить длину сверху
GVector& limit(float mag);

// ограничить длину в диапазоне
GVector& clamp(float minm, float maxm);

// установить направление
GVector& setHeading(float rad);

// установить направление
GVector& setHeadingDeg(int deg);

// интерполировать текущий вектор к v, где t — коэффициент от 0.0 до 1.0.
GVector& lerp(const GVector& v, float t);
```

## Примеры
### Движение с отскоком
```cpp
int w = 200, h = 100;
GVector pos(w / 2, h / 2);
GVector vel(3, 2);

void loop() {
    pos += vel;
    if (pos.x >= w || pos.x < 0) {
        pos.x = constrain(pos.x, 0, w - 1);
        vel.reflectY();
    }
    if (pos.y >= h || pos.y < 0) {
        pos.y = constrain(pos.y, 0, h - 1);
        vel.reflectX();
    }
    delay(30);
}
```

### Расстояние между точками
```cpp
GVector A(10, 20);
GVector B(30, 40);
GVector AB = B - A;
float dist = AB.mag();
```

<a id="versions"></a>

## Версии
- v1.0

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **GVector** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GVector/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!

<a id="feedback"></a>

## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!

При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код