// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp):BitField(mp){
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField() const
{
    TBitField res = TBitField(MaxPower);
    res = BitField;
    return res;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{   
    try {
        return BitField.GetBit(Elem);
    }
    catch (...) {
        throw "Wrong index";
    }
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{   
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower) {
        return 0;
    }
    if (BitField == s.BitField) {
        return 1;
    }
    else return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower) {
        return 1;
    }
    if (BitField == s.BitField) {
        return 0;
    }
    else return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TBitField temp =BitField | s.BitField;
    return TSet(temp);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{   
    if (Elem >= MaxPower) {
        throw "non existing element";
    }
    TSet temp = *this;
    TSet t = TSet(MaxPower);
    t.InsElem(Elem);
    temp = temp + t;
    return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem >= MaxPower) {
        throw "non existing element";
    }
    TSet temp = *this;
    if (Elem < MaxPower) {
        temp.BitField.ClrBit(Elem);
        return temp;
    }
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TBitField temp = TBitField(*this) & TBitField(s);
    return TSet(temp);
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp = TSet(MaxPower);
    temp.BitField = ~BitField;
    return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int n;
    istr >> n;
    try {
        s.InsElem(n);
    }
    catch (...) {
        throw "Wrong index";
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << "{";
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.IsMember(i)) {
            ostr << i<< " ";
        }
    }
    ostr << "}";
    return ostr;
}
