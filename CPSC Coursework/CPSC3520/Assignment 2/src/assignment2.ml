(* Assignment 2 - Functional Programming - OCaml [Michael Joseph Ellis]*)

let rec first_duplicate lst =
  let rec has_duplicate x rest = 
    match rest with 
    | [] -> false 
    | h::t -> if h = x then true else has_duplicate x t 
  in
  match lst with 
  | [] -> -10000
  | h::t -> 
    if has_duplicate h t then h 
    else first_duplicate t

let rec sumOfTwo (a, b, v) =
  match a with
  | [] -> false
  | h::t ->
      let rec check_b lst =
        match lst with
        | [] -> false
        | x::xs ->
            if h + x = v then true
            else check_b xs
      in
      if check_b b then true
      else sumOfTwo (t, b, v)

let rec list_intersection (a, b) =
  let rec helper lst seen =
    match lst with
    | [] -> []
    | h::t ->
        if List.mem h b && not (List.mem h seen)
        then h :: helper t (h::seen)
        else helper t seen
  in
  helper a []

let rec unique lst =
  let rec helper l seen =
    match l with
    | [] -> []
    | h::t ->
        if List.mem h seen
        then helper t seen
        else h :: helper t (h::seen)
  in
  helper lst []

let rec powerset lst =
  match lst with
  | [] -> [[]]
  | h::t ->
      let p = powerset t in
      let rec add_head ps =
        match ps with
        | [] -> []
        | x::xs -> (h::x) :: add_head xs
      in
      List.append p (add_head p)