#include <stdio.h>
#include <iostream>
#include "math.h"
#include <complex>

using namespace std;

namespace solver{

    class RealVariable {
    public:
        double real;

        RealVariable() {}
        ~RealVariable() {}
    };

    class ComplexVariable {
    public:
        complex<double> img;

        ComplexVariable() {}
        ~ComplexVariable() {}
    };

    class POLI{     //FORM: ar^e+br+c
    private:
        double a,b,c;
        int e;
        RealVariable* r;
        bool var;

    public:
        POLI() : a(0), b(0), c(0), e(1), var(false){}            //default Constructor
        POLI(int c) : a(0), b(0), c(c), e(1), var(false){}
        POLI(double c) : a(0), b(0), c(c), e(1), var(false){}
        POLI(RealVariable& r) : a(0), r(&r), b(1), c(0), var(true), e(1) {}     //holds the x Final Resault into LINE
        POLI(double a, int e) : a(a), b(0), c(0), e(e), var(false) {}        //make form of: x^e into POLI
        POLI(double a, double b, double c, int e) : a(a), b(b), c(c), e(e), var(false) {}   //copy Constructor
        ~POLI(){}

        double getA() { return a; };
        double getB() { return b; };
        double getC() { return c; };
        int getE() { return e; };
        RealVariable* getX() { return r; };
        void setX(RealVariable* R) { this->r = R; }
        bool haveVar() {return this->var;}
    };



//------------------------------------------------------------------------------------------------------------------------

    class POLIcx{     //FORM: ax^e+bx+c
    private:
        complex<double> a,b,c;
        int e;
        ComplexVariable* x;
        bool var;

    public:
        POLIcx(): a(0), b(0), c(0), e(1), var(false){}            //default Constructor
        POLIcx(int c) : a(0), b(0), c(c), e(1), var(false){}
        POLIcx(double c) : a(0), b(0), c(c), e(1), var(false){}
        POLIcx(complex<double> c) : a(0), b(0), c(c), e(1), var(false){}
        POLIcx(ComplexVariable& x) : a(0), x(&x), b(1), c(0), e(1), var(true) {}     //holds the x Final Resault into LINE
        POLIcx(complex<double> a, int e) : a(a), b(0), c(0), e(e), var(false) {}        //make form of: x^e into POLI
        POLIcx(complex<double> a, complex<double> b, complex<double> c, int e) : a(a), b(b), c(c), e(e), var(false) {}   //copy Constructor
        ~POLIcx(){}

        complex<double> getA() { return a; };
        complex<double> getB() { return b; };
        complex<double> getC() { return c; };
        int getE() { return e; };
        ComplexVariable* getX() { return x; };
        void setX(ComplexVariable* X) { this->x = X; }
        bool haveVar() {return this->var;}
    };

//------------------------------------------------------------------------------------------------------------------------

    POLI operator ^ (POLI A, int e){
        POLI R( A.getB(),0, A.getC(), e);
        R.setX(A.getX());
        return R;
    }

    POLI operator + (POLI A, POLI B){
        POLI R(A.getA()+B.getA(), A.getB()+B.getB(), A.getC()+B.getC(), 1);
        if(A.getX()) R.setX(A.getX());
        else R.setX(B.getX());
        return R;
    }

    POLI operator - (POLI A, POLI B){
        POLI R(A.getA()-B.getA(), A.getB()-B.getB(), A.getC()-B.getC(), 1);
        if(A.getX()) R.setX(A.getX());
        else R.setX(B.getX());
        return R;
    }

    POLI operator * (POLI A, POLI B){  // b1r+c1 * b2r+c2
        POLI R(0,(A.getC()*B.getB())+(B.getC()*A.getB()), A.getC()*B.getC(),1);
        if (A.haveVar()) R.setX(A.getX());
        else R.setX(B.getX());
        return R;
    }

    POLI operator / (POLI A, POLI B){ //  b1*r+c1 / b2*r+c2   ->   (b1/b2)*r+(c1/c2)
        if (B.getC() == 0 ) return A;
        POLI R(0, A.getB() / B.getC(), A.getC() / B.getC(), 1);
        R.setX(A.getX());
        return R;
    }

    POLI operator == (POLI A, POLI B){
        POLI C = A - B;
        if (C.getA()==0) C.getX()->real = -C.getC()/C.getB();
        else C.getX()->real = (-C.getB() + sqrtf(powf(C.getB(), 2) - (4*C.getA()*C.getC())))/(2*C.getA());
        return C;
    }



//------------------------------------------------------------------------------------------------------------------------



    POLIcx operator ^ (POLIcx A, int e){
        POLIcx R( A.getB(),0, A.getC(), e);
        R.setX(A.getX());
        return R;
    }

    POLIcx operator + (POLIcx A, POLIcx B){
        POLIcx R(A.getA()+B.getA(), A.getB()+B.getB(), A.getC()+B.getC(), 1);
        if(A.getX()) R.setX(A.getX());
        else R.setX(B.getX());
        return R;
    }

    POLIcx operator - (POLIcx A, POLIcx B){
        POLIcx R(A.getA()-B.getA(), A.getB()-B.getB(), A.getC()-B.getC(), 1);
        if(A.getX()) R.setX(A.getX());
        else R.setX(B.getX());
        return R;
    }

    POLIcx operator * (POLIcx A, POLIcx B){
        POLIcx R(0,(A.getC()*B.getB())+(B.getC()*A.getB()), A.getC()*B.getC(),1);
        if (A.haveVar()) R.setX(A.getX());
        else R.setX(B.getX());
        return R;
    }

    POLIcx operator / (POLIcx A, POLIcx B){
        complex<double> zero=0;
        if (B.getC() == zero ) return A;
        POLIcx R(0, A.getB() / B.getC(), A.getC() / B.getC(), 1);
        R.setX(A.getX());
        return R;
    }

    POLIcx operator == (POLIcx A, POLIcx B){
        POLIcx C = A - B;
        complex<double> zero=0, two = 2, four = 4;
        if (C.getA()==zero) C.getX()->img = -C.getC()/C.getB();
        else C.getX()->img = (-C.getB() + sqrt(pow(C.getB(), two) - (four*C.getA()*C.getC())))/(two*C.getA());
        return C;
    }

    double solve(POLI r){return r.getX()->real;}
    complex<double> solve(POLIcx x){return x.getX()->img;}

}

