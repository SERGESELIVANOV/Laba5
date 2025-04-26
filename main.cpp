#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "PatternTemplates.h"
#include <vector>
#include <list>


using namespace std;
 class MP3_player
 {
 public:
    int Memory;
    wstring Size;
    wstring Screen_resolution;
    wstring Color;
    MP3_player();
    void Get_Size() const {wcout << L"Размер плеера "<< Size << endl;}
    void Get_Color() const {wcout << L"Цвет плеера " << Color << endl;}
    void Get_memory() const {wcout << L"Память ровна " << Memory << L" Гб" << endl;}
    void Get_screen_resolution() const {wcout << L"Разрешение экрана равно " << Screen_resolution << endl;}
    virtual void rewind_music() = 0;
    virtual void add_songs() = 0;
    virtual void switch_new_song() = 0;
    virtual ~MP3_player();
 };

 MP3_player::MP3_player()
 {
    wcout << L"Создание музыкального плеера" << endl;
 }

 MP3_player::~MP3_player()
 {
     wcout << L"Удаление элемента MP3_player" << endl;
 }

 class MP3_cassette_players: public MP3_player
 {
 public:
   MP3_cassette_players();
   ~MP3_cassette_players();
   void add_songs() {wcout << L"Заменим касету в плеере" << endl;}
   void rewind_music() {wcout << L"Скурутить плёнку на плеере" << endl;}
   void switch_new_song() {wcout << L"Перекрутить плёнку на нужную песню" << endl;}
 };

 MP3_cassette_players::MP3_cassette_players()
 {
     wcout << L"Создание касетного плеера" << endl;
     Size = L"20*10*10";
     Memory = 4;
     Screen_resolution = L"Экрана нет";
     Color = L"Красный";
 }

 MP3_cassette_players::~MP3_cassette_players()
 {
      wcout << L"Удаление касетного плеера" << endl;
 }


 class MP3_Hirez_players: public MP3_player
 {
public:
    MP3_Hirez_players();
    ~MP3_Hirez_players();
    void rewind_music() {wcout << L"Задержать кнопку переключения песен" << endl;}
    void add_songs() {wcout << L"Поставитьт другую Sd карту" << endl;}
    void switch_new_song() {wcout << L"Нажать два раза на кнопку переключения песен" << endl;}
 };

 MP3_Hirez_players::MP3_Hirez_players()
 {
     wcout << L"Создание хайрез плеера" << endl;
     Size = L"5*5*5";
     Memory = 512;
     Screen_resolution = L"1920*1080";
     Color = L"Синий";
 }

 MP3_Hirez_players::~MP3_Hirez_players()
 {
      wcout << L"Удаление элемента хайрез плеера" << endl;
 }

 class MP3_player_sensor_screen: public MP3_player
{
public:
    MP3_player_sensor_screen();
    ~MP3_player_sensor_screen();
    void rewind_music() {wcout << L"Перетащить ползунок обозначающий проигрование песен" << endl;}
    void add_songs() {wcout << L"Скачать песни с интернета" << endl;}
    void switch_new_song() {wcout << L"Провести влево по экранну" << endl;}
};

MP3_player_sensor_screen::MP3_player_sensor_screen()
{
    wcout << L"Создание плеера с сенсорным управлениием" << endl;
    Size = L"6*10*5";
    Memory = 100;
    Screen_resolution = L"2048*1536";
    Color = L"Серый";
}

MP3_player_sensor_screen::~MP3_player_sensor_screen()
{
     wcout << L"Удаление элемента плеера с сенсорным управлением" << endl;
}


// реализация паттерна "Фабричный метод"
enum class MP3_player_type: int
{
    MP3_cassette_players = 1,
    MP3_Hirez_players = 2,
    MP3_player_sensor_screen = 3,
    undefined = 0
};

MP3_player *create_MP3_player(MP3_player_type type)
{
    MP3_player *new_MP3_player = nullptr;
    if (type == MP3_player_type::MP3_cassette_players)
    {
       return new_MP3_player = new MP3_cassette_players;
    }
    else if (type == MP3_player_type::MP3_Hirez_players)
    {
        return new_MP3_player = new MP3_Hirez_players;
    }
    else if(type == MP3_player_type::MP3_player_sensor_screen)
    {
        return new_MP3_player = new MP3_player_sensor_screen;
    }
    else
    {
       return new_MP3_player = nullptr;
    }
}


// Функция, позволяющая "Переключиться на новую песню" на всех плеерах из любого созданого нами контейнера
void Switch_ALL(Iterator<MP3_player*> *it)
{
    for(it->First(); !it->Is_Done(); it->Next())
    {
        MP3_player *current_MP3_player = it -> Get_Current();
        current_MP3_player -> switch_new_song();
    }
}

//Декоратор итератора для выделения mp3_player по цвету
class MP3_Plaer_Color_Decorator : public Iterator_Decorator<class MP3_player*>
{
private:
    wstring Target_Color;
public:
    MP3_Plaer_Color_Decorator(Iterator<class MP3_player*> *it, wstring color) : Iterator_Decorator<MP3_player*>(it),Target_Color(color){}
    void First()
    {
        It->First();
        while(!It->Is_Done() && It->Get_Current()->Color != Target_Color)
        {
            It->Next();
        }
    }
    void Next()
    {
        do
        {
            It->Next();
        }while(!It->Is_Done()&& It->Get_Current()->Color != Target_Color);
    }
};

//Декоратор итератора для выделения mp3_player по памяти
class MP3_Plaer_Memory_Decorator : public Iterator_Decorator<class MP3_player*>
{
private:
    int Target_Memory;
public:
    MP3_Plaer_Memory_Decorator(Iterator<class MP3_player*> *it, int memory) : Iterator_Decorator<MP3_player*>(it),Target_Memory(memory){}
    void First()
    {
      It->First();
        while(!It->Is_Done() && It->Get_Current()->Memory <= Target_Memory)
        {
            It->Next();
        }
    }
     void Next()
    {
        do
        {
            It->Next();
        }while(!It->Is_Done()&& It->Get_Current()->Memory <= Target_Memory);
    }
};

//Декоратор итератора для выделения mp3_plaer по разрешению экранна
class MP3_Plaer_Screen_resolution_Decorator : public Iterator_Decorator<class MP3_player*>
{
private:
    wstring Target_Screen_resolution;
public:
    MP3_Plaer_Screen_resolution_Decorator(Iterator<class MP3_player*> *it, wstring screen) : Iterator_Decorator<MP3_player*>(it),Target_Screen_resolution(screen){}
    void First()
    {
        It->First();
        while(!It->Is_Done() && It->Get_Current()->Screen_resolution != Target_Screen_resolution)
        {
            It->Next();
        }
    }
    void Next()
    {
        do
        {
            It->Next();
        }while(!It->Is_Done()&& It->Get_Current()->Screen_resolution != Target_Screen_resolution);
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    // создадим элементы каждого из  4 классов,выведим для каждого элемента его атрибуты
    MP3_player *new_player1 = new MP3_cassette_players;
    new_player1 -> Get_Color();
    new_player1->Get_memory();
    new_player1->Get_screen_resolution();
    new_player1->Get_Size();
    cout << endl;
    MP3_player *new_player2 = new MP3_Hirez_players;
    new_player2 -> Get_Color();
    new_player2->Get_memory();
    new_player2->Get_screen_resolution();
    new_player2->Get_Size();
    cout << endl;
    MP3_player *new_player3 = new MP3_player_sensor_screen;
    new_player3 -> Get_Color();
    new_player3->Get_memory();
    new_player3->Get_screen_resolution();
    new_player3->Get_Size();
    cout << endl;
    //Перемотаем песню на каждом плеере
    wcout << L"Перемотка песни на new_player1" << endl;
    new_player1->rewind_music();
    cout << endl;
    wcout << L"Перемотка песни на new_player2" << endl;
    new_player2->rewind_music();
    cout << endl;
    wcout << L"Перемотка песни на new_player3" << endl;
    new_player3->rewind_music();
    cout << endl;
    // Добавим новвые песни в наши MP-3 плееры
    wcout << L"добавление новой песни на new_player1" << endl;
    new_player1->add_songs();
    cout << endl;
    wcout << L"добавление новой песни на new_player2" << endl;
    new_player2->add_songs();
    cout << endl;
    wcout << L"добавление новой песни на new_player3" << endl;
    new_player3->add_songs();
    cout << endl;
    // Переключимся на новую песню на каждом плеере
    wcout << L"переключимся на новую песню, на new_player1" << endl;
    new_player1->switch_new_song();
    cout << endl;
    wcout << L"переключимся на новую песню, на new_player2" << endl;
    new_player2->switch_new_song();
    cout << endl;
    wcout << L"переключимся на новую песню, на new_player3" << endl;
    new_player3->switch_new_song();
    cout << endl;
    MP3_player_type index_mp3 = MP3_player_type::undefined;
    int index_index_mp3;

    // Создание фрукта при помощи фабричного метода и вывод его характеристик
    wcout << L"Какой mp3_plaer создать (1-касетный, 2-hirez, 3-сенсорный)" << endl;
    cin >> index_index_mp3;
    index_mp3 = static_cast <MP3_player_type>(index_index_mp3);
    MP3_player *new_MP3_player = create_MP3_player(index_mp3);
    new_MP3_player -> Get_Color();
    new_MP3_player->Get_memory();
    new_MP3_player->Get_screen_resolution();
    new_MP3_player->Get_Size();
    cout << endl;
    delete new_player1;
    delete new_player2;
    delete new_player3;
    delete new_MP3_player;
    cout << endl;
    wcout <<L"Заполнение массива плеерами"<< endl;
    // Заполнение массива плеерами
    Array_Class<MP3_player*> MP3_Array;
    for(size_t i = 0; i<5; i++)
    {
        int MP3_num = rand()%3+1;
        MP3_player_type MP3_type = static_cast<MP3_player_type>(MP3_num);
        MP3_player *new_MP3_player4 = create_MP3_player(MP3_type);
        MP3_Array.Add(new_MP3_player4);
    }
    cout << endl;
    wcout <<L"Заполнение вектора плеерами"<< endl;
    // Заполним вектор плеерами
    Vector_Class<MP3_player*> MP3_Vector;
    for(size_t i = 0; i<5; i++)
    {
        int MP3_num = rand()%3+1;
        MP3_player_type MP3_type = static_cast<MP3_player_type>(MP3_num);
        MP3_player *new_MP3_player5 = create_MP3_player(MP3_type);
        MP3_Vector.Push(new_MP3_player5);
    }

// Переключение песен с помощью итератора
/*   cout << endl;
   wcout << L"Переключение песен в массиве" << endl;
   Iterator<MP3_player*> *it = new  Array_Iterator<MP3_player*>(&MP3_Array);
   Switch_ALL(it);
   cout << endl;
   wcout << L"Переключение песен в векторе" << endl;
   Iterator<MP3_player*> *it2 = new  Vector_Iterator<MP3_player*>(&MP3_Vector);
   Switch_ALL(it2);
   delete it;
   delete it2;
*/
// Переключение песен с помощью итератора каторый реализован внутри класса контейнера
cout << endl;
wcout << L"Переключение песен в массиве" << endl;
Iterator<MP3_player*> *it4 = MP3_Array.Get_Iterator();
Switch_ALL(it4);
cout << endl;
wcout << L"Переключение песен в векторе" << endl;
Iterator<MP3_player*> *it5 = MP3_Vector.Get_Iterator();
Switch_ALL(it5);
cout << endl;
delete it4;
delete it5;
//Обход всех серых mp3 плееров
wcout << L"Переключение песен только на серых плеерах" << endl;
Iterator<MP3_player*> *grey_switch = new MP3_Plaer_Color_Decorator(MP3_Array.Get_Iterator(),L"Серый");
Switch_ALL(grey_switch);
delete grey_switch;
cout << endl;
//Обход всех пллееров у каторых память больше 5
wcout << L"Переключение песен только на  плеерах у каторых память больше 5" << endl;
Iterator<MP3_player*> *grey_switch2 = new MP3_Plaer_Memory_Decorator(MP3_Vector.Get_Iterator(),5);
Switch_ALL(grey_switch2);
delete grey_switch2;
cout << endl;
//Обход всех плеера у каторых размер экранна 2048*1536
wcout << L"Переключение песен только на  плеерах у каторых  разрешение 2048*1536" << endl;
Iterator<MP3_player*> *grey_switch3 = new MP3_Plaer_Screen_resolution_Decorator(MP3_Vector.Get_Iterator(),L"2048*1536");
Switch_ALL(grey_switch3);
delete grey_switch3;
cout << endl;
list<MP3_player*> Mp3_list;
size_t N = 10;
for (size_t i=0; i<N; i++)
{
    int Mp3_num = rand()%3+1;
    MP3_player_type player_type = static_cast<MP3_player_type>(Mp3_num);
    MP3_player *new_MP3_player2 = create_MP3_player(player_type);
    Mp3_list.push_back(new_MP3_player2);
}

// Работа адаптера
cout << endl;
wcout << L"Прослушаем все плееры у каторых цвет серый, используя адаптированый итератор (другой контейнер)" << endl;
Iterator<MP3_player*> *adapted_switch = new Const_Iterator_Adapter<std::list<MP3_player*>,MP3_player*>(&Mp3_list);
Iterator<MP3_player*> *adapted_grey_switch = new MP3_Plaer_Color_Decorator(new MP3_Plaer_Color_Decorator(adapted_switch, L"Серый"), L"Серый");
Switch_ALL(adapted_grey_switch);
delete adapted_grey_switch;


return 0;
}
