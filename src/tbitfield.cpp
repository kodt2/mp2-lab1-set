// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0) {
        throw "Negative Length";
    }
    BitLen = len;//кол-во бит
    MemLen = len / (sizeof(TELEM)*8);//кол-во переменных
    if (len % (sizeof(TELEM)*8) != 0) {
        MemLen++;
    }
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{

    return 0;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM res;
    if (n < sizeof(TELEM) * 8) {
        res = 1 << (sizeof(TELEM) * 8 - n - 1);
    }
    else {
        res = 0;
    }
    return res;
}


// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0) {
        throw "negative index";
    }
    if (n >= BitLen) {
        throw "No such bit";
    }
    int Nperem = n / (sizeof(TELEM) * 8);
    int Nbit = n % (sizeof(TELEM) * 8);
    pMem[Nperem] = pMem[Nperem] | GetMemMask(Nbit);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0) {
        throw "negative index";
    }
    if (n >= BitLen) {
        throw "No such bit";
    }
    int Nperem = n / (sizeof(TELEM) * 8);
    int Nbit = n % (sizeof(TELEM) * 8);
    pMem[Nperem] = pMem[Nperem] & ~GetMemMask(Nbit);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0) {
        throw "negative index";
    }
    if (n >= BitLen) {
        throw "No such bit";
    }
    int Nperem = n / (sizeof(TELEM) * 8);
    int Nbit = n % (sizeof(TELEM) * 8);
    TELEM temp = pMem[Nperem];
    temp = (temp & GetMemMask(n))>>((sizeof(TELEM) * 8) -n-1);
    return temp;
}
// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return TBitField(0);
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return TBitField(0);
}

TBitField TBitField::operator~(void) // отрицание
{
    return TBitField(0);
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}