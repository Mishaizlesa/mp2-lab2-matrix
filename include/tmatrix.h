// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz <= 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz>MAX_VECTOR_SIZE)  throw out_of_range("Vector size can't be greater than MAX_VECOR_SIZE");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолча
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (sz <= 0) throw out_of_range("Vector size should be greater than zero");
        if (sz>MAX_VECTOR_SIZE)  throw out_of_range("Vector size can't be greater than MAX_VECOR_SIZE");
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz]();
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v){
        pMem=new T[v.sz]();
        sz=v.sz;
        for(int i=0;i<sz;++i) {
            pMem[i]=v.pMem[i];
            
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept{
        sz=v.sz;
        delete []pMem;
        pMem=new T[sz]();
        for(int i=0;i<sz;++i) pMem[i]=v.pMem[i];
        v.pMem=nullptr;
        v.sz=0;
    }
    ~TDynamicVector(){
        delete []pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v){
        if (this==&v) return *this;
        T* tmp=new T[v.sz]();
        sz=v.sz;
        delete[] pMem;
        pMem=tmp;
        for(int i=0;i<sz;++i) pMem[i]=v.pMem[i];
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this==&v) return *this;
        if (&v == this) return *this;
        delete[] pMem;
        sz = v.sz;
        pMem = v.pMem;
        v.pMem=nullptr;
        v.sz = 0;
        return *this;
    }
    
    size_t size() const noexcept { return sz; }
    
    // индексация
    T& operator[](size_t ind)
    {
        if (ind>=sz || ind<0) throw out_of_range("index is out of range");
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind>=sz || ind<0) throw out_of_range("index is out of range");
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind>=sz || ind<0) throw out_of_range("index is out of range");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind>=sz || ind<0) throw out_of_range("index is out of range");
        return pMem[ind];
    }
    
    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz!=v.sz) return false;
        for(int i=0;i<sz;++i) if (pMem[i]!=v.pMem[i]) return false;
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this==v);
    }
    
    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector tmp(*this);
        for(int i=0;i<sz;++i) tmp[i]+=val;
        return tmp;
    }
    TDynamicVector operator-(double val)
    {
        TDynamicVector tmp(*this);
        for(int i=0;i<sz;++i) tmp[i]-=val;
        return tmp;
    }
    TDynamicVector operator*(double val)
    {
        TDynamicVector tmp(*this);
        for(int i=0;i<sz;++i) tmp[i]*=val;
        return tmp;
    }
    
    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz!=v.sz) throw "sizes are not equal";
        TDynamicVector tmp(*this);
        for(int i=0;i<sz;++i) tmp[i]+=v.pMem[i];
        return tmp;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz!=v.sz) throw "sizes are not equal";
        TDynamicVector tmp(*this);
        for(int i=0;i<sz;++i) tmp[i]-=v.pMem[i];
        return tmp;
    }
    T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
    {
        if (sz!=v.sz) throw "sizes are not equal";
        T ans=0;
        for(int i=0;i<sz;++i) ans+=v.pMem[i]*pMem[i];
        return ans;
    }
    
    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }
    
    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T> >
{
    using TDynamicVector<TDynamicVector<T> >::pMem;
    using TDynamicVector<TDynamicVector<T> >::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T> >(s)
    {
        if (s <= 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz>MAX_MATRIX_SIZE)  throw out_of_range("Vector size can't be greater than MAX_VECOR_SIZE");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }
    
    using TDynamicVector<TDynamicVector<T> >::operator[];
    
    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept{
        if (sz!=m.sz) return false;
        for(int i=0;i<sz;++i) if (pMem[i]!=m.pMem[i]) return false;
        return true;
    }
    bool operator!=(const TDynamicMatrix& m) const noexcept{
        return !(*this==m);
    }
    // матрично-скалярные операции
    TDynamicVector<T> operator*(const T& val)
    {
        TDynamicMatrix tmp(*this);
        for(int i=0;i<sz;++i) tmp[i]=tmp[i]*val;
        return tmp;
    }
    
    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz!=v.sz) throw "sizes dont match";
        TDynamicVector<int>ans(v.sz);
        for(int i=0;i<sz;++i){
            ans[i]=0;
            for(int j=0;j<sz;++j){
                ans[i]+=pMem[i][j]*v[j];
            }
        }
        return ans;
    }
    size_t size() const noexcept { return sz; }
    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz!=m.sz){
            throw "sizes are not equal";
        }
        TDynamicMatrix tmp(*this);
        for(int i=0;i<sz;++i){
            tmp.pMem[i]=tmp.pMem[i]+m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz!=m.sz){
            throw "sizes are not equal";
        }
        TDynamicMatrix tmp(*this);
        for(int i=0;i<sz;++i){
            tmp.pMem[i]=tmp.pMem[i]-m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz!=m.sz) throw "sizes don't match";
        TDynamicMatrix<int>ans(m.sz);
        for(int i=0;i<sz;++i){
            for(int k=0;k<sz;++k){
                for(int j=0;j<sz;++j){
                    ans.pMem[i][j]+=pMem[i][k]*pMem[k][j];
                }
            }
        }
        return ans;
    }
    
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for(int i=0;i<v.sz;++i) cin>>v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix v)
    {
        for(int i=0;i<v.sz;++i) cout<<v.pMem[i]<<"\n";
        return ostr;
    }
};

#endif
