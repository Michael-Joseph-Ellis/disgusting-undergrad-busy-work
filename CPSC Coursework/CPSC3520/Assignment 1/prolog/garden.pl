% -------------------------------
% garden.pl
% -------------------------------

% Facts: flower(Name, Size, WetDry, Color).
flower(daisies, med, wet, yellow).
flower(roses, med, dry, red).
flower(petunias, med, wet, pink).
flower(daffodils, med, wet, yellow).
flower(begonias, tall, wet, white).
flower(snapdragons, tall, dry, red).
flower(marigolds, short, wet, yellow).
flower(gardenias, med, wet, red).
flower(gladiolas, tall, wet, red).
flower(bird_of_paradise, tall, wet, white).
flower(lilies, short, dry, white).
flower(azalea, med, dry, pink).
flower(buttercup, short, dry, yellow).
flower(poppy, med, dry, red).
flower(crocus, med, dry, orange).
flower(carnation, med, wet, white).
flower(tulip, short, wet, red).
flower(orchid, short, wet, white).
flower(chrysanthemum, tall, dry, pink).
flower(dahlia, med, wet, purple).
flower(geranium, short, dry, red).
flower(lavender, short, dry, purple).
flower(iris, tall, dry, purple).
flower(peonies, short, dry, pink).
flower(periwinkle, med, wet, purple).
flower(sunflower, tall, dry, yellow).
flower(violet, short, dry, purple).
flower(zinnia, short, wet, yellow).

% ---------- helpers ----------
species(S)       :- flower(S,_,_,_).
size_of(S,Size)  :- flower(S,Size,_,_).
water_of(S,W)    :- flower(S,_,W,_).
color_of(S,C)    :- flower(S,_,_,C).

size_rank(short,0).
size_rank(med,1).
size_rank(tall,2).

adjacent_ok(A,B) :-
    color_of(A,CA), color_of(B,CB), CA \= CB,
    size_of(A,SA), size_of(B,SB),
    size_rank(SA,RA), size_rank(SB,RB),
    Diff is abs(RA-RB), Diff =< 1.

% ---------- (1) plantassign/2 ----------
plantassign(N, List) :-
    length(List, N),
    maplist(species, List).

% ---------- (2) uniquecheck/1 ----------
uniquecheck([]).
uniquecheck([H|T]) :-
    \+ member(H, T),
    uniquecheck(T).

% ---------- (3) colorcheck/1 ----------
colorcheck([_]).
colorcheck([A,B|Rest]) :-
    color_of(A,CA), color_of(B,CB), CA \= CB,
    colorcheck([B|Rest]).

% ---------- (4) sizecheck/1 ----------
sizecheck([_]).
sizecheck([A,B|Rest]) :-
    size_of(A,SA), size_of(B,SB),
    size_rank(SA,RA), size_rank(SB,RB),
    Diff is abs(RA-RB), Diff =< 1,
    sizecheck([B|Rest]).

% ---------- (5) wetcheck/2 ----------
wetcheck(N, List) :-
    N >= 4,
    nth1(1,  List, F1), water_of(F1, dry),
    nth1(N,  List, FN), water_of(FN, dry),
    nth1(2,  List, F2), water_of(F2, wet),
    N1 is N-1,
    nth1(N1, List, F3), water_of(F3, wet).

% ---------- (6) writegarden/1 ----------
writegarden(List) :-
    writeln('Garden plan:'),
    writegarden_(1, List).

writegarden_(_, []) :- !.
writegarden_(I, [S|Rest]) :-
    flower(S,Size,Wet,Color),
    format('~d: ~w (~w, ~w, ~w)~n', [I, S, Size, Wet, Color]),
    I2 is I + 1,
    writegarden_(I2, Rest).

% ---------- (7) gardenplan/2 ----------
gardenplan(N, List) :-
    N >= 4,
    build(1, N, none, [], [], Rev),
    reverse(Rev, List),
    writegarden(List).

required_water(Pos,N,dry)    :- Pos =:= 1 ; Pos =:= N.
required_water(Pos,N,wet)    :- Pos =:= 2 ; Pos =:= N-1.
required_water(Pos,N,either) :- Pos > 2, Pos < N-1.

build(Pos, N, _, Used, Acc, Acc) :- Pos > N, !.
build(Pos, N, Prev, Used, Acc, Out) :-
    required_water(Pos,N,Req),
    flower(S,_,Wet,_),
    (Req = either ; Wet = Req),
    \+ member(S, Used),
    ( Prev = none -> true ; adjacent_ok(Prev,S) ),
    Pos1 is Pos + 1,
    build(Pos1, N, S, [S|Used], [S|Acc], Out).

valid_garden(N, List) :-
    length(List, N),
    uniquecheck(List),
    colorcheck(List),
    sizecheck(List),
    wetcheck(N, List).
