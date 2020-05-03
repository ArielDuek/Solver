#include <stdio.h>
#include "solver.hpp"
using solver::RealVariable, solver::ComplexVariable;

solver::RealVariable::RealPolinom solver::operator ^ (solver::RealVariable::RealPolinom A, int e){
    if (e !=2 ) throw runtime_error("can not pow by number thet different from 2");
    solver::RealVariable::RealPolinom R( A.getB(),0, A.getC());
    R.setX(A.getX());
    return R;
}

solver::RealVariable::RealPolinom solver::operator + (solver::RealVariable::RealPolinom A, solver::RealVariable::RealPolinom B){
    solver::RealVariable::RealPolinom R(A.getA() + B.getA(), A.getB() + B.getB(), A.getC() + B.getC());
    if(A.getX()) R.setX(A.getX());
    else R.setX(B.getX());
    return R;
}

solver::RealVariable::RealPolinom solver::operator - (solver::RealVariable::RealPolinom A, solver::RealVariable::RealPolinom B){
    solver::RealVariable::RealPolinom R(A.getA() - B.getA(), A.getB() - B.getB(), A.getC() - B.getC());
    if(A.getX()) R.setX(A.getX());
    else R.setX(B.getX());
    return R;
}

solver::RealVariable::RealPolinom solver::operator * (solver::RealVariable::RealPolinom A, solver::RealVariable::RealPolinom B){  // b1r+c1 * b2r+c2
    solver::RealVariable::RealPolinom R(0, (A.getC() * B.getB()) + (B.getC() * A.getB()), A.getC() * B.getC());
    if (A.haveVar()) R.setX(A.getX());
    else R.setX(B.getX());
    return R;
}

solver::RealVariable::RealPolinom solver::operator / (solver::RealVariable::RealPolinom A, solver::RealVariable::RealPolinom B){ //  b1*r+c1 / b2*r+c2   ->   (b1/b2)*r+(c1/c2)
    if (B.getC() == 0 && B.getB()==0 && B.getA()==0) throw runtime_error("can not divide by 0!!");
    if (B.getC() == 0 && B.getB()==0) return A;
    if (B.getC() == 0) {
        solver::RealVariable::RealPolinom R(0, 0, A.getB() / B.getB());
        R.setX(A.getX());
        return R;
    }
    solver::RealVariable::RealPolinom R(0, A.getB() / B.getC(), A.getC() / B.getC());
    R.setX(A.getX());
    return R;
}

solver::RealVariable::RealPolinom solver::operator == (solver::RealVariable::RealPolinom A, solver::RealVariable::RealPolinom B){
    solver::RealVariable::RealPolinom C = A - B;
    if (C.getA()==0 && C.getB()==0) {
        if (C.getC()==0){
            C.getX()->real=0;
            return C;
        }
        else throw runtime_error("there is no solution");
    }
    if (C.getA()==0) C.getX()->real = -C.getC()/C.getB();
    else {
        double x = (-C.getB() + sqrtf(powf(C.getB(), 2) - (4*C.getA()*C.getC())))/(2*C.getA());
        if (isnan(x)) throw runtime_error("there is no solution");
        C.getX()->real = x;
    }
    return C;
}

//===========================================================================================================================

solver::ComplexVariable::ComplexPolinom solver::operator ^ (solver::ComplexVariable::ComplexPolinom A, int e){
    if (e !=2 ) throw runtime_error("can not pow by number thet different from 2");
    solver::ComplexVariable::ComplexPolinom R(A.getB(), 0, A.getC());
    R.setX(A.getX());
    return R;
}

solver::ComplexVariable::ComplexPolinom solver::operator + (solver::ComplexVariable::ComplexPolinom A, solver::ComplexVariable::ComplexPolinom B){
    solver::ComplexVariable::ComplexPolinom R(A.getA() + B.getA(), A.getB() + B.getB(), A.getC() + B.getC());
    if(A.getX()) R.setX(A.getX());
    else R.setX(B.getX());
    return R;
}

solver::ComplexVariable::ComplexPolinom solver::operator - (solver::ComplexVariable::ComplexPolinom A, solver::ComplexVariable::ComplexPolinom B){
    solver::ComplexVariable::ComplexPolinom R(A.getA() - B.getA(), A.getB() - B.getB(), A.getC() - B.getC());
    if(A.getX()) R.setX(A.getX());
    else R.setX(B.getX());
    return R;
}

solver::ComplexVariable::ComplexPolinom solver::operator * (solver::ComplexVariable::ComplexPolinom A, solver::ComplexVariable::ComplexPolinom B){
    solver::ComplexVariable::ComplexPolinom R(0, (A.getC() * B.getB()) + (B.getC() * A.getB()), A.getC() * B.getC());
    if (A.haveVar()) R.setX(A.getX());
    else R.setX(B.getX());
    return R;
}

solver::ComplexVariable::ComplexPolinom solver::operator / (solver::ComplexVariable::ComplexPolinom A, solver::ComplexVariable::ComplexPolinom B){
    complex<double> zero=0;
    if (B.getC() == zero && B.getB()==zero && B.getA()==zero) throw runtime_error("can not divide by 0!!");
    if (B.getC() == zero && B.getB()==zero) return A;
    if (B.getC() == zero ){
        solver::ComplexVariable::ComplexPolinom R(0, 0, A.getB() / B.getB());
        R.setX(A.getX());
        return R;
    }
    solver::ComplexVariable::ComplexPolinom R(0, A.getB() / B.getC(), A.getC() / B.getC());
    R.setX(A.getX());
    return R;
}

solver::ComplexVariable::ComplexPolinom solver::operator == (solver::ComplexVariable::ComplexPolinom A, solver::ComplexVariable::ComplexPolinom B){
    solver::ComplexVariable::ComplexPolinom C = A - B;
    complex<double> zero=0, two = 2, four = 4;
    if (C.getA()==zero && C.getB()==zero) {
        if (C.getC()==zero){
            C.getX()->img=zero;
            return C;
        }
        else throw runtime_error("there is no solution");
    }
    if (C.getA()==zero) C.getX()->img = -C.getC()/C.getB();
    else C.getX()->img = (-C.getB() + sqrt(pow(C.getB(), two) - (four*C.getA()*C.getC())))/(two*C.getA());
    return C;
}

//===========================================================================================================================

double solver::solve(RealVariable::RealPolinom r){return r.getX()->real;}
complex<double> solver::solve(ComplexVariable::ComplexPolinom x){
    if(x.getX()->img.imag()==(-0)) x.getX()->img.imag(0);
    return x.getX()->img;
}