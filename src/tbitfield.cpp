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
    temp = (temp & GetMemMask(Nbit))>>((sizeof(TELEM) * 8) -Nbit-1);
    return temp;
}
// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{   
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    delete[] pMem;
    pMem = new TELEM[MemLen];    
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    int temp = 1;
    if (BitLen != bf.BitLen) {
        throw "non equal size";
    }
    for (int i = 0; i < BitLen; i++) {
        if (this->GetBit(i) == bf.GetBit(i)) {
        }
        else {
            temp = 0;
        }
    }
    return temp;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    int temp = 0;
    if (BitLen != bf.BitLen) {
        throw "non equal size";
    }
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] == bf.pMem[i]) {
        }
        else {
            temp = 1;
        }
    }
    return temp;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField res = TBitField(std::max(BitLen, bf.BitLen));
    for (int i = 0; i < std::min(MemLen, bf.MemLen); i++) {
        res.pMem[i] = pMem[i] | bf.pMem[i];
    }

    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField res = TBitField(std::max(BitLen, bf.BitLen));
    for (int i = 0; i < std::min(MemLen, bf.MemLen); i++) {
        res.pMem[i] = pMem[i] & bf.pMem[i];
    }

    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res = *this;
    for (int i = 0; i < res.MemLen; i++) {
        res.pMem[i] = ~res.pMem[i];
    }
    int Nperem;
    int Nbit;
    for (int i = BitLen; i < res.MemLen * sizeof(TELEM) * 8; i++) {
        Nperem = i / (sizeof(TELEM) * 8);
        Nbit = i % (sizeof(TELEM) * 8);
        res.pMem[Nperem] = res.pMem[Nperem] & ~GetMemMask(Nbit);
    }
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{   
    int n;
    istr >> n;
    try {
        bf.SetBit(n);
    }
    catch (...) {
        throw "Wrong index";
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    ostr << "{";
    for (int i = 0; i < bf.BitLen; i++) {
        ostr << bf.GetBit(i)<<" ";
    }
    ostr << "}";
    return ostr;
}