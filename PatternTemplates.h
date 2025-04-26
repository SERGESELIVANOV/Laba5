#ifndef PATTERNTEMPLATES_H_INCLUDED
#define PATTERNTEMPLATES_H_INCLUDED
#include <vector>
#include <iostream>
using namespace std;
template<typename T>
class Iterator
{
protected:
    Iterator() {}
public:
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool Is_Done() const = 0;
    virtual T Get_Current() const = 0;
};

template<typename T>
class Container
{
public:
    virtual ~Container() {}
    virtual Iterator<T>* Get_Iterator() = 0;
};

const size_t Max_Size = 20;
template <typename T>
class Array_Class : public Container<T>
{
private:
    T Items[Max_Size];
    size_t Array_Size;
public:
    void Add(T new_Object) {Items[Array_Size++]=new_Object;}
    size_t Size() const{return Array_Size; }
    T Get_Element(size_t index) const {return Items[index];}
    Array_Class() : Array_Size(0) {}
   class Array_Iterator : public Iterator<T>
   {
    private:
      Array_Class<T>* Array_Container;
      size_t Pos;
    public:
      Array_Iterator(Array_Class<T>* container) : Array_Container(container), Pos(0) {}
      void First() override {Pos = 0;}
      void Next() override {Pos++; }
      bool Is_Done() const  override {return (Pos >= Array_Container->Size()); }
      T Get_Current() const override {return Array_Container->Get_Element(Pos); }
   };
    Iterator<T>* Get_Iterator()
    {
        return new Array_Iterator(this);
    }
};


template <typename T>
class Vector_Class : public Container<T>
{
private:
    vector<T> Items;
public:
    size_t Size() const { return Items.size(); }
    void Push(T new_Object) {Items.push_back(new_Object);}
    T First() {return Items.front();}
    T Back() {return Items.back();}
    T Get_Element_By_Index(size_t index) const {return Items[index];}
    class Vector_Iterator : public Iterator<T>
    {
    private:
      const vector<T>& Vector_Container;
      size_t Pos;
    public:
      Vector_Iterator(const vector<T>& container) : Vector_Container(container), Pos(0) {}
      void First() override {Pos = 0;}
      void Next() override {Pos++; }
      bool Is_Done() const  override {return (Pos >= Vector_Container.size()); }
      T Get_Current() const override {return Vector_Container[Pos]; }
    };
    Iterator<T>* Get_Iterator()
    {
        return new Vector_Iterator(Items);
    }
};

// Шаблон для Декоратора
template <typename T>
class Iterator_Decorator : public Iterator<T>
{
protected:
    Iterator<T> *It;
public:
    Iterator_Decorator(Iterator<T> *it): It(it) {}
    virtual ~Iterator_Decorator() {delete It;}
    virtual void First() {It -> First();}
    virtual void Next() {It -> Next();}
    virtual bool Is_Done() const {return It->Is_Done();}
    virtual T Get_Current() const{return It->Get_Current();}

};
//адаптер для контейнерных классов STL
template <typename Container_Type, typename Item_Type>
class Const_Iterator_Adapter : public Iterator<Item_Type>
{
protected:
    Container_Type *Container;
    typename Container_Type::const_iterator It;

public:
    Const_Iterator_Adapter(Container_Type *container)
    : Container(container)
    {
        It = Container->begin();
    }

    virtual ~Const_Iterator_Adapter() {}
    virtual void First() { It = Container->begin(); }
    virtual void Next() { It++; }
    virtual bool Is_Done() const { return (It == Container->end()); }
    virtual Item_Type Get_Current() const { return *It; }
};
#endif // PATTERNTEMPLATES_H_INCLUDED
