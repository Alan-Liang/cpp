#include <iostream>
#include <functional>

using std::cin, std::cout, std::endl;

// http://www.cs.nott.ac.uk/~psztxa/g53cfr/l05.html/l05.html

class True {
 public:
  True () = default;
  template <typename T>
  True (T t) {}
};
class False {
 public:
  False () = delete;
};

template <typename A, typename B>
using Implies = std::function<B *(A *)>;

template <typename P>
P *id (P *in) { return in; }

template <int i>
struct Axiom {};
template <typename T>
T *axiom () {
  return nullptr;
}

void id_test () {
  Axiom<1> *x = id(new Axiom<1>());
}

template <typename A, typename B>
using And = std::pair<A *, B *>;

template <typename P, typename Q>
And<Q, P> *andComm (And<P, Q> *in) {
  return new And(in->second, in->first);
}
template <typename P, typename Q>
P *andLeft (And<P, Q> *in) { return in->first; }
template <typename P, typename Q>
Q *andRight (And<P, Q> *in) { return in->second; }

void and_test () {
  And<Axiom<1>, Axiom<2>> *a = new And(new Axiom<1>(), new Axiom<2>());
  Axiom<1> *l = andLeft<Axiom<1>, Axiom<2>>(a);
  Axiom<2> *r = andRight<Axiom<1>, Axiom<2>>(a);
  And<Axiom<2>, Axiom<1>> *ac = andComm(a);
}

template <typename A, typename B>
class Or {
 protected:
  Or (int) {}
 public:
  Or () = delete;
  virtual ~Or () {}
  virtual bool isLeft () { return 2; }
};
template <typename A, typename B>
class OrLeft : public Or<A, B> {
 public:
  A *value;
  OrLeft () = delete;
  OrLeft (A *a) : Or<A, B>(0), value(a) {}
  bool isLeft () { return true; }
};
template <typename A, typename B>
class OrRight : public Or<A, B> {
 public:
  B *value;
  OrRight () = delete;
  OrRight (B *b) : Or<A, B>(0), value(b) {}
  bool isLeft () { return false; }
};

template <typename P, typename Q>
Or<Q, P> *orComm (Or<P, Q> *in) {
  if (in->isLeft()) return new OrRight<Q, P>(dynamic_cast<OrLeft<P, Q> *>(in)->value);
  return new OrLeft<Q, P>(dynamic_cast<OrRight<P, Q> *>(in)->value);
}

template <typename P, typename Q, typename R>
Or<And<P, Q>, And<P, R>> *distribAndOr (And<P, Or<Q, R>> *in) {
  P *p = andLeft(in);
  Or<Q, R> *oqr = andRight(in);
  if (oqr->isLeft()) return new OrLeft<And<P, Q>, And<P, R>>(new And(p, dynamic_cast<OrLeft<Q, R> *>(oqr)->value));
  return new OrRight<And<P, Q>, And<P, R>>(new And(p, dynamic_cast<OrRight<Q, R> *>(oqr)->value));
}

void or_test () {
  Axiom<1> *p = new Axiom<1>;
  Axiom<2> *q = new Axiom<2>;
  Axiom<3> *r = new Axiom<3>;
  Or<Axiom<1>, Axiom<2>> *opq = new OrLeft<Axiom<1>, Axiom<2>>(p);
  Or<Axiom<2>, Axiom<1>> *oqp = orComm(opq);
  Or<And<Axiom<3>, Axiom<1>>, And<Axiom<3>, Axiom<2>>> *distrib = distribAndOr(new And(r, opq));
}

template <typename A, typename B>
using Iff = And<Implies<A, B>, Implies<B, A>>;

template <typename A>
using Not = Implies<A, False>;

template <typename P>
False *contradict (And<P, Not<P>> *pnp) {
  auto [ p, notp ] = *pnp;
  return (*notp)(p);
}

template <typename P>
Not<Not<P>> *notIntro (P *p) {
  return new Not<Not<P>>([=] (Not<P> *np) -> False * {
    return contradict(new And(p, np));
  });
}
template <typename P>
P *notElim (Not<Not<P>> *in) {
  // impossible to prove
  return nullptr;
}

template <typename T, typename R>
R *deMorgan (T *);
template <typename P, typename Q>
And<Not<P>, Not<Q>> *deMorgan (Not<Or<P, Q>> *npq) {
  return new And(
    new Not<P>([=] (P *p) -> False * { return (*npq)(new OrLeft<P, Q>(p)); }),
    new Not<Q>([=] (Q *q) -> False * { return (*npq)(new OrRight<P, Q>(q)); })
  );
}
template <typename P, typename Q>
Not<Or<P, Q>> *deMorgan (And<Not<P>, Not<Q>> *npnq) {
  Not<P> *np = andLeft(npnq);
  Not<Q> *nq = andRight(npnq);
  return new Not<Or<P, Q>>([=] (Or<P, Q> *opq) -> False * {
    if (opq->isLeft()) return (*np)(dynamic_cast<OrLeft<P, Q> *>(opq)->value);
    return (*nq)(dynamic_cast<OrRight<P, Q> *>(opq)->value);
  });
}
template <typename P, typename Q>
Or<Not<P>, Not<Q>> *deMorgan (Not<And<P, Q>> *npnq) {
  return notElim(new Not<Not<Or<Not<P>, Not<Q>>>>([=] (Not<Or<Not<P>, Not<Q>>> *no) -> False * {
    And<Not<Not<P>>, Not<Not<Q>>> *annpnnq = deMorgan(no);
    And<P, Q> *pq = new And(notElim(andLeft(annpnnq)), notElim(andRight(annpnnq)));
    return contradict(new And(pq, npnq));
  }));
}
template <typename P, typename Q>
Not<And<P, Q>> *deMorgan (Or<Not<P>, Not<Q>> *npnq) {
  if (npnq->isLeft()) {
    return new Not<And<P, Q>>([=] (And<P, Q> *apq) -> False * {
      return (*dynamic_cast<OrLeft<Not<P>, Not<Q>> *>(npnq)->value)(andLeft(apq));
    });
  }
  return new Not<And<P, Q>>([=] (And<P, Q> *apq) -> False * {
    return (*dynamic_cast<OrRight<Not<P>, Not<Q>> *>(npnq)->value)(andRight(apq));
  });
}

void deMorgan_test () {
  using P = Axiom<1>;
  using Q = Axiom<2>;
  And<Not<P>, Not<Q>> *dm1 = deMorgan(axiom<Not<Or<P, Q>>>());
  Not<Or<P, Q>> *dm2 = deMorgan(dm1);
  Or<Not<P>, Not<Q>> *dm3 = deMorgan(axiom<Not<And<P, Q>>>());
  Not<And<P, Q>> *dm4 = deMorgan(dm3);
}

int main () {
  return 0;
}
