parse(Tokens, AST) :- phrase(prog(AST), Tokens).

prog(prog(F,Y)) --> funcDecl(F),[';'], prog(Y).
prog(prog(S,Y)) --> statement(S),[';'],prog(Y).
prog(prog(R)) --> retStatement(R).

funcDecl(funcDecl(X, Y, W)) --> ['function'],id(X),['('],id(Y),[')'],['{'], prog(W), ['}'],[';'].

statement(statement(L)) --> loop(L).
statement(statement(C)) --> conditional(C).
statement(statement(X)) --> declare(X).
statement(statement(X)) --> declAssign(X).
statement(statement(X)) --> assign(X).

declare(declare(X)) --> var, id(X).
declAssign(declAssign(id(X), Expr)) --> var, id(X), ['<-'], expr(Expr).
assign(assign(id(X), Expr)) --> id(X), ['<-'], expr(Expr).

conditional(conditional(C, S1, S2)) --> ['if'],['('],condition(C),[')'],['then'], statementSeq(S1),['else'],statementSeq(S2),['endif'].
conditional(conditional(C, S1)) --> ['if'],['('],condition(C),[')'],['then'], statementSeq(S1),['endif'].
loop(loop(C,S)) --> ['while'],['('],condition(C),[')'],['do'],statementSeq(S),['done'].

statementSeq(statementSeq(S)) --> statement(S),['.'].
statementSeq(statementSeq(S1, S2)) --> statement(S1),[';'], statementSeq(S2).
condition(condition(B1, C, B2)) --> base(B1), comp(C), base(B2).
condition(condition(C1, L, C2)) --> ['('],condition(C1), logOp(L), condition(C2),[')'].
funcCall(funcCall(F,B)) --> id(F),base(B).

id(X) --> [X],{ atom(X) }.
var --> ['var'].
expr(expr(Term)) --> term(Term).
expr(expr(Term, Op, Expr)) --> term(Term), addOp(Op), expr(Expr).

term(term(F)) --> factor(F).
term(term(F, Op, Term)) --> factor(F), mulOp(Op), term(Term).

factor(factor(N)) --> base(N). 
factor(factor(Expr)) --> ['('], expr(Expr), [')'].

addOp(Op) --> [Op], {memberchk(Op, ['+', '-'])}.
mulOp(Op) --> [Op], {memberchk(Op, ['*', '/'])}.
logOp(Op) --> [and], {memberchk(Op, ['&&'])}.
logOp(Op) --> [or], {memberchk(Op, ['||'])}.
comp(Op) --> [Op], {memberchk(Op, ['==','<','>','<=','>='])}.
comp(Op) --> [\==], {memberchk(Op, ['!='])}.

retStatement(retStatement(Base)) --> ['return'],base(Base),['.'].
base(base(X)) --> ['('], expr(X), [')']| [X],{number(X)} | id(X) | funcCall(X).


evaluate(AST, Return) :- empty_assoc(List), evaluateProg(AST, List, Return).

evaluateProg(Tree, List, Return) :-
	prog(X,Y) = Tree,
	evaluateFuncDecl(X, List, Outlist),
	evaluateProg(Y, Outlist, Return).

evaluateProg(Tree, List, Return) :-
	prog(X,Y) = Tree,
	evaluateStatement(X, List, Outlist),
	evaluateProg(Y, Outlist, Return).

evaluateProg(Tree, List, Return) :-
	prog(X) = Tree,
	evaluateR(X, List, Return).

evaluateFuncDecl(Tree, List, Outlist) :-
	funcDecl(X,Y,Z) = Tree,
	evaluateId(X),
	put_assoc(X, List, 0, Outlist),
	evaluateId(Y),
	put_assoc(Y, List, 0, Outlist),
	evaluateProg(Z).

evaluateStatement(Tree, List, Outlist) :-
	statement(X) = Tree,
	evaluateD(X, List, Outlist).	

evaluateStatement(Tree, List, Outlist) :-
	statement(X) = Tree,	
	evaluateA(X, List, Outlist).

evaluateStatement(Tree, List, Outlist) :-
	statement(X) = Tree,
	evaluateDA(X, List, Outlist).

evaluateStatement(Tree, List, Outlist) :-
	statement(X) = Tree,
	evaluateConditional(X, List, Outlist).

evaluateStatement(Tree, List, Outlist) :-
	statement(X) = Tree,
	evaluateLoop(X, List, Outlist).

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

evaluateConditional(Tree, In, Out) :-
	conditional(X,Y,Z) = Tree,
	evaluateCond(X, In, Ret),
	(Ret == true, 
	evaluateStSeq(Y, In, Out));
	evaluateStSeq(Z, In, Out).

evaluateConditional(Tree, In, Out) :-
	conditional(X,Y) = Tree,
	evaluateCond(X, In, Ret),
	Ret == true,
	evaluateStSeq(Y, In, Out).

evaluateLoop(Tree, In, Out) :-
	loop(X, Y) = Tree,
	evaluateCond(X, In, Ret),
	evaluateStSeq(Y, In, Out),
	evaluateLoop(X, In, Out).

evaluateCond(Tree, In, Out) :-
	condition(X,Y,Z) = Tree,
	evaluateCond(X, In, Ret),
	evaluateCond(Z, In, Ret2),
	Eq =.. [Y, Ret, Ret2],
	Return = Eq.

evaluateCond(Tree, In, Return) :-
	condition(X,Y,Z) = Tree,
	evaluateBase(X, In, Ret),
	evaluateBase(Z, In, Ret2),
	Eq =.. [Y, Ret, Ret2],
	Return = Eq.

and(X,Y) :- is_true(X), is_true(Y).
or(X,Y) :- is_true(X); is_true(Y).

evaluateStSeq(Tree, In, Out) :-
	statementSeq(X) = Tree,
	evaluateStatement(X, In, Out).

evaluateStSeq(Tree, In, Out) :-
	statementSeq(X,Y) = Tree,
	evaluateStatement(X, In, Out),
	evaluateStSeq(Y, In, Out).

evaluateFuncCall(Tree, In, Out) :-
	funcCall(X,Y) = Tree,
	evaluateId(X, Ret),
	evaluateBase(Y, In, Ret).

evaluateBase(Tree, List, Return) :-
	base(X) = Tree,
	evaluateFuncCall(X, List, Return).

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
