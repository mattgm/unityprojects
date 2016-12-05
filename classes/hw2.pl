parse(Tokens, AST) :- phrase(prog(AST), Tokens).

prog(prog(D,Y)) --> declare(D), prog(Y).
prog(prog(DA,Y)) --> declAssign(DA), prog(Y).
prog(prog(A,Y)) --> assign(A), prog(Y).
prog(prog(R)) --> retStatement(R).

declare(declare(X)) --> var, id(X), [';'].
declAssign(declAssign(id(X), Expr)) --> var, id(X), ['<-'], expr(Expr), [';'].
assign(assign(id(X), Expr)) --> id(X), ['<-'], expr(Expr), [';'].


id(X) --> [X],{atom(X)}.
var --> ['var'].
expr(expr(Term)) --> term(Term).
expr(expr(Term, Op, Expr)) --> term(Term), addOp(Op), expr(Expr).

term(term(F)) --> factor(F).
term(term(F, Op, Term)) --> factor(F), mulOp(Op), term(Term).

factor(factor(N)) --> base(N). 
factor(factor(Expr)) --> ['('], expr(Expr), [')'].

addOp(Op) --> [Op], {memberchk(Op, ['+', '-'])}.
mulOp(Op) --> [Op], {memberchk(Op, ['*', '/'])}.

retStatement(retStatement(Base)) --> ['return'],base(Base),['.'].
base(base(X)) --> ['('], expr(X), [')']| [X],{number(X)} | id(X).

evaluate(AST, Return) :- empty_assoc(List), evaluateProg(AST, List, Return).

evaluateProg(Tree, List, Return) :-
	prog(X,Y) = Tree,
	evaluateD(X, List, Outlist),
	evaluateProg(Y, Outlist, Return).

evaluateProg(Tree, List, Return) :-
	prog(X,Y) = Tree,	
	evaluateA(X, List, Outlist),
	evaluateProg(Y, Outlist, Return).

evaluateProg(Tree, List, Return) :-
	prog(X,Y) = Tree,
	evaluateDA(X, List, Outlist),
	evaluateProg(Y, Outlist, Return).

evaluateProg(Tree, List, Return) :-
	prog(X) = Tree,
	evaluateR(X, List, Return).

evaluateD(Tree, In, Out) :-
	declare(X) = Tree,
	evaluateId(X, Id),
	put_assoc(Id, In, 0, Out).

evaluateDA(Tree, In, Out) :-
	declAssign(X, Y) = Tree,
	evaluateId(X, Id),
	evaluateExpr(Y, In, Ret),
	put_assoc(Id, In, Ret, Out).

evaluateA(Tree, In, Out) :-
	assign(X, Z) = Tree,
	evaluateId(X, Id),
	evaluateExpr(Z, In, Ret),
	put_assoc(Id, In, Ret, Out).

evaluateR(Tree, List, Return) :-
	retStatement(Z) = Tree,
	evaluateBase(Z, List, Ret),
	Return is Ret.

evaluateBase(Tree, List, Return) :-
	base(X) = Tree,
	number(X),
	Return is X.

evaluateBase(Tree, List, Return) :-
	base(X) = Tree,
	atom(X),
	atom_number(X,Y),
	Return is Y.

evaluateBase(Tree, List, Return) :-
	base(X) = Tree,	
	evaluateId(X, Id),
	get_assoc(id(X), List, Y),
	Return is Y.

evaluateBase(Tree, List, Return) :-
	base(X) = Tree,
	evaluateExpr(X, List, Ret),
	Return is Ret.

evaluateId(Tree, Return) :-
	Return = Tree.

evaluateExpr(Tree, List, Return) :-
	expr(X) = Tree,
	evaluateTerm(X, List, Ret),
	Return is Ret.

evaluateExpr(Tree, List, Return) :-
	expr(X, Y, Z) = Tree,
	evaluateTerm(X, List, Ret),
	evaluateExpr(Z, List, Ret2),
	Eq =.. [Y, Ret, Ret2],
	Return is Eq.

evaluateTerm(Tree, List, Return) :-
	term(X) = Tree,
	evaluateFactor(X, List, Ret),
	Return is Ret.

evaluateTerm(Tree, List, Return) :-
	term(X, Y, Z) = Tree,
	evaluateFactor(X, List, Ret),
	evaluateTerm(Z, List, Ret2),
	Eq =.. [Y, Ret, Ret2],
	Return is Eq.

evaluateFactor(Tree, List, Return) :-
	factor(X) = Tree,
	evaluateBase(X, List, Ret),
	Return is Ret.

evaluateFactor(Tree, List, Return) :-
	factor(X) = Tree,
	evaluateExpr(X, List,Ret),
	Return is Ret.