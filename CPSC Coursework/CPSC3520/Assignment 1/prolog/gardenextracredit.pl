% ---------------------------------------------
% gardenextracredit.pl  (2D garden version)
% ---------------------------------------------

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

% ---------- helpers 
species(S)       :- flower(S,_,_,_).
size_of(S,Size)  :- flower(S,Size,_,_).
water_of(S,W)    :- flower(S,_,W,_).
color_of(S,C)    :- flower(S,_,_,C).

size_rank(short,0).
size_rank(med,1).
size_rank(tall,2).

colors_ok(A,B) :-
    color_of(A,CA), color_of(B,CB), CA \= CB.

sizes_ok(A,B) :-
    size_of(A,SA), size_of(B,SB),
    size_rank(SA,RA), size_rank(SB,RB),
    Diff is abs(RA-RB), Diff =< 1.

% 2D index helpers (row-major)
index_from_rc(R,C,M,I) :- I is (R-1)*M + C.
species_at(List,M,R,C,S) :- index_from_rc(R,C,M,I), nth1(I,List,S).

% min distance to the border (0 outer ring, 1 next ring, etc.)
border_min(R,C,N,M,D) :-
    D1 is R-1, D2 is C-1, D3 is N-R, D4 is M-C,
    D is min(min(D1,D2), min(D3,D4)).

% ring-based watering requirement
required_water2d(R,C,N,M,dry)    :- border_min(R,C,N,M,0).
required_water2d(R,C,N,M,wet)    :- border_min(R,C,N,M,1).
required_water2d(R,C,N,M,either) :- border_min(R,C,N,M,D), D >= 2.

% iterate neighbor pairs (right and down)
check_right(N,M,List,Pred) :-
    ( M =< 1 -> true
    ; M1 is M-1,
      forall( (between(1,N,R),
               between(1,M1,C),
               species_at(List,M,R,C,S1),
               C2 is C+1, species_at(List,M,R,C2,S2)),
              call(Pred,S1,S2) )
    ).

check_down(N,M,List,Pred) :-
    ( N =< 1 -> true
    ; N1 is N-1,
      forall( (between(1,N1,R),
               between(1,M,C),
               species_at(List,M,R,C,S1),
               R2 is R+1, species_at(List,M,R2,C,S2)),
              call(Pred,S1,S2) )
    ).

% (1) plantassign/3 (2D)
plantassign(N,M,List) :-
    NM is N*M,
    length(List,NM),
    maplist(species,List).

% (2) uniquecheck/1
uniquecheck([]).
uniquecheck([H|T]) :- \+ member(H,T), uniquecheck(T).

% (3) colorcheck/3 (2D)
colorcheck(N,M,List) :-
    check_right(N,M,List,colors_ok),
    check_down(N,M,List,colors_ok).

% (4) sizecheck/3 (2D)
sizecheck(N,M,List) :-
    check_right(N,M,List,sizes_ok),
    check_down(N,M,List,sizes_ok).

% (5) wetcheck/3 (2D)
wetcheck(N,M,List) :-
    N >= 2, M >= 2,
    forall( (between(1,N,R), between(1,M,C)),
            ( required_water2d(R,C,N,M,Req),
              species_at(List,M,R,C,S),
              ( Req = either -> true ; water_of(S,Req) ) ) ).

% (6) writegarden/3 (2D pretty print)
writegarden(N,M,List) :-
    writeln('Garden plan (R,C: species (size, water, color))'),
    forall( between(1,N,R),
            ( forall( between(1,M,C),
                      ( species_at(List,M,R,C,S),
                        flower(S,Size,Wet,Color),
                        format('(~d,~d): ~w (~w, ~w, ~w)  ', [R,C,S,Size,Wet,Color]) )),
              nl )).

% (7) gardenplan/3 (2D generator with pruning)
gardenplan(N,M,List) :-
    N >= 2, M >= 2,
    %           R  C   N   M   PrevRow  Left  CurRowAcc  Used   Acc   Out
    build2d(1, 1,  N,  M,  [],   none,   [],     [],     [],   Rev),
    reverse(Rev,List),
    writegarden(N,M,List).

ok_water2d(R,C,N,M,S) :-
    required_water2d(R,C,N,M,Req),
    ( Req = either -> true ; water_of(S,Req) ).

ok_left(S,none) :- !.
ok_left(S,Left) :- colors_ok(S,Left), sizes_ok(S,Left).

ok_up(S,none)   :- !.
ok_up(S,Up)     :- colors_ok(S,Up),  sizes_ok(S,Up).

build2d(R,_,N,_,_,_,_,Used,Acc,Acc) :- R > N, !.
build2d(R,C,N,M,PrevRow,Left,CurRowAcc,Used,Acc,Out) :-
    ( C =< M ->
        ( (R =:= 1 -> Up = none ; nth1(C,PrevRow,Up)),
          flower(S,_,_,_),
          \+ member(S,Used),
          ok_water2d(R,C,N,M,S),
          ok_left(S,Left),
          ok_up(S,Up),
          Used1 = [S|Used],
          Acc1  = [S|Acc],
          CurRowAcc1 = [S|CurRowAcc],
          ( C < M ->
                C2 is C+1,
                build2d(R,C2,N,M,PrevRow,S,CurRowAcc1,Used1,Acc1,Out)
          ;   reverse(CurRowAcc1,NewPrevRow),
              R2 is R+1,
              build2d(R2,1,N,M,NewPrevRow,none,[],Used1,Acc1,Out)
          )
        )
    ).


valid_garden(N,M,List) :-
    length(List,L), L =:= N*M,
    uniquecheck(List),
    colorcheck(N,M,List),
    sizecheck(N,M,List),
    wetcheck(N,M,List).

